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


class UI_Functions {
public:
	UI_Functions();
	virtual ~UI_Functions();
	unsigned char Init();
	bool FullUpdate(unsigned char mode);	// Updates the whole screen, according to selected mode
	bool PartialUpdate(unsigned char area);	// Updates part of the screen, defined by the selected area
	void TestScreen(bool highlights);	// Displays a Test-screen
	void CheckInputs();
private:
	bool TouchInit();
	void TouchCalibration();
	void ReadTouch();
	void CalcPixelPos();
};

#endif /* UIFUNCTIONS_H_ */
