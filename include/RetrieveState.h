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
};

#endif // RETRIEVE_STATE_H
