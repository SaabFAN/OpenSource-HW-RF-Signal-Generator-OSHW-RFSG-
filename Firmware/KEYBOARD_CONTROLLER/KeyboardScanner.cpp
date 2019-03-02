/*
 * KeyboardScanner.cpp
 *
 *  Created on: 02.03.2019
 *      Author: voyag
 */

#include "KeyboardScanner.h"

KeyboardScanner::KeyboardScanner() {
	// TODO Auto-generated constructor stub
	key = 0xFF;
}

KeyboardScanner::~KeyboardScanner() {
	// TODO Auto-generated destructor stub
}

int KeyboardScanner::getKey() {
// TODO Scan the Keyboard-Matrix and decode the key
	return key;
}
