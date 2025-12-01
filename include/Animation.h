#ifndef ANIMATION_H
#define ANIMATION_H

#include "vex.h"
#include <string>

// Represents a images for an animation.
class Animation
{
private:
    std::string baseName;
    int framesPerSecond;
    int width;
    int height;
    int horizontalFrames;
    int verticalFrames;
    int currentFrame;
    int frameCount;
    vex::timer animationTimer;

public:
    Animation(const std::string& baseName,
              int frameCount,
              int framesPerSecond = 12,
              int width = 100,
              int height = 100,
              int horizontalFrames = 2,
              int verticalFrames = 2);

    // Updates the animation.
    void update();

    // Forces the next animation frame.
    void forceUpdate();

    // Draws the current frame.
    void draw();

    bool isFinished();
};

#endif // ANIMATION_H
