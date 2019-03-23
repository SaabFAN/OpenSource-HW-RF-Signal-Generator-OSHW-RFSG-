/*
 * SignalControl.h
 *
 *  Created on: 15.03.2019
 *      Author: voyag
 */

#ifndef SIGNALCONTROL_H_
#define SIGNALCONTROL_H_

#include "SignalControls/ADF4351Driver.h"
#include "SignalControls/AD9910Driver.h"

class SignalControl {
public:
	SignalControl();
	virtual ~SignalControl();
	unsigned char Init(bool AD9910_SPIMode, unsigned char GPIO_Addr_ADF4351);
	bool SetFreq_Auto(double freq);
	bool SetFreq_Man(double freq, bool hf_source);	// Set the manually selected signal source to a specified frequency (true = HF-Source, false = LF-Source)
	int GetSigPath();	// Return the currently selected Signal-Path on the analog board.
	bool SigPathMode(bool automatic, bool answer);
};

#endif /* SIGNALCONTROL_H_ */
