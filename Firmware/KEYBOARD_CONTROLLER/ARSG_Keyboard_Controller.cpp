// Do not remove the include below
#include "ARSG_Keyboard_Controller.h"

// Constant-definitions

// Define the PINS
const uint8_t ROTARY_SW = 11;
const uint8_t ROTARY_CLK = 12;
const uint8_t ROTARY_DIR = 13;
const uint8_t ROTARY_MIN = 1;
const uint8_t ROTARY_MAX = 12;

const uint8_t BUZZER = 8;

const uint8_t INT = 9;

const uint8_t LED_GREEN = 6;
const uint8_t LED_RED = 10;

// Global Variables
unsigned long task_time1 = 0;	// Timer-Variable for scanning the keyboard
unsigned long task_time2 = 0;	// Timer for checking the
unsigned long task_time3 = 0;	// Timer for checking the Rotary encoder
uint8_t failmode = 0x00;	// Stores the last detected failure-mode
bool make_noise = true;
bool rotary_enable = true;

// Variables for the Keyboard-data
uint8_t current_key = 0xFF;
uint8_t old_key = 0xFF;

// Variables for the rotary encoder-data
long current_pos = 6;
long old_pos = 6;

// Variables for the bus-communication
uint8_t i2c_cmd;	// Last received command
uint8_t response;

RotaryEncoder encoder(ROTARY_CLK, ROTARY_DIR);
KeyboardScanner keyboard;

//#define DEBUG
//The setup function is called once at startup of the sketch
void setup() {
// Add your initialization code here
	// Configure the PINS
	delay(5000); // Delay to get the serial-monitor up
	Serial.begin(57600);
	Serial.println(F("Keyboard-Controller for the ARSG"));
#ifdef DEBUG
	Serial.println(F("Setting up Pins"));
#endif
	pinMode(INT, OUTPUT);
	digitalWrite(INT, HIGH);
	pinMode(BUZZER, OUTPUT);
	pinMode(LED_RED, OUTPUT);
	pinMode(LED_GREEN, OUTPUT);
	pinMode(ROTARY_SW, INPUT_PULLUP);
	digitalWrite(LED_GREEN, HIGH);
#ifdef DEBUG
	Serial.println(F("Pin-Setup complete"));
	Serial.println(F("Initialize the keyboard-scanner"));
#endif
	keyboard.init();
#ifdef DEBUG
	Serial.println(F("Initialize the rotary-scanner"));
#endif
	encoder.setPosition(0);
	encoder.tick();
#ifdef DEBUG
	Serial.println(F("Initialize the i2c-Bus driver"));
#endif
	Wire.begin(0x3F);
	Wire.onReceive(receiveEvent);
	Wire.onRequest(respond);
#ifdef DEBUG
	Serial.println(F("Make some noise"));
#endif
	enableBuzzer(100);
	response = 0xFF;
	encoder.tick();
	current_pos = encoder.getPosition();
	old_pos = current_pos;
	task_time1 = millis();
	task_time2 = millis();
	task_time3 = millis();
	i2c_cmd = 0x20;
#ifdef DEBUG
	Serial.println(F("Setup complete"));
#endif
}

