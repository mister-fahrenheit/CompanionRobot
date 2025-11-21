#include "FollowState.h"
#include "hardware-config.h"
#include "RobotPet.h"

FollowState::FollowState(RobotPet& robot) : robot(robot) {
    // The constructor initializes the reference to the robot.
}

void FollowState::enter() {
    // This is where the follow behavior will go.
    printf("Entered Follow State\n");
    Brain.Screen.setFillColor(white);
    Brain.Screen.drawRectangle(0, 0, 160, 108);
    Brain.Screen.setPenColor(black);
    Brain.Screen.setFont(mono20);
    Brain.Screen.printAt(10, 30, "FOLLOW MODE");
    Brain.Screen.render();
    Optical.objectDetectThreshold(20);
    Optical.setLight(ledState::on);
    while (!(Optical.isNearObject())) {}
    lastOptical = true;
    lastDistance = false;
    leftMotorSpeed = 0;
    rightMotorSpeed = 0;
}

void FollowState::update() {
    // This is the main loop for the follow state.
    if (Optical.isNearObject()) {
        leftMotorSpeed -= 20;
        rightMotorSpeed -= 20;
        if (leftMotorSpeed < 0)
            leftMotorSpeed = 0;
        if (rightMotorSpeed < 0)
            rightMotorSpeed = 0;
        lastOptical = true;
    } else {
        if (lastOptical)
        {
            if (leftMotorSpeed == rightMotorSpeed) {
                leftMotorSpeed += 5;
                rightMotorSpeed += 5;
            } else {
                leftMotorSpeed = 40;
                rightMotorSpeed = 40;
            }
            if (leftMotorSpeed > 100)
                leftMotorSpeed = 100;
            if (rightMotorSpeed > 100)
                rightMotorSpeed = 100;
            Brain.Screen.clearLine(3);
            Brain.Screen.printAt(10, 60, "Following");
        } else if (Distance.objectDistance(mm) < 300 || lastDistance) {
            leftMotorSpeed = 45;
            rightMotorSpeed = 35;
            if (leftMotorSpeed > 100)
                leftMotorSpeed = 100;
            if (rightMotorSpeed < 0)
                rightMotorSpeed = 0;
            Brain.Screen.clearLine(3);
            Brain.Screen.printAt(10, 60, "Turning Right");
        } else {
            leftMotorSpeed = 35;
            rightMotorSpeed = 45;
            if (leftMotorSpeed < 0)
                leftMotorSpeed = 0;
            if (rightMotorSpeed > 100)
                rightMotorSpeed = 100;
            Brain.Screen.clearLine(3);
            Brain.Screen.printAt(10, 60, "Turning Left");
        }
        lastOptical = false;
    }
    Brain.Screen.render();
    lastDistance = (Distance.objectDistance(mm) < 300);
    LeftMotor.spin(forward, leftMotorSpeed, percent);
    RightMotor.spin(forward, rightMotorSpeed, percent);
    wait(1000, msec);

    // If the screen is pressed, show the menu. (Keep at bottom)
    if (Brain.buttonCheck.pressing() || Controller.ButtonFUp.pressing()) {
        robot.getMenu().show();
    }
}

void FollowState::exit() {
    // This is where any cleanup for the follow state will go.
    Brain.Screen.clearScreen();
    Optical.setLight(ledState::off);
}