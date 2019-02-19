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

void SetAmplitude(float Amplitude) {
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
      SIGPATH_CTRL = SIGPATH_CTRL + 0x04; // ADD value to the signalpath-control to set the select-bits of the filters
      break;
    case LPF_750:
      SIGPATH_CTRL = SIGPATH_CTRL + 0x18;
      break;
    case LPF_1500:
      SIGPATH_CTRL = SIGPATH_CTRL + 0x28;
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
