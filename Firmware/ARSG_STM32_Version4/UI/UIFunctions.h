/*
 * UIFunctions.h
 *	High level Functions of the UI (Draw the screen, react to inputs, etc.)
 *  Created on: 15.03.2019
 *      Author: voyag
 */

#ifndef UIFUNCTIONS_H_
#define UIFUNCTIONS_H_

#include "Arduino.h"
#include "../UI/UIPrimitives.h"
#include <Adafruit_STMPE610.h>


// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 3790
#define TS_MAXX 250
#define TS_MINY 3800
#define TS_MAXY 250

typedef enum {
	FREQ_ENTER = 0xF0, // Enter Frequency-Mode
	AMP_ENTER = 0xA0, // Enter Amplitude-Mode
	PHASE_ENTER = 0xD0,
	MOD_SELECT = 0xC0,
	MOD_FM = 0xC1,
	MOD_FSK = 0xC2,
	MOD_AM = 0xC3,
	MOD_ASK = 0xC4,
	MOD_SOURCE = 0xCC,
	MOD_DATA = 0xDD
}dispMode_t;

class UI_Functions {
public:
	UI_Functions();
	virtual ~UI_Functions();
	unsigned char Init();
	bool FullUpdate(dispMode_t mode);	// Updates the whole screen, according to selected mode
	bool PartialUpdate(dispArea_t area, dispMode_t mode);	// Updates part of the screen, defined by the selected area
	void TestScreen(bool highlights);	// Displays a Test-screen
	void CheckInputs();
	void Messenger(String message, bool error);	// Write a message to the top of the screen
private:
	bool TouchInit();
	void TouchCalibration();
	void ReadTouch();
	void CalcPixelPos();
};



#endif /* UIFUNCTIONS_H_ */
