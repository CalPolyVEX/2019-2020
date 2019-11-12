using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern pneumatics dig1;
extern motor moveF;
extern motor moveB;
extern motor moveL;
extern motor moveR;
extern motor Lintake;
extern motor Rintake;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );