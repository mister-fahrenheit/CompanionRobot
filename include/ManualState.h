#ifndef MANUAL_STATE_H
#define MANUAL_STATE_H

#include "RobotState.h"
#include "RobotPet.h"

// The state for when the robot is being manually controlled.
class ManualState : public RobotState {
public:
    ManualState(RobotPet& robot);

    void enter() override;
    void update() override;
    void exit() override;

private:
    RobotPet& robot;
};

#endif // MANUAL_STATE_H
