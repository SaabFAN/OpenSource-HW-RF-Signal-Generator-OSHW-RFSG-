/*
 * SignalControl.cpp
 *
 *  Created on: 15.03.2019
 *      Author: voyag
 */

#include "SignalControl.h"

extern int SYS_ERROR;

ADF4351Driver HF;
AD9910Driver LF;
AnalogBoardDriver PATH;
AttenuatorDriver ATTEN;
UI_Primitives SigDraw;


SignalControl::SignalControl() {
	// TODO Auto-generated constructor stub
	freq_Old = 0;
	SigCtrl_State = 0;
	SigPath_Auto = true;
}

SignalControl::~SignalControl() {
	// TODO Auto-generated destructor stub
}

unsigned char SignalControl::Init(bool AD9910_SPIMode) {
	Serial.println(F("SignalControl-Init"));
	unsigned char Init_Result = 0;
	Serial.print(F("Check SigSource-GPIO-Address..."));
	char sigSource_i2c_Address = 0x22;
	Wire.beginTransmission(sigSource_i2c_Address);
	if (Wire.endTransmission() == 0) {
		Serial.print(F("Found at 0x"));
		Serial.println(sigSource_i2c_Address, HEX);
		goto SigSource_GPIO_FOUND;
	}
	sigSource_i2c_Address = 0x3A;
	Wire.beginTransmission(sigSource_i2c_Address);
	if (Wire.endTransmission() == 0) {
		Serial.print(F("Found at 0x"));
		Serial.println(sigSource_i2c_Address, HEX);
		goto SigSource_GPIO_FOUND;
	} else {
		Serial.println(F("Critical Error: GPIO-Expander for SigSource on Mainboard not found!"));
		return 0xFF;
	}
	SigSource_GPIO_FOUND: SigDraw.BootMessage(F("SigSource-Setup: "));
	Serial.print(F("Setup ADF4351-SignalSource: "));
	bool ADF_Init = HF.Init(20000000, 1000, PB14, PB13, sigSource_i2c_Address);
	HF.SetMode(0x00);
	HF.SetFrequency(50000000);
	freq_Old = 50000000;
	switch (ADF_Init) {
	case true:
		Init_Result = Init_Result + 0x01;
		Serial.println(F("OK"));
		SigDraw.BootMessage(F("ADF4351 OK"));
		break;
	case false:
		Init_Result = 0x0F;
		Serial.println(F("ERROR"));
		SigDraw.BootMessage(F("ADF4351 ERROR"));
		break;
	}
	int lf_ref_freq = 40000000;
	Serial.print(F("Setup AD9910-SignalSource with RefFrequency = "));
	Serial.print(lf_ref_freq, DEC);
	Serial.println(F("Hz / And Set Output-Frequency to 25 MHz"));
	bool AD9910_Init = LF.Init(lf_ref_freq, sigSource_i2c_Address);
	LF.SetMode('N');
	LF.SetFrequency(25000000);
	switch (AD9910_Init) {
	case true:
		Init_Result = Init_Result + 0x10;
		Serial.println(F("AD9910 Setup OK"));
		SigDraw.BootMessage(F("AD9910 OK"));
		break;
	case false:
		Init_Result = Init_Result + 0xF0;
		Serial.println(F("AD9910 Setup ERROR"));
		SigDraw.BootMessage(F("AD9910 ERROR"));
		if (LF.CheckLock() == false){
			Serial.println(F("AD9910 UNLOCK or OFF"));
		}else{
			Serial.println(F("Unknown Error in AD9910"));
			LF.Dump();
		}
		break;
	}
	Serial.println(F("Setup AnalogBoard:"));
	char Path_Init = 0x00;
	Path_Init = PATH.Init();
	switch (Path_Init) {
	case 0x00:
		PATH.SetLPF(0x75);
		PATH.UpdateAGC(freq_Old);
		Serial.println(F("AnalogBoard - Status:"));
		Serial.print(F("AGC LVL = "));
		Serial.print(PATH.GetLEVEL(), DEC);
		Serial.print(F(" AGC_PWR = "));
		Serial.print(PATH.GetPWR(), DEC);
		Serial.print(F(" VCCD = "));
		Serial.println(PATH.GetVCCD(), DEC);
		Serial.println(F("AnalogBoard OK"));
		SigDraw.BootMessage(F("AnalogBoard OK"));
		break;
	default:
		Serial.println(F("AnalogBoard ERROR"));
		SigDraw.BootMessage(F("AnalogBoard ERROR"));
		break;
	}
	Serial.println(F("Setup Attenuator"));
	switch(ATTEN.Init()){
	case true:
		Serial.println(F("Attenuator OK and set to 0dB"));
		SigDraw.BootMessage(F("Attenuator OK"));
		break;
	case false:
		Serial.println(F("Attenuator ERROR"));
		SigDraw.BootMessage(F("Attenuator OK"));
		break;
	}
	return Init_Result;
}

