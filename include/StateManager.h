#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "RobotState.h"

// Manages the current state and handles transitions.
class StateManager
{
private:
    RobotState* currentState;

public:
    StateManager();

    // Transitions to a new state.
    void transitionTo(RobotState* newState);

    // Updates the current state.
    void update();
};

#endif // STATE_MANAGER_H
