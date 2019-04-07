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
#include "SignalControls/AnalogBoardDriver.h"

class SignalControl {
public:
	SignalControl();
	virtual ~SignalControl();
	unsigned char Init(bool AD9910_SPIMode, unsigned char GPIO_Addr_ADF4351);
	bool SetFreq_Auto(unsigned long freq);
	bool SetFreq_Man(unsigned long freq, bool hf_source);	// Set the manually selected signal source to a specified frequency (true = HF-Source, false = LF-Source)
	bool SetSigPath(char filter, bool source, bool mixpath);
	void SigPathMode(bool automatic);
	uint64_t GetSigControl_State();	// Returns the current state of the SigControl_Subsystem
private:
	unsigned long freq_Old;
	int SigCtrl_State;
	bool SigPath_Auto;
};

#endif /* SIGNALCONTROL_H_ */
