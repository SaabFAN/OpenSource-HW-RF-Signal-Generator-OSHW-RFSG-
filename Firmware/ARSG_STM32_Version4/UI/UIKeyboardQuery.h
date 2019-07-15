/*
 * UIKeyboardQuery.h
 *	Read keyboard-inputs and report back to the UI-Functions
 *  Created on: 15.03.2019
 *      Author: voyag
 */

#ifndef UIKEYBOARDQUERY_H_
#define UIKEYBOARDQUERY_H_

class UI_KeyboardQuery {
public:
	UI_KeyboardQuery();
	virtual ~UI_KeyboardQuery();
	unsigned char GetKey();
	unsigned char GetRotary();
	bool RotaryPresent();
};

#endif /* UIKEYBOARDQUERY_H_ */
