#ifndef MUSIC_STATE_H
#define MUSIC_STATE_H

#include "RobotState.h"
#include "RobotPet.h"

// The state for when the robot is playing music.
class MusicState : public RobotState {
public:
    MusicState(RobotPet& robot);

    void enter() override;
    void update() override;
    void exit() override;

private:
    RobotPet& robot;
};

#endif // MUSIC_STATE_H
