#include "ShutdownState.h"
#include "hardware-config.h"

ShutdownState::ShutdownState(RobotPet& robot) : robot(robot)
{
}

void ShutdownState::enter()
{
    printf("Entered Shutdown State\n");
    TouchLED.setColor(black);
    wait(5, seconds);
}

void ShutdownState::update()
{
}

void ShutdownState::exit()
{
}
