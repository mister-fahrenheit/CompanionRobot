#include "RetrieveState.h"
#include "hardware-config.h"
#include "RobotPet.h"

RetrieveState::RetrieveState(RobotPet &robot) : robot(robot)
{
    currentStep = INIT;
    stepStartTime = 0;
    motorsRunning = false;
    colorIndex = 0;
    avoidanceStep = AVOID_NONE;
    gripStep = GRIP_SEARCHING;
    effectiveDistanceCovered = 0;
    currentDegrees = 0;
}

float RetrieveState::mmToDegrees(float mm)
{
    return (mm / WHEEL_CIRCUMFERENCE) * 360.0;
}

void RetrieveState::startDriveDist(float distanceMM, int speed)
{
    LeftMotor.setPosition(0, degrees);
    RightMotor.setPosition(0, degrees);

    targetDegrees = mmToDegrees(abs(distanceMM));

    directionType dir = forward;
    if (distanceMM < 0)
        dir = reverse;

    LeftMotor.spin(dir, speed, percent);
    RightMotor.spin(dir, speed, percent);
    motorsRunning = true;
}

bool RetrieveState::isDriveDistComplete()
{
    if (!motorsRunning)
        return true;
    
    float avgPosition = (abs(LeftMotor.position(degrees)) + abs(RightMotor.position(degrees))) / 2;
    
    if (avgPosition >= targetDegrees)
    {
        LeftMotor.stop();
        RightMotor.stop();
        motorsRunning = false;
        return true;
    }
    return false;
}

void RetrieveState::startTurnDeg(float degreesToTurn)
{
    startAngle = BrainInertial.rotation(degrees);
    targetAngle = startAngle + degreesToTurn;

    int turnSpeed = 15;

    if (degreesToTurn > 0)
    {
        LeftMotor.spin(forward, turnSpeed, percent);
        RightMotor.spin(reverse, turnSpeed, percent);
    }
    else
    {
        LeftMotor.spin(reverse, turnSpeed, percent);
        RightMotor.spin(forward, turnSpeed, percent);
    }
    motorsRunning = true;
}

bool RetrieveState::isTurnComplete()
{
    if (!motorsRunning)
        return true;
    
    float currentRotation = BrainInertial.rotation(degrees);
    bool complete = false;
    
    if (targetAngle > startAngle)
        complete = (currentRotation >= targetAngle);
    else
        complete = (currentRotation <= targetAngle);
    
    if (complete)
    {
        LeftMotor.stop();
        RightMotor.stop();
        motorsRunning = false;
        return true;
    }
    return false;
}

void RetrieveState::startDriveWithAvoidance(int distanceMM)
{
    Brain.Screen.setFillColor(white);
    Brain.Screen.drawRectangle(0, 0, 160, 108);
    Brain.Screen.setPenColor(black);
    Brain.Screen.setFont(mono30);
    Brain.Screen.printAt(10, 65, "Searching");
    Brain.Screen.render();

    LeftMotor.setPosition(0, degrees);
    RightMotor.setPosition(0, degrees);

    targetDegrees = mmToDegrees(distanceMM);
    effectiveDistanceCovered = 0;

    LeftMotor.spin(forward, 50, percent);
    RightMotor.spin(forward, 50, percent);
    motorsRunning = true;
    avoidanceStep = AVOID_NONE;
}

