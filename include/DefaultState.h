#ifndef DEFAULT_STATE_H
#define DEFAULT_STATE_H

#include "RobotState.h"
#include "RobotPet.h"
#include "Animation.h"

// The default state for the robot.
class DefaultState : public RobotState
{
private:
    RobotPet& robot;
    Animation* currentAnimation;

    void selectAnimation();
    void changeAnimationTo(Animation* newAnimation);

public:
    DefaultState(RobotPet& robot);

    void enter() override;
    void update() override;
    void exit() override;
};

#endif // DEFAULT_STATE_H