//#define DEBUG2
// The loop function is called in an endless loop
void loop() {
	if ((millis() - task_time1) >= 50 && response == 0xFF) {
#ifdef DEBUG2
		Serial.println(F("50ms have passed, check the keys"));
#endif
		digitalWrite(LED_GREEN, LOW);
		current_key = keyboard.getKey();
#ifdef DEBUG2
		Serial.print(F("keyboard.getKey = 0x"));
		Serial.println(current_key, HEX);
#endif
		if (current_key != 0xFF) {
			response = current_key;
			setInterrupt();
			if (make_noise == true) {
				enableBuzzer(15);
			}
		}
#ifdef DEBUG2
		Serial.print(F("KeyCheck-Routine set Response to: 0x"));
		Serial.println(response, HEX);
#endif
		task_time1 = millis();
		task_time3 = millis();
		digitalWrite(LED_GREEN, HIGH);
	}
	if ((millis() - task_time2) >= 10 && response == 0xFF
			&& rotary_enable == true) {
#ifdef DEBUG2
		Serial.println(F("10ms passed, checking the Rotary encoder"));
#endif
		digitalWrite(LED_GREEN, LOW);
		encoder.tick();
		current_pos = encoder.getPosition();
		if (current_pos > old_pos) {
			response = 0xC0;
			if (make_noise == true) {
				enableBuzzer(5);
			}
		}
		if (current_pos < old_pos) {
			response = 0xCA;
			if (make_noise == true) {
				enableBuzzer(5);
			}
		}
		if (current_pos < ROTARY_MIN) {
			encoder.setPosition(6);
		}
		if (current_pos > ROTARY_MAX) {
			encoder.setPosition(6);
		}
		old_pos = current_pos;
#ifdef DEBUG2
		Serial.print(F("Encoder-Routine set Response to: 0x"));
		Serial.println(response, HEX);
#endif
		task_time2 = millis();
		task_time3 = millis();
		digitalWrite(LED_GREEN, HIGH);
	}
	if ((millis() - task_time3) >= 2000 && response != 0xFF) {
#ifdef DEBUG2
		Serial.println(F("Timeout! - Discarding data"));
#endif
		response = 0xFF; // Data wasn't fetched, discard data.
		releaseInterrupt();
		task_time3 = millis();
	}
}

//#define i2c_DEBUG
void receiveEvent(int howMany) {
	int i2c_data[howMany];
	int pointer = 0;
	while (Wire.available() != 0) {	// Read the data-buffer until nothing is in there.
		pointer++;
		i2c_data[pointer] = Wire.read();
	}
	i2c_cmd = i2c_data[pointer];
#ifdef i2c_DEBUG
	Serial.println(F("I2C_RECEIVE:"));
	Serial.print(F("Data-Buffer Size: "));
	Serial.println(howMany, DEC);
	int dump_pointer = 0;
	Serial.println(F("DUMPING DATA-BUFFER: "));
	while (dump_pointer <= howMany) {
		Serial.print(F("ENTRY: "));
		Serial.print(dump_pointer, DEC);
		Serial.print(F(" DATA: 0x"));
		Serial.println(i2c_data[dump_pointer], HEX);
		dump_pointer++;
	}
#endif
	switch (i2c_cmd) {
	case 0x10:
		releaseInterrupt();
		old_pos = 6;
		current_pos = 6;
		current_key = 0xFF;
		old_key = 0xFF;
		response = 0xFF;
		i2c_cmd = 0x10;
		break;
	case 0x11:
		setInterrupt();
		delay(250);
		releaseInterrupt();
		i2c_cmd = 0x20;
		break;
	case 0x12:
		make_noise = false;
		break;
	case 0x13:
		make_noise = true;
		break;
	case 0x14:
		rotary_enable = false;
		break;
	case 0x15:
		rotary_enable = true;
		break;
	case 0x20:
		i2c_cmd = 0x20;
		break;
	case 0x30:
		enableBuzzer(50);
		break;
	case 0x31:
		enableBuzzer(100);
		break;
	case 0x32:
		enableBuzzer(250);
		break;
	case 0xB0:
		reset();
		break;
	case 0xFA:
		i2c_cmd = 0xFA;
		response = failmode;
		break;
	case 0xFB:
//		i2c_cmd = 0xFB;
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
		i2c_cmd = 0x20;
		break;
	case 0x20:
		Wire.write(response);
		response = 0xFF;
		releaseInterrupt();
		i2c_cmd = 0x20;
		break;
	case 0xFA:
		Wire.write(response);
		i2c_cmd = 0x20;
		break;
	default:
		break;
	}
}

void setInterrupt() {
#ifdef DEBUG2
	Serial.println(F("Set Interrupt"));
#endif
	digitalWrite(LED_RED, HIGH);
	digitalWrite(INT, LOW);
}

void releaseInterrupt() {
#ifdef DEBUG2
	Serial.println(F("Release Interrupt"));
#endif
	digitalWrite(INT, HIGH);
	digitalWrite(LED_RED, LOW);
}

void enableBuzzer(int buzzertime) {
	digitalWrite(BUZZER, LOW);
	delay(buzzertime);
	digitalWrite(BUZZER, HIGH);
}

void reset() {
	releaseInterrupt();
	old_pos = 6;
	current_pos = 6;
	current_key = 0xFF;
	old_key = 0xFF;
	response = 0xFF;
	i2c_cmd = 0x20;
}
