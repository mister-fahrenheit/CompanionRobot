#include "RobotPet.h"
#include "hardware-config.h"

RobotPet::RobotPet() : menu(*this) {
    // The RobotPet owns the StateManager and Menu, so they are initialized here.
}

void RobotPet::update() {
    // If the menu is visible, update it.
    if (menu.isVisible()) {
        menu.update();
    } else {
        // Otherwise, update the state manager.
        stateManager.update();
    }
}

StateManager& RobotPet::getStateManager() {
    return stateManager;
}

Menu& RobotPet::getMenu() {
    return menu;
}