bool SignalControl::SetFreq_Auto(unsigned long freq) {
	Serial.print(F("FRQ: "));
	Serial.print(freq);
	Serial.println(F(" Hz"));
	bool SelAD9910 = false;
	if (freq == 0) {
		freq = freq_Old; // Set Frequency-Variable to previous value
		return false; // There was an error - False indicates unsuccessful
	} else {
		if (freq >= 4200000000) {
			// TODO Add code to update the SigCtrl_State-Variable with Error-Code for too high Frequency (Out of Range)
			freq = freq_Old; // Set Frequency-Variable to previous value
			return false; // Cancel updating Frequency
		}
		if (freq >= 3000000000) {
			// TODO Add code to update the SigCtrl_State-Variable with Error-Code for uncal high-frequency (UnCal High)
		}
		if (freq >= 400000000UL) {
			Serial.println(F(" - Freq >= 400MHz - "));
			if (freq_Old <= 400000000UL) {
				Serial.print(F(" - Freq_Old <= 400MHZ - "));
				HF.SetMode('N'); // Enable the ADF4351-Output
				Serial.print(F(" - ADF4351 ENABLED - "));
				LF.SetMode('S'); // Disable the AD9910-Output
				Serial.print(F(" - AD9910 DISABLED - "));
			}
			Serial.println(F(" Using ADF4351"));
			HF.SetFrequency(freq);
		} else {
			Serial.println(F(" - Freq <= 400MHz - "));
			if (freq_Old >= 400000000UL) {
				Serial.print(F("FREQ_OLD >= 400MHZ"));
				HF.SetMode('S'); // Disable the ADF4351-Output
				Serial.print(F(" - ADF4351 DISABLED - "));
				LF.SetMode('N'); // Enable the AD9910-Output
				Serial.print(F(" - AD9910 ENABLED - "));
			}
			Serial.print(F(" Using AD9910"));
			LF.SetFrequency(freq);
			Serial.println(F("DONE"));
			SelAD9910 = true;
		}
		freq_Old = freq;
		Serial.print(F("Freq_Old = "));
		Serial.println(freq_Old, DEC);
		// Check if SigPath-Settings are set to AUTO and adjust the Filtering depending on the frequency
		//    SigPathAuto = false; // DEBUG-Statement - Disable for normal operation
		if (freq <= 700000000) {
			PATH.SetLPF(0x75);
		}
		if (freq >= 700000000 && freq <= 1300000000) {
			PATH.SetLPF(0x15);
		} else {
			PATH.SetLPF(0x30);
		}
		PATH.SetSource(SelAD9910);
		PATH.UpdateAGC(freq);
	}
	return true;
}

bool SignalControl::SetFreq_Man(unsigned long freq, bool hf_source) {// Set the manually selected signal source to a specified frequency (true = HF-Source, false = LF-Source)
	switch (hf_source) {
	case true:
		HF.SetFrequency(freq);
		break;
	case false:
		LF.SetFrequency(freq);
		break;
	}
	return true;
}

void SignalControl::SigPathMode(bool automatic) {
	SigPath_Auto = automatic;
}

bool SignalControl::SetSigPath(char filter, bool source, bool mixpath) {
	SetFreq_Man(freq_Old, source);
	PATH.SetLPF(filter);
	char sig_source = 'H';
	switch (source) {
	case true:
		sig_source = 'H';
		break;
	case false:
		sig_source = 'L';
		break;
	}
	switch (mixpath) {
	case true:
		sig_source = 'M';
		break;
	case false:
		break;
	}
	PATH.SetSource(sig_source);
	return true;
}

void SignalControl::SetAmplitude(int db) {
	// Sets the Amplitude of the device by calculating the necessary Attenuation and updating the Attenuator-Controls accordingly.
}

void SignalControl::GetSigControl_State(int pointer) {// Return the current status of the SignalControl-Subsystem
	// TODO: Gather all the data about the Analog Subsystem and write data to the array specified by the pointer

}

char SignalControl::ADF4351_Status() {
	// Return the status of the ADF4351 LD and MUX-Pin.
	char answer = HF.CheckLock() << 1;
	answer = answer + HF.CheckMux();
	return answer;
}

bool SignalControl::ADF4351_LOCK() {
	// Returns if the ADF4351-Output is locked.
	return HF.CheckLock();
}

int SignalControl::AD9910_Status() {
	int answer = LF.CheckLock() << 24;
	return answer;
}
