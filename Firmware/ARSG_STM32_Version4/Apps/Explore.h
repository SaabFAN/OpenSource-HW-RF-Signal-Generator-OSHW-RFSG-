/*
 * Explore.h
 *
 *  Created on: Jul 6, 2019
 *      Author: voyag
 */

#ifndef EXPLORE_H_
#define EXPLORE_H_

#include "Wire.h"
#include "SPI.h"

class Explore {
public:
	Explore();
	virtual ~Explore();
	char SigSourceExplore();
	char i2c_check(char adr);
};

#endif /* EXPLORE_H_ */
