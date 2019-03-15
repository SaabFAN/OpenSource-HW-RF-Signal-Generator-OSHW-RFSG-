// Do not remove the include below
#include "RF_SigGen_STM32_Version3.h"


//The setup function is called once at startup of the sketch
void setup() {
// Add your initialization code here
	Serial.begin(57600);
	Serial.println(F("Display-Init"));
	UI.Init();
}

// The loop function is called in an endless loop
void loop() {
	Serial.println(F("Loop-Start"));
	UI.TestScreen();
	delay(1000);
	Serial.println(F("Loop End"));
	//Add your repeated code here
}
