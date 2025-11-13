#ifndef STARTUP_STATE_H
#define STARTUP_STATE_H

#include "RobotState.h"
#include "RobotPet.h"
#include "Animation.h"

// The state for when the robot is starting up.
class StartupState : public RobotState {
public:
    StartupState(RobotPet& robot);

    void enter() override;
    void update() override;
    void exit() override;

private:
    RobotPet& robot;
    Animation* startupAnimation;
};

#endif // STARTUP_STATE_H
