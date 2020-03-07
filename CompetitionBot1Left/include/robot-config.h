using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor_group armMotorGroup;
extern bumper armBumper;

extern motor_group intakeGroup;
extern motor_group intakeWires;

extern inertial threeAxisGyro;
extern smartdrive Drivetrain;
extern controller Controller1;

extern pneumatics dig1;
extern pneumatics dig2;


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );