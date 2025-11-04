#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "RobotState.h"

// Manages the current state and handles transitions.
class StateManager {
public:
    StateManager();

    // Transitions to a new state.
    void transitionTo(RobotState* newState);

    // Updates the current state.
    void update();

private:
    RobotState* currentState;
};

#endif // STATE_MANAGER_H
