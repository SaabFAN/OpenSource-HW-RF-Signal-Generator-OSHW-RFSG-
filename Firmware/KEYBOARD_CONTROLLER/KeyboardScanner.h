/*
 * KeyboardScanner.h
 *
 *  Created on: 02.03.2019
 *      Author: voyag
 */

#ifndef KEYBOARDSCANNER_H_
#define KEYBOARDSCANNER_H_
#include "Arduino.h"

#define RB0 4
#define RB1 5
#define RB2 2
#define RB3 3
#define SW_AUX_1 A3
#define SW_AUX_2 A2
#define ARROW_UP A1
#define ARROW_DN A0

class KeyboardScanner {
public:
	KeyboardScanner();
	virtual ~KeyboardScanner();
	// Public Functions
	void init();
	int getKey();
private:
	// Private Functions
	void SetLOWPin(unsigned char pin);
	unsigned char decode(unsigned char decode_data, unsigned char row);

	// Private data
	unsigned char key;
	unsigned char matrix_state[4];
};

#endif /* KEYBOARDSCANNER_H_ */
