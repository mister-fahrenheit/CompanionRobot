#ifndef RETRIEVE_STATE_H
#define RETRIEVE_STATE_H

#include "RobotState.h"
#include "RobotPet.h"

using namespace vex;

// The state for when the robot is retrieving items.
class RetrieveState : public RobotState
{
public:
    RetrieveState(RobotPet &robot);

    void enter() override;
    void update() override;
    void exit() override;

private:
    RobotPet &robot;

    float mmToDegrees(float mm);
    void driveDist(float distanceMM, int speed);
    void turnDeg(float degreesToTurn);
    void performAvoidance();
    void driveWithAvoidance(int distanceMM);
    void findAndGrip(color target);
    void selectColorSequence();

    const float WHEEL_DIAMETER = 63.5; // mm
    const float WHEEL_CIRCUMFERENCE = WHEEL_DIAMETER * 3.14159;
    const int TARGET_DISTANCE_MM = 2000; // 2 meters
    const int APPROACH_DIST_MM = 80;
    const int AVOID_BACKUP_MM = 80;
    const int AVOID_FORWARD_MM = 750;
    color desiredColor = red;
};

#endif // RETRIEVE_STATE_H
