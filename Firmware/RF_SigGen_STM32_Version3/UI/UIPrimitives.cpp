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
	tft.setCursor(0,0);
	tft.setTextSize(2);
	tft.setTextColor(AMBER);
	tft.println(F("DISPLAY INIT"));
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

	void UI_Primitives::FrequencyArea(bool part_update, double disp_frequency, bool fm_mod, bool sigpath_auto, unsigned char sigpath_selected){

	}
	void UI_Primitives::AmpArea(bool part_update, int amplitude, bool dBm, bool atten_auto, unsigned char attenuation){

	}
	void UI_Primitives::ModArea(bool part_update, unsigned char mod_mode, int mod_strength, unsigned char mod_source, int mod_data){

	}
	void UI_Primitives::ArbArea(bool part_update, unsigned char arb_select, int amp, bool atten_auto, unsigned char attenuation, double repetition_frequency){

	}

	void UI_Primitives::BootMessage(String message){
		tft.println(message);
	}


	void FreqArea_Data(double disp_freq, unsigned char sigpath){

	}
	void FreqArea_Outline(bool fm_mod){	// Draw the Frequency-Area - If FM-Modulation is active, add information that the displayed frequency is the Center Frequency

	}
	void ModArea_Data(unsigned char mod_mode, int mod_strength, unsigned char mod_source, int mod_data){ // Information for the modulation-Display. "mod_data"-Value represents modulation-frequency or the hex-value of the digital pattern, depending on the mod_mode. mod_data is ignored when EXTERNAL Modulation is selected.

	}
	void ModArea_Outline(unsigned char mod_mode){

	}
	void AmpArea_Data(int amp, bool dBm, bool atten_auto, unsigned char attenuation){

	}
	void AmpArea_Outline(bool atten_auto, bool dBm){

	}
	void ArbArea_Data(unsigned char arb_select, int amp, bool atten_auto, unsigned char attenuation, double repetition_frequency){

	}
	void ArbArea_Outline(unsigned char arb_select){

	}

