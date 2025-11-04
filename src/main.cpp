/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Levon Yaseman Conan Ralph                                 */
/*    Description:  CELY Companion Bot                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "hardware-config.h"
#include "RobotPet.h"
#include "StartupState.h"
#include "DefaultState.h"
#include "ManualState.h"
#include "MusicState.h"
#include "FollowState.h"

// define your global instances of motors and other devices here

// Factory functions for creating states.
RobotState* createDefaultState(RobotPet& robot) { return new DefaultState(robot); }
RobotState* createManualState(RobotPet& robot) { return new ManualState(robot); }
RobotState* createMusicState(RobotPet& robot) { return new MusicState(robot); }
RobotState* createFollowState(RobotPet& robot) { return new FollowState(robot); }

int main() {
    // Toggle for Testing Mode
    const bool TESTING = false;
    if (TESTING) {
        // Area for testing code without dealing with menus 
    } else {
        // Create the robot pet.
        RobotPet robot;

        // Add menu items.
        robot.getMenu().addMenuItem("Default State", &createDefaultState);
        robot.getMenu().addMenuItem("Follow State", &createFollowState);
        robot.getMenu().addMenuItem("Music State", &createMusicState);
        robot.getMenu().addMenuItem("Manual State", &createManualState);
        

        // Initialize the robot.
        robot.initialize();

        // Create the startup state.
        StartupState* startupState = new StartupState(robot);

        // Transition to the startup state.
        robot.getStateManager().transitionTo(startupState);

        // Main loop.
        while (true) {
            robot.update();
            wait(20, msec);
        }
    }
}
