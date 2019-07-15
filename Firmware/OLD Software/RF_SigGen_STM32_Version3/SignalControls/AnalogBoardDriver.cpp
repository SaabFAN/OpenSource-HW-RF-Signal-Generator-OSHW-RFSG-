/*
 * AnalogBoardDriver.cpp
 *
 *  Created on: 16.03.2019
 *      Author: voyag
 */

#include "AnalogBoardDriver.h"

Adafruit_ADS1015 adsSigPath;

AnalogBoardDriver::AnalogBoardDriver() {
	// TODO Auto-generated constructor stub
	_ANALOG_ADR = 0x24; // Default-Address
	AGC_AUTO = true;
	LPF_SEL = 0x75;
	SelectAD9910 = false;
	mixpath = false;
	agc_lvl = 1200;
	agc_bias = 750;
	VCCD = 3300.0; // Default-Value - Needs to be calculated upon initialization
	analog_state = 0x0000;
	SIGPATH_CTRL = 0xA5;
}

AnalogBoardDriver::~AnalogBoardDriver() {
	// TODO Auto-generated destructor stub
}

char AnalogBoardDriver::Init(char address) {
	Wire.begin();
	adsSigPath.begin();
	adsSigPath.setGain(GAIN_TWO);
	char AnalogInit = 0x00;
	if (address != 0) {
		_ANALOG_ADR = address;
	} else {
		_ANALOG_ADR = 0x24; // Default-Address
	}
	CalDAC();
	return AnalogInit;
}

void AnalogBoardDriver::SetLPF(char filter) {
	LPF_SEL = filter;
	UpdateSigPath();
}

void AnalogBoardDriver::SetSource(char source) {
	switch (source) {
	case 'H':
		SelectAD9910 = false;
		mixpath = false;
		break;
	case 'L':
		SelectAD9910 = true;
		mixpath = false;
		break;
	case 'M':
		SelectAD9910 = false;
		mixpath = true;
		break;
	}
	UpdateSigPath();
}

void AnalogBoardDriver::AGC_Mode(bool automatic) {
	AGC_AUTO = automatic;
}

void AnalogBoardDriver::UpdateAGC(unsigned long freq) {
	if (AGC_AUTO == false) {
		return;
	} else {
		if (freq > 3000000000) {
			freq = 3000000000; // Reset Freq-Variable to 3 GHz - AGC only supposed to work up to 3 GHz
		}
		if (freq < 450000000) {
			freq = 450000000; // Reset freq-Variable to 450 MHz - AGC-Corrections only stored down to 450 MHz
		}
		ReadNVRAM_Entry(freq);
		SetLVL(agc_lvl);
		SetBIAS(agc_bias);
	}
}

uint64_t AnalogBoardDriver::GetAnalogState() { // Returns 8 bytes, encoding the state of the AnalogBoard-Subsystem: BYTE 0 & 1 = Errors | BYTE 2 = SigPath-Switches | BYTES 3 & 4 = BIAS | BYTES 5 & 6 = LEVEL
	uint64_t answer = agc_lvl;
	answer = answer << 40;
	answer = answer + (agc_bias << 24);
	answer = answer + (SIGPATH_CTRL << 16);
	answer = answer + analog_state;
	return answer;
}

bool AnalogBoardDriver::WriteNVRAM_Byte(char nv_address, char nv_data) { // Write a Byte at the specified address of NVRAM-Page 0
	Wire.beginTransmission(NVRAM_ADDR); // Access the NVRAM at the page specied by the 3 last bits of the i2c-Bus-Address
	Wire.write(nv_address);	//write the remaining 8 bits of the address
	Wire.write(nv_data);
	return true;
}

bool AnalogBoardDriver::WriteNVRAM_Entry(unsigned long freq, int lvl,
		int bias) { // Write a Entry to the NVRAM
	int entry = CalcEntry(freq);
	if (entry < 1) {
		// TODO Update the analog_state-variable - NVRAM-Adderess WRONG
		return false;
	}
	byte buf[4];
	for (byte i = 0; i < 2; i++) {
		buf[i] = lvl >> (8 * i);
	}
	for (byte i = 2; i < 4; i++) {
		buf[i] = bias >> (8 * i);
	}
	// Function to adjust NVRAM_ADDR to access different pages
	byte NVRAM_ADDR_OFFSET = entry % 0xFF; // Calculate the i2c_Bus-Address: First 4 bits are always 1010b, the remaining 3 bits are the upper 3 bits of the word-address
	entry = entry - NVRAM_ADDR_OFFSET; // Subtract the highByte from the entry-value
	byte entryLowByte = byte(entry); // and create a byte-variable to prevent the wire.write-function from writing more than one byte
	Wire.beginTransmission(NVRAM_ADDR + NVRAM_ADDR_OFFSET); // Access the NVRAM at the page specied by the 3 last bits of the i2c-Bus-Address
	Wire.write(entryLowByte);	//write the remaining 8 bits of the address
	for (byte i = 0; i < 4; i++) { // Write 4 bytes to the NVRAM
		Wire.write(buf[i]);
	}
	Wire.endTransmission();
	return true;
}

