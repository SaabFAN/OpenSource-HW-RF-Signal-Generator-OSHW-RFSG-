/*
 * SignalControl.h
 *
 *  Created on: 15.03.2019
 *      Author: voyag
 *
 *      Abstraction-Layer for the Signal generating hardware.
 *      Sends the correct commands to the drivers to configure the Signal Sources and the AnalogBoard to route a signal to the output.
 *      Also configures the Attenuator and the Automatic Level Control on the Analog board to adjust the Amplitude.
 *
 */

#ifndef SIGNALCONTROL_H_
#define SIGNALCONTROL_H_

#include "ADF4351Driver.h"
#include "AD9910Driver.h"
#include "AnalogBoardDriver.h"
#include "AttenuatorDriver.h"
#include "../UI/UIPrimitives.h"


class SignalControl: public ADF4351Driver, public AD9910Driver, public AttenuatorDriver, public AnalogBoardDriver {
public:
	SignalControl();
	virtual ~SignalControl();
	unsigned char Init(bool AD9910_SPIMode); // Initializes the Hardware. Note: Address for the GPIO-Expander is found automatically.
	bool SetFreq_Auto(unsigned long freq); // Sets the frequency and automatically configures the SignalPath-Configuration on the AnalogBoard.
	bool SetFreq_Man(unsigned long freq, bool hf_source);	// Set the manually selected signal source to a specified frequency (true = HF-Source, false = LF-Source)
	bool SetSigPath(char filter, bool source, bool mixpath); // Function to manually set the Signal Path-Configuration
	void SigPathMode(bool automatic); // Configures if the SignalPath-Configuration is supposed to run in automatic or manual mode.
	void SetAmplitude(int db); // Sets the Amplitude of the device by calculating the necessary Attenuation and updating the Attenuator-Controls accordingly.
	void GetSigControl_State(int pointer);	// Returns the current state of the SigControl_Subsystem
	char ADF4351_Status(); // Return the status of the ADF4351 LD and MUX-Pin.
	bool ADF4351_LOCK(); // Returns if the ADF4351-Output is locked.
	int AD9910_Status();
private:
	unsigned long freq_Old;
	int SigCtrl_State;
	bool SigPath_Auto;
};

#endif /* SIGNALCONTROL_H_ */
