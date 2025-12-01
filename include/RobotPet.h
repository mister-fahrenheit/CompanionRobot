#ifndef ROBOT_PET_H
#define ROBOT_PET_H

#include "StateManager.h"
#include "Menu.h"

// Represents the robot pet.
class RobotPet
{
private:
    StateManager stateManager;
    Menu menu;

public:
    RobotPet();

    // Updates the robot's state.
    void update();

    // Gets the state manager.
    StateManager& getStateManager();

    // Gets the menu.
    Menu& getMenu();
};

#endif // ROBOT_PET_H
