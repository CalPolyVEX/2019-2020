using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor armMotor;
extern bumper armBumper;

extern motor intakeLMotor;
extern motor intakeRMotor;

extern drivetrain Drivetrain;
extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );