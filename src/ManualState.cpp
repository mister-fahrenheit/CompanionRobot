#include "ManualState.h"
#include "hardware-config.h"

ManualState::ManualState(RobotPet& robot) : robot(robot) {
    // The constructor initializes the reference to the robot.
}

void ManualState::enter() {
    // This is where the manual control behavior will go.
    // For now, it just prints a message to the console.
    printf("Entered Manual State\n");
}

void ManualState::update() {
    // This is the main loop for the manual state.
    // If the screen is pressed, show the menu.
    if (Brain.buttonCheck.pressing() || Controller.ButtonFUp.pressing()) {
        robot.getMenu().show();
    }
}

void ManualState::exit() {
    // This is where any cleanup for the manual state will go.
    Brain.Screen.clearScreen();
}
