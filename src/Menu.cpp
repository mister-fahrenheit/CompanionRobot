#include "Menu.h"
#include "RobotPet.h"
#include "hardware-config.h"

Menu::Menu(RobotPet& robot) : robot(robot), visible(false), selectedIndex(0) {
    // The constructor initializes the menu.
}

void Menu::addMenuItem(const std::string& name, RobotState* (*createState)(RobotPet&)) {
    // Adds a menu item to the list.
    menuItems.push_back({name, createState});
}

void Menu::show() {
    // Shows the menu.
    visible = true;
    draw();
    wait(200, msec);
    printf("Menu Opened\n");
}

void Menu::hide() {
    // Hides the menu.
    visible = false;
    printf("Menu Closed\n");
}

void Menu::update() {
    // If the menu is not visible, do nothing.
    if (!visible) {
        return;
    }
    // Handle button presses.
    if (Brain.buttonLeft.pressing() || Controller.ButtonEUp.pressing()) {
        selectedIndex--;
        if (selectedIndex < 0) {
            selectedIndex = menuItems.size() - 1;
        }
        printf("Menu moved to %d\n", selectedIndex);
        draw();
    } else if (Brain.buttonRight.pressing() || Controller.ButtonEDown.pressing()){
        selectedIndex++;
        if (selectedIndex >= menuItems.size()) {
            selectedIndex = 0;
        }
        printf("Menu moved to %d\n", selectedIndex);
        draw();
    }else if (Brain.buttonCheck.pressing()  || Controller.ButtonFUp.pressing()) {
        if (menuItems.size() > 0) {
            Brain.Screen.clearScreen();
            robot.getStateManager().transitionTo(menuItems[selectedIndex].createState(robot));
            hide();
        }
    }
    wait(100, msec); // Debounce
}

bool Menu::isVisible() const {
    return visible;
}

void Menu::draw() {
    Brain.Screen.setFillColor(vex::color(0x333333));
    Brain.Screen.drawRectangle(0, 0, 160, 108);

    if (selectedIndex >= 0 && selectedIndex < menuItems.size()) {
        Brain.Screen.setFillColor(vex::color(0x555555));
        Brain.Screen.drawRectangle(40, 30, 80, 48);
    }
    Brain.Screen.setPenColor(vex::color(0xFFFFFF));
    Brain.Screen.printAt(45, 55, menuItems[selectedIndex].name.c_str());
}
