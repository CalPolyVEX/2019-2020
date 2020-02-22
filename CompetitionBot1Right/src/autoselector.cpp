#include "vex.h"
#include "autoselector.h"
using namespace vex;

/*---------------------------------------------------------------------------

       WalshBots 9791 unified competition template                              
       Authors:  Liam Donovan, CJ Crocker
       Contributors:  
                James Pearman - Brain Auton Button Selector
                Pascal Chesnais - multimotor abstractions

                Modification History:
                1/5/2019 - prc - instructional version...
  ---------------------------------------------------------------------------*/


// storage for our auton selection
int autonomousSelection = -1;

// forward ref
void displayButtonControls( int index, bool pressed );

button buttonsArr[] = {
    {   30,  30, 60, 60,  false, 0x303030, 0x0000E0, "Left Side" },
    {  150,  30, 60, 60,  false, 0x303030, 0xD0D0D0, "Right Side" },
    {  270,  30, 60, 60,  false, 0x303030, 0xF700FF, "No Auto" },
};

/*-----------------------------------------------------------------------------*/
/** @brief      Check if touch is inside button                                */
/*-----------------------------------------------------------------------------*/
int
findButton(  int16_t xpos, int16_t ypos ) {
    int nButtons = sizeof(buttonsArr) / sizeof(button);

    for( int index=0;index < nButtons;index++) {
      button *pButton = &buttonsArr[ index ];
      if( xpos < pButton->xpos || xpos > (pButton->xpos + pButton->width) )
        continue;

      if( ypos < pButton->ypos || ypos > (pButton->ypos + pButton->height) )
        continue;

      return(index);
    }
    return (-1);
}

/*-----------------------------------------------------------------------------*/
/** @brief      Init button states                                             */
/*-----------------------------------------------------------------------------*/
void
initButtons() {
    int nButtons = sizeof(buttonsArr) / sizeof(button);

    for( int index=0;index < nButtons;index++) {
      buttonsArr[index].state = false;
    }
}

/*-----------------------------------------------------------------------------*/
/** @brief      Screen has been touched                                        */
/*-----------------------------------------------------------------------------*/
void
userTouchCallbackPressed() {
    int index;
    int xpos = Brain.Screen.xPosition();
    int ypos = Brain.Screen.yPosition();

    if( (index = findButton( xpos, ypos )) >= 0 ) {
      displayButtonControls( index, true );
    }

}

/*-----------------------------------------------------------------------------*/
/** @brief      Screen has been (un)touched                                    */
/*-----------------------------------------------------------------------------*/
void
userTouchCallbackReleased() {
    int index;
    int xpos = Brain.Screen.xPosition();
    int ypos = Brain.Screen.yPosition();

    if( (index = findButton( xpos, ypos )) >= 0 ) {
      // clear all buttons to false, ie. unselected
      initButtons(); 

      // now set this one as true
      if( buttonsArr[index].state == true) {
      buttonsArr[index].state = false; }
      else    {
      buttonsArr[index].state = true;}

      // save as auton selection
      autonomousSelection = index;

      displayButtonControls( index, false );
    }
}

/*-----------------------------------------------------------------------------*/
/** @brief      Draw all buttons                                               */
/*-----------------------------------------------------------------------------*/
void
displayButtonControls( int index, bool pressed ) {
    vex::color c;
    Brain.Screen.setPenColor( vex::color(0xe0e0e0) );

    for(int i=0;i<sizeof(buttonsArr)/sizeof(button);i++) {

      if( buttonsArr[i].state )
        c = buttonsArr[i].onColor;
      else
        c = buttonsArr[i].offColor;

      Brain.Screen.setFillColor( c );

      // button fill
      if( i == index && pressed == true ) {
        Brain.Screen.drawRectangle( buttonsArr[i].xpos, buttonsArr[i].ypos, buttonsArr[i].width, buttonsArr[i].height, c );
      }
      else
        Brain.Screen.drawRectangle( buttonsArr[i].xpos, buttonsArr[i].ypos, buttonsArr[i].width, buttonsArr[i].height );

      // outline
      Brain.Screen.drawRectangle( buttonsArr[i].xpos, buttonsArr[i].ypos, buttonsArr[i].width, buttonsArr[i].height, vex::color::transparent );

// draw label
      if(  buttonsArr[i].label != NULL )
        Brain.Screen.printAt( buttonsArr[i].xpos + 8, buttonsArr[i].ypos + buttonsArr[i].height - 8, buttonsArr[i].label );
    }
}

