#include "hardware-config.h"
#include "StartupState.h"
#include "DefaultState.h"

StartupState::StartupState(RobotPet& robot) : robot(robot), startupAnimation(NULL)
{
}

void StartupState::enter()
{
    Brain.Screen.render();
    Brain.Screen.setFillColor(white);
    Brain.Screen.drawRectangle(0, 0, 160, 108);
    startupAnimation = new Animation("STARTUP", 14, 6);
    printf("Entered Startup State\n");
    startupAnimation->draw();
    TouchLED.setColor(red);
}

void StartupState::update()
{
    if (!hardwareChecked)
    {
        printf("Performing hardware checks...\n");

        // Motors
        bool ok = LeftMotor.installed();
        printf("LeftMotor: %s\n", ok ? "PASS" : "FAIL");
        if (!ok) hardwareOk = false;

        ok = RightMotor.installed();
        printf("RightMotor: %s\n", ok ? "PASS" : "FAIL");
        if (!ok) hardwareOk = false;

        ok = ArmMotor.installed();
        printf("ArmMotor: %s\n", ok ? "PASS" : "FAIL");
        if (!ok) hardwareOk = false;

        ok = GripperMotor.installed();
        printf("GripperMotor: %s\n", ok ? "PASS" : "FAIL");
        if (!ok) hardwareOk = false;

        // Sensors
        ok = Bumper.installed();
        printf("Bumper: %s\n", ok ? "PASS" : "FAIL");
        if (!ok) hardwareOk = false;

        ok = TouchLED.installed();
        printf("TouchLED: %s\n", ok ? "PASS" : "FAIL");
        if (!ok) hardwareOk = false;

        ok = Optical.installed();
        printf("Optical: %s\n", ok ? "PASS" : "FAIL");
        if (!ok) hardwareOk = false;

        ok = Distance.installed();
        printf("Distance: %s\n", ok ? "PASS" : "FAIL");
        if (!ok) hardwareOk = false;

        ok = BrainInertial.installed();
        printf("Inertial: %s\n", ok ? "PASS" : "FAIL");
        if (!ok) hardwareOk = false;

        // SD card
        ok = Brain.SDcard.isInserted();
        printf("SD Card: %s\n", ok ? "PASS" : "FAIL");
        if (!ok) hardwareOk = false;

        hardwareChecked = true;
        printf("Hardware check complete.\n");
    }

    // After the animation, transition to the default state.
    if (!startupAnimation->isFinished())
        startupAnimation->update();
    else
        robot.getStateManager().transitionTo(new DefaultState(robot));
}

void StartupState::exit()
{
    delete startupAnimation;

    if (hardwareOk)
        TouchLED.setColor(green);
    else
        TouchLED.setColor(red);

    Brain.Screen.clearScreen();
}
