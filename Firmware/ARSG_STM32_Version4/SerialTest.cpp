/*
 * SerialTest.cpp
 *
 *  Created on: Jul 8, 2019
 *      Author: voyag
 */

#include "SerialTest.h"

#define SPI_SPEED 24000000

SerialTest::SerialTest() {
	// TODO Auto-generated constructor stub

}

SerialTest::~SerialTest() {
	// TODO Auto-generated destructor stub
}

void SerialTest::SPI_Datapattern() {
	SPI.begin();
	Serial.print(F("SPI Init"));
	unsigned char datapattern[17] = { 15, 219, 238, 22, 58, 84, 130, 168, 121,
			234, 129, 242, 129, 188, 226, 31 };
	Serial.print(F("Datapattern populated"));
	Serial.print(F("SPI-Hardware configured, now run the data-transfers"));
	pinMode(PA8, OUTPUT);
	SPI.beginTransaction(SPISettings(SPI_SPEED, MSBFIRST, SPI_MODE0));
	while (1) {
		digitalWrite(PA8, LOW);
		SPI.transfer(datapattern[0]);
		SPI.transfer(datapattern[1]);
		SPI.transfer(datapattern[2]);
		SPI.transfer(datapattern[3]);
		SPI.transfer(datapattern[4]);
		SPI.transfer(datapattern[5]);
		SPI.transfer(datapattern[6]);
		SPI.transfer(datapattern[7]);
		SPI.transfer(datapattern[8]);
		SPI.transfer(datapattern[9]);
		SPI.transfer(datapattern[10]);
		SPI.transfer(datapattern[11]);
		SPI.transfer(datapattern[12]);
		SPI.transfer(datapattern[13]);
		SPI.transfer(datapattern[14]);
		SPI.transfer(datapattern[15]);
		SPI.transfer(datapattern[16]);
		digitalWrite(PA8, HIGH);
	}
}