char AnalogBoardDriver::ReadNVRAM_Byte(char nv_address) { // Retrieve the data at the specified NVRAM-Address of NVRAM-Page 0
	// TODO Write Subroutine to read ONE Byte from the NVRAM at Address in Page 0
	Wire.beginTransmission(NVRAM_ADDR); // Access the NVRAM at the page specied by the 3 last bits of the i2c-Bus-Address
	Wire.write(nv_address);	//write the remaining 8 bits of the address
	Wire.requestFrom(NVRAM_ADDR, 1);
	char NV_DATA = Wire.read();
	return NV_DATA;
}

int AnalogBoardDriver::ReadNVRAM_Entry(unsigned long freq) { // Retrieve the 4 Bytes of an NVRAM-Entry: BYTES 3 & 2 = BIAS | BYTES 1 & 0 = LEVEL - AND Update AGC-LEVEL and AGC-BIAS Variables
	int entry = CalcEntry(freq);
	if (entry < 1) {
		// TODO Update the analog_state-variable - NVRAM-ADDRESS WRONG
		return 0xFFFF;
	}
	byte NVRAM_ADDR_OFFSET = entry % 0xFF; // Calculate the i2c_Bus-Address: First 4 bits are always 1010b, the remaining 3 bits are the upper 3 bits of the word-address
	entry = entry - NVRAM_ADDR_OFFSET; // Subtract the highByte from the entry-value
	byte entryLowByte = byte(entry); // and create a byte-variable to prevent the wire.write-function from writing more than one byte
	Wire.beginTransmission(NVRAM_ADDR + NVRAM_ADDR_OFFSET); // Access the NVRAM at the page specied by the 3 last bits of the i2c-Bus-Address
	Wire.write(entryLowByte);	//write the remaining 8 bits of the address
	Wire.requestFrom(NVRAM_ADDR + NVRAM_ADDR_OFFSET, 2);
	int lvl = Wire.read() << 8;
	lvl = lvl + Wire.read();
	int bias = Wire.read() << 8;
	bias = bias + Wire.read();
	int NV_DATA = bias << 16;
	NV_DATA = NV_DATA + lvl;
	agc_lvl = lvl;
	agc_bias = bias;
	return NV_DATA;
}

void AnalogBoardDriver::DumpNVRAM_Serial() { // Dump the entire content of the NVRAM to the Serial-Console
// TODO Write Subroutine that dumps the entire NVRAM-Content to the Serial Console in a easily readable format
}

int AnalogBoardDriver::GetPWR() { // Returns the current value from the PWR-Sensor
	int pwr_data = adsSigPath.readADC_SingleEnded(0);
	return pwr_data;
}

int AnalogBoardDriver::GetLEVEL() {	// Returns the current value from the LEVEL-Sensor
	int lvl_data = adsSigPath.readADC_SingleEnded(3);
	return lvl_data;
}

int AnalogBoardDriver::GetCAL() {// Returns the current value from an external calibration-sensor
	int cal_data = adsSigPath.readADC_SingleEnded(1);
	return cal_data;
}

int AnalogBoardDriver::GetVCCD() {// Returns the calculated value of VCCD (3.3V supply for digital devices on the analog board)
	return VCCD;
}

// PRIVATE FUNCTIONS
void AnalogBoardDriver::CalDAC() {
	int dac_cal = 2048;
#ifdef DAC_DEBUG
	Serial.print(F("Setting DAC-CAL-Output to: 0x"));
	Serial.print(dac_cal, HEX);
#endif
	byte buf[2];
	buf[1] = (byte) dac_cal;
	buf[0] = (byte) (dac_cal >> 8);
	// MultiWrite-Command to set DAC to new value
	Wire.beginTransmission(RF_DAC_ADR);
	Wire.write(0x41);
	Wire.write(buf[0]);
	Wire.write(buf[1]);
	Wire.endTransmission();
#ifdef DAC_DEBUG
	Serial.print(F("Wait 250ms to let the voltages stabilize"));
#endif
	delay(250);
	int vccd_raw = adsSigPath.readADC_SingleEnded(2);
	float VCCD_Float = vccd_raw / dac_cal;
	VCCD_Float = VCCD_Float * 4096;
	VCCD = (int)VCCD_Float;
}

