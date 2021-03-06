// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _ARSG_Keyboard_Controller_H_
#define _ARSG_Keyboard_Controller_H_
#include "Arduino.h"

//add your includes for the project ARSG_Keyboard_Controller here
#include "Wire.h"
#include "KeyboardScanner.h"
#include "RotaryEncoder.h"

//end of add your includes here


//add your function definitions for the project ARSG_Keyboard_Controller here
void setInterrupt();
void releaseInterrupt();
void respond();
void receiveEvent(int howMany);
void enableBuzzer(int buzzertime);
void reset(); // resets the controller by performing a jump to address 0


//Do not add code below this line
#endif /* _ARSG_Keyboard_Controller_H_ */
