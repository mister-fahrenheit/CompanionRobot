#ifndef PLAY_MUSIC_STATE_H
#define PLAY_MUSIC_STATE_H

#include "RobotState.h"
#include "RobotPet.h"

// The state for when the robot is playing music.
class PlayMusicState : public RobotState
{
private:
    RobotPet &robot;
    vex::timer musicTimer;
    bool lastBumper = false;
    bool lastLED= false;
    int octave = 1;

    void setNote(int &);

public:
    PlayMusicState(RobotPet &robot);

    void enter() override;
    void update() override;
    void exit() override;
};

#endif // PLAY_MUSIC_STATE_H
