/*
 * ARSGSigPathConfig.h
 *
 *  Created on: 16.02.2019
 *      Author: voyag
 */
#include "Arduino.h"
#include "Wire.h"
#include "Adafruit_ADS1015.h"

#ifndef ARSGSIGPATHCONFIG_H_
#define ARSGSIGPATHCONFIG_H_



class ARSG_SigPathConfig {
public:
	ARSG_SigPathConfig(byte ANALOG_ADR, byte DAC_ADR, byte ADC_ADR);
	void SetAGC(int Amplitude, long Frequency);
	void SetLPF(byte LPF_SEL, bool SelectAD9910, bool mixpath);
	void SetDAC(bool dac_chan);
	int GetLEVEL();	// Get the current value of the LEVEL-Sense
	int GetPWROUT();	// Get the current value of the PWR_OUT-Sensor
	int GetCAL();// Get the value at the CAL-Input of the ADC (Connect this to a calibration-module)
	int NVRAM_getCALdata(int entry);
	void NVRAM_writeCALdata(int entry, int data);
	virtual ~ARSG_SigPathConfig();
private:
	int ADC_read(byte channel);
	void ADC_setGain(byte gain);
	void ADC_init();
	int NVRAM_calCALentry(int Amplitude, long frequency);
	byte _SIGPATH_CTRL;
	byte _ANALOG_ADR;
	byte _DAC_ADR;
	byte _ADC_ADR;
	byte _NVRAM_AnalogBoard_ADR;
};

#endif /* ARSGSIGPATHCONFIG_H_ */
