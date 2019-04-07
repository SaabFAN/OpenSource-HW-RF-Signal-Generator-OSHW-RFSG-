// Do not remove the include below
#include "RF_SigGen_STM32_Version3.h"

bool blink = true;
//The setup function is called once at startup of the sketch
void setup() {
// Add your initialization code here
	Serial.begin(57600);
	Serial.println(F("Display-Init"));
	unsigned char UI_Init = UI.Init();
	switch (UI_Init) {
	case 0x01:
		Serial.println(F("Keyboard: ERROR | Touch: ERROR | UI: OK"));
		break;
	case 0x03:
		Serial.println(F("Keyboard: ERROR | Touch: OK | UI: OK"));
		break;
	case 0x07:
		Serial.println(F("Keyboard: OK | Touch: OK | UI: OK"));
		break;
	case 0x02:
		Serial.println(F("Keyboard: ERROR | Touch: OK | UI: ERROR"));
		break;
	case 0x05:
		Serial.println(F("Keyboard: OK | Touch: ERROR | UI: OK"));
		break;
	case 0x04:
		Serial.println(F("Keyboard: OK | Touch: ERROR | UI: ERROR"));
		break;
	}
	Serial.print(F("SignlControl_Init - "));
	unsigned char SigControlInit = SigCTRL.Init(true, 0x3A);
	switch (SigControlInit) {
	case 0x11:
		Serial.println(F("LF_Source: SUCCESS | HF_Source: SUCCESS"));
		break;
	case 0xF1:
		Serial.println(F("LF_Source: ERROR | HF_Source: SUCCESS"));
		break;
	case 0x1F:
		Serial.println(F("LF_Source: SUCCESS | HF_Source: ERROR"));
		break;
	case 0xFF:
		Serial.println(F("LF_Source: ERROR | HF_Source: ERROR"));
		break;
	}

}

// The loop function is called in an endless loop
void loop() {
	blink = !blink;
	Serial.println(F("Loop-Start"));
	UI.TestScreen(blink);
	Remote.CheckSerial();
	SigCTRL.SetFreq_Man(50000000, true);
	delay(1000);
	Serial.println(F("Loop End"));
	//Add your repeated code here
}
