#include "ManualState.h"
#include "hardware-config.h"

ManualState::ManualState(RobotPet& robot) : robot(robot) {
    // The constructor initializes the reference to the robot.
}

void ManualState::enter() {
    // This is where the manual control behavior will go.
    // For now, it just prints a message to the console.
    printf("Entered Manual State\n");
    Brain.Screen.setFillColor(white);
    Brain.Screen.drawRectangle(0, 0, 160, 108);
    Brain.Screen.render();

    ArmMotor.setStopping(hold);
    GripperMotor.setStopping(hold);
}

void ManualState::update() {
    // This is the main loop for the manual state.
    LeftMotor.spin(forward, Controller.AxisA.position() / 2, percent);
    RightMotor.spin(forward, Controller.AxisD.position() / 2, percent);
   
    if (Controller.ButtonLUp.pressing()) {
      // Move Up at constant speed
      ArmMotor.spin(forward, 20, percent);
    }
    else if (Controller.ButtonLDown.pressing()) {
      // Move Down at constant speed
      ArmMotor.spin(reverse, 20, percent);
    }
    else {
      // If no button is pressed, stop and hold position
      ArmMotor.stop();
    }

    if (Controller.ButtonRUp.pressing()) {
      // Open Claw
      GripperMotor.spin(forward, 20, percent);
    }
    else if (Controller.ButtonRDown.pressing()) {
      // Close Claw
      GripperMotor.spin(reverse, 20, percent);
    }
    else {
      // If no button is pressed, stop and hold
      GripperMotor.stop();
    }

    // If the screen is pressed, show the menu.
    if (Brain.buttonCheck.pressing() || Controller.ButtonFUp.pressing()) {
        robot.getMenu().show();
    }
}

void ManualState::exit() {
    // This is where any cleanup for the manual state will go.
    ArmMotor.setStopping(coast);
    GripperMotor.setStopping(coast);
    Brain.Screen.clearScreen();
}
