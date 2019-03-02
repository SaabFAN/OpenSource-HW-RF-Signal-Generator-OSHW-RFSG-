// Do not remove the include below
#include "ARSG_Keyboard_Controller.h"

// Constant-definitions

// Define the PINS
const char ROTARY_SW = 11;
const char ROTARY_CLK = 12;
const char ROTARY_DIR = 13;
const char ROTARY_MIN = 1;
const char ROTARY_MAX = 12;

const char SW_AUX_1 = A3;
const char SW_AUX_2 = A2;
const char ARROW_UP = A1;
const char ARROW_DN = A0;

const char INT = 9;

// Global Variables
unsigned long task_time1 = 0;	// Timer-Variable for scanning the keyboard
unsigned long task_time2 = 0;	// Timer for checking the
unsigned long task_time3 = 0;	// Timer for checking the Rotary encoder

// Variables for the Keyboard-data
char current_key = 0xFF;
char old_key = 0xFF;

// Variables for the rotary encoder-data
long current_pos = 6;
long old_pos = 6;

// Variables for the bus-communication
char i2c_cmd;	// Last received command
byte response;

RotaryEncoder encoder(ROTARY_CLK, ROTARY_DIR);
KeyboardScanner keyboard;

//The setup function is called once at startup of the sketch
void setup() {
// Add your initialization code here
	// Configure the PINS
	pinMode(INT, INPUT);
	pinMode(SW_AUX_1, INPUT_PULLUP);
	pinMode(SW_AUX_2, INPUT_PULLUP);
	pinMode(ARROW_UP, INPUT_PULLUP);
	pinMode(ARROW_DN, INPUT_PULLUP);
	pinMode(ROTARY_SW, INPUT_PULLUP);
	encoder.setPosition(0);
	encoder.tick();
	Wire.begin(0x3F);
	Wire.onReceive(receiveEvent);
	Wire.onRequest(respond);
}

// The loop function is called in an endless loop
void loop() {
	while (response == 0xFF) {// Only run these functions while the response is set to 0xFF (data has been transmitted, no new data available)
		if ((millis() - task_time1) >= 50) {
			current_key = keyboard.getKey();
			if (current_key != old_key) {
				response = current_key;
				setInterrupt();
			}
			task_time1 = millis();
		}
		if ((millis() - task_time2) >= 10) {
			encoder.tick();
			current_pos = encoder.getPosition();
			if (current_pos > old_pos) {
				response = 0xC0;
			}
			if (current_pos < old_pos) {
				response = 0xCA;
			}
			if (current_pos < ROTARY_MIN) {
				encoder.setPosition(6);
			}
			if (current_pos > ROTARY_MAX) {
				encoder.setPosition(6);
			}
			old_pos = current_pos;
		}
	}
}

void receiveEvent(int howMany) {
	int i2c_data[howMany];
	int pointer = 0;
	while (Wire.available() != 0) {// Read the data-buffer until nothing is in there.
		pointer++;
		i2c_data[pointer] = Wire.read();
	}
	i2c_cmd = i2c_data[pointer];
	switch(i2c_cmd){
	case 0x10:
		releaseInterrupt();
		old_pos = 6;
		current_pos = 6;
		current_key = 0xFF;
		old_key = 0xFF;
		response = 0xFF;
		break;
	case 0x11:
		setInterrupt();
		delay(250);
		break;
	default:
		break;
	}
}

void respond() {
	switch (i2c_cmd) {
	case 0x00:
		Wire.write(0xFF); // Nothing to report.
		break;
	case 0x10:
		Wire.write(0xA0);
		break;
	case 0x20:
		Wire.write(response);
		response = 0xFF;
		releaseInterrupt();
		break;
	default:
		break;
	}
}

void setInterrupt() {
	digitalWrite(INT, LOW);
}

void releaseInterrupt() {
	pinMode(INT, INPUT);
}
