#include "PlayMusicState.h"
#include "hardware-config.h"

PlayMusicState::PlayMusicState(RobotPet &robot) : robot(robot)
{
    // The constructor initializes the reference to the robot.
}

void PlayMusicState::enter()
{
    // This is where the Music control behavior will go.
    // For now, it just prints a message to console.
    Brain.Screen.setFillColor(white);
    Brain.Screen.drawRectangle(0, 0, 160, 108);
    printf("Entered Play Music State\n");
    Brain.Screen.render();
}
void PlayMusicState::setNote(int &note)
{
    note = static_cast<int>(Distance.objectDistance(mm) / 50);
    if(note>6){
        note =6;
    }
    else if (note<0){
        note=0;
    }
    bool currentBumper = Bumper.pressing();
    if (currentBumper && !lastBumper)
    {
        octave++;
    }
    bool currentLED=TouchLED.pressing();
    if(currentLED && !lastLED){
        octave--;
    }
    if(octave<1){
        octave=1;
    }
    else if(octave>7){
        octave=7;
    }
    lastLED=currentLED;
    lastBumper= currentBumper;    
}

void PlayMusicState::update()
{
    // This is the main loop for the Music state.
    // If the screen is pressed, show the menu.
    int note = 0;
    setNote(note);
    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(white);
    Brain.Screen.drawRectangle(0, 0, 160, 108);
    Brain.Screen.setPenColor(black);
    Brain.Screen.setFont(mono20);
    Brain.Screen.printAt(40, 40, "Note: %d", note);
    Brain.Screen.printAt(40, 75, "Octave: %d", octave);
    Brain.Screen.render();
    Brain.playNote(octave, note, 400);
    if (Brain.buttonCheck.pressing() || Controller.ButtonFUp.pressing())
    {
        robot.getMenu().show();
    }
}

void PlayMusicState::exit()
{
    // This is where any cleanup for the Music state will go.
    Brain.Screen.clearScreen();
}
