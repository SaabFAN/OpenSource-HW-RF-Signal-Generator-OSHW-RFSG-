/*
 * ADF4351Driver.h
 *
 *  Created on: 19.02.2019
 *      Author: voyag
 */

#ifndef ADF4351DRIVER_H_
#define ADF4351DRIVER_H_

#include "SPI.h"


class ADF4351_Driver {
public:
	ADF4351_Driver();
	virtual ~ADF4351_Driver();
	bool Init(unsigned long reference_frequency);
	void SetMode(int mode);
	void SetAmplitude(int amplitude);

private:
	unsigned long ADF4351refin = 20000000;      // Reference-Frequency for the ADF4351 in Hz - Reference-Frequency = 10 Mhz (ATTENTION: The ADF4351 methods later require this value to be expressed in kHz!)
	long ChanStep = 1000;		// Channel-Step = 10 kHz (Register-Value = kHz-Value * 100)
	unsigned long Reg[6];		// Array for the ADF4351 Registers
	// Variables from the SetFreq-Function to have them exposed for other functions
	int dBm = 3;				// Variable to configure the output-power of the ADF4351 - Default: +5dBm
	int output_enable = 1;		// 1bit  OutPwr 1=on           0 = off  Outport Null freischalten
	int aux_enable = 1;		// 1bit  aux OutEna 1=on       0 = off  Outport Aux freischalten
	int aux_select = 1;		// 1bit  aux OutSel
	int MTLD = 0;				// 1bit | This controls the "Mute til lock detect"-Function of the chip. It disables the output if the internal PLL has not locked.
	int VcoPwrDown = 0;		// 1bit 1=VCO off
};

#endif /* ADF4351DRIVER_H_ */
