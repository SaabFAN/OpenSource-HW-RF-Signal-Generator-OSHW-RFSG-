//RF_Level_Sense-Voltages @ Bias-Current = 1mA. Vf = 250mV:
//NoSignal: 300mV
//-12dBm FILTERED_RF-Power = 863mV
//-2dBm FILTERED_RF-Power = 2082mV
int RF_LEVEL_SENSE;
//RF_OUT_Sense-Voltages @ Bias-Current = 1mA. Vf = 250mV:
//NoSignal: 300mV
//0dBm Output-Power = 363mV
//+15dBm Output-Power = 656mV
int RF_OUT_SENSE;

//volatile byte SIGPATH_CTRL = B00100101; // Controls the Output of the GPIO-Expander on the Analog board.
//BITMAP: UNUSED | UNUSED | Select 750MHz LPF | Select 1,5GHz LPF | Select Bypass-Path | Select Filtered Path | Select other signal source | Select ADF4351-Module

// Function to calculate the Attenuator and DAC-Settings to set the amplitude. Amplitude is expressed as (dBm + 110) x 10 (avoid Floating-Point calculations)
// #define AnalogDebug

void SetAmplitude(int Amplitude) {
  float AmplitudeFine;
  int DAC_OFFSET;
  if (AttenAuto == true) {
    Atten = Amplitude / 10.00;
    Amplitude = Amplitude + 10.00; // Compensation for the 10dB Loss in the Attenuator
    AmplitudeFine = Amplitude - Atten;
    SetAttenuator(Atten);
  }
  else {
    AmplitudeFine = 5.0;
  }
  int AttenBiasCalDataLocation = ((Freq / 25000000UL) * 2) + 0x0F0;
  int PwrOffsetCalDataLocation = (Freq / 25000000UL) * 2;
  if (Freq >= 400000000UL) {
    if (Freq >= 3000000000UL) {
      AGC_ATTEN_BIAS = 0xFFF;
      DAC_OFFSET = ReadNVData(0x0F0);
    }
    else {
      AGC_ATTEN_BIAS = ReadNVData(AttenBiasCalDataLocation);
      DAC_OFFSET = ReadNVData(PwrOffsetCalDataLocation);
    }
    PWR_SET = AmplitudeFine + DAC_OFFSET; // PWR_SET is set to the Correct Value-Value corresponding to the currently set frequency.
#ifdef AnalogDebug
    PWR_SET = 3500;
    AGC_ATTEN_BIAS = 2048;
    Serial.println(F("ANALOG DEBUG-MODE SET!"));
#endif
    SetAGC_LVL(PWR_SET);
    SetAGC_BIAS(AGC_ATTEN_BIAS);
  }
  else {

  }
}

/*
   "DRIVERS" FOR THE HARDWARE ON THE ANALOG-BOARD
*/
//#define SetAttenDEBUG
//#define SetAttenDEBUG2


