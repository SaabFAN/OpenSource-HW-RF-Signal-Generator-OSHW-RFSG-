/*
 * AttenuatorDriver.h
 *
 *  Created on: 16.03.2019
 *      Author: voyag
 */

#ifndef ATTENUATORDRIVER_H_
#define ATTENUATORDRIVER_H_

#include "Wire.h"
#include "../Apps/Explore.h"

class AttenuatorDriver {
public:
	AttenuatorDriver();
	virtual ~AttenuatorDriver();
	bool Init();
	void SetAtten(char attenuation);
	char ReadAtten();
private:
	char ATTEN_ADR;
	void UpdateGPIO(char data);
};

#endif /* ATTENUATORDRIVER_H_ */
