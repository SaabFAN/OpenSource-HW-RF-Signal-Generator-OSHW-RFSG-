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
//#define KBD_DEBUG
void KeyboardScanner::init() {
	pinMode(RB0, INPUT_PULLUP);
	pinMode(RB1, INPUT_PULLUP);
	pinMode(RB2, INPUT_PULLUP);
	pinMode(RB3, INPUT_PULLUP);
	pinMode(ARROW_UP, INPUT_PULLUP);
	pinMode(ARROW_DN, INPUT_PULLUP);
	pinMode(SW_AUX_1, INPUT_PULLUP);
	pinMode(SW_AUX_2, INPUT_PULLUP);
}

int KeyboardScanner::getKey() {
	key = 0xFF;
// TODO Scan the Keyboard-Matrix and decode the key
	pinMode(RB0, INPUT_PULLUP);
	pinMode(RB1, INPUT_PULLUP);
	pinMode(RB2, INPUT_PULLUP);
	pinMode(RB3, INPUT_PULLUP);
	pinMode(ARROW_UP, INPUT_PULLUP);
	pinMode(ARROW_DN, INPUT_PULLUP);
	pinMode(SW_AUX_1, INPUT_PULLUP);
	pinMode(SW_AUX_2, INPUT_PULLUP);
	if (digitalRead(ARROW_DN) == false) {
		key = 0xAD;
		return key;
	}
	if (digitalRead(ARROW_UP) == false) {
		key = 0xAA;
		return key;
	}
	if (digitalRead(SW_AUX_1) == false) {
		key = 0xA5;
		return key;
	}
	if (digitalRead(SW_AUX_2) == false) {
		key = 0xA6;
		return key;
	}
//	const unsigned char mask = 0x07;
	SetLOWPin(RB0);
	matrix_state[RB0] = PIND;
	//	matrix_state[RB1] &= mask;
	SetLOWPin(RB1);
	matrix_state[RB1] = PIND;
	//	matrix_state[RB1] &= mask;
	SetLOWPin(RB2);
	matrix_state[RB2] = PIND;
	//	matrix_state[RB2] &= mask;
	SetLOWPin(RB3);
	matrix_state[RB3] = PIND;
	SetLOWPin(0xFF);
	//	matrix_state[RB3] &= mask;
#ifdef KBD_DEBUG
	Serial.print(F("Matrix_State[RB0] = 0x"));
	Serial.print(matrix_state[RB0], HEX);
	Serial.print(F(" Matrix_State[RB1] = 0x"));
	Serial.print(matrix_state[RB1], HEX);
	Serial.print(F(" Matrix_State[RB2] = 0x"));
	Serial.print(matrix_state[RB2], HEX);
	Serial.print(F(" Matrix_State[RB3] = 0x"));
	Serial.println(matrix_state[RB3], HEX);
#endif
	key = decode(matrix_state[RB0], RB0);
	if (key != 0xFF) {
		return key;
	}
	key = decode(matrix_state[RB1], RB1);
	if (key != 0xFF) {
		return key;
	}
	key = decode(matrix_state[RB2], RB2);
	if (key != 0xFF) {
		return key;
	}

	key = decode(matrix_state[RB3], RB3);
	if (key != 0xFF) {
		return key;
	}
	return key;
}

void KeyboardScanner::SetLOWPin(unsigned char pin) {
#ifdef KBD_DEBUG
	Serial.print(F("Setting PIN D"));
	Serial.print(pin);
	Serial.print(F(" to LOW - PIND = 0x"));
	Serial.println(PIND, HEX);
#endif

	pinMode(RB0, INPUT_PULLUP);
	pinMode(RB1, INPUT_PULLUP);
	pinMode(RB2, INPUT_PULLUP);
	pinMode(RB3, INPUT_PULLUP);
	if (pin != 0xFF) {
		pinMode(pin, OUTPUT);
		digitalWrite(pin, LOW);
	}
}

/*	Keyboard-Matrix:
 * 	7 [0x07] 8 [0x08] 9 [0x09]		MHZ / +dBm 	[0xA1]		AUX KEY 2	[0xA5]	PowerButton	[0xA6]
 * 	4 [0x04] 5 [0x05] 6 [0x06]		kHz / -dBm	[0xA2]
 * 	1 [0x01] 2 [0x02] 3 [0x03]		Hz / mV	[0xA3]
 * 	0 [0x00] . [0x10] BACK [0x20]	ENTER	[0xA4]			ARROW DOWN	[0xAD]	ARROW UP	[0xAA]
 * */

//#define DECODE_DEBUG
#define TELL_KEY
unsigned char KeyboardScanner::decode(unsigned char decode_data,
		unsigned char row) {
	unsigned char decoded_key = 0x00;
	// rearrange the data
	bool column_1 = bitRead(decode_data, 4);
	bool column_2 = bitRead(decode_data, 5);
	bool column_3 = bitRead(decode_data, 2);
	bool column_4 = bitRead(decode_data, 3);
	decode_data = 0x00;
	bitWrite(decode_data, 0, column_1);
	bitWrite(decode_data, 1, column_2);
	bitWrite(decode_data, 2, column_3);
	bitWrite(decode_data, 3, column_4);
#ifdef DECODE_DEBUG
	Serial.print(F("Active ROW-Pin = D"));
	Serial.print(row);
	Serial.print(F(" decode_data = 0x"));
	Serial.print(decode_data, HEX);
	Serial.print(F(" Decodes to: 0x"));
#endif
	switch (row) {
	case RB0:
		switch (decode_data) {
		case 0x02:
			decoded_key = 0x07;
			break;
		case 0x04:
			decoded_key = 0x08;
			break;
		case 0x06:
			decoded_key = 0x09;
			break;
		case 0x08:
			decoded_key = 0xA1;
			break;
		default:
			decoded_key = 0xFF;
			break;
		}
		break;
	case RB1:
		switch (decode_data) {
		case 0x01:
			decoded_key = 0x04;
			break;
		case 0x05:
			decoded_key = 0x05;
			break;
		case 0x04:
			decoded_key = 0x06;
			break;
		case 0x09:
			decoded_key = 0xA2;
			break;
		default:
			decoded_key = 0xFF;
			break;
		}
		break;
	case RB2:
		switch (decode_data) {
		case 0x03:
			decoded_key = 0x01;
			break;
		case 0x01:
			decoded_key = 0x02;
			break;
		case 0x02:
			decoded_key = 0x03;
			break;
		case 0x09:
			decoded_key = 0xA3;
			break;
		default:
			decoded_key = 0xFF;
			break;
		}
		break;
	case RB3:
		switch (decode_data) {
		case 0x03:
			decoded_key = 0x00;
			break;
		case 0x05:
			decoded_key = 0x10;
			break;
		case 0x06:
			decoded_key = 0x20;
			break;
		case 0x01:
			decoded_key = 0xA4;
			break;
		default:
			decoded_key = 0xFF;
			break;
		}
		break;
	}
#ifdef DECODE_DEBUG
	Serial.println(decoded_key, HEX);
#endif
#ifdef TELL_KEY
	if (decoded_key != 0xFF) {
		Serial.print(F("DECODED KEY = 0x"));
		Serial.println(decoded_key, HEX);
	}
#endif
	return decoded_key;
}
