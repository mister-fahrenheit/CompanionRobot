#include "vex.h"

using namespace vex;

brain Brain;

motor LeftMotor = motor(PORT1, false);  // false means the motor hasn't been reversed
motor RightMotor = motor(PORT2, false);
motor ArmMotor = motor(PORT3, false);
motor GripperMotor = motor(PORT4, false);

bumper Bumper = bumper(PORT5);
touchled TouchLED = touchled(PORT6);

optical Optical = optical(PORT7);
distance Distance = distance(PORT8);

controller Controller = controller();
