#ifndef ROBOT_STATE_H
#define ROBOT_STATE_H

// Interface for a robot state.
class RobotState
{
public:
    // Called when the state is entered.
    virtual void enter() = 0;

    // Called repeatedly to update the state.
    virtual void update() = 0;

    // Called when the state is exited.
    virtual void exit() = 0;
};

#endif // ROBOT_STATE_H
