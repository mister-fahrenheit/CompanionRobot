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

    // State machine for retrieve sequence
    enum RetrieveStep {
        INIT,
        CALIBRATING,
        SELECTING_COLOR,
        DRIVING_TO_TARGET,
        FINDING_OBJECT,
        GRIPPING_OBJECT,
        TURNING_HOME,
        DRIVING_HOME,
        COMPLETE
    };

    RetrieveStep currentStep;
    int stepStartTime;
    
    // Tracking variables for non-blocking operations
    float targetDegrees;
    float startAngle;
    float targetAngle;
    bool motorsRunning;
    int colorIndex;
    float effectiveDistanceCovered;
    float currentDegrees;
    float degreesToFaceHome;

    // Helper functions
    float mmToDegrees(float mm);
    void startDriveDist(float distanceMM, int speed);
    bool isDriveDistComplete();
    void startTurnDeg(float degreesToTurn);
    bool isTurnComplete();
    void performAvoidanceStep();
    void startDriveWithAvoidance(int distanceMM);
    bool updateDriveWithAvoidance();
    void startFindAndGrip(color target);
    bool updateFindAndGrip();
    bool updateColorSelection();

    const float WHEEL_DIAMETER = 63.5; // mm
    const float WHEEL_CIRCUMFERENCE = WHEEL_DIAMETER * 3.14159;
    const int TARGET_DISTANCE_MM = 2000; // 2 meters
    const int APPROACH_DIST_MM = 80;
    const int AVOID_BACKUP_MM = 80;
    const int AVOID_FORWARD_MM = 750;
    color desiredColor = red;
    
    // Avoidance state tracking
    enum AvoidanceStep {
        AVOID_NONE,
        AVOID_BACKUP,
        AVOID_TURN1,
        AVOID_DRIVE1,
        AVOID_TURN2,
        AVOID_DRIVE2,
        AVOID_TURN3,
        AVOID_DRIVE3,
        AVOID_TURN4,
        AVOID_COMPLETE
    };
    AvoidanceStep avoidanceStep;
    
    // Grip sequence tracking
    enum GripStep {
        GRIP_SEARCHING,
        GRIP_FOUND_WAIT,
        GRIP_CLOSING,
        GRIP_LIFTING,
        GRIP_COMPLETE
    };
    GripStep gripStep;
};

#endif // RETRIEVE_STATE_H
