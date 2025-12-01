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
    // After the animation, transition to the default state.
    if (!startupAnimation->isFinished())
        startupAnimation->update();
    else
        robot.getStateManager().transitionTo(new DefaultState(robot));
}

void StartupState::exit()
{
    // This is where any cleanup for the startup state will go.
    delete startupAnimation;
    TouchLED.setColor(green);
    Brain.Screen.clearScreen();
}
