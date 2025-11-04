#ifndef HARDWARE_CONFIG_H
#define HARDWARE_CONFIG_H

#include "vex.h"

using namespace vex;

extern brain Brain; // The VEX Brain

extern motor LeftMotor; // Left drive motor
extern motor RightMotor; // Right drive motor
extern motor ArmMotor; // Arm motor
extern motor GripperMotor; // Gripper motor

extern bumper Bumper; // Bumper sensor
extern touchled TouchLED; // Touch LED sensor
extern optical Optical; // Optical sensor
extern distance Distance; // Distance sensor
extern controller Controller; // VEX Controller

#endif // HARDWARE_CONFIG_H
