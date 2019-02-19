/*
 * Calibration-Program for the SignalPath calls all the other Calibration-Subroutines
 * This Subroutine is running in a continous loop until 
 */

 // TO DO: REWRITE THIS TO BE UNDER THE CONTROL OF THE MAIN LOOP
void SigPathCalibration(){
    SetLPF(BYPASS, false, false);
    Freq = 450000000;
    SetFreq(Freq);
    
    // Put calibration-routines here
}

void CalRef(){
  Freq = 250000000;
  SetFreq(Freq);
  SetAmplitudeAD9910(-10, true);
  UpdateDisplay();
  RF_OUT_REF = ADC_READ(ADC_RF_OUT_SENSE);
  WriteNVData(RF_OUT_REF, REF_OUT_CAL_NVRAM);
}

//void Cal
