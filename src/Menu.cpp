#include "Menu.h"
#include "RobotPet.h"
#include "hardware-config.h"

Menu::Menu(RobotPet& robot) : robot(robot), visible(false), selectedIndex(0), menuItemCount(0)
{
}

void Menu::addMenuItem(const std::string& name, RobotState* (*createState)(RobotPet&))
{
    menuItems[menuItemCount].name = name;
    menuItems[menuItemCount].createState = createState;
    menuItemCount++;
}

void Menu::show()
{
    visible = true;
    draw();
    wait(200, msec);
    printf("Menu Opened\n");
}

void Menu::hide()
{
    visible = false;
    printf("Menu Closed\n");
}

void Menu::update()
{
    if (!visible)
        return;

    // Handle button presses.
    if (Brain.buttonLeft.pressing() || Controller.ButtonEUp.pressing())
    {
        selectedIndex--;
        if (selectedIndex < 0)
            selectedIndex = menuItemCount - 1;
        
        printf("Menu moved to %d\n", selectedIndex);
        draw();
    }
    else if (Brain.buttonRight.pressing() || Controller.ButtonEDown.pressing())
    {
        selectedIndex++;
        if (selectedIndex >= menuItemCount)
            selectedIndex = 0;
        
        printf("Menu moved to %d\n", selectedIndex);
        draw();
    }
    else if (Brain.buttonCheck.pressing()  || Controller.ButtonFUp.pressing())
    {
        if (menuItemCount > 0)
        {
            Brain.Screen.clearScreen();
            robot.getStateManager().transitionTo(menuItems[selectedIndex].createState(robot));
            hide();
        }
    }
    wait(100, msec); // Debounce
}

bool Menu::isVisible()
{
    return visible;
}

void Menu::draw()
{
    Brain.Screen.setFillColor(white);
    Brain.Screen.drawRectangle(0, 0, 160, 108);
    Brain.Screen.setPenColor(black);
    Brain.Screen.drawImageFromFile((std::to_string(selectedIndex) + "_1.bmp").c_str(), 39, 13);
    Brain.Screen.drawImageFromFile((std::to_string(selectedIndex) + "_2.bmp").c_str(), 79, 13);
    Brain.Screen.drawImageFromFile((std::to_string(selectedIndex) + "_3.bmp").c_str(), 39, 53);
    Brain.Screen.drawImageFromFile((std::to_string(selectedIndex) + "_4.bmp").c_str(), 79, 53);
    Brain.Screen.drawImageFromFile("LEFTARROW_1", 4, 23);
    Brain.Screen.drawImageFromFile("LEFTARROW_2", 4, 53);
    Brain.Screen.drawImageFromFile("RIGHTARROW_1", 134, 23);
    Brain.Screen.drawImageFromFile("RIGHTARROW_2", 134, 53);
    Brain.Screen.setFont(mono15);
    Brain.Screen.printAt((160-Brain.Screen.getStringWidth(menuItems[selectedIndex].name.c_str()))/2, 95, menuItems[selectedIndex].name.c_str());
    Brain.Screen.render();
}
