using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern drivetrain Drivetrain;
extern motor ArmMotor1;
extern motor ArmMotor2;
extern motor_group ArmMotors;
extern motor WristMotor;
// extern pneumatics dig1;
extern motor ClawMotor;


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );