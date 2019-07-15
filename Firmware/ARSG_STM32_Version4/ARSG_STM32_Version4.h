// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _ARSG_STM32_Version4_H_
#define _ARSG_STM32_Version4_H_

//add your includes for the project ARSG_STM32_Version4 here
#include "Arduino.h"
//#include "UI/UIPrimitives.h"
#include "UI/UIFunctions.h"
#include "Apps/FrequencyControl.h"
#include "Apps/ModulationControl.h"
#include "Apps/AmplitudeControl.h"
#include "Interrupts.h"
#include "RemoteControl.h"
#include "SignalControls/SignalControl.h"
#include "SerialTest.h"


//end of add your includes here


//add your function definitions for the project ARSG_STM32_Version4 here
UI_Functions UI;
RemoteControl Remote;
SignalControl SigCTRL;
SerialTest SerTest;


//Do not add code below this line
#endif /* _ARSG_STM32_Version4_H_ */
