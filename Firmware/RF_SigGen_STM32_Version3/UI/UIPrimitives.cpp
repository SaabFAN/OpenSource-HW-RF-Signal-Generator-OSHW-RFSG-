/*
 * UIPrimitives.cpp
 *
 *  Created on: 15.03.2019
 *      Author: voyag
 */

#include "../UI/UIPrimitives.h"

Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST); // Create Display-Object

UI_Primitives::UI_Primitives() {
	// TODO Auto-generated constructor stub

}

UI_Primitives::~UI_Primitives() {
	// TODO Auto-generated destructor stub
}

void UI_Primitives::Init() {
	tft.begin(HX8357D);
	tft.fillScreen(BLACK);
	tft.setRotation(1);
}

void UI_Primitives::clearScreen() {
	tft.fillScreen(BLUE);
	tft.fillScreen(BLACK);
}

void UI_Primitives::SideButton(unsigned char number, String button_text,
		bool highlight) {
	int XPosButt = 330;
	int YPosButt = 0;
	tft.setTextSize(2);
	switch (number) {
	case 1:
		YPosButt = 30;
		break;
	case 2:
		YPosButt = 90;
		break;
	case 3:
		YPosButt = 150;
		break;
	case 4:
		YPosButt = 210;
		break;
	case 5:
		YPosButt = 270;
		break;
	default:
		return;
		break;
	}
	int TextX = XPosButt + 20;
	int TextY = YPosButt + 16;
	int ButtColor = BLACK;
	tft.drawRoundRect(XPosButt, YPosButt, 150, 50, 5, ButtColor);
	XPosButt = XPosButt + 4;
	YPosButt = YPosButt + 3;
	ButtColor = AMBER;
	switch (highlight) {
	case false:
		tft.drawRoundRect(XPosButt, YPosButt, 142, 44, 4, ButtColor);
		tft.setCursor(TextX, TextY);
		tft.setTextColor(ButtColor);
		tft.println(button_text);
		break;
	case true:
		tft.fillRoundRect(XPosButt, YPosButt, 142, 44, 4, ButtColor);
		tft.setCursor(TextX, TextY);
		tft.setTextColor(BLACK);
		tft.println(button_text);
		break;
	}
}

void UI_Primitives::SmallButton(unsigned char location,
		unsigned char button_char) {
// TODO Draw a small 20x20 Pixel Button

}