bool RetrieveState::updateDriveWithAvoidance()
{
    // Handle avoidance sequence if active
    if (avoidanceStep != AVOID_NONE)
    {
        if (avoidanceStep == AVOID_BACKUP)
        {
            if (isDriveDistComplete())
            {
                avoidanceStep = AVOID_TURN1;
                startTurnDeg(90);
            }
        }
        else if (avoidanceStep == AVOID_TURN1)
        {
            if (isTurnComplete())
            {
                avoidanceStep = AVOID_DRIVE1;
                startDriveDist(300, 40);
            }
        }
        else if (avoidanceStep == AVOID_DRIVE1)
        {
            if (isDriveDistComplete())
            {
                avoidanceStep = AVOID_TURN2;
                startTurnDeg(-90);
            }
        }
        else if (avoidanceStep == AVOID_TURN2)
        {
            if (isTurnComplete())
            {
                avoidanceStep = AVOID_DRIVE2;
                startDriveDist(AVOID_FORWARD_MM, 40);
            }
        }
        else if (avoidanceStep == AVOID_DRIVE2)
        {
            if (isDriveDistComplete())
            {
                avoidanceStep = AVOID_TURN3;
                startTurnDeg(-90);
            }
        }
        else if (avoidanceStep == AVOID_TURN3)
        {
            if (isTurnComplete())
            {
                avoidanceStep = AVOID_DRIVE3;
                startDriveDist(300, 40);
            }
        }
        else if (avoidanceStep == AVOID_DRIVE3)
        {
            if (isDriveDistComplete())
            {
                avoidanceStep = AVOID_TURN4;
                startTurnDeg(90);
            }
        }
        else if (avoidanceStep == AVOID_TURN4)
        {
            if (isTurnComplete())
            {
                // Avoidance complete, resume driving
                LeftMotor.setPosition(0, degrees);
                RightMotor.setPosition(0, degrees);

                targetDegrees -= (currentDegrees - mmToDegrees(AVOID_BACKUP_MM) + mmToDegrees(AVOID_FORWARD_MM));
                effectiveDistanceCovered = 0;

                LeftMotor.spin(forward, 50, percent);
                RightMotor.spin(forward, 50, percent);
                motorsRunning = true;
                avoidanceStep = AVOID_NONE;
            }
        }
        return false;
    }

    // Normal driving with obstacle detection
    currentDegrees = (LeftMotor.position(degrees) + RightMotor.position(degrees)) / 2;
    effectiveDistanceCovered = currentDegrees;

    if (Optical.isNearObject() && Optical.brightness() > 10)
    {
        // Start avoidance
        LeftMotor.stop();
        RightMotor.stop();
        motorsRunning = false;
        avoidanceStep = AVOID_BACKUP;
        stepStartTime = Brain.timer(msec);
        return false;
    }

    if (effectiveDistanceCovered >= targetDegrees)
    {
        LeftMotor.stop();
        RightMotor.stop();
        motorsRunning = false;
        return true;
    }

    return false;
}

void RetrieveState::startFindAndGrip(color target)
{
    LeftMotor.stop();
    RightMotor.stop();

    LeftMotor.spin(forward, 5, percent);
    RightMotor.spin(reverse, 5, percent);
    
    gripStep = GRIP_SEARCHING;
    motorsRunning = true;
}

bool RetrieveState::updateFindAndGrip()
{
    if (gripStep == GRIP_SEARCHING)
    {
        if (Optical.color() == desiredColor)
        {
            Brain.Screen.setFillColor(white);
            Brain.Screen.drawRectangle(0, 0, 160, 108);
            Brain.Screen.setPenColor(black);
            Brain.Screen.setFont(mono30);
            Brain.Screen.printAt(40, 65, "Found");
            Brain.Screen.render();

            LeftMotor.stop();
            RightMotor.stop();
            motorsRunning = false;
            
            gripStep = GRIP_FOUND_WAIT;
            stepStartTime = Brain.timer(msec);
        }
    }
    else if (gripStep == GRIP_FOUND_WAIT)
    {
        if (Brain.timer(msec) - stepStartTime >= 500)
        {
            GripperMotor.spin(reverse, 60, percent);
            gripStep = GRIP_CLOSING;
            stepStartTime = Brain.timer(msec);
        }
    }
    else if (gripStep == GRIP_CLOSING)
    {
        if (Brain.timer(msec) - stepStartTime >= 1000)
        {
            GripperMotor.stop();
            ArmMotor.spin(forward, 60, percent);
            gripStep = GRIP_LIFTING;
            stepStartTime = Brain.timer(msec);
        }
    }
    else if (gripStep == GRIP_LIFTING)
    {
        if (Brain.timer(msec) - stepStartTime >= 1000)
        {
            ArmMotor.stop();
            gripStep = GRIP_COMPLETE;
            return true;
        }
    }
    else if (gripStep == GRIP_COMPLETE)
    {
        return true;
    }
    
    return false;
}

bool RetrieveState::updateColorSelection()
{
    if (Bumper.pressing())
    {
        TouchLED.on(desiredColor);
        return true;
    }

    if (TouchLED.pressing())
    {
        // Debounce - wait for release
        while (TouchLED.pressing())
        {
            wait(10, msec);
        }

        colorIndex++;
        if (colorIndex > 2)
            colorIndex = 0;
            
        if (colorIndex == 0)
        {
            TouchLED.on(red);
            desiredColor = red;
        }
        else if (colorIndex == 1)
        {
            TouchLED.on(green);
            desiredColor = green;
        }
        else if (colorIndex == 2)
        {
            TouchLED.on(blue);
            desiredColor = blue;
        }
    }
    
    return false;
}

