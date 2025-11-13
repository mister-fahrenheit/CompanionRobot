#include "MusicState.h"
#include "hardware-config.h"

MusicState::MusicState(RobotPet& robot) : robot(robot) {
    // The constructor initializes the reference to the robot.
}

void MusicState::enter() {
    // This is where the Music control behavior will go.
    // For now, it just prints a message to console.
    printf("Entered Music State\n");
    Brain.Screen.setFillColor(white);
    Brain.Screen.drawRectangle(0, 0, 160, 108);
    Brain.Screen.render();
}

void MusicState::update() {
    // This is the main loop for the Music state.

    
    // If the screen is pressed, show the menu. (Keep at bottom)
    if (Brain.buttonCheck.pressing() || Controller.ButtonFUp.pressing()) {
        robot.getMenu().show();
    }
}

void MusicState::exit() {
    // This is where any cleanup for the Music state will go.
    Brain.Screen.clearScreen();
}
