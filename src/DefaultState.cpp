#include "DefaultState.h"
#include "hardware-config.h"
#include "RobotPet.h"

DefaultState::DefaultState(RobotPet& robot) : robot(robot), currentAnimation(NULL) {
    // The constructor initializes the reference to the robot.
}

void DefaultState::selectAnimation() {
    int randomNumber = rand() % 101;
    if (randomNumber > 75) {
        changeAnimationTo(new Animation("NORMAL", 14, 6));
        printf("Animation Changed to HAPPY\n");
    } else if (randomNumber > 50) {
        changeAnimationTo(new Animation("NORMAL", 14, 6));
        printf("Animation Changed to SAD\n");
    } else if (randomNumber > 25) {
        changeAnimationTo(new Animation("NORMAL", 14, 6));
        printf("Animation Changed to ANGRY\n");
    } else {
        changeAnimationTo(new Animation("NORMAL", 14, 6));
        printf("Animation Changed to NORMAL\n");
    }
}

void DefaultState::changeAnimationTo(Animation* newAnimation) {
    if (currentAnimation != NULL) {
        delete currentAnimation;
    }
    currentAnimation = newAnimation;
    currentAnimation->draw();
    Brain.Screen.render();
}

void DefaultState::enter() {
    Brain.Screen.setFillColor(white);
    Brain.Screen.drawRectangle(0, 0, 160, 108);
    printf("Entered Default State\n");
    currentAnimation = new Animation("NORMAL", 14, 6);
    currentAnimation->draw();
    Brain.Screen.render();
}

void DefaultState::update() {
    // This is the main loop for the default state.
    if (!currentAnimation->isFinished()) {
        currentAnimation->update();
    } else {
        selectAnimation();
    }

    // If the screen is pressed, show the menu. (Keep at bottom)
    if (Brain.buttonCheck.pressing() || Controller.ButtonFUp.pressing()) {
        robot.getMenu().show();
    }
}

void DefaultState::exit() {
    // This is where any cleanup for the default state will go.
    delete currentAnimation;
    Brain.Screen.clearScreen();
}
