#include "StateManager.h"
#include <cstddef>

StateManager::StateManager() : currentState(NULL) {
    // The current state is initialized to null.
}

void StateManager::transitionTo(RobotState* newState) {
    // If there is a current state, call its exit method.
    if (currentState != NULL) {
        currentState->exit();
        delete currentState; // Clean up the old state.
    }

    // Set the new state and call its enter method.
    currentState = newState;
    if (currentState != NULL) {
        currentState->enter();
    }
}

void StateManager::update() {
    // If there is a current state, call its update method.
    if (currentState != NULL) {
        currentState->update();
    }
}
