/*
 * AD9910Driver.cpp
 *
 *  Created on: 16.03.2019
 *      Author: voyag
 */

#include "AD9910Driver.h"

AD9910Driver::AD9910Driver() {
	// TODO Auto-generated constructor stub

}

AD9910Driver::~AD9910Driver() {
	// TODO Auto-generated destructor stub
}

bool AD9910Driver::Init(unsigned long reference_frequency){

}
void AD9910Driver::SetMode(char mode){
	switch (mode) {
		case 'P':	// Power Down-Mode

			break;
		case 'C':	// ColdStart

			break;
		case 'S':	// Standby-Mode

			break;
		case 'T':	// Test-Mode

			break;
		case 'N':	// Normal-Mode

			break;
		}
}
void AD9910Driver::Configure(int selector, int value){

}
bool AD9910Driver::SetAmplitude(char amplitude){

}
void AD9910Driver::SetFrequency(unsigned long frequency){

}
void AD9910Driver::SetPhase(float phase_angle){

}
bool AD9910Driver::CheckLock(){

}
bool AD9910Driver::CheckMux(){

}
unsigned long AD9910Driver::GetFrequency(){

}
char AD9910Driver::GetAmplitude(){

}
int AD9910Driver::GetPhase(){

}
