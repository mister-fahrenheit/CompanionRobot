#include "FollowState.h"
#include "hardware-config.h"
#include "RobotPet.h"

FollowState::FollowState(RobotPet& robot) : robot(robot) {
    // The constructor initializes the reference to the robot.
}

void FollowState::enter() {
    // This is where the follow behavior will go.
    // For now, it just prints a message to the console.
    printf("Entered Follow State\n");
    Brain.Screen.setFillColor(white);
    Brain.Screen.drawRectangle(0, 0, 160, 108);
    Brain.Screen.render();
}

void FollowState::update() {
    // This is the main loop for the follow state.

    
    // If the screen is pressed, show the menu. (Keep at bottom)
    if (Brain.buttonCheck.pressing() || Controller.ButtonFUp.pressing()) {
        robot.getMenu().show();
        return;
    }
}

void FollowState::exit() {
    // This is where any cleanup for the follow state will go.
    Brain.Screen.clearScreen();
}