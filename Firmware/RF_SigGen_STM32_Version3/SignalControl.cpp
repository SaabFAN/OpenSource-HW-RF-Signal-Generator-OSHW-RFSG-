/*
 * SignalControl.cpp
 *
 *  Created on: 15.03.2019
 *      Author: voyag
 */

#include "SignalControl.h"

ADF4351Driver HF;
AD9910Driver LF;

SignalControl::SignalControl() {
	// TODO Auto-generated constructor stub

}

SignalControl::~SignalControl() {
	// TODO Auto-generated destructor stub
}

unsigned char SignalControl::Init(bool AD9910_SPIMode, unsigned char GPIO_Addr_ADF4351){
	unsigned char Init_Result = 0;
	bool ADF_Init = HF.Init(20000000, 1000, PB14, PB13, GPIO_Addr_ADF4351);
	HF.SetMode(0x00);
	HF.SetFrequency(50000000);
	switch (ADF_Init){
	case true:
		Init_Result = Init_Result + 1;
		break;
	case false:
		Init_Result = 0x0F;
		break;
	}
	bool AD9910_Init = false;
	switch (AD9910_Init){
	case true:
		Init_Result = Init_Result + 0x10;
		break;
	case false:
		Init_Result = Init_Result + 0xF0;
		break;
	}
	return Init_Result;
}

bool SignalControl::SetFreq_Auto(double freq){

}

bool SignalControl::SetFreq_Man(double freq, bool hf_source){	// Set the manually selected signal source to a specified frequency (true = HF-Source, false = LF-Source)
	switch (hf_source){
	case true:
		HF.SetFrequency(freq);
		break;
	case false:
		break;
	}
}

int SignalControl::GetSigPath(){	// Return the currently selected Signal-Path on the analog board.

}

bool SignalControl::SigPathMode(bool automatic, bool answer){

}

