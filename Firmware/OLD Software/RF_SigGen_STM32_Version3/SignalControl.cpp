/*
 * SignalControl.cpp
 *
 *  Created on: 15.03.2019
 *      Author: voyag
 */

#include "SignalControl.h"

ADF4351Driver HF;
AD9910Driver LF;
AnalogBoardDriver PATH;

SignalControl::SignalControl() {
	// TODO Auto-generated constructor stub
	freq_Old = 0;
	SigCtrl_State = 0;
	SigPath_Auto = true;
}

SignalControl::~SignalControl() {
	// TODO Auto-generated destructor stub
}

unsigned char SignalControl::Init(bool AD9910_SPIMode,
		unsigned char GPIO_Addr_ADF4351) {
	unsigned char Init_Result = 0;
	bool ADF_Init = HF.Init(20000000, 1000, PB14, PB13, GPIO_Addr_ADF4351);
	HF.SetMode(0x00);
	HF.SetFrequency(50000000);
	freq_Old = 50000000;
	switch (ADF_Init) {
	case true:
		Init_Result = Init_Result + 1;
		break;
	case false:
		Init_Result = 0x0F;
		break;
	}
	int lf_ref_freq = 40000000;
	bool AD9910_Init = LF.Init(lf_ref_freq);
	switch (AD9910_Init) {
	case true:
		Init_Result = Init_Result + 0x10;
		break;
	case false:
		Init_Result = Init_Result + 0xF0;
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

bool SignalControl::SetSigPath(char filter, bool source, bool mixpath){
	SetFreq_Man(freq_Old, source);
	PATH.SetLPF(filter);
	char sig_source = 'H';
	switch (source){
	case true:
		sig_source = 'H';
		break;
	case false:
		sig_source = 'L';
		break;
	}
	switch(mixpath){
	case true:
		sig_source = 'M';
		break;
	case false:
		break;
	}
	PATH.SetSource(sig_source);
return true;
}

uint64_t SignalControl::GetSigControl_State() {	// Return the current status of the SignalControl-Subsystem
	return PATH.GetAnalogState();
}
