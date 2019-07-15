/*
 * Explore.cpp
 *
 *  Created on: Jul 6, 2019
 *      Author: voyag
 */

#include "Explore.h"

extern int SYS_ERROR;

Explore::Explore() {
	// TODO Auto-generated constructor stub

}

Explore::~Explore() {
	// TODO Auto-generated destructor stub
}


char Explore::SigSourceExplore() {

}

char Explore::i2c_check(char adr) {
	Wire.beginTransmission(adr);
	return Wire.endTransmission();
}

/*
 * char address;
 Serial.print(F("Scanning i2c-Bus on MB: "));
 address = 0x20;
 if (i2c_check(address) == 0) {
 MB_GPIO_ADR = address;
 Serial.print(F("GPIO found at 0x"));
 Serial.print(address, HEX);
 goto ADC_SCAN;
 }
 address = 0x38;
 if (i2c_check(address) == 0) {
 MB_GPIO_ADR = address;
 Serial.print(F("GPIO found at 0x"));
 Serial.print(address, HEX);
 goto ADC_SCAN;
 } else {
 bitSet(MB_ERROR, 0); // GPIO-Expander not found - Hardware Error! Chip dead, wrong type, or not soldered correctly
 Serial.print(F("ERROR: GPIO-Expander not found!"));
 }
 ADC_SCAN: address = 0x48;
 if (i2c_check(address) == 0) {
 MB_ADC_ADR = address;
 Serial.print(F(" | ADC found at 0x"));
 Serial.print(address, HEX);
 goto DAC_SCAN;
 } else {
 bitSet(MB_ERROR, 1); // ADC not found - Hardware Error! Chip dead, wront type, or not soldered correctly
 Serial.print(F(" | ERROR: ADC not found!"));
 }
 DAC_SCAN: address = 0x60;
 if (i2c_check(address) == 0) {
 MB_DAC_ADR = address;
 Serial.print(F(" | DAC found at 0x"));
 Serial.print(address, HEX);
 goto DONE;
 }
 address = 0x62;
 if (i2c_check(address) == 0) {
 MB_DAC_ADR = address;
 Serial.print(F(" | DAC found at 0x"));
 Serial.print(address, HEX);
 goto DONE;
 }
 address = 0x64;
 if (i2c_check(address) == 0) {
 MB_DAC_ADR = address;
 Serial.print(F(" | DAC found at 0x"));
 Serial.print(address, HEX);
 goto DONE;
 } else {
 bitSet(MB_ERROR, 2); // DAC not found - Hardware Error! Chip dead, wrong type, or not soldered correctly
 Serial.print(F(" | ERROR: DAC not found!"));
 }
 DONE: error = 0x00;
 Serial.println(F(""));
 */
