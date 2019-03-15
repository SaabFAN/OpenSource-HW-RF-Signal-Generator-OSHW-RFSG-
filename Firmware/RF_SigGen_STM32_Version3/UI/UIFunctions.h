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


class UI_Functions {
public:
	UI_Functions();
	virtual ~UI_Functions();
	bool Init();
	bool FullUpdate(unsigned char mode);	// Updates the whole screen, according to selected mode
	bool PartialUpdate(unsigned char area);	// Updates part of the screen, defined by the selected area
	void TestScreen();	// Displays a Test-screen
};

#endif /* UIFUNCTIONS_H_ */
