/*
 * SerialTest.h
 *
 *  Created on: Jul 8, 2019
 *      Author: voyag
 */

#ifndef SERIALTEST_H_
#define SERIALTEST_H_

#include "Arduino.h"
#include "SPI.h"
#include "Wire.h"

class SerialTest {
public:
	SerialTest();
	virtual ~SerialTest();
	void SPI_Datapattern();
};

#endif /* SERIALTEST_H_ */
