// Do not remove the include below
#include "ARSG_STM32_Version4.h"


bool blink = true;

bool sys_ok = false;
int SYS_ERROR = 0x0000; // Error-Variable to store any Errors - Coding: Byte 0 = Mainboard / Byte 1 = Analog Board / Byte 2 = User Interface (Keyboard, Touch, Display) / Byte 3 = SignalSources

unsigned long main_timer = 0;


#define ADF_INVERTER // Remove this if your ADF-Module is connected directly to the Mainboard. If CS and LE-Signals are inverted via a Inverter-Module, activate this statement.
bool ADF_Inverter = false;

/*
 * SYS_ERROR-Content:
 * Byte 0 = X | X | X | X | GPIO_Expander SignalSourcce | GPIO_Expander Attenuator | VCC Undervolt | X
 * Byte 1 = ? / ? / UNLEVEL / PWR / ALC / ADC / DAC / GPIO_Expander
 * Byte 2 = ? / ? / ? / ? / Display / Rotary / Touch / Keyboard
 * Byte 3 = ? / ? / ? / ? / ? / ? / ? / ?
 */
//The setup function is called once at startup of the sketch
//#define SYSDEBUG
#define SERIAL_WAIT
//#define SPI_SigIntegDebug
void setup() {
#ifdef ADF_INVERTER
	ADF_Inverter = true; // Enable the ADF_Inverter if the define-directive specifies it.
#endif
// Add your initialization code here
	SYS_ERROR = 0x0000;
	sys_ok = false;
	Serial.begin(57600);
#ifdef SERIAL_WAIT
	while(!Serial);
#endif
#ifdef SPI_SigIntegDebug
	delay(2000);
	Serial.print(F("SPI-Datapattern-Test: "));
	delay(5000);
	Serial.println(F("GO!"));
	SerTest.SPI_Datapattern();
#endif
	pinMode(PA8, OUTPUT);
	Serial.println(F("Sys-Init"));
	Serial.println(F("User Interface"));
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
				sys_ok = true;
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
			unsigned char SigControlInit = SigCTRL.Init(true, ADF_Inverter);
			switch (SigControlInit) {
			case 0x11:
				Serial.println(F("LF_Source: SUCCESS | HF_Source: SUCCESS"));
				sys_ok = true;
				break;
			case 0xF1:
				Serial.println(F("LF_Source: ERROR | HF_Source: SUCCESS"));
				sys_ok = false;
				break;
			case 0x1F:
				Serial.println(F("LF_Source: SUCCESS | HF_Source: ERROR"));
				sys_ok = false;
				break;
			case 0xFF:
				Serial.println(F("LF_Source: ERROR | HF_Source: ERROR"));
				sys_ok = false;
				break;
			}
	switch (sys_ok){
	case true:
		SigCTRL.SetFreq_Auto(5000000);
		Serial.println(F("SysInit DONE!"));
		Serial.println(F("Starting Main-App"));
		break;
	case false:
		Serial.println(F("Error during SysInit!"));
		Serial.print(F("Error-Variable = 0x"));
		Serial.println(SYS_ERROR, HEX);
		Serial.println(F("Starting Main App - Attention: System might run unreliable and functions might not work!"));
		break;
	}
SigCTRL.SetFreq_Man(210000000, true);
	Serial.print(F("Boot-Time = "));
	Serial.print(millis(), DEC);
	Serial.println(F("ms"));
	main_timer = millis();
}

const int loop_brake = 1000;// This is a variable that slows down the execution of the loop to prevent flooding the serial-port with data.
// The loop function is called in an endless loop
void loop() {
#ifdef SYSDEBUG
	Serial.println(F("Loop-Start"));
#endif
	Remote.CheckSerial();
//	SigCTRL.SetFreq_Auto(freq);
	if(millis() - main_timer >= loop_brake){
		blink = !blink;
		UI.TestScreen(blink);
		main_timer = millis();
	}
#ifdef SYSDEBUG
	Serial.println(F("Loop End"));
#endif
	//Add your repeated code here
}
