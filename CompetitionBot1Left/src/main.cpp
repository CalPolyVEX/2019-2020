/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Khanh Hoang                                               */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Code                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <cmath>
#include "autoselector.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

// user defined functions

void whenArmBumperIsPressed() {
  armMotorGroup.stop();
  armMotorGroup.resetRotation();
  armMotorGroup.resetPosition();

}

void rotateArm() {
  while(!armBumper.pressing()){
      armMotorGroup.spin(forward, 60, rpm);
  }
  armMotorGroup.stop();
  armMotorGroup.resetRotation();
  armMotorGroup.resetPosition();
}

void straightenArm(int turnAngle) {
  armMotorGroup.setVelocity(25, rpm);
  armMotorGroup.spinToPosition(-turnAngle, degrees, true);
}

void intake(bool forw, double t, timeUnits u) {
  if (forw){
      intakeGroup.spin(forward);
  } else {
      intakeGroup.spin(reverse);
  }
  wait(t, u);
  intakeGroup.stop();
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
  
  // Callback for when the arm limit switch is pressed 
  armBumper.pressed(whenArmBumperIsPressed);

  threeAxisGyro.calibrate(); 
  Drivetrain.setDriveVelocity(50, rpm);
  intakeGroup.setVelocity(180, rpm);
  
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

  if(autonomousSelection == 2) {

  } else{
    int flipAngle = 1;
    if(autonomousSelection == 1){
      flipAngle = -1;
    }

    //First batch of blocks
    Drivetrain.driveFor(forward, 5, inches, 70, rpm, true);
    rotateArm();
    Drivetrain.driveFor(forward, 27, inches, 40, rpm, false);
    intake(true, 4.4, seconds);
    Drivetrain.driveFor(forward, 4, inches, 40, rpm, false);
    intake(true, 1.3, seconds);
    intake(false, 0.2, seconds);
    intake(true, 0.5, seconds);

    //tower block
    Drivetrain.driveFor(reverse, 5, inches, 70, rpm, true);
    Drivetrain.turnFor(flipAngle * 25, degrees, true);
    Drivetrain.driveFor(forward, 16, inches, 50, rpm, false);
    intake(true, 2.8, seconds);
    intake(false, 0.2, seconds);
    intake(true, 0.5, seconds);
    Drivetrain.driveFor(reverse, 16, inches, 70, rpm, true);

    //Reverse into the 2nd stack
    Drivetrain.turnToHeading(flipAngle * -34, degrees, 60, rpm);
    straightenArm(150);
    Drivetrain.driveFor(reverse, 32, inches, 100, rpm, false);
    intake(true, 2, seconds);

    //grab 2nd stack
    Drivetrain.turnToHeading(0, degrees, 50, rpm);
    rotateArm();
    intake(true, 0.7, seconds);
    Drivetrain.driveFor(forward, 22, inches, 40, rpm, false);
    intake(true, 3.8, seconds);
    Drivetrain.driveFor(forward, 6, inches, 40, rpm, false);
    intake(true, 2.5, seconds);
    intake(false, 0.2, seconds);
    intake(true, 0.5, seconds);
    Drivetrain.driveFor(reverse, 5, inches, 50, rpm, true);

    //go to scoring zone
    straightenArm(150);
    Drivetrain.turnToHeading(flipAngle * -90, degrees);
    rotateArm();
    intake(true, 1, seconds);
    Drivetrain.driveFor(forward, 14, inches, 60, rpm, true);
    Drivetrain.turnToHeading(flipAngle * -130, degrees);
    Drivetrain.setTimeout(4, seconds);
    Drivetrain.driveFor(forward, 39, inches, 100, rpm, true);

    //Dump and backup
    Drivetrain.setTimeout(2, seconds);
    straightenArm(580);
    Drivetrain.driveFor(forward, 2, inches, 30, rpm, true);
    wait(0.6, seconds);
    Drivetrain.driveFor(reverse, 9, inches, 30, rpm, true);
    rotateArm(); 
  }
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
  Controller1.ButtonB.pressed(rotateArm);
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    if(Controller1.ButtonX.pressing()){
      armMotorGroup.spin(reverse, 60, rpm);
    } else if(Controller1.ButtonL1.pressing()){
      armMotorGroup.spin(reverse, 40, rpm);
    } else if(Controller1.ButtonA.pressing()){
      armMotorGroup.spin(forward, 60, rpm);
    } else{
      armMotorGroup.stop();
    }

    if(Controller1.ButtonR1.pressing()){
      intakeGroup.spin(forward);
    } else if(Controller1.ButtonR2.pressing()) {
      intakeGroup.spin(reverse, 60, percent);
    } else {
      intakeGroup.stop();
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

  // register events for button selection
  Brain.Screen.pressed( userTouchCallbackPressed );
  Brain.Screen.released( userTouchCallbackReleased );

  // make nice background
  Brain.Screen.setFillColor( vex::color(0x404040) );
  Brain.Screen.setPenColor( vex::color(0x404040) );
  Brain.Screen.drawRectangle( 0, 0, 480, 120 );
  Brain.Screen.setFillColor( vex::color(0x808080) );
  Brain.Screen.setPenColor( vex::color(0x808080) );
  Brain.Screen.drawRectangle( 0, 120, 480, 120 );

  // initial display
  displayButtonControls( 0, false );

  // Prevent main from exiting with an infinite loop.
  while (true) {
    if( !Competition.isEnabled() )
        Brain.Screen.setFont(fontType::mono40);
    Brain.Screen.setFillColor( vex::color(0xFFFFFF) );
    Brain.Screen.setPenColor( vex::color(0xc11f27));
    wait(100, msec);
  }
}
