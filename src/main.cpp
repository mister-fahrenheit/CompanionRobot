/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Conan Yaseman Ralph Levon                                 */
/*    Description:  CYEL Companion Bot                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "hardware-config.h"
#include "RobotPet.h"
#include "StartupState.h"
#include "DefaultState.h"
#include "ManualState.h"
#include "PlayMusicState.h"
#include "FollowState.h"
#include "ListenMusicState.h"
#include "RetrieveState.h"
#include "ShutdownState.h"

// Factory functions for creating states.
RobotState *createDefaultState(RobotPet &robot)
{
    return new DefaultState(robot);
}
RobotState *createFollowState(RobotPet &robot)
{
    return new FollowState(robot);
}
RobotState *createRetrieveState(RobotPet &robot)
{      
    return new RetrieveState(robot);
}
RobotState *createPlayMusicState(RobotPet &robot)
{
    return new PlayMusicState(robot);
}
RobotState *createListenMusicState(RobotPet &robot)
{
    return new ListenMusicState(robot);
}
RobotState *createManualState(RobotPet &robot)
{
    return new ManualState(robot);
}

int main()
{
    // Create the robot pet.
    RobotPet robot;

    // Add menu items.
    robot.getMenu().addMenuItem("Default State", &createDefaultState);
    robot.getMenu().addMenuItem("Follow State", &createFollowState);
    robot.getMenu().addMenuItem("Retrieve State", &createRetrieveState);
    robot.getMenu().addMenuItem("Play Music State", &createPlayMusicState);
    robot.getMenu().addMenuItem("Listen Music State", &createListenMusicState);
    robot.getMenu().addMenuItem("Manual State", &createManualState);

    // Create the startup state.
    StartupState *startupState = new StartupState(robot);

    // Transition to the startup state.
    robot.getStateManager().transitionTo(startupState);

    // Main loop.
    timer exitTimer;
    exitTimer.reset();
    while (exitTimer.value() < 5000)
    {
        robot.update();
        wait(20, msec);

        if (!(TouchLED.pressing()))
            exitTimer.reset();
    }

    ShutdownState *shutdownState = new ShutdownState(robot);
    robot.getStateManager().transitionTo(shutdownState);
    delete shutdownState;

    Brain.programStop();
}
