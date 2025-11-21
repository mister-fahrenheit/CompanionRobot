#ifndef SHUTDOWN_STATE_H
#define SHUTDOWN_STATE_H

#include "RobotState.h"
#include "RobotPet.h"

// The state for when the robot is shutting down.
class ShutdownState : public RobotState {
public:
    ShutdownState(RobotPet& robot);

    void enter() override;
    void update() override;
    void exit() override;

private:
    RobotPet& robot;
};

#endif // SHUTDOWN_STATE_H
