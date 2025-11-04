#ifndef DEFAULT_STATE_H
#define DEFAULT_STATE_H

#include "RobotState.h"
#include "RobotPet.h"
#include "Animation.h"

// The default state for the robot.
class DefaultState : public RobotState {
public:
    DefaultState(RobotPet& robot);
    ~DefaultState();

    void enter() override;
    void update() override;
    void exit() override;

private:
    RobotPet& robot;
    Animation* happyAnimation;
};

#endif // DEFAULT_STATE_H
