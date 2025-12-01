#include "RobotPet.h"
#include "hardware-config.h"

RobotPet::RobotPet() : menu(*this)
{
}

void RobotPet::update()
{
    if (menu.isVisible())
        menu.update();
    else
        stateManager.update();
}

StateManager& RobotPet::getStateManager()
{
    return stateManager;
}

Menu& RobotPet::getMenu()
{
    return menu;
}
