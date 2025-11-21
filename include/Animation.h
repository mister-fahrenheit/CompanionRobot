#ifndef ANIMATION_H
#define ANIMATION_H

#include "vex.h"
#include <string>

// Represents a sequence of images for an animation.
class Animation {
public:
    Animation(const std::string& baseName, int frameCount, int framesPerSecond = 12, int width = 100, int height = 100,
              int horizontalFrames = 2, int verticalFrames = 2);

    // Updates the animation.
    void update();

    // Forces the next animation frame.
    void forceUpdate();

    // Draws the current frame.
    void draw();

    bool isFinished();

private:
    std::string baseName;  // Changed from vector to single string
    int framesPerSecond;
    int width;
    int height;
    int horizontalFrames;
    int verticalFrames;
    int currentFrame;
    int frameCount;
    vex::timer animationTimer;
};

#endif // ANIMATION_H
