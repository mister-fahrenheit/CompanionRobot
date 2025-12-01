#ifndef MANUAL_STATE_H
#define MANUAL_STATE_H

#include "RobotState.h"
#include "RobotPet.h"

// The state for when the robot is being manually controlled.
class ManualState : public RobotState
{
private:
    RobotPet& robot;

public:
    ManualState(RobotPet& robot);

    void enter() override;
    void update() override;
    void exit() override;
};

#endif // MANUAL_STATE_H
