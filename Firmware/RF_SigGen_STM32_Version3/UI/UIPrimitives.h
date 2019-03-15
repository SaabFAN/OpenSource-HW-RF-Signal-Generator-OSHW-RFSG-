/*
 * UIPrimitives.h
 *	These functions draw the elements of the UI on the screen
 *  Created on: 15.03.2019
 *      Author: voyag
 */
#include <Arduino.h>
#ifndef UIPRIMITIVES_H_
#define UIPRIMITIVES_H_

// Display-Libraries
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Adafruit_HX8357.h>

// Setup-Data for TFT-Display
#define TFT_DC PA1 // Connect TFT_DC to D3
#define TFT_CS PA2  // Connect TFT_CS to D4
#define TFT_RST PA0 //

// Assign HEX-Values to color-names
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define AMBER 0xFDC0



class UI_Primitives {
public:
	UI_Primitives();
	virtual ~UI_Primitives();
	void Init();
	void SideButton(unsigned char number, String button_text, bool highlight);
	void SmallButton(unsigned char location, unsigned char button_char);
	void clearScreen();
};

#endif /* UIPRIMITIVES_H_ */
