#include "ListenMusicState.h"
#include "hardware-config.h"

#include "RobotPet.h"
ListenMusicState::ListenMusicState(RobotPet &robot) : robot(robot)
{
}

void ListenMusicState::enter()
{
    printf("Entered Listen Music State\n");

    currentSongIndex = 0;
    currentSongPtr = badRomance;
    currentSongLength = SONG4_LEN;
    currentNoteIndex = 0;
    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(white);
    Brain.Screen.drawRectangle(0, 0, 160, 108);
    Brain.Screen.setPenColor(black);
    Brain.Screen.setFont(mono15);
    Brain.Screen.printAt(40, 60, songName.c_str());
    Brain.Screen.render();
}

void ListenMusicState::switchSong()
{
    currentSongIndex = (currentSongIndex + 1) % 4;

    switch (currentSongIndex)
    {
    case 0:
        currentSongPtr = badRomance;
        currentSongLength = SONG4_LEN;
        songName = "Bad Romance";
        break;
    case 1:
        currentSongPtr = baby;
        currentSongLength = SONG6_LEN;
        songName = "Baby";
        break;
    case 2:
        currentSongPtr = IloveU;
        currentSongLength = ILOVEU_LEN;
        songName = "I love U";
        break;
    case 3:
        currentSongPtr = uifu;
        currentSongLength = UIFU_LEN;
        songName = "Until I found U";
        break;
    }
    printf("switched Song");
    currentNoteIndex = 0;
}

void ListenMusicState::update()
{

    bool bumperPressed = Bumper.pressing();
    if (bumperPressed && !lastState)
    {
        switchSong();
        Brain.Screen.clearScreen();
        Brain.Screen.setFillColor(white);
        Brain.Screen.drawRectangle(0, 0, 160, 108);
        Brain.Screen.setPenColor(black);
        Brain.Screen.setFont(mono15);
        Brain.Screen.printAt(40, 60, songName.c_str());

        Brain.Screen.render();
    }
    lastState = bumperPressed;

    if (currentNoteIndex >= currentSongLength)
        currentNoteIndex = 0;

    const Note &n = currentSongPtr[currentNoteIndex];
    printf("song= %d\n", currentSongIndex);
    
    if (n.octave == 0 && n.note == 0)
        wait(n.duration, msec);
    else
        Brain.playNote(n.octave, n.note, n.duration);
    currentNoteIndex++;

    if (Brain.buttonCheck.pressing() || Controller.ButtonFUp.pressing())
        robot.getMenu().show();
}

void ListenMusicState::exit()
{
    Brain.Screen.clearScreen();
}
