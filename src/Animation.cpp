#include "Animation.h"
#include "hardware-config.h"

Animation::Animation(const std::string& baseName, int frameCount) : currentFrame(0), frameCount(frameCount * 2) {
    // The constructor creates the filenames for the animation.
    for (int i = 1; i <= frameCount; ++i) {
        filenames.push_back(baseName + std::to_string(i) + "_1.bmp");
        filenames.push_back(baseName + std::to_string(i) + "_2.bmp");
    }
    animationTimer.reset();
}

void Animation::update() {
    // Update the animation frame based on the timer.
    if (animationTimer.time(msec) > 1000 / 12) { // 12 fps
        currentFrame +=2;
        if (currentFrame >= frameCount) {
            currentFrame = 0;
        }
        animationTimer.reset();
    }
}

void Animation::draw() {
    Brain.Screen.drawImageFromFile(filenames[currentFrame].c_str(), 30, 4);
    Brain.Screen.drawImageFromFile(filenames[currentFrame+1].c_str(), 30, 54);
}
