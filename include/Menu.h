#ifndef MENU_H
#define MENU_H

#include "vex.h"
#include "RobotState.h"
#include "StateManager.h"
#include <vector>
#include <string>

class RobotPet; // Forward declaration

// A pair of a state name and a function to create the state.
struct MenuItem {
    std::string name;
    RobotState* (*createState)(RobotPet&);
};

// Manages the on-screen menu.
class Menu {
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

private:
    // Draws the menu on the screen.
    void draw();

    RobotPet& robot;
    bool visible;
    int selectedIndex;
    std::vector<MenuItem> menuItems;
    float slidePosition; // 0.0 = hidden, 1.0 = shown
}; 

#endif // MENU_H
