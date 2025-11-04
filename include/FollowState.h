#ifndef FOLLOW_STATE_H
#define FOLLOW_STATE_H

#include "RobotState.h"
#include "RobotPet.h"

// The state for when the robot is following the user.
class FollowState : public RobotState {
public:
    FollowState(RobotPet& robot);

    void enter() override;
    void update() override;
    void exit() override;

private:
    RobotPet& robot;
};

#endif // FOLLOW_STATE_H