bool AnalogBoardDriver::SetLVL(int lvl_mv) {
#ifdef DAC_DEBUG
	Serial.print(F("Setting LEVEL-DAC to: "));
	Serial.print(lvl_mv, DEC);
	Serial.println(F(" mV"));
#endif
	if (lvl_mv > VCCD) {
#ifdef DAC_DEBUG
		Serial.println(F("DAC-Value out of range! Set to 3300 mV!"));
#endif
		return false;
	}
	int lvl = map(lvl_mv, 0, VCCD, 0, 4095);
#ifdef DAC_DEBUG
	Serial.print(F("DAC_Value = 0x"));
	Serial.println(lvl, HEX);
#endif
	byte buf[2];
	buf[1] = (byte) lvl;
	buf[0] = (byte) (lvl >> 8);
	// MultiWrite-Command to set DAC to new value
	Wire.beginTransmission(RF_DAC_ADR);
	Wire.write(0x42);
	Wire.write(buf[0]);
	Wire.write(buf[1]);
	Wire.endTransmission();
	return true;
}

bool AnalogBoardDriver::SetBIAS(int bias_mv) {
#ifdef DAC_DEBUG
	Serial.print(F("Setting BIAS-DAC to: "));
	Serial.print(bias_mv, DEC);
	Serial.println(F(" mV"));
#endif
	int VCCD2 = VCCD * 2;
	if (bias_mv > VCCD2) {
#ifdef DAC_DEBUG
		Serial.println(F("DAC-Value out of range! Set to 6600 mV!"));
#endif
		return false;
	}
	int bias = map(bias_mv, 0, VCCD2, 0, 4095);
#ifdef DAC_DEBUG
	Serial.print(F("DAC_Value = 0x"));
	Serial.println(bias, HEX);
#endif
	byte buf[2];
	buf[1] = (byte) bias;
	buf[0] = (byte) (bias >> 8);
	// MultiWrite-Command to set DAC to new value
	Wire.beginTransmission(RF_DAC_ADR);
	Wire.write(0x40);
	Wire.write(buf[0]);
	Wire.write(buf[1]);
	Wire.endTransmission();
	return true;
}

void AnalogBoardDriver::UpdateSigPath() {
	switch (SelectAD9910) {
	case true:
		SIGPATH_CTRL = 0xA5; // SELECT the Direct Signal-Source and set the other path up for 750LPF, NOT BYPASSED, NOT MIXED
		goto writeLPFdata;
		// Go to the write-command - All other values are irrelevant, as the signal is not passing through the affected signal-switches.
		break;
	case false:
		SIGPATH_CTRL = 0x40; // Bitwise OR to PROGRAM Bits 7 to 2
		break;
	}
	switch (LPF_SEL) {
	case 0x30:
		SIGPATH_CTRL = SIGPATH_CTRL + 0x04; // ADD value to the signalpath-control to set the select-bits of the filters
		break;
	case 0x75:
		SIGPATH_CTRL = SIGPATH_CTRL + 0x18;
		break;
	case 0x15:
		SIGPATH_CTRL = SIGPATH_CTRL + 0x28;
		break;
	default:
		//	ErrorMode(DATA_ERROR_SIGPATH, true); // Something else than BYPASS, LPF_750 or LPF_1500 was sent to this function -> Report this error
		break;
	}
	switch (mixpath) {
	case true:
		SIGPATH_CTRL = SIGPATH_CTRL + 0x01;
		break;
	case false:
		SIGPATH_CTRL = SIGPATH_CTRL + 0x02;
		break;
	}
	writeLPFdata: Serial.print(F("SIGPATH_CTRL = 0x"));
	Serial.println(SIGPATH_CTRL, HEX);
	Wire.beginTransmission(_ANALOG_ADR);
	Wire.write(SIGPATH_CTRL);
	Wire.endTransmission();
}

int AnalogBoardDriver::CalcEntry(long freq) { // calculate the entry-number
	freq = freq - 400000000;
	freq = freq / 50000000;
	return freq;
}
