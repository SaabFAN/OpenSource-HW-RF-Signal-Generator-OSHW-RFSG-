/*
 * AttenuatorDriver.h
 *
 *  Created on: 19.02.2019
 *      Author: voyag
 */

#ifndef ATTENUATORDRIVER_H_
#define ATTENUATORDRIVER_H_

#include "Arduino.h"
#include "Wire.h"

#define ATTEN_ADR 0x3E

class Attenuator_Driver {
public:
	Attenuator_Driver();
	virtual ~Attenuator_Driver();
	void SetAttenuator(unsigned char Attenuation);
	unsigned char GetAttenuation();
private:
	unsigned char current_attenuation;
};

#endif /* ATTENUATORDRIVER_H_ */
