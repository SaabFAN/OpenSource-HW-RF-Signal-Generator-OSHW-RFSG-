/*
 * AnalogBoardDriver.h
 *
 *  Created on: 16.03.2019
 *      Author: voyag
 */

#ifndef ANALOGBOARDDRIVER_H_
#define ANALOGBOARDDRIVER_H_

#include "Arduino.h"
#include "Wire.h"
#include "Adafruit_ADS1015.h"

class AnalogBoardDriver {
public:
	AnalogBoardDriver();
	virtual ~AnalogBoardDriver();
	char Init();	// Initialize the AnalogBoard with the Default-Values
	void SetLPF(char filter);
	void SetSource(char source);
	void AGC_Mode(bool automatic);
	void UpdateAGC(unsigned long freq);
	uint64_t GetAnalogState();	// Returns 8 bytes, encoding the state of the AnalogBoard-Subsystem: BYTE 0 = Errors | BYTE 1 = SigPath-Switches | BYTES 2 & 3 = BIAS | BYTES 4 & 5 = LEVEL | BYTES 6 & 7 = NVRAM-Address
	bool WriteNVRAM_Byte(char nv_address, char nv_data);
	bool WriteNVRAM_Entry(unsigned long freq, int lvl, int bias);	// Write a Entry to the
	char ReadNVRAM_Byte(char nv_address);	// Retrieve the data at the specified NVRAM-Address
	int ReadNVRAM_Entry(unsigned long freq);	// Retrieve the 4 Bytes of an NVRAM-Entry: BYTES 0 & 1 = LEVEL | BYTES 2 & 3 = BIAS
	void DumpNVRAM_Serial(); // Dump the entire content of the NVRAM to the Serial-Console
	int GetPWR();		// Returns the current value from the PWR-Sensor
	int GetLEVEL();		// Returns the current value from the LEVEL-Sensor
	int GetCAL();		// Returns the current value from an external calibration-sensor
	int GetVCCD();		// Returns the calculated value of VCCD (3.3V supply for digital devices on the analog board)
	bool SetLVL(int lvl_mv);
	bool SetBIAS(int bias_mv);
private:
	void CalDAC();	// calibrate the DAC against the voltage-reference inside the ADC on the analog board
	void UpdateSigPath();
	int CalcEntry(long freq);
	char _ANALOG_ADR;
	int VCCD;
	uint16_t agc_lvl;
	uint16_t agc_bias;
	bool AGC_AUTO;
	bool SelectAD9910;
	bool mixpath;
	char LPF_SEL;
	unsigned char SIGPATH_CTRL;
	const byte ANALOG_ADR = 0x24;
	const byte SIGPATH_ADC = 0x48;
	const byte RF_DAC_ADR = 0x60;
	const short int PWR_SET_CAL_START = 0x000;
	const short int AGC_BIAS_CAL_START = 0x0F2;
	const short int REF_OUT_CAL_NVRAM = 0x200;
	const short int USER_CONFIG_START = 0x400;
	const short int SYSCONFIG_START = 0x05B0;
	const short int SWEEP_SETTINGS_START = 0x600;
	const short int NVRAM_ADR_END = 0x7FF;
	const byte NVRAM_ADDR = 0x50;
	int16_t analog_state;	// Variable to store the state of the Analog-Board Subsystem: BYTE 1 = AGC-ERRORS | BYTE 0 = SIGPATH-ERRORS
	/*
	 * BitMap of analog_state:
	 *
	 * BYTE 0 =
	 * BYTE 1 = NVRAM-Address ERROR | UNUSED | LVL-DAC_NO_RESPONSE | LVL-DAC_OUT_OF_RANGE | LVL-DAC UPDATE OK | BIAS-DAC NO RESPONSE | BIAS-DAC OUT OF RANGE | BIAS-DAC UPDATE OK
	 */
};

#endif /* ANALOGBOARDDRIVER_H_ */
