/*
 * AttenuatorDriver.cpp
 *
 *  Created on: 16.03.2019
 *      Author: voyag
 */

#include "AttenuatorDriver.h"

extern int SYS_ERROR;

//#define AttenDEBUG

AttenuatorDriver::AttenuatorDriver() {
	// TODO Auto-generated constructor stub

}

AttenuatorDriver::~AttenuatorDriver() {
	// TODO Auto-generated destructor stub
}

bool AttenuatorDriver::Init() {
	char address = 0x26;
	Serial.print(F("Checking i2c_Address for Attenutor: "));
	Wire.beginTransmission(address);
	if (Wire.endTransmission() == 0) {
		Serial.print(F("Attenuator-Control found at 0x"));
		Serial.print(address, HEX);
		goto atten_done;
	}
	address = 0x3E;
	Wire.beginTransmission(address);
	if (Wire.endTransmission() == 0) {
		Serial.print(F("GPIO found at 0x"));
		Serial.println(address, HEX);
	} else {
		bitSet(SYS_ERROR, 0); // GPIO-Expander not found - Hardware Error! Chip dead, wrong type, or not soldered correctly
		Serial.println(F("ERROR: Attenuator-Control not found!"));
		goto atten_error;
	}
	atten_done: ATTEN_ADR = address;
	SetAtten(0);
return true;
	atten_error: return false;
}

void AttenuatorDriver::SetAtten(char attenuation) {
#ifdef AttenDEBUG
	Serial.print(F("Attenuation = "));
	Serial.print(attenuation, HEX);
#endif
	if (attenuation > 96) {
		attenuation = 95; // Set Attenuation to 95, as attenuation cannot be higher than 95dB
	}
	if (attenuation > 63) {
		attenuation = attenuation - 32; // Subtract 32 and set the "64"-Bit manually, as any attenuation higher than 64 requires bits 5 and 6 to be HIGH
		bitSet(attenuation, 6);
	}
	bitClear(attenuation, 7); // Make sure the LE-Pin is LOW

#ifdef AttenDEBUG
	Serial.print(F(" Attenuation = "));
	Serial.println(attenuation, HEX);
#endif

}

char AttenuatorDriver::ReadAtten() {
	Wire.requestFrom(ATTEN_ADR, 1);
	return Wire.read();
}



void AttenuatorDriver::UpdateGPIO(char data) {
	Wire.beginTransmission(ATTEN_ADR);
	Wire.write(data);
	Wire.endTransmission();
	bitSet(data, 7); // Set LE-Pin HIGH
	Wire.beginTransmission(ATTEN_ADR);
	Wire.write(data);
	Wire.endTransmission();
	bitClear(data, 7); // Set LE-Pin LOW again
	Wire.beginTransmission(ATTEN_ADR);
	Wire.write(data);
	Wire.endTransmission();
}
