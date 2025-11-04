#ifndef ROBOT_PET_H
#define ROBOT_PET_H

#include "StateManager.h"
#include "Menu.h"

// Represents the robot pet.
class RobotPet {
public:
    RobotPet();

    // Initializes the robot.
    void initialize();

    // Updates the robot's state.
    void update();

    // Gets the state manager.
    StateManager& getStateManager();

    // Gets the menu.
    Menu& getMenu();

    // Returns true if the SD card is initialized.
    bool isSdCardInitialized() const;

private:
    StateManager stateManager;
    Menu menu;
    bool sdCardInitialized;
};

#endif // ROBOT_PET_H
