#ifndef ANIMATION_H
#define ANIMATION_H

#include "vex.h"
#include <string>
#include <vector>

// Represents a sequence of images for an animation.
class Animation {
public:
    Animation(const std::string& baseName, int frameCount);

    // Updates the animation.
    void update();

    // Draws the current frame.
    void draw();

private:
    std::vector<std::string> filenames;
    int currentFrame;
    int frameCount;
    vex::timer animationTimer;
};

#endif // ANIMATION_H
