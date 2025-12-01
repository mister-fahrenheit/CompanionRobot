#include "ManualState.h"
#include "hardware-config.h"

ManualState::ManualState(RobotPet& robot) : robot(robot)
{
}

void ManualState::enter()
{
    printf("Entered Manual State\n");
    Brain.Screen.setFillColor(white);
    Brain.Screen.drawRectangle(0, 0, 160, 108);
    Brain.Screen.render();

    ArmMotor.setStopping(hold);
    GripperMotor.setStopping(hold);
}

void ManualState::update()
{
    // This is the main loop for the manual state.
    LeftMotor.spin(forward, Controller.AxisA.position() / 2, percent);
    RightMotor.spin(forward, Controller.AxisD.position() / 2, percent);
   
    if (Controller.ButtonLUp.pressing())
        ArmMotor.spin(forward, 20, percent);
    else if (Controller.ButtonLDown.pressing())
        ArmMotor.spin(reverse, 20, percent);
    else 
        ArmMotor.stop();

    if (Controller.ButtonRUp.pressing())
        GripperMotor.spin(forward, 20, percent);
    else if (Controller.ButtonRDown.pressing())
        GripperMotor.spin(reverse, 20, percent);
    else
        GripperMotor.stop();

    // If the screen is pressed, show the menu.
    if (Brain.buttonCheck.pressing() || Controller.ButtonFUp.pressing())
        robot.getMenu().show();
}

void ManualState::exit()
{
    // This is where any cleanup for the manual state will go.
    ArmMotor.setStopping(coast);
    GripperMotor.setStopping(coast);
    Brain.Screen.clearScreen();
}
