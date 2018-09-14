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
#define AnalogDebug
void SetAmplitude(int Amplitude) {
  float AmplitudeFine;
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
  int DAC_OFFSET;
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
    PWR_SET = 4095;
    AGC_ATTEN_BIAS = 2048;
    Serial.println(F("ANALOG DEBUG-MODE SET!"));
#endif
    byte buf[2];
    buf[1] = PWR_SET;
    buf[0]  = PWR_SET >> 8;
    // FastWrite-Command to set DAC: Bit 15, 14 = 0 (Fast Write), Bit 13, 12 = 0 (DAC Enabled), Bit 11 - 0 = 12bit DAC-Value
    Wire.beginTransmission(PWR_SET_DAC);
    Wire.write(buf[0]);
    Wire.write(buf[1]);
    Wire.endTransmission();

    buf[1] = AGC_ATTEN_BIAS;
    buf[0]  = AGC_ATTEN_BIAS >> 8;
    // FastWrite-Command to set DAC: Bit 15, 14 = 0 (Fast Write), Bit 13, 12 = 0 (DAC Enabled), Bit 11 - 0 = 12bit DAC-Value
    Wire.beginTransmission(AGC_BIAS_DAC);
    Wire.write(buf[0]);
    Wire.write(buf[1]);
    Wire.endTransmission();
  }
  else {

  }
}

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

void SetAGC_Bias() {
  byte buf[2];
  buf[1] = AGC_ATTEN_BIAS;
  buf[0]  = AGC_ATTEN_BIAS >> 8;
  Wire.beginTransmission(AGC_BIAS_DAC);
  Wire.write(buf[0]);
  Wire.write(buf[1]);
  Wire.endTransmission();
}

//SIGPATH_CTRL BITMAP: UNUSED | UNUSED | Select 750MHz LPF  (U2_V2)| Select 1,5GHz LPF (U2_V1)| Select Bypass-Path (U5_V1)| Select Filtered Path (U5_V2)| Select other signal source | Select ADF4351-Module
void SetLPF(int LPF_SEL, bool SelectAD9910) {
  switch (LPF_SEL) {
    case BYPASS:
      switch (SelectAD9910) {
        case true:
          SIGPATH_CTRL = 0xE5; // Bitwise OR to PROGRAM Bits 7 to 2
          break;
        case false:
          SIGPATH_CTRL = 0xE6; // Bitwise OR to PROGRAM Bits 7 to 2
          break;
      }
      //      bitClear(SIGPATH_CTRL, 2);  // DISABLE the Filtered-Path
      //      bitSet(SIGPATH_CTRL, 3);  // ENABLE Bypass-Path
      //      bitClear(SIGPATH_CTRL, 4); // DISABLE 1.5GHz-Path to have that signal-path in a known state
      //      bitSet(SIGPATH_CTRL, 5); // ENABLE 750MHz-Path to have that signal-path in a known state
      break;
    case LPF_750:
      switch (SelectAD9910) {
        case true:
          SIGPATH_CTRL = 0xD9; // Bitwise OR to PROGRAM Bits 7 to 2
        case false:
          SIGPATH_CTRL = 0xDA; // Bitwise OR to PROGRAM Bits 7 to 2
          break;
      }
      //      bitSet(SIGPATH_CTRL, 2);
      //      bitClear(SIGPATH_CTRL, 3);
      //      bitSet(SIGPATH_CTRL, 4);
      //      bitClear(SIGPATH_CTRL, 5);
      break;
    case LPF_1500:
      switch (SelectAD9910) {
        case true:
          SIGPATH_CTRL = 0xE9; // Bitwise OR to PROGRAM Bits 7 to 2
          break;
        case false:
          SIGPATH_CTRL = 0xEA; // Bitwise OR to PROGRAM Bits 7 to 2
          break;
      }
      //      bitSet(SIGPATH_CTRL, 2);
      //      bitClear(SIGPATH_CTRL, 3);
      //      bitClear(SIGPATH_CTRL, 4);
      //      bitSet(SIGPATH_CTRL, 5);
      break;
    default:
      ErrorMode(DATA_ERROR_SIGPATH, true);
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

