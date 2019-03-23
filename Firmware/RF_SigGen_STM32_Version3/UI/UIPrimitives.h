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
	void FrequencyArea(bool part_update, double disp_frequency, bool fm_mod, bool sigpath_auto, unsigned char sigpath_selected);
	void AmpArea(bool part_update, int amplitude, bool dBm, bool atten_auto, unsigned char attenuation);
	void ModArea(bool part_update, unsigned char mod_mode, int mod_strength, unsigned char mod_source, int mod_data);
	void ArbArea(bool part_update, unsigned char arb_select, int amp, bool atten_auto, unsigned char attenuation, double repetition_frequency);
	void BootMessage(String message);
private:
	void FreqArea_Data(double disp_freq, unsigned char sigpath);
	void FreqArea_Outline(bool fm_mod);	// Draw the Frequency-Area - If FM-Modulation is active, add information that the displayed frequency is the Center Frequency
	void ModArea_Data(unsigned char mod_mode, int mod_strength, unsigned char mod_source, int mod_data); // Information for the modulation-Display. "mod_data"-Value represents modulation-frequency or the hex-value of the digital pattern, depending on the mod_mode. mod_data is ignored when EXTERNAL Modulation is selected.
	void ModArea_Outline(unsigned char mod_mode);
	void AmpArea_Data(int amp, bool dBm, bool atten_auto, unsigned char attenuation);
	void AmpArea_Outline(bool atten_auto, bool dBm);
	void ArbArea_Data(unsigned char arb_select, int amp, bool atten_auto, unsigned char attenuation, double repetition_frequency);
	void ArbArea_Outline(unsigned char arb_select);
	double display_freq;
};

#endif /* UIPRIMITIVES_H_ */