void RetrieveState::enter()
{
    printf("Entered Retrieve State\n");
    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(white);
    Brain.Screen.drawRectangle(0, 0, 160, 108);
    Brain.Screen.render();

    ArmMotor.setStopping(hold);
    GripperMotor.setStopping(hold);
    Optical.setLight(ledState::on);

    GripperMotor.spin(forward, 60, percent);
    
    currentStep = INIT;
    stepStartTime = Brain.timer(msec);
}

void RetrieveState::update()
{
    if (currentStep == INIT)
    {
        // Start calibration
        BrainInertial.calibrate();
        currentStep = CALIBRATING;
    }
    else if (currentStep == CALIBRATING)
    {
        if (!BrainInertial.isCalibrating())
        {
            GripperMotor.stop();
            
            // Setup color selection
            colorIndex = 0;
            TouchLED.on(red);
            desiredColor = red;

            Brain.Screen.setFillColor(white);
            Brain.Screen.drawRectangle(0, 0, 160, 108);
            Brain.Screen.setPenColor(black);
            Brain.Screen.setFont(mono15);
            Brain.Screen.printAt(15, 40, "Select a Color");
            Brain.Screen.printAt(10, 75, "Then press Bumper");
            Brain.Screen.render();
            
            currentStep = SELECTING_COLOR;
        }
    }
    else if (currentStep == SELECTING_COLOR)
    {
        if (updateColorSelection())
        {
            stepStartTime = Brain.timer(msec);
            currentStep = DRIVING_TO_TARGET;
            startDriveWithAvoidance(TARGET_DISTANCE_MM);
        }
    }
    else if (currentStep == DRIVING_TO_TARGET)
    {
        if (updateDriveWithAvoidance())
        {
            currentStep = FINDING_OBJECT;
            startFindAndGrip(desiredColor);
        }
    }
    else if (currentStep == FINDING_OBJECT)
    {
        if (updateFindAndGrip())
        {
            currentStep = TURNING_HOME;
            
            float currentHeading = BrainInertial.rotation(degrees);
            degreesToFaceHome = 180.0 - currentHeading;

            Brain.Screen.setFillColor(white);
            Brain.Screen.drawRectangle(0, 0, 160, 108);
            Brain.Screen.setPenColor(black);
            Brain.Screen.setFont(mono30);
            Brain.Screen.printAt(20, 65, "Returning");
            Brain.Screen.render();
            
            startTurnDeg(degreesToFaceHome);
        }
    }
    else if (currentStep == TURNING_HOME)
    {
            if (isTurnComplete())
            {
                stepStartTime = Brain.timer(msec);
                currentStep = DRIVING_HOME;
            }
    }
    else if (currentStep == DRIVING_HOME)
    {
        if (Brain.timer(msec) - stepStartTime >= 500)
        {
            if (!motorsRunning)
                startDriveDist(TARGET_DISTANCE_MM, 50);
            
            if (isDriveDistComplete())
            {
                currentStep = COMPLETE;
                
                ArmMotor.setStopping(brake);
                GripperMotor.setStopping(brake);
                Brain.Screen.setFillColor(white);
                Brain.Screen.drawRectangle(0, 0, 160, 108);
                Brain.Screen.printAt(30, 75, "Press Bumper");
                Brain.Screen.render();
            }
        }
    }
    else if (currentStep == COMPLETE)
    {
        if (Bumper.pressing())
        {
            // Reset the state to start over
            currentStep = INIT;
            stepStartTime = 0;
            motorsRunning = false;
            colorIndex = 0;
            avoidanceStep = AVOID_NONE;
            gripStep = GRIP_SEARCHING;
            effectiveDistanceCovered = 0;
            currentDegrees = 0;
            
            Brain.Screen.clearScreen();
            Brain.Screen.setFillColor(white);
            Brain.Screen.drawRectangle(0, 0, 160, 108);
            Brain.Screen.render();
            
            GripperMotor.spin(forward, 60, percent);
            stepStartTime = Brain.timer(msec);
        }
    }

    // If the screen is pressed, show the menu. (Keep at bottom)
    if (Brain.buttonCheck.pressing() || Controller.ButtonFUp.pressing())
        robot.getMenu().show();
}

void RetrieveState::exit()
{
    ArmMotor.setStopping(coast);
    GripperMotor.setStopping(coast);
    Optical.setLight(ledState::off);
    Brain.Screen.clearScreen();
    
    LeftMotor.stop();
    RightMotor.stop();
}
