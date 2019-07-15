
#define DAC_DEBUG
void DAC_Setup() {
  // Read the Status of the DAC and write it to the serial console for debugging-purposes
  byte dac_data[24];
#ifdef DAC_DEBUG
  Serial.println(F("Reading all registers of the DAC"));
  Wire.requestFrom(RF_DAC_ADR, 24);
  byte dac_data_pointer = 0;
  while (Wire.available()) {
    dac_data[dac_data_pointer] = Wire.read();
    dac_data_pointer++;
  }
  Serial.print(F("Channel A: ")); Serial.print(dac_data[0], HEX); Serial.print(F(" ")); Serial.print(dac_data[1], HEX); Serial.print(F(" ")); Serial.println(dac_data[2], HEX);
  Serial.print(F("Channel A EEPROM: ")); Serial.print(dac_data[3], HEX); Serial.print(F(" ")); Serial.print(dac_data[4], HEX); Serial.print(F(" ")); Serial.println(dac_data[5], HEX);

  Serial.print(F("Channel B: ")); Serial.print(dac_data[6], HEX); Serial.print(F(" ")); Serial.print(dac_data[7], HEX); Serial.print(F(" ")); Serial.println(dac_data[8], HEX);
  Serial.print(F("Channel B EEPROM: ")); Serial.print(dac_data[9], HEX); Serial.print(F(" ")); Serial.print(dac_data[10], HEX); Serial.print(F(" ")); Serial.println(dac_data[11], HEX);

  Serial.print(F("Channel C: ")); Serial.print(dac_data[12], HEX); Serial.print(F(" ")); Serial.print(dac_data[13], HEX); Serial.print(F(" ")); Serial.println(dac_data[14], HEX);
  Serial.print(F("Channel C EEPROM: ")); Serial.print(dac_data[15], HEX); Serial.print(F(" ")); Serial.print(dac_data[16], HEX); Serial.print(F(" ")); Serial.println(dac_data[17], HEX);

  Serial.print(F("Channel D: ")); Serial.print(dac_data[18], HEX); Serial.print(F(" ")); Serial.print(dac_data[19], HEX); Serial.print(F(" ")); Serial.println(dac_data[20], HEX);
  Serial.print(F("Channel D EEPROM: ")); Serial.print(dac_data[21], HEX); Serial.print(F(" ")); Serial.print(dac_data[22], HEX); Serial.print(F(" ")); Serial.println(dac_data[23], HEX);

  Serial.println(F("Setting up the DAC for normal Operation: VREF = INTERNAL, GAIN = 1, POWERDOWN-RESISTOR = 100kOhm, OUTPUT-VALUE = 0x888"));
#endif
  /*
    BITMAPs for the bytes during sequential write:
    Byte 0: C2 (0), C1 (1), C0 (0), W1 (1), W2 (0), DAC1 (0), DAC0 (0), !UDAC (0) = Select MULTI-WRITE (C2, C1, C0, W1, W0), starting at DAC-Channel 0, UPDATE Immediately
    Byte 1: VREF (1), PD1 (0), PD0 (0), Gx (0), 4 bit DAC-Data = Select INTERNAL VREF and ENABLE Outputs with a GAIN of 1, then transmit the 4 most siginificant bits of the Output-Value
    Byte 2: 8bits DAC-Data = Transmit the remaining 8 bits of DAC-Data
  */
  dac_data[0] = 0x40; dac_data[1] = 0x88; dac_data[2] = 0x88;
  Wire.beginTransmission(RF_DAC_ADR);
  for (int i = 0; i < 3; i++) {
    Wire.write(dac_data[0] + (i << 1) );  // LEFT-SHIFT i by 1 to use it as the DAC-Channel-Selector and ADD the value to the first byte of the 3-Byte long setup.
    Wire.write(dac_data[1]);
    Wire.write(dac_data[2]);
  }
  Wire.endTransmission();
}

void SetAGC_LVL(int lvl) {
  if (lvl >  0x0FFF) {
    ErrorMode(DAC_OVERFLOW, false);
    lvl = 0x0FFF;
  }
  byte buf[2];
  buf[1] =  (byte) lvl;
  buf[0] = (byte) (lvl >> 8);
  // MultiWrite-Command to set DAC to new value
  Wire.beginTransmission(RF_DAC_ADR);
  Wire.write(0x42);
  Wire.write(buf[0]);
  Wire.write(buf[1]);
  Wire.endTransmission();
}

void SetAGC_BIAS(int bias) {
  if (bias >  0x0FFF) {
    ErrorMode(DAC_OVERFLOW, false);
    bias = 0x0FFF;
  }
  byte buf[2];
  buf[1] = (byte) bias;
  buf[0] = (byte) (bias >> 8);
  // MultiWrite-Command to set DAC to new value
  Wire.beginTransmission(RF_DAC_ADR);
  Wire.write(0x40);
  Wire.write(buf[0]);
  Wire.write(buf[1]);
  Wire.endTransmission();
}

