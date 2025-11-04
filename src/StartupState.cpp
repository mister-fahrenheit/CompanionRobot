#include "hardware-config.h"
#include "StartupState.h"
#include "DefaultState.h"

StartupState::StartupState(RobotPet& robot) : robot(robot) {
    // The constructor initializes the reference to the robot.
}

void StartupState::enter() {
    // This is where the startup behavior will go.
    // For now, it just prints a message to the brain screen.
    Brain.Screen.setCursor(3, 1);
    printf("Entered Startup State\n");
    Brain.Screen.print("Starting up...");
    Brain.Screen.setFont(mono12);
}

void StartupState::update() {
    // After a short delay, transition to the default state.
    wait(2, seconds);
    robot.getStateManager().transitionTo(new DefaultState(robot));
}

void StartupState::exit() {
    // This is where any cleanup for the startup state will go.
    Brain.Screen.clearScreen();
}
