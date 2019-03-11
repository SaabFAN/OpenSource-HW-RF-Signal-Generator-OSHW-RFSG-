/*
 * ARSGSigPathConfig.cpp
 *
 *  Created on: 16.02.2019
 *      Author: voyag
 */

#include "../DRIVER_ANALOGBOARD/ARSGSigPathConfig.h"
Adafruit_ADS1015 adsSigPath;
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

ARSG_SigPathConfig::ARSG_SigPathConfig(byte ANALOG_ADR, byte DAC_ADR,
		byte ADC_ADR) {
	// TODO Auto-generated constructor stub
	Wire.begin();
	adsSigPath.begin();
	_ANALOG_ADR = ANALOG_ADR;
	_DAC_ADR = DAC_ADR;
	_ADC_ADR = ADC_ADR;
	_SIGPATH_CTRL = 0xA5;
	_NVRAM_AnalogBoard_ADR = NVRAM_ADDR;
}

ARSG_SigPathConfig::~ARSG_SigPathConfig() {
	// TODO Auto-generated destructor stub
}

#define AnalogDebug

void ARSG_SigPathConfig::SetAGC(int Amplitude, long Frequency) {
// CODE TO SET THE AGC
}

bool ARSG_SigPathConfig::SetLEVEL(int lvl_mv) {
#ifdef DAC_DEBUG
	Serial.print(F("Setting LEVEL-DAC to: "));
	Serial.print(lvl_mv, DEC);
	Serial.println(F(" mV"));
#endif
	if (lvl_mv > 3300) {
#ifdef DAC_DEBUG
		Serial.println(F("DAC-Value out of range! Set to 3300 mV!"));
#endif
		return false;
	}
	int lvl = map(lvl_mv, 0, 3300, 0, 4095);
#ifdef DAC_DEBUG
	Serial.print(F("DAC_Value = 0x"));
	Serial.println(lvl, HEX);
#endif
	byte buf[2];
	buf[1] = (byte) lvl;
	buf[0] = (byte)(lvl >> 8);
	// MultiWrite-Command to set DAC to new value
	Wire.beginTransmission(RF_DAC_ADR);
	Wire.write(0x42);
	Wire.write(buf[0]);
	Wire.write(buf[1]);
	Wire.endTransmission();
}

bool ARSG_SigPathConfig::SetBIAS(int bias_mv) {
#ifdef DAC_DEBUG
	Serial.print(F("Setting BIAS-DAC to: "));
	Serial.print(bias_mv, DEC);
	Serial.println(F(" mV"));
#endif
	if (bias_mv > 6600) {
#ifdef DAC_DEBUG
		Serial.println(F("DAC-Value out of range! Set to 6600 mV!"));
#endif
		return false;
	}
	int bias = map(bias_mv, 0, 6600, 0, 4095);
#ifdef DAC_DEBUG
	Serial.print(F("DAC_Value = 0x"));
	Serial.println(bias, HEX);
#endif
	byte buf[2];
	buf[1] = (byte) bias;
	buf[0] = (byte)(bias >> 8);
	// MultiWrite-Command to set DAC to new value
	Wire.beginTransmission(RF_DAC_ADR);
	Wire.write(0x40);
	Wire.write(buf[0]);
	Wire.write(buf[1]);
	Wire.endTransmission();
}

