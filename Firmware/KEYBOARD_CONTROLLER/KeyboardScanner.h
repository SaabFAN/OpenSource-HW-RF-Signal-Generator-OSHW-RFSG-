/*
 * KeyboardScanner.h
 *
 *  Created on: 02.03.2019
 *      Author: voyag
 */

#ifndef KEYBOARDSCANNER_H_
#define KEYBOARDSCANNER_H_

class KeyboardScanner {
public:
	KeyboardScanner();
	virtual ~KeyboardScanner();
	// Public Functions
	int getKey();
private:
	// Private Functions
	void SetHighPin(char pin);
	void SetInterrupt();
	void ReadTouchInt();

	// Private data
	char key;
	char matrix_state;
	char RB0 = 0; // Pin Connected to ROW 0
	char RB1 = 1;	// Pin connected to ROW 1
	char RB2 = 2; // Pin connected to ROW 2
	char RB3 = 3; // Pin connected to ROW 3
};

#endif /* KEYBOARDSCANNER_H_ */
