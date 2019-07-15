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
	tft.setCursor(0, 0);
	tft.setTextSize(2);
	tft.setTextColor(AMBER);
	tft.println(F("DISPLAY INIT"));
}

void UI_Primitives::clearScreen() {
	tft.fillScreen(BLUE);
	tft.fillScreen(BLACK);
}

void UI_Primitives::SideButton(dispArea_t number, String button_text,
		bool highlight) {
	int XPosButt = 330;
	int YPosButt = 0;
	tft.setTextSize(2);
	switch (number) {
	case BUTTON_1:
		YPosButt = 30;
		break;
	case BUTTON_2:
		YPosButt = 90;
		break;
	case BUTTON_3:
		YPosButt = 150;
		break;
	case BUTTON_4:
		YPosButt = 210;
		break;
	case BUTTON_5:
		YPosButt = 270;
		break;
	default:
		return;
		break;
	}
	int TextX = XPosButt + 20;
	int TextY = YPosButt + 16;
	int ButtColor = AMBER;
	tft.drawRoundRect(XPosButt, YPosButt, 150, 50, 5, ButtColor);
	XPosButt = XPosButt + 4;
	YPosButt = YPosButt + 3;
	ButtColor = AMBER;
	switch (highlight) {
	case false:
		tft.fillRoundRect(XPosButt, YPosButt, 142, 44, 4, BLACK);
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

void UI_Primitives::FrequencyArea(bool part_update, double disp_frequency,
		bool fm_mod, bool sigpath_auto, unsigned char sigpath_selected) {

}
void UI_Primitives::AmpArea(bool part_update, int amplitude, bool dBm,
		bool atten_auto, unsigned char attenuation) {

}
void UI_Primitives::ModArea(bool part_update, unsigned char mod_mode,
		int mod_strength, unsigned char mod_source, int mod_data) {

}
void UI_Primitives::ArbArea(bool part_update, unsigned char arb_select, int amp,
		bool atten_auto, unsigned char attenuation,
		double repetition_frequency) {

}

void UI_Primitives::BootMessage(String message) {
	Message(AREA_POST, message, false);
}

void UI_Primitives::FreqArea_Data(double disp_freq, unsigned char sigpath) {

}
void UI_Primitives::FreqArea_Outline(bool fm_mod) {	// Draw the Frequency-Area - If FM-Modulation is active, add information that the displayed frequency is the Center Frequency

}
void UI_Primitives::ModArea_Data(unsigned char mod_mode, int mod_strength,
		unsigned char mod_source, int mod_data) { // Information for the modulation-Display. "mod_data"-Value represents modulation-frequency or the hex-value of the digital pattern, depending on the mod_mode. mod_data is ignored when EXTERNAL Modulation is selected.

}
void UI_Primitives::ModArea_Outline(unsigned char mod_mode) {

}
void UI_Primitives::AmpArea_Data(int amp, bool dBm, bool atten_auto,
		unsigned char attenuation) {

}
void UI_Primitives::AmpArea_Outline(bool atten_auto, bool dBm) {

}
void UI_Primitives::ArbArea_Data(unsigned char arb_select, int amp,
		bool atten_auto, unsigned char attenuation,
		double repetition_frequency) {

}
void UI_Primitives::ArbArea_Outline(unsigned char arb_select) {

}

void UI_Primitives::Message(dispArea_t area, String message, bool error) { // Draw a text-line on screen.
	if (area == AREA_POST) {
		tft.println(message);
		return;
	}
	if (area == MESSAGE) {
		Blank (MESSAGE);
		tft.setCursor(0, 0);
		tft.setTextSize(0);
		if (error == true) {
			tft.setTextColor(RED);
		} else {
			tft.setTextColor(AMBER);
		}
		tft.print(message);
	}
}

void UI_Primitives::Blank(dispArea_t area) {
	/*
	 *  Subroutines to simplify Drawing Boxes on the Screen for specific purposes.
	 *  Box-Codes:
	 *  - 0x0000: Fill Screen BLACK
	 *  - 0x0001: Fill Top Icon-Box BLACK
	 *  - 0x000E: Fill Message-Box BLACK
	 *  - 0x000F: Fill the Message-Area for the POST BLACK
	 */
	switch (area) {
	case FULL_SCREEN:
		tft.fillScreen(BLACK);
		break;
	case SYMBOLS:
		tft.fillRect(261, 0, 60, 10, BLACK);
		break;
	case MESSAGE:
		tft.fillRect(0, 0, 260, 10, BLACK);
		break;
	case AREA_POST:
		tft.fillScreen(BLACK);
		break;
	}
	return;
}