// Driver for the Attenuator, controlled by one GPIO-Controller
// Bitmap for the Attenuator: Latch_Enable(LE) | 32dB | 32dB | 16dB | 8dB | 4dB | 2dB | 1dB
void SetAttenuator(byte Attenuation) {

#ifdef SetAttenDEBUG
  Serial.print(F("Attenuation = "));
  Serial.print(Attenuation, HEX);
#endif

  if (Attenuation > 63) {
    Attenuation = Attenuation - 32;
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

void DAC_Setup() {
  // Read the Status of the DAC and write it to the serial console for debugging-purposes
  Serial.println(F("Reading all registers of the DAC"));
  Wire.requestFrom(RF_DAC_ADR, 24);
  byte dac_data[24];
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
  /*
    BITMAPs for the bytes during sequential write:
    Byte 0: C2 (0), C1 (1), C0 (0), W1 (1), W2 (0), DAC1 (0), DAC0 (0), !UDAC (0) = Select SEQUENTIAL WRITE (C2, C1, C0, W1, W0), starting at DAC-Channel 0, UPDATE Immediately
      Byte 1: VREF (1), PD1 (0), PD0 (0), Gx (0), 4 bit DAC-Data = Select INTERNAL VREF and ENABLE Outputs with a GAIN of 1, then transmit the 4 most siginificant bits of the Output-Value
      Byte 2: 8bits DAC-Data = Transmit the remaining 8 bits of DAC-Data
  */
  dac_data[0] = 0x50; dac_data[1] = 0x88; dac_data[2] = 0x88;
  Wire.beginTransmission(RF_DAC_ADR);
  Wire.write(dac_data[0]);
  for (int i = 0; i < 3; i++) {
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
  buf[1] = lvl + 0x1000; // add 0x1000 to the value to set the bits that select DAC-Channel 1
  buf[0]  = lvl >> 8;
  // FastWrite-Command to set DAC: Bit 15, 14 = 0 (Fast Write), Bit 13, 12 = 0 (DAC Enabled), Bit 11 - 0 = 12bit DAC-Value
  Wire.beginTransmission(RF_DAC_ADR);
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
  buf[1] = bias;
  buf[0]  = bias >> 8;
  // FastWrite-Command to set DAC: Bit 15, 14 = 0 (Fast Write), Bit 13, 12 = 0 (DAC Enabled), Bit 11 - 0 = 12bit DAC-Value
  Wire.beginTransmission(RF_DAC_ADR);
  Wire.write(buf[0]);
  Wire.write(buf[1]);
  Wire.endTransmission();
}

//SIGPATH_CTRL BITMAP: DIRECT Signal Source | FILTERED or MIXED Signal Source | Select 750MHz LPF  (U2_V2)| Select 1,5GHz LPF (U2_V1)| Select Bypass-Path (U5_V1)| Select Filtered Path (U5_V2)| Select UNMIXED Signal-Path | Select MIXED Signal-Path
void SetLPF(int LPF_SEL, bool SelectAD9910, bool mixpath) {
  switch (SelectAD9910) {
    case true:
      SIGPATH_CTRL = 0xA5; // SELECT the Direct Signal-Source and set the other path up for 750LPF, NOT BYPASSED, NOT MIXED
      goto writeLPFdata;  // Go to the write-command - All other values are irrelevant, as the signal is not passing through the affected signal-switches.
      break;
    case false:
      SIGPATH_CTRL = 0x40; // Bitwise OR to PROGRAM Bits 7 to 2
      break;
  }
  switch (LPF_SEL) {
    case BYPASS:
      SIGPATH_CTRL = SIGPATH_CTRL + 0x28; // ADD value to the signalpath-control to set the select-bits of the filters
      break;
    case LPF_750:
      SIGPATH_CTRL = SIGPATH_CTRL + 0x24;
      break;
    case LPF_1500:
      SIGPATH_CTRL = SIGPATH_CTRL + 0x14;
      break;
    default:
      ErrorMode(DATA_ERROR_SIGPATH, true); // Something else than BYPASS, LPF_750 or LPF_1500 was sent to this function -> Report this error
      break;
  }
  switch (mixpath) {
    case true:
      SIGPATH_CTRL = SIGPATH_CTRL + 0x01;
      break;
    case false:
      SIGPATH_CTRL = SIGPATH_CTRL + 0x02;
      break;
  }
writeLPFdata:
  Serial.print(F("SIGPATH_CTRL = 0x"));
  Serial.println(SIGPATH_CTRL, HEX);
  Wire.beginTransmission(ANALOG_ADR);
  Wire.write(SIGPATH_CTRL);
  Wire.endTransmission();
}

void SetMixpath(bool mixpath) {
  switch (mixpath) {
    case true:

      break;
    case false:

      break;
  }
  Serial.print(F("SIGPATH_CTRL = 0x"));
  Serial.println(SIGPATH_CTRL, HEX);
  Wire.beginTransmission(ANALOG_ADR);
  Wire.write(SIGPATH_CTRL);
  Wire.endTransmission();
}

int ADC_READ(byte ADC_CHANNEL) { // Returns the voltage present at the selected input of the ADC in millivolt
  switch (ADC_CHANNEL) {
    case ADC_RF_OUT_SENSE:
      ads.setGain(GAIN_TWO);
      break;
    case ADC_RF_LEVEL_SENSE:
      ads.setGain(GAIN_ONE);
  }
  int ADC_Value = ads.readADC_SingleEnded(ADC_CHANNEL);
  int ADC_Volt = 0;
  switch (ADC_CHANNEL) {
    case ADC_RF_OUT_SENSE:
      ADC_Volt = ADC_Value * 1; // Scale the ADC-Value to the Vref and the selected gain (Gain = 1): 1bit = 2mV
      break;
    case ADC_RF_LEVEL_SENSE:
      ADC_Volt = ADC_Value * 2; // Scale the ADC-Value to the Vref and the selected gain (Gain = 2): 1bit = 4mV
      break;
  }
  return ADC_Value;
}
