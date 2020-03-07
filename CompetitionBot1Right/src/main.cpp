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
bool pneumaticsOpened = false;

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
  armMotorGroup.setVelocity(30, rpm);
  armMotorGroup.spinToPosition(-turnAngle, degrees, true);
}

void togglePneumatics() {
  if(pneumaticsOpened) {
    dig1.close();
    dig2.close();
    pneumaticsOpened = false;
  } else {
    dig1.open();
    dig2.open();
    pneumaticsOpened = true;
  }
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

void openIntake(double distance, double vel, bool waitComplete) {
  intakeWires.spinTo(distance, degrees, vel, rpm, waitComplete);
}

void wiggle() {
  Drivetrain.setTimeout(500, msec);
  LeftDriveSmart.setTimeout(500, msec);
  RightDriveSmart.setTimeout(500, msec);
  LeftDriveSmart.spinFor(reverse, 2, rev, 50, rpm, true);
  Drivetrain.driveFor(fwd, 4, inches, 50, rpm);
  RightDriveSmart.spinFor(reverse, 2, rev, 50, rpm, true);
  Drivetrain.setTimeout(1500, msec);
  Drivetrain.driveFor(fwd, 4, inches ,50, rpm);
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
  Drivetrain.setTurnThreshold(3);
  // Callback for when the arm limit switch is pressed 
  armBumper.pressed(whenArmBumperIsPressed);

  threeAxisGyro.calibrate(); 
  Drivetrain.setDriveVelocity(50, rpm);
  intakeGroup.setVelocity(180, rpm);
  intakeWires.setVelocity(150, rpm);
  
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

  int flipAngle = -1;
  //First batch of blocks
  rotateArm();
  Drivetrain.driveFor(forward, 5, inches, 70, rpm, true);
  togglePneumatics();
  openIntake(100, 40, false);
  Drivetrain.driveFor(forward, 29, inches, 40, rpm, false);
  intake(true, 3.2, seconds);
  togglePneumatics();
  wait(0.3, seconds);

  //tower block
  Drivetrain.turnToHeading(flipAngle * 20, degrees, 30, rpm, true);
  Drivetrain.driveFor(forward, 12, inches, 50, rpm, false);
  intake(true, 2.8, seconds);
  Drivetrain.driveFor(reverse, 12, inches, 70, rpm, true);
  wait(0.3, seconds);

  //Reverse into the 2nd stack
  Drivetrain.turnToHeading(flipAngle * -35, degrees, 30, rpm);
  straightenArm(100);
  Drivetrain.driveFor(reverse, 43, inches, 80, rpm, false);
  intake(true, 2, seconds);

  //grab 2nd stack
  Drivetrain.turnToHeading(0, degrees, 30, rpm);
  rotateArm();
  intake(true, 0.2, seconds);
  openIntake(150, 30, false);
  Drivetrain.driveFor(forward, 40, inches, 40, rpm, false);
  intake(true, 2.5, seconds);
  Drivetrain.driveFor(reverse, 17, inches, 50, rpm, true);

  //go to scoring zone
  straightenArm(100);
  Drivetrain.turnToHeading(flipAngle * -90, degrees, 30, rpm);
  rotateArm();
  intake(true, 0.2, seconds);
  Drivetrain.driveFor(forward, 16, inches, 60, rpm, true);
  wait(0.3, seconds);
  Drivetrain.turnToHeading(flipAngle * -125, degrees, 30, rpm);
  Drivetrain.setTimeout(2500, msec);
  Drivetrain.driveFor(forward, 33, inches, 100, rpm, true);
  // wiggle();

  //Dump and backup
  wait(0.2, seconds);
  Drivetrain.setTimeout(2, seconds);
  Drivetrain.driveFor(reverse, 1.6, inches, 30, rpm, true);
  intake(false, 0.15, seconds);
  straightenArm(240);
  openIntake(-200, 150, true);
  straightenArm(500);
  openIntake(-737, 150, true);
  wait(0.3, seconds);
  Drivetrain.driveFor(forward, 3, inches, 15, rpm, true);
  Drivetrain.driveFor(reverse, 9, inches, 30, rpm, true);
  rotateArm();
  openIntake(0, 150, true);
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
  Controller1.ButtonY.pressed(togglePneumatics);
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    if(Controller1.ButtonX.pressing()){
      armMotorGroup.spin(reverse, 40, rpm);
    } else if(Controller1.ButtonA.pressing() && armMotorGroup.position(degrees) < 0){
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

    if(Controller1.ButtonL1.pressing()){
      intakeWires.spin(forward);
    } else if(Controller1.ButtonL2.pressing()) {
      intakeWires.spin(reverse);
    } else if(Controller1.ButtonLeft.pressing()){
      intakeWireL.spin(forward);
    } else if(Controller1.ButtonRight.pressing()) {
      intakeWireR.spin(forward);
    } else {
      intakeWires.stop();
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
