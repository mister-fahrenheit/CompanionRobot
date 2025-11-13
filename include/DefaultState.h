#ifndef DEFAULT_STATE_H
#define DEFAULT_STATE_H

#include "RobotState.h"
#include "RobotPet.h"
#include "Animation.h"

// The default state for the robot.
class DefaultState : public RobotState {
public:
    DefaultState(RobotPet& robot);

    void enter() override;
    void update() override;
    void exit() override;

    void selectAnimation();
    void changeAnimationTo(Animation* newAnimation);

private:
    RobotPet& robot;
    Animation* currentAnimation;
};

#endif // DEFAULT_STATE_H
