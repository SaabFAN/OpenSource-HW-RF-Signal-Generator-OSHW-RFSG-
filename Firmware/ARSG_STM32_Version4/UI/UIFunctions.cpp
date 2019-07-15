/*
 * UIFunctions.cpp
 *
 *  Created on: 15.03.2019
 *      Author: voyag
 */

#include "UIFunctions.h"

UI_Primitives draw;
Adafruit_STMPE610 touch = Adafruit_STMPE610(); // Create TouchController-Object

// Touch-Position Variables
uint16_t x, y;
uint8_t z;
// Adjusted value of the Touch-Coordinates to fit the grid
uint16_t cx, cy;

UI_Functions::UI_Functions() {
	// TODO Auto-generated constructor stub

}

UI_Functions::~UI_Functions() {
	// TODO Auto-generated destructor stub
}

unsigned char UI_Functions::Init() {
	unsigned char UI_init_complete = 0x00;
	draw.Init();
	draw.clearScreen();
	draw.BootMessage(F("Display Init complete"));
	UI_init_complete = 0x01;
	draw.BootMessage(F("Init Touch"));
	bool touch_init_checker = TouchInit();
	if (touch_init_checker == true) {
		bitSet(UI_init_complete, 2);
	}
	draw.BootMessage(F("Touch Init complete"));
	return UI_init_complete;
}

bool UI_Functions::FullUpdate(dispMode_t mode) {

}

bool UI_Functions::PartialUpdate(dispArea_t area, dispMode_t mode) {

}

void UI_Functions::TestScreen(bool highlights) {
//	draw.clearScreen();
	switch (highlights) {
	case true:
		draw.SideButton(BUTTON_1, "test1", false);
		draw.SideButton(BUTTON_2, "test2", true);
		draw.SideButton(BUTTON_3, "test3", false);
		draw.SideButton(BUTTON_4, "test4", true);
		draw.SideButton(BUTTON_5, "test5", false);
		break;
	case false:
		draw.SideButton(BUTTON_1, "test1", true);
		draw.SideButton(BUTTON_2, "test2", false);
		draw.SideButton(BUTTON_3, "test3", true);
		draw.SideButton(BUTTON_4, "test4", false);
		draw.SideButton(BUTTON_5, "test5", true);
		break;
	}
}

void UI_Functions::CheckInputs() {
	ReadTouch();
}

/*
 Touch-Functions
 */



#define TOUCH_DEBUG
bool UI_Functions::TouchInit() {
#ifdef TOUCH_DEBUG
	draw.BootMessage(F("i2c Started, reset STMPE610"));
#endif
	if (!touch.begin()) {
#ifdef TOUCH_DEBUG
		draw.BootMessage(F("COMM-FAILURE"));
#endif
		return false;
	} else {
		touch.writeRegister8(STMPE_INT_STA, 0xFF); // reset all ints
#ifdef TOUCH_DEBUG
		draw.BootMessage(F("OK"));
#endif
		return true;
	}
}

/*
 Touch-Calibration Routine
 */

void UI_Functions::TouchCalibration() {
Serial.println(F("Touch Calibration Not implemented yet"));
// TODO: Implement Touch Calibration
}

void UI_Functions::ReadTouch() {
	cx = 0; // Reset cx and cy to prevent overflow
	cy = 0;
	if (touch.touched()) {
		// read x & y & z;
		while (!touch.bufferEmpty()) {
			//      Serial.print(touch.bufferSize());
			touch.readData(&x, &y, &z);
			//      Serial.print("->(");
			//      Serial.print(x); Serial.print(", ");
			//      Serial.print(y); Serial.print(", ");
			//      Serial.print(z);
			//      Serial.println(")");
			cy = map(x, TS_MINX, TS_MAXX, 320, 0);
			cx = map(y, TS_MINY, TS_MAXY, 0, 480);
		}
		touch.writeRegister8(STMPE_INT_STA, 0xFF); // reset all ints
	}
}

void UI_Functions::Messenger(String message, bool error){
	draw.Message(MESSAGE, message, error);
}
