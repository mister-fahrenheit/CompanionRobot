#ifndef FOLLOW_STATE_H
#define FOLLOW_STATE_H

#include "RobotState.h"
#include "RobotPet.h"

// The state for when the robot is following the user.
class FollowState : public RobotState
{
private:
    RobotPet& robot;
    bool lastOptical = false;
    bool lastDistance = false;
    int leftMotorSpeed = 0;
    int rightMotorSpeed = 0;

public:
    FollowState(RobotPet& robot);

    void enter() override;
    void update() override;
    void exit() override;
};

#endif // FOLLOW_STATE_H
