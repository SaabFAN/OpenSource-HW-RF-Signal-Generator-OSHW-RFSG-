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
	ARSG_SigPathConfig(byte ANALOG_ADR);
	virtual ~ARSG_SigPathConfig();
	void SetAGC(int Amplitude, long Frequency);
	void SetLPF(byte LPF_SEL, bool SelectAD9910, bool mixpath);
	bool SetLEVEL(int lvl_mv);
	bool SetBIAS(int bias_mv);
	int GetLEVEL();	// Get the current value of the LEVEL-Sense
	int GetPWROUT();	// Get the current value of the PWR_OUT-Sensor
	int GetCAL();// Get the value at the CAL-Input of the ADC (Connect this to a calibration-module)
	int NVRAM_getCALdata(int entry);
	void NVRAM_writeCALdata(int entry, int data);
	int GetCALPWR();
private:
	int ADC_read(byte channel);
	int GetVCCD();
	void ADC_setGain(byte gain);
	void ADC_init();
	int NVRAM_calcCALentry(int Amplitude, long frequency);
	byte _SIGPATH_CTRL;
	byte _ANALOG_ADR;
	const byte _DAC_ADR = 0x60;
	byte _ADC_ADR;
	byte _NVRAM_AnalogBoard_ADR;
};

#endif /* ARSGSIGPATHCONFIG_H_ */
