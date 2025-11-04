#include "RobotPet.h"
#include "hardware-config.h"

RobotPet::RobotPet() : menu(*this), sdCardInitialized(false) {
    // The RobotPet owns the StateManager and Menu, so they are initialized here.
}

void RobotPet::initialize() {
    if (Brain.SDcard.isInserted()) {
        sdCardInitialized = true;
        printf("SD OK!\n");
    } else {
        sdCardInitialized = false;
        printf("SD Missing or File Not Found!\n");
    }
    wait(2, seconds);
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

bool RobotPet::isSdCardInitialized() const {
    return sdCardInitialized;
}
