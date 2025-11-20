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
public:
    ListenMusicState(RobotPet &robot);
    void enter() override;
    void update() override;
    void exit() override;
    void switchSong();

private:
    RobotPet &robot;
    bool lastState = false; // will use as last bumper state

    // --- Songs (note arrays) ---
    static constexpr int SONG4_LEN = 18;
    static constexpr int SONG6_LEN = 19;
    static constexpr int ILOVEU_LEN = 17;
    std::string songName = "Bad Romance";

    const Note badRomance[SONG4_LEN] = {
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

    const Note baby[SONG6_LEN] = {
        {4, 3, 150}, // F4, 8
        {4, 3, 150}, // F4, 8
        {4, 4, 150}, // G4, 8
        {4, 3, 300}, // F4, 4
        {4, 4, 300}, // G4, 4
        {4, 3, 300}, // F4, 4
        {4, 4, 300}, // G4, 4
        {4, 3, 150}, // F4, 8
        {4, 4, 300}, // G4, 4
        {4, 3, 150}, // F4, 8
        {4, 5, 600}, // A4
        {4, 4, 300}, // G4, 4
        {4, 4, 300}, // G4, 4
        {4, 3, 300}, // F4, 4
        {4, 4, 300}, // G4, 4
        {4, 3, 150}, // F4, 8
        {4, 4, 300}, // G4, 4
        {4, 3, 150}, // F4, 8
        {5, 0, 600}  // C5, 2
    };

    const Note IloveU[17] = {
        {5, 1, 300}, // D5, duration 4
        {5, 3, 150}, // F5, 8
        {5, 0, 300}, // C5, 4
        {4, 5, 400}, // AS4 → A4, 3
        {0, 0, 300}, // REST, 4
        {5, 1, 300}, // D5, 4
        {5, 3, 300}, // F5, 4
        {5, 4, 300}, // G5, 4
        {5, 3, 150}, // F5, 8
        {5, 1, 300}, // DS5 → D5, 4
        {5, 1, 400}, // D5, 3
        {5, 0, 150}, // C5, 8
        {0, 0, 300}, // REST, 4
        {5, 1, 300}, // D5, 4
        {5, 3, 150}, // F5, 8
        {5, 0, 300}, // C5, 4
        {4, 5, 400}  // AS4 → A4, 3
    };
    static constexpr int UIFU_LEN = 30;

    const Note uifu[UIFU_LEN] = {
        {4, 3, 150}, // F4
        {4, 3, 150}, // F4
        {4, 4, 300}, // G4
        {4, 4, 150}, // G4
        {5, 1, 300}, // DS5 -> D5
        {5, 1, 150}, // D5
        {4, 5, 300}, // A4
        {4, 5, 150}, // A4
        {4, 5, 150}, // A4
        {4, 5, 150}, // AS4 -> A4
        {5, 0, 150}, // C5
        {5, 1, 400}, // D5
        {5, 3, 400}, // F5
        {5, 1, 600}, // D5
        {4, 3, 150}, // F4
        {4, 3, 150}, // F4
        {4, 4, 300}, // G4
        {4, 4, 150}, // G4
        {5, 1, 300}, // DS5 -> D5
        {5, 1, 150}, // D5
        {4, 5, 300}, // A4
        {4, 5, 150}, // A4
        {4, 5, 300}, // AS4 -> A4
        {5, 0, 150}, // C5
        {5, 1, 300}, // D5
        {5, 3, 150}, // F5
        {5, 3, 150}, // F5
        {5, 1, 150}, // D5
        {5, 1, 150}, // D5
        {5, 0, 400}  // C5
    };

    // playback state
    int currentSongIndex = 0; // 0 = song4, 1 = song6, 2 = IloveU
    int currentNoteIndex = 0;
    int currentSongLength = SONG4_LEN;
    const Note *currentSongPtr = badRomance;
};

#endif // LISTEN_MUSIC_STATE_H
