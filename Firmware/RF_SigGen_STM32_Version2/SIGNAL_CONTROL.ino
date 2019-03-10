/*
    This File contains the functions that configure the rest of the hardware to generate the desired signals
*/

/*
  Checks if the Frequency is below or above 400MHz and then calls the Subroutines that program the signal-sources accordingly
*/
void SetFreq(double FreqSetFreq) {
  Serial.print(F("FRQ: "));
  Serial.print(FreqSetFreq);
  Serial.println(F(" Hz"));
  bool SelAD9910 = false;
  if (FreqSetFreq == 0) {
    Message(F("ERROR! Frequency may not be 0!"), RED);
    Freq = Freq_Old; // Set Frequency-Variable to previous value
  }
  else {
    if (FreqSetFreq >= 4400000000) {
      Message("ERROR: Frequency outside limits", RED);
      Freq = Freq_Old; // Set Frequency-Variable to previous value
      return; // Cancel updating Frequency
    }
    if (FreqSetFreq >= 3000000000) {
      Message("WARNING: Frequency outside CAL-Area", AMBER);
    }
    Freq = FreqSetFreq; // Update "Freq" in case the calling function didn't already do so - Kept in here for compatibility reasons.
    if (FreqSetFreq >= 400000000UL) {
      Serial.println(F(" - Freq >= 400MHz - "));
      if (Freq_Old <= 400000000UL) {
        Serial.print(F(" - Freq_Old <= 400MHZ - "));
        SetupADF4351(STATE_NORM_OP); // Enable the ADF4351-Output
        Serial.print(F(" - ADF4351 ENABLED - "));
        SetupAD9910(STATE_STANDBY); // Disable the AD9910-Output
        Serial.print(F(" - AD9910 DISABLED - "));
      }
      Serial.println(F(" Using ADF4351"));
      SetFreqADF4351(FreqSetFreq);
    }
    else {
      Serial.println(F(" - Freq <= 400MHz - "));
      if (Freq_Old >= 400000000UL) {
        Serial.print(F("FREQ_OLD >= 400MHZ"));
        SetupADF4351(STATE_STANDBY); // Disable the ADF4351-Output
        Serial.print(F(" - ADF4351 DISABLED - "));
        SetupAD9910(STATE_NORM_OP); // Enable the AD9910-Output
        Serial.print(F(" - AD9910 ENABLED - "));
      }
      Serial.print(F(" Using AD9910"));
      SetFreqAD9910(FreqSetFreq);
      Serial.println(F("DONE"));
      SelAD9910 = true;
    }
    Freq_Old = FreqSetFreq;
    Serial.print(F("Freq_Old = "));
    Serial.println(Freq_Old, DEC);
    UpdateFreqArea = true;
    // Check if SigPath-Settings are set to AUTO and adjust the Filtering depending on the frequency
    //    SigPathAuto = false; // DEBUG-Statement - Disable for normal operation
    switch (SigPathAuto) {
      case true:
        if (Freq <= 700000000) {
          SetLPF(LPF_750, SelAD9910, false);
          break;
        }
        if (Freq >= 700000000 && Freq <= 1400000000) {
          SetLPF(LPF_1500, SelAD9910, false);
          break;
        }
        else {
          SetLPF(BYPASS, SelAD9910, false);
          break;
        }
        break;
      case false:
        SetLPF(BYPASS, SelAD9910, false); // DEBUG-Statement - Disable for normal operation
        break;
    }
  }
}

// Function to be called when using FM or FSK to speed up frequency adjustments - Copy of primary Frequency Set-Function that omits the check which Filter is to be used and all unneccesary checks.
void SetFreqFAST(double FreqSetFreq) {
  // Freq = FreqSetFreq; // Update "Freq" in case the calling function didn't already do so - Kept in here for compatibility reasons due to some older code.
  if (FreqSetFreq >= 40000000UL) {
    SetFreqADF4351(FreqSetFreq);
  }
  else {
    SetFreqAD9910(FreqSetFreq);
  }
  Freq_Old = FreqSetFreq;
  UpdateFreqArea = true;
}
