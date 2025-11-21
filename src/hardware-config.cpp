#include "vex.h"

using namespace vex;

brain Brain;

motor LeftMotor = motor(PORT12, false); // false means the motor hasn't been reversed
motor RightMotor = motor(PORT7, true);
motor ArmMotor = motor(PORT3, true);
motor GripperMotor = motor(PORT4, true);

bumper Bumper = bumper(PORT1);
touchled TouchLED = touchled(PORT6);

optical Optical = optical(PORT5);
distance Distance = distance(PORT2);

controller Controller = controller();

inertial BrainInertial = inertial();
