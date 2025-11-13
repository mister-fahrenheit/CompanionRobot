#include "DefaultState.h"
#include "hardware-config.h"
#include "RobotPet.h"

DefaultState::DefaultState(RobotPet& robot) : robot(robot), happyAnimation(NULL) {
    // The constructor initializes the reference to the robot.
    happyAnimation = new Animation("numbers", 8);
}

DefaultState::~DefaultState() {
    // delete happyAnimation;
}

void DefaultState::enter() {
    printf("Entered Default State\n");
    Brain.Screen.setFillColor(white);
    Brain.Screen.drawRectangle(0, 0, 160, 108);
    happyAnimation->draw();
}

void DefaultState::update() {
    // This is the main loop for the default state.
    // If the screen is pressed, show the menu.
    if (Brain.buttonCheck.pressing() || Controller.ButtonFUp.pressing()) {
        robot.getMenu().show();
    }

    // Update the animation.
    happyAnimation->update();
}

void DefaultState::exit() {
    // This is where any cleanup for the default state will go.
    Brain.Screen.clearScreen();
}
