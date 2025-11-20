#include "RetrieveState.h"
#include "hardware-config.h"
#include "RobotPet.h"

RetrieveState::RetrieveState(RobotPet &robot) : robot(robot)
{
    // The constructor initializes the reference to the robot.
}

inertial BrainInertial = inertial();

// conan

const float WHEEL_DIAMETER = 63.5; // mm
const float WHEEL_CIRCUMFERENCE = WHEEL_DIAMETER * 3.14159;

const int TARGET_DISTANCE_MM = 2000; // 2 meters
const int APPROACH_DIST_MM = 80;

const int AVOID_BACKUP_MM = 80;
const int AVOID_FORWARD_MM = 750;

color desiredColor = red;
// conan

// conan
float mmToDegrees(float mm)
{
    return (mm / WHEEL_CIRCUMFERENCE) * 360.0;
}

void driveDist(float distanceMM, int speed)
{
    LeftMotor.setPosition(0, degrees);
    RightMotor.setPosition(0, degrees);

    float targetDeg = mmToDegrees(distanceMM);

    directionType dir = forward;
    if (distanceMM < 0)
    {
        dir = reverse;
        targetDeg = -targetDeg;
    }

    LeftMotor.spin(dir, speed, percent);
    RightMotor.spin(dir, speed, percent);

    while ((abs(LeftMotor.position(degrees)) + abs(RightMotor.position(degrees))) / 2 < targetDeg)
    {
        wait(10, msec);
    }

    LeftMotor.stop();
    RightMotor.stop();
}

void turnDeg(float degreesToTurn)
{
    float startAngle = BrainInertial.rotation(degrees);
    float targetAngle = startAngle + degreesToTurn;

    int turnSpeed = 15;

    if (degreesToTurn > 0)
    {
        LeftMotor.spin(forward, turnSpeed, percent);
        RightMotor.spin(reverse, turnSpeed, percent);

        while (BrainInertial.rotation(degrees) < targetAngle)
        {
            wait(10, msec);
        }
    }
    else
    {
        LeftMotor.spin(reverse, turnSpeed, percent);
        RightMotor.spin(forward, turnSpeed, percent);

        while (BrainInertial.rotation(degrees) > targetAngle)
        {
            wait(10, msec);
        }
    }

    LeftMotor.stop();
    RightMotor.stop();
}

void performAvoidance()
{
    LeftMotor.stop();
    RightMotor.stop();
    wait(500, msec);

    driveDist(-AVOID_BACKUP_MM, 40);

    turnDeg(90);
    driveDist(300, 40);
    turnDeg(-90);

    driveDist(AVOID_FORWARD_MM, 40);

    turnDeg(-90);
    driveDist(300, 40);
    turnDeg(90);
}

void driveWithAvoidance(int distanceMM)
{
    LeftMotor.setPosition(0, degrees);
    RightMotor.setPosition(0, degrees);

    float targetDegrees = mmToDegrees(distanceMM);
    float currentDegrees = 0;
    float effectiveDistanceCovered = 0;

    LeftMotor.spin(forward, 50, percent);
    RightMotor.spin(forward, 50, percent);

    while (effectiveDistanceCovered < targetDegrees)
    {
        currentDegrees = (LeftMotor.position(degrees) + RightMotor.position(degrees)) / 2;
        effectiveDistanceCovered = currentDegrees;

        if (Optical.isNearObject() && Optical.brightness() > 10)
        {
            performAvoidance();

            LeftMotor.setPosition(0, degrees);
            RightMotor.setPosition(0, degrees);

            // MATH UPDATE:
            // Remaining = Target - (Driven - Backup + ForwardPass)
            targetDegrees -= (currentDegrees - mmToDegrees(AVOID_BACKUP_MM) + mmToDegrees(AVOID_FORWARD_MM));

            effectiveDistanceCovered = 0;

            LeftMotor.spin(forward, 50, percent);
            RightMotor.spin(forward, 50, percent);
        }
        wait(20, msec);
    }

    LeftMotor.stop();
    RightMotor.stop();
}

void findAndGrip(color target)
{
    LeftMotor.stop();
    RightMotor.stop();

    LeftMotor.spin(forward, 5, percent);
    RightMotor.spin(reverse, 5, percent);

    while (true)
    {
        if (Optical.isNearObject() && Optical.color() == target)
        {
            break;
        }
        wait(20, msec);
    }

    LeftMotor.stop();
    RightMotor.stop();
    wait(500, msec);

    driveDist(APPROACH_DIST_MM, 20);
    GripperMotor.spin(reverse, 60, percent);
    wait(1000, msec);
    GripperMotor.stop();
    ArmMotor.spin(forward, 60, percent);
    wait(1000, msec);
    ArmMotor.stop();

    driveDist(-APPROACH_DIST_MM, 30);
}

void selectColorSequence()
{
    int colorIndex = 0;
    TouchLED.on(red);

    while (!Bumper.pressing())
    {
        if (TouchLED.pressing())
        {
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
        wait(50, msec);
    }
    wait(500, msec);
    TouchLED.on(desiredColor);
}
// conan

void RetrieveState::enter()
{
    // This is where the follow behavior will go.
    // For now, it just prints a message to the console.
    printf("Entered Follow State\n");
    Brain.Screen.setFillColor(white);
    Brain.Screen.drawRectangle(0, 0, 160, 108);
    Brain.Screen.render();

    // conan
    ArmMotor.setStopping(hold);
    GripperMotor.setStopping(hold);
    Optical.setLight(ledState::on);

    BrainInertial.calibrate();
    while (BrainInertial.isCalibrating())
    {
        wait(100, msec);
    }

    selectColorSequence();

    driveWithAvoidance(TARGET_DISTANCE_MM);

    findAndGrip(desiredColor);

    float currentHeading = BrainInertial.rotation(degrees);
    float degreesToFaceHome = 180.0 - currentHeading;

    turnDeg(degreesToFaceHome);
    wait(500, msec);

    driveDist(TARGET_DISTANCE_MM, 50);
    // conan
}

void RetrieveState::update()
{
    // This is the main loop for the follow state.

    // If the screen is pressed, show the menu. (Keep at bottom)
    if (Brain.buttonCheck.pressing() || Controller.ButtonFUp.pressing())
    {
        robot.getMenu().show();
        return;
    }
}

void RetrieveState::exit()
{
    // This is where any cleanup for the follow state will go.
    Brain.Screen.clearScreen();
}