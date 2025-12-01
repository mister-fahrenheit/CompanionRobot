#include "FollowState.h"
#include "hardware-config.h"
#include "RobotPet.h"

FollowState::FollowState(RobotPet& robot) : robot(robot)
{
}

void FollowState::enter()
{
    printf("Entered Follow State\n");
    Brain.Screen.setFillColor(white);
    Brain.Screen.drawRectangle(0, 0, 160, 108);
    Brain.Screen.setPenColor(black);
    Brain.Screen.setFont(mono20);
    Brain.Screen.printAt(10, 30, "FOLLOW MODE");
    Brain.Screen.render();
    Optical.objectDetectThreshold(40);
    Optical.setLight(ledState::on);
    while (!(Optical.isNearObject())) {}
    lastOptical = true;
    lastDistance = true;
    leftMotorSpeed = 0;
    rightMotorSpeed = 0;
}

void FollowState::update()
{
    int extend = 0;
    if (Optical.isNearObject())
    {
        leftMotorSpeed = fmax(0, leftMotorSpeed - 20);
        rightMotorSpeed = fmax(0, rightMotorSpeed - 20);
        lastOptical = true;
    }
    else
    {
        if (Distance.objectDistance(mm) < 500 && lastDistance)
        {
            leftMotorSpeed = fmin(100, leftMotorSpeed + 5);
            rightMotorSpeed = fmin(100, rightMotorSpeed + 5);
            extend = 1500;
            Brain.Screen.clearLine(3);
            Brain.Screen.printAt(10, 60, "Following");
        }
        else if (Distance.objectDistance(mm) < 500 || lastDistance)
        {
            leftMotorSpeed = 45;
            rightMotorSpeed = 35;
            Brain.Screen.clearLine(3);
            Brain.Screen.printAt(10, 60, "Turning Right");
            extend = 2000;
        }
        else
        {
            leftMotorSpeed = 35;
            rightMotorSpeed = 45;
            Brain.Screen.clearLine(3);
            Brain.Screen.printAt(10, 60, "Turning Left");
        }
        lastOptical = false;
    }
    
    Brain.Screen.render();
    lastDistance = (Distance.objectDistance(mm) < 300);
    LeftMotor.spin(forward, leftMotorSpeed, percent);
    RightMotor.spin(forward, rightMotorSpeed, percent);
    
    wait(extend, msec);
    wait(200, msec);

    if (Brain.buttonCheck.pressing() || Controller.ButtonFUp.pressing())
    {
        robot.getMenu().show();
        LeftMotor.stop();
        RightMotor.stop();
    }
}

void FollowState::exit()
{
    // This is where any cleanup for the follow state will go.
    Brain.Screen.clearScreen();
    Optical.setLight(ledState::off);
}
