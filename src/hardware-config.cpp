#include "vex.h"

using namespace vex;

brain Brain;

motor LeftMotor = motor(PORT12, false); // false means the motor hasn't been reversed
motor RightMotor = motor(PORT7, false);
motor ArmMotor = motor(PORT3, false);
motor GripperMotor = motor(PORT4, false);

bumper Bumper = bumper(PORT1);
touchled TouchLED = touchled(PORT2);

optical Optical = optical(PORT5);
distance Distance = distance(PORT8);

controller Controller = controller();
