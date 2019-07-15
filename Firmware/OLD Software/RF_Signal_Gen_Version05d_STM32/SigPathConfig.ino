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
    PWR_SET = 1100;
    AGC_ATTEN_BIAS = 768;
    Serial.println(F("ANALOG DEBUG-MODE SET!"));
#endif
  SetAGC_LVL(PWR_SET);
  SetAGC_BIAS(AGC_ATTEN_BIAS);
  }
  else {

  }
}

