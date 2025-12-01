#ifndef LISTEN_MUSIC_STATE_H
#define LISTEN_MUSIC_STATE_H

#include "RobotState.h"
#include "RobotPet.h"

struct Note
{
    int octave;   // e.g. 4
    int note;     // 0=C,1=D,2=E,3=F,4=G,5=A,6=B
    int duration; // ms
};

// The state for when the robot is playing music.
class ListenMusicState : public RobotState
{
private:
    RobotPet &robot;
    bool lastState = false;

    std::string songName = "Bad Romance";

    static const int SONG4_LEN = 18;
    const Note badRomance[SONG4_LEN] =
    {
        {4, 0, 300},  // C4, 8
        {4, 1, 300},  // D4, 8
        {4, 2, 300},  // E4, 8
        {4, 0, 300},  // C4, 8
        {4, 3, 1200}, // F4, 2
        {4, 2, 300},  // E4, 8
        {4, 3, 300},  // F4, 8
        {4, 2, 300},  // E4, 8
        {4, 1, 1200}, // D4, 2
        {3, 6, 300},  // B3, 8
        {4, 0, 600},  // C4, 4
        {4, 1, 600},  // D4, 4
        {4, 2, 600},  // E4, 4
        {4, 2, 300},  // E4, 8
        {4, 2, 300},  // E4, 8
        {4, 2, 300},  // E4, 8
        {4, 1, 600},  // D4, 4
        {4, 0, 600}   // C4, 4
    };

    static const int SONG6_LEN = 19;
    const Note baby[SONG6_LEN] =
    {
        {3, 3, 300},  // F4, 8
        {3, 3, 300},  // F4, 8
        {3, 4, 300},  // G4, 8
        {3, 3, 600},  // F4, 4
        {3, 4, 600},  // G4, 4
        {3, 3, 600},  // F4, 4
        {3, 4, 600},  // G4, 4
        {3, 3, 300},  // F4, 8
        {3, 4, 600},  // G4, 4
        {3, 3, 300},  // F4, 8
        {3, 5, 1200}, // A4
        {3, 4, 600},  // G4, 4
        {3, 4, 600},  // G4, 4
        {3, 3, 600},  // F4, 4
        {3, 4, 600},  // G4, 4
        {3, 3, 300},  // F4, 8
        {3, 4, 600},  // G4, 4
        {3, 3, 300},  // F4, 8
        {4, 0, 1200}  // C5, 2
    };

    static const int ILOVEU_LEN = 17;
    const Note IloveU[17] =
    {
        {4, 1, 600}, // D5, duration 4
        {4, 3, 300}, // F5, 8
        {4, 0, 600}, // C5, 4
        {4, 5, 800}, // AS4 → A4, 3
        {0, 0, 600}, // REST, 4
        {4, 1, 600}, // D5, 4
        {4, 3, 600}, // F5, 4
        {4, 4, 600}, // G5, 4
        {4, 3, 300}, // F5, 8
        {4, 1, 600}, // DS5 → D5, 4
        {4, 1, 800}, // D5, 3
        {4, 0, 300}, // C5, 8
        {0, 0, 600}, // REST, 4
        {4, 1, 600}, // D5, 4
        {4, 3, 300}, // F5, 8
        {4, 0, 600}, // C5, 4
        {3, 5, 800}  // AS4 → A4, 3
    };

    static const int UIFU_LEN = 30;
    const Note uifu[UIFU_LEN] =
    {
        {3, 3, 300},  // F4
        {3, 3, 300},  // F4
        {3, 4, 600},  // G4
        {3, 4, 300},  // G4
        {4, 1, 600},  // DS5 -> D5
        {4, 1, 300},  // D5
        {3, 5, 600},  // A4
        {3, 5, 300},  // A4
        {3, 5, 300},  // A4
        {3, 5, 300},  // AS4 -> A4
        {4, 0, 300},  // C5
        {4, 1, 800},  // D5
        {4, 3, 800},  // F5
        {4, 1, 1200}, // D5
        {3, 3, 300},  // F4
        {3, 3, 300},  // F4
        {3, 4, 600},  // G4
        {3, 4, 300},  // G4
        {4, 1, 600},  // DS5 -> D5
        {4, 1, 300},  // D5
        {3, 5, 600},  // A4
        {3, 5, 300},  // A4
        {3, 5, 600},  // AS4 -> A4
        {4, 0, 300},  // C5
        {4, 1, 600},  // D5
        {4, 3, 300},  // F5
        {4, 3, 300},  // F5
        {4, 1, 300},  // D5
        {4, 1, 300},  // D5
        {4, 0, 800}   // C5
    };

    int currentSongIndex = 0; // 0 = song4, 1 = song6, 2 = IloveU etc
    int currentNoteIndex = 0;
    int currentSongLength = SONG4_LEN;
    const Note *currentSongPtr = badRomance;

    void switchSong();

public:
    ListenMusicState(RobotPet &robot);
    void enter() override;
    void update() override;
    void exit() override;
};

#endif // LISTEN_MUSIC_STATE_H
