int ADC_READ(byte ADC_CHANNEL) { // Returns the voltage present at the selected input of the ADC in millivolt
  switch (ADC_CHANNEL) {
    case ADC_RF_OUT_SENSE:
      ads.setGain(GAIN_TWO);
      break;
    case ADC_RF_LEVEL_SENSE:
      ads.setGain(GAIN_TWO);
      break;
  }
  int ADC_Value = ads.readADC_SingleEnded(ADC_CHANNEL);
  int ADC_Volt = 0;
  switch (ADC_CHANNEL) {
    case ADC_RF_OUT_SENSE:
      ADC_Volt = ADC_Value * 1; // Scale the ADC-Value to the Vref and the selected gain (Gain = 1): 1bit = 2mV
      break;
    case ADC_RF_LEVEL_SENSE:
      ADC_Volt = ADC_Value * 1; // Scale the ADC-Value to the Vref and the selected gain (Gain = 2): 1bit = 2mV
      break;
  }
  return ADC_Value;
}