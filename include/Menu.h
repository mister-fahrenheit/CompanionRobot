#ifndef MENU_H
#define MENU_H

#include "vex.h"
#include "RobotState.h"
#include "StateManager.h"
#include "Animation.h"
#include <string>

class RobotPet;

struct MenuItem
{
    std::string name;
    RobotState* (*createState)(RobotPet&);
};

class Menu
{
private:
    void draw();

    RobotPet& robot;
    bool visible;
    int selectedIndex;
    MenuItem menuItems[6];
    int menuItemCount;

public:
    Menu(RobotPet& robot);

    // Adds a menu item.
    void addMenuItem(const std::string& name, RobotState* (*createState)(RobotPet&));

    // Shows the menu.
    void show();

    // Hides the menu.
    void hide();

    // Updates the menu.
    void update();

    // Returns true if the menu is visible.
    bool isVisible() const;
}; 

#endif // MENU_H
