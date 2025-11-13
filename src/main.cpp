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
#include "MusicState.h"
#include "FollowState.h"
#include "RetrieveState.h"
#include "ShutdownState.h"

// Factory functions for creating states.
RobotState* createDefaultState(RobotPet& robot) { return new DefaultState(robot); }
RobotState* createFollowState(RobotPet& robot) { return new FollowState(robot); }
RobotState* createRetrieveState(RobotPet& robot) { return new RetrieveState(robot); }
RobotState* createMusicState(RobotPet& robot) { return new MusicState(robot); }
RobotState* createManualState(RobotPet& robot) { return new ManualState(robot); }

int main() {
    // Toggle for Testing Mode
    const bool TESTING = false;
    if (TESTING)
    {
        // Area for testing code without dealing with menus
    }
    else
    {
        // Create the robot pet.
        RobotPet robot;

        // Add menu items.
        robot.getMenu().addMenuItem("Default State", &createDefaultState);
        robot.getMenu().addMenuItem("Follow State", &createFollowState);
        robot.getMenu().addMenuItem("Retrieve State", &createRetrieveState);
        robot.getMenu().addMenuItem("Music State", &createMusicState);
        robot.getMenu().addMenuItem("Manual State", &createManualState);

        // Create the startup state.
        StartupState* startupState = new StartupState(robot);

        // Transition to the startup state.
        robot.getStateManager().transitionTo(startupState);

        // Main loop.
        int ExitCounter = 0;
        while (ExitCounter < 200) {
            robot.update();
            wait(20, msec);

            if (TouchLED.pressing( ))
                ExitCounter++;
            else
                ExitCounter = 0;
        }

        ShutdownState* shutdownState = new ShutdownState(robot);
        robot.getStateManager().transitionTo(shutdownState);
    }

    Brain.programStop();
}
