// Define some constants

const byte DATA_ERROR_SIGPATH = 0xA0;


/*
   "DRIVERS" FOR THE HARDWARE ON THE ANALOG-BOARD
*/

// Bitmap for the Attenuator: Latch_Enable(LE) | 32dB | 32dB | 16dB | 8dB | 4dB | 2dB | 1dB
//#define SetAttenDEBUG
//#define SetAttenDEBUG2

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

void SetAGC_LVL(int lvl) {
  byte buf[2];
  buf[1] = lvl;
  buf[0]  = lvl >> 8;
  // FastWrite-Command to set DAC: Bit 15, 14 = 0 (Fast Write), Bit 13, 12 = 0 (DAC Enabled), Bit 11 - 0 = 12bit DAC-Value
  Wire.beginTransmission(PWR_SET_DAC);
  Wire.write(buf[0]);
  Wire.write(buf[1]);
  Wire.endTransmission();
}

void SetAGC_BIAS(int bias) {
  byte buf[2];
  buf[1] = bias;
  buf[0]  = bias >> 8;
  Wire.beginTransmission(AGC_BIAS_DAC);
  Wire.write(buf[0]);
  Wire.write(buf[1]);
  Wire.endTransmission();
}

//SIGPATH_CTRL BITMAP: UNUSED | UNUSED | Select 750MHz LPF  (U2_V2)| Select 1,5GHz LPF (U2_V1)| Select Bypass-Path (U5_V1)| Select Filtered Path (U5_V2)| Select other signal source | Select ADF4351-Module
void SetLPF(int LPF_SEL, bool SelectAD9910) {
  switch (LPF_SEL) {
    case BYPASS:
      SIGPATH_CTRL = 0xE6; // Bitwise OR to PROGRAM Bits 7 to 2
      break;
    case LPF_750:
      SIGPATH_CTRL = 0xDA; // Bitwise OR to PROGRAM Bits 7 to 2
      break;
    case LPF_1500:
      SIGPATH_CTRL = 0xEA; // Bitwise OR to PROGRAM Bits 7 to 2
      break;
    default:
      ErrorMode(DATA_ERROR_SIGPATH, true);
      break;
  }
  switch (SelectAD9910) {
    case false:
      bitClear(SIGPATH_CTRL, 1);
      bitSet(SIGPATH_CTRL, 0);
      break;
    case true:
      bitClear(SIGPATH_CTRL, 0);
      bitSet(SIGPATH_CTRL, 1);
      break;
  }
  Serial.print(F("SIGPATH_CTRL = 0x"));
  Serial.println(SIGPATH_CTRL, HEX);
  Wire.beginTransmission(ANALOG_ADR);
  Wire.write(SIGPATH_CTRL);
  Wire.endTransmission();
}

int ADC_READ(byte ADC_CHANNEL) { // Returns the voltage present at the selected input of the ADC in millivolt
  int ADC_Value = 0;
  switch (ADC_CHANNEL) {
    case ADC_RF_OUT_SENSE:
      ADC_Value = ads.readADC_SingleEnded(ADC_CHANNEL);
      ads.setGain(GAIN_TWO);
      ADC_Value = ads.readADC_SingleEnded(ADC_CHANNEL);
      ADC_Value = ads.readADC_SingleEnded(ADC_CHANNEL);
      break;
    case ADC_RF_LEVEL_SENSE:
      ADC_Value = ads.readADC_SingleEnded(ADC_CHANNEL);
      ads.setGain(GAIN_TWO);
      ADC_Value = ads.readADC_SingleEnded(ADC_CHANNEL);
      ADC_Value = ads.readADC_SingleEnded(ADC_CHANNEL);
  }
  ADC_Value = ads.readADC_SingleEnded(ADC_CHANNEL);
  int ADC_Volt = 0;
  switch (ADC_CHANNEL) {
    case ADC_RF_OUT_SENSE:
      ADC_Volt = ADC_Value * 1; // Scale the ADC-Value to the Vref and the selected gain (Gain = 1): 1bit = 2mV
      break;
    case ADC_RF_LEVEL_SENSE:
      ADC_Volt = ADC_Value * 1; // Scale the ADC-Value to the Vref and the selected gain (Gain = 2): 1bit = 4mV
      break;
  }
  return ADC_Value;
}

