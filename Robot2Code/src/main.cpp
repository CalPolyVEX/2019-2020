/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Dexti                                            */
/*    Created:      Sat Jan 11 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    1, 2, 3, 4      
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

void whenArmBumperIsPressed() {
  armMotor.stop();
  armMotor.resetRotation();
}

void rotateArm() {
  while(!armBumper.pressing()){
      armMotor.spin(forward, 30, percent);
  }
  armMotor.stop();
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  while(true){
    armBumper.pressed(whenArmBumperIsPressed);
    Controller1.ButtonX.pressed(rotateArm);
    if(Controller1.ButtonR1.pressing()&&!armBumper.pressing()){
      armMotor.spin(forward, 30, percent);
    } else if(Controller1.ButtonR2.pressing()&&armMotor.rotation(degrees)>-380){
      armMotor.spin(reverse, 30, percent);
    }
    else {
      armMotor.stop();
    }

    if(Controller1.ButtonL1.pressing()){
      intakeLMotor.spin(forward, 50, percent);
      intakeRMotor.spin(forward, 50, percent);
    } else if(Controller1.ButtonL2.pressing()) {
      intakeLMotor.spin(reverse, 50, percent);
      intakeRMotor.spin(reverse, 50, percent);
    } else {
      intakeLMotor.stop();
      intakeRMotor.stop();
    }

    task::sleep(20);
  }
}

