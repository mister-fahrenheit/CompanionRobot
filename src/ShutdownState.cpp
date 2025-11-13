#include "ShutdownState.h"
#include "hardware-config.h"

ShutdownState::ShutdownState(RobotPet& robot) : robot(robot) {
    // The constructor initializes the reference to the robot.
}

void ShutdownState::enter() {
    // This is where the shutdown behavior will go.
    // For now, it just prints a message to the console.
    printf("Entered Shutdown State\n");
    TouchLED.setColor(black);
    wait(5, seconds);
}

void ShutdownState::update() {}

void ShutdownState::exit() {}
