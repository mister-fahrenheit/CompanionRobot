#include "Animation.h"
#include "hardware-config.h"
#include <cstdio>

Animation::Animation(const std::string& baseName,
                     int frameCount,
                     int framesPerSecond,
                     int width,
                     int height,
                     int horizontalFrames,
                     int verticalFrames) : 
                     baseName(baseName),
                     framesPerSecond(framesPerSecond),
                     width(width),
                     height(height), 
                     horizontalFrames(horizontalFrames),
                     verticalFrames(verticalFrames),
                     currentFrame(0),
                     frameCount(frameCount)
{
    animationTimer.reset();
}

void Animation::update()
{
    // Update the animation frame based on the timer.
    if (animationTimer.time(msec) > 1000 / framesPerSecond)
    {
        forceUpdate();
    }
}

void Animation::forceUpdate()
{
    Brain.Screen.render();
    currentFrame += horizontalFrames * verticalFrames; 
    int totalFrames = frameCount * horizontalFrames * verticalFrames;
    if (currentFrame >= totalFrames)
        currentFrame = 0;
    draw();
    animationTimer.reset();
}

void Animation::draw()
{
    static int Corner_x = (160 - width)/2 - 1;
    static int Corner_y = (108 - height)/2 - 1;
    
    char filename[128];
    int counter = 0;
    
    // Calculate which logical frame we're on (1-indexed)
    int logicalFrame = (currentFrame / (horizontalFrames * verticalFrames)) + 1;
    
    for (int i = 0; i < verticalFrames; i++)
    {
        for (int j = 0; j < horizontalFrames; j++)
        {
            // Generate filename
            int subFrame = counter + 1;
            snprintf(filename, sizeof(filename), "%s%d_%d.bmp", baseName.c_str(), logicalFrame, subFrame);
            
            Brain.Screen.drawImageFromFile(filename, 
                                           Corner_x + j * width / horizontalFrames, 
                                           Corner_y + i * height / verticalFrames);
            counter++;
        }
    }
}

bool Animation::isFinished()
{
    int totalFrames = frameCount * horizontalFrames * verticalFrames;
    return currentFrame + horizontalFrames * verticalFrames >= totalFrames;
}
