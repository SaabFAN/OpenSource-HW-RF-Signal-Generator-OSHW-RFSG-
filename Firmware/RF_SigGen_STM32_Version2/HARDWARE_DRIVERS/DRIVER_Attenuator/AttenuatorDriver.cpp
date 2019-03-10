/*
 * AttenuatorDriver.cpp
 *
 *  Created on: 19.02.2019
 *      Author: voyag
 */

#include "AttenuatorDriver.h"

Attenuator_Driver::Attenuator_Driver() {
	// TODO Auto-generated constructor stub
current_attenuation = 0;
}

Attenuator_Driver::~Attenuator_Driver() {
	// TODO Auto-generated destructor stub
}

#define SetAttenDEBUG

void Attenuator_Driver::SetAttenuator(unsigned char Attenuation) {

#ifdef SetAttenDEBUG
  Serial.print(F("Attenuation = "));
  Serial.print(Attenuation, HEX);
#endif
  current_attenuation = Attenuation;
if( Attenuation > 96){
  Attenuation = 95; // Set Attenuation to 95, as there's no
}
  if (Attenuation > 63) {
    Attenuation = Attenuation - 32; // Subtract 32 and set the "64"-Bit manually, as any attenuation higher than 64 requires bits 5 and 6 to be HIGH
    bitSet(Attenuation, 6);
  }
  bitClear(Attenuation, 7); // Make sure the LE-Pin is LOW

#ifdef SetAttenDEBUG
  Serial.print(F("Attenuation = "));
  Serial.println(Attenuation, HEX);
#endif

  Wire.beginTransmission(ATTEN_ADR);
  Wire.write(Attenuation);
  Wire.endTransmission();
  bitSet(Attenuation, 7); // Set LE-Pin HIGH
  Wire.beginTransmission(ATTEN_ADR);
  Wire.write(Attenuation);
  Wire.endTransmission();
  bitClear(Attenuation, 7); // Set LE-Pin LOW again
  Wire.beginTransmission(ATTEN_ADR);
  Wire.write(Attenuation);
  Wire.endTransmission();
}

unsigned char Attenuator_Driver::GetAttenuation(){
	return current_attenuation;
}