//SIGPATH_CTRL BITMAP: DIRECT Signal Source | FILTERED or MIXED Signal Source | Select 750MHz LPF  (U2_V2)| Select 1,5GHz LPF (U2_V1)| Select Bypass-Path (U5_V1)| Select Filtered Path (U5_V2)| Select UNMIXED Signal-Path | Select MIXED Signal-Path
void ARSG_SigPathConfig::SetLPF(byte LPF_SEL, bool SelectAD9910, bool mixpath) {
	const byte BYPASS = 0x00;
	const byte LPF_750 = 0x10;
	const byte LPF_1500 = 0x20;
	switch (SelectAD9910) {
	case true:
		_SIGPATH_CTRL = 0xA5; // SELECT the Direct Signal-Source and set the other path up for 750LPF, NOT BYPASSED, NOT MIXED
		goto writeLPFdata;
		// Go to the write-command - All other values are irrelevant, as the signal is not passing through the affected signal-switches.
		break;
	case false:
		_SIGPATH_CTRL = 0x40; // Bitwise OR to PROGRAM Bits 7 to 2
		break;
	}
	switch (LPF_SEL) {
	case BYPASS:
		_SIGPATH_CTRL = _SIGPATH_CTRL + 0x04; // ADD value to the signalpath-control to set the select-bits of the filters
		break;
	case LPF_750:
		_SIGPATH_CTRL = _SIGPATH_CTRL + 0x18;
		break;
	case LPF_1500:
		_SIGPATH_CTRL = _SIGPATH_CTRL + 0x28;
		break;
	default:
		//	ErrorMode(DATA_ERROR_SIGPATH, true); // Something else than BYPASS, LPF_750 or LPF_1500 was sent to this function -> Report this error
		break;
	}
	switch (mixpath) {
	case true:
		_SIGPATH_CTRL = _SIGPATH_CTRL + 0x01;
		break;
	case false:
		_SIGPATH_CTRL = _SIGPATH_CTRL + 0x02;
		break;
	}
	writeLPFdata: Serial.print(F("SIGPATH_CTRL = 0x"));
	Serial.println(_SIGPATH_CTRL, HEX);
	Wire.beginTransmission(_ANALOG_ADR);
	Wire.write(_SIGPATH_CTRL);
	Wire.endTransmission();
}

int ARSG_SigPathConfig::GetLEVEL() {
	// Get the current value of the LEVEL-Sense
	int lvl_data = adsSigPath.readADC_SingleEnded(3);
	return lvl_data;
}

int ARSG_SigPathConfig::GetPWROUT() {
	// Get the current value of the PWR_OUT-Sensor
	int pwr_data = adsSigPath.readADC_SingleEnded(0);
	return pwr_data;
}

int ARSG_SigPathConfig::GetCAL() {
	// Get the value at the CAL-Input of the ADC (Connect this to a calibration-module)
	int cal_data = adsSigPath.readADC_SingleEnded(1);
	return cal_data;
}

int ADC_read(byte channel) {

}

void ADC_setGain(byte gain) {

}

void ADC_init() {

}

int NVRAM_getCALdata(int entry) {
	byte NVRAM_ADDR_OFFSET = entry % 0xFF;// Calculate the i2c_Bus-Address: First 4 bits are always 1010b, the remaining 3 bits are the upper 3 bits of the word-address
	entry = entry - NVRAM_ADDR_OFFSET; // Subtract the highByte from the entry-value
	byte entryLowByte = byte(entry);// and create a byte-variable to prevent the wire.write-function from writing more than one byte
	Wire.beginTransmission(NVRAM_ADDR + NVRAM_ADDR_OFFSET); // Access the NVRAM at the page specied by the 3 last bits of the i2c-Bus-Address
	Wire.write(entryLowByte);	//write the remaining 8 bits of the address
	int NV_DATA;
	Wire.requestFrom(NVRAM_ADDR + NVRAM_ADDR_OFFSET, 2);
	NV_DATA = Wire.read() << 8;
	NV_DATA = NV_DATA + Wire.read();
	return NV_DATA;
}

void NVRAM_writeCALdata(int entry, int data) {
	byte buf[2];
	for (byte i = 0; i < 2; i++) {
		buf[i] = data >> (8 * i);
	}
	// Function to adjust NVRAM_ADDR to access different pages
	byte NVRAM_ADDR_OFFSET = entry % 0xFF;// Calculate the i2c_Bus-Address: First 4 bits are always 1010b, the remaining 3 bits are the upper 3 bits of the word-address
	entry = entry - NVRAM_ADDR_OFFSET; // Subtract the highByte from the entry-value
	byte entryLowByte = byte(entry);// and create a byte-variable to prevent the wire.write-function from writing more than one byte
	Wire.beginTransmission(NVRAM_ADDR + NVRAM_ADDR_OFFSET); // Access the NVRAM at the page specied by the 3 last bits of the i2c-Bus-Address
	Wire.write(entryLowByte);	//write the remaining 8 bits of the address
	for (byte i = 0; i < 2; i++) { // Write 2 bytes to the NVRAM
		Wire.write(buf[i]);
	}
	Wire.endTransmission();
}

int NVRAM_calcCALentry(int Amplitude, long frequency) {

}
