/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

// user defined functions
bool autoRunning = false;

void whenArmBumperIsPressed() {
  armMotor.stop();
  armMotor.resetRotation();
}

void rotateArm() {
  while(!armBumper.pressing()){
      armMotor.spin(forward, 60, rpm);
  }
  armMotor.stop();
}

void straightenArm() {
  armMotor.spinFor(reverse, 380, degrees, false);
}

void intake(bool forw, double t, timeUnits u) {
  if (forw){
      intakeLMotor.spin(forward);
      intakeRMotor.spin(forward);

  } else {
      intakeLMotor.spin(reverse);
      intakeRMotor.spin(reverse);
  }
  wait(t, u);
}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Drivetrain.setDriveVelocity(50, rpm);
  intakeLMotor.setVelocity(150, rpm);
  intakeRMotor.setVelocity(150, rpm);
  
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  autoRunning = true;
  Drivetrain.driveFor(forward, 36, inches, false);
  intake(true, 10, seconds);
}

void autoButton(){
  pre_auton();
  autonomous();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    Controller1.ButtonA.pressed(autoButton);
    if(autoRunning) {
      wait(2, seconds);
      autoRunning = false;
    }

    intakeLMotor.setVelocity(80, percent);
    intakeRMotor.setVelocity(80, percent);

    Controller1.ButtonB.pressed(rotateArm);
    if(Controller1.ButtonX.pressing()&&armMotor.rotation(degrees)>-380){
      armMotor.spin(reverse, 60, rpm);
    } else if(Controller1.ButtonL1.pressing()&&armMotor.rotation(degrees)>-380){
      armMotor.spin(reverse, 40, rpm);
    }
    else {
      armMotor.stop();
    }

    if(Controller1.ButtonR1.pressing()){
      intakeLMotor.spin(forward);
      intakeRMotor.spin(forward);
    } else if(Controller1.ButtonR2.pressing()) {
      intakeLMotor.spin(reverse, 60, percent);
      intakeRMotor.spin(reverse, 60, percent);
    } else {
      intakeLMotor.stop();
      intakeRMotor.stop();
    }


    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    armBumper.pressed(whenArmBumperIsPressed);
    wait(100, msec);
  }
}
