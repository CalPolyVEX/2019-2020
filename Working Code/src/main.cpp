/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Chris Suzuki                                     */
/*    Created:      Mon Nov 11 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Motor1               motor         1               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
bool opened = false;
int axis3,axis4,axis1,axis2;
int main() {
  
  while(1) {
    axis3 = Controller1.Axis3.position();
    axis4 = Controller1.Axis4.position();
    axis1 = Controller1.Axis1.position();
    axis2 = Controller1.Axis2.position();

    moveL.spin(directionType::fwd,0.8*axis3 + 0.8*axis1,percentUnits::pct);
    moveR.spin(directionType::fwd,0.8*axis3 - 0.8*axis1,percentUnits::pct);
    moveF.spin(directionType::fwd,0.8*axis4 + 0.8*axis1,percentUnits::pct);
    moveB.spin(directionType::fwd,0.8*axis4 - 0.8*axis1,percentUnits::pct);

    if( Controller1.ButtonL1.pressing() && !opened) {
     dig1.open();
     vex::task::sleep(250);
     opened = true;
    }
    if(Controller1.ButtonL1.pressing() && opened) {
      dig1.close();
      vex::task::sleep(250);
      opened = false;
    }
    if(Controller1.ButtonR1.pressing() ) {
      Lintake.spin(directionType::fwd,100,velocityUnits::rpm);
      Rintake.spin(directionType::fwd,100,velocityUnits::rpm);
    }
    else if(Controller1.ButtonR2.pressing()){
      Lintake.spin(directionType::rev,100,velocityUnits::rpm);
      Rintake.spin(directionType::rev,100,velocityUnits::rpm);
    }
    else{
      Lintake.stop();
      Rintake.stop();
    }

  }
}