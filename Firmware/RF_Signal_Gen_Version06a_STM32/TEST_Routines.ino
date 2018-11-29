// *** DISPLAY-TESTS ***
// *** Copied from the GraphicsTest-Example by Adafruit ***
void TestDisplay() {
  // read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(HX8357_RDPOWMODE);
  Serial.print(F("Display Power Mode: 0x")); Serial.println(x, HEX);
  x = tft.readcommand8(HX8357_RDMADCTL);
  Serial.print(F("MADCTL Mode: 0x")); Serial.println(x, HEX);
  x = tft.readcommand8(HX8357_RDCOLMOD);
  Serial.print(F("Pixel Format: 0x")); Serial.println(x, HEX);
  x = tft.readcommand8(HX8357_RDDIM);
  Serial.print(F("Image Format: 0x")); Serial.println(x, HEX);
  x = tft.readcommand8(HX8357_RDDSDR);
  Serial.print(F("Self Diagnostic: 0x")); Serial.println(x, HEX);
  yield();
}


// Tune the Signal Sources from 1 to 3000MHz in 200MHz steps and measure amplitude - Compare with saved values. If values are out of tolerance set the Uncal-Bit
void SignalPathTest() {
  Serial.println(F("SignalPath-Test"));
  Serial.println(F("Setup ADF9910 in TEST-MODE"));
  SetupAD9910(STATE_TEST);
  // Put code to check for amplitudes here - ATTENTION! Use of "delay(0)" necessary to prevent problems with Wifi-Module, if ESP8266 is used!
  Serial.println(F("LF-Test done. Setting AD9910 to Standby-Mode"));
  SetupAD9910(STATE_STANDBY);
  Serial.println(F("ADF4351 in TEST-MODE"));
  SetupADF4351(STATE_TEST);
  Serial.println(F("ADF4351 STANDBY"));
  SetupADF4351(STATE_STANDBY);
  Serial.println(F("ADF4351 TEST COMPLETE"));

  SetAmplitude(100);
}

// Runs the SignalPath-Compensation
void SigPathCompensate() {
  SetAmplitude(115); // Set the Amplitude to +5dBm
  SetFreq(9000UL); // Set Frequency to 9kHz (Lowest frequency)
  AD9910_AMP_OFFSET = 0;
  int TestAmpAD9910 = 50;
  SetAmplitudeAD9910(TestAmpAD9910, false); // Set Amplitude of AD9910 to 50mVpp
  while (ADC_READ(ADC_RF_OUT_SENSE) <= 636) {
    TestAmpAD9910++;  // Increase Amplitude by 1
    SetAmplitudeAD9910(TestAmpAD9910, false); // Set AMplitude of AD9910
  }
  for (byte i = 0; i < 15; i++) {

  }
  SetFreq(400000000UL);
  PWR_SET = 0;
  while (ADC_READ(ADC_RF_OUT_SENSE) <= 636) {
    PWR_SET++;

  }
}

void CheckAttenuator(bool PowerOnTest) {
  switch (PowerOnTest) {
    case true:
      Serial.print(F("Checking Attenuator: "));
      tft.print(F("Checking Attenuator: "));
      Atten = 0;
      SetAttenuator(Atten);
      Serial.print(Atten);
      Serial.print(F("dB "));
      tft.print(Atten);
      tft.print(F("dB "));
      delay(100);
      Atten++;
      while (Atten < 95) {
        SetAttenuator(Atten);
        Serial.print(Atten);
        Serial.print(F("dB "));
        tft.print(Atten);
        tft.print(F("dB "));
        delay(100);
        Atten = Atten * 2;
      }
      Atten = 95;
      SetAttenuator(Atten);
      Serial.print(Atten);
      Serial.print(F("dB "));
      tft.print(Atten);
      tft.print(F("dB "));
      delay(1000);
      Serial.println(F("DONE"));
      tft.println(F( "DONE"));
      break;
    case false:
      Serial.print(F("Checking Attenuator(SLOW): "));
      Atten = 0;
      SetAttenuator(Atten);
      UpdateAmpArea = true;
      DrawAmplitudeArea(OUTPUT_dBm);
      Serial.print(Atten);
      Serial.print(F("dB "));
      delay(1000);
      Atten++;
      while (Atten < 95) {
        SetAttenuator(Atten);
        UpdateAmpArea = true;
        DrawAmplitudeArea(OUTPUT_dBm);
        Serial.print(Atten);
        Serial.print(F("dB "));
        delay(1000);
        Atten = Atten * 2;
      }
      Atten = 95;
      SetAttenuator(Atten);
      UpdateAmpArea = true;
      DrawAmplitudeArea(OUTPUT_dBm);
      Serial.print(Atten);
      Serial.print(F("dB "));
      delay(1000);

      Serial.print(F("Checking Attenuator(FAST): "));
      Atten = 0;
      while (Atten < 95) {
        SetAttenuator(Atten);
        UpdateAmpArea = true;
        DrawAmplitudeArea(OUTPUT_dBm);
        delay(10);
        Atten++;
      }
      Atten = 95;
      SetAttenuator(Atten);
      UpdateAmpArea = true;
      DrawAmplitudeArea(OUTPUT_dBm);
      delay(1000);
      Serial.println(F("DONE"));
      break;
  }

}

void CheckAD9910() {

}

void CheckADF4351() {
  long waittimer = millis();
  Message("VCO_CHECK", RED);
  SetupADF4351(STATE_VCO_CHECK); // Enable the ADF4351-Output
  Freq = 2200000000;
  UpdateFreqArea = true;
  DrawFrequencyArea(Freq);
  waittimer = millis() + 2000;
  while (millis() < waittimer) {
    DrawSigPathParams();
  }
  SetupADF4351(STATE_NORM_OP); // Enable the ADF4351-Output
  Message("ADF4351 NORM_OP", RED);
  UpdateFreqArea = true;
  DrawFrequencyArea(Freq);

  waittimer = millis() + 100;
  while (millis() < waittimer) {
    DrawSigPathParams();
  }

  SetFreqADF4351(50000000);
  Freq = 50000000;
  Message("ADF4351 @ 50MHZ", RED);
  UpdateFreqArea = true;
  DrawFrequencyArea(Freq);
  waittimer = millis() + 2000;
  while (millis() < waittimer) {
    DrawSigPathParams();
  }
  SetFreqADF4351(100000000);
  Freq = 100000000;
  Message("ADF4351 @ 100MHZ", RED);
  UpdateFreqArea = true;
  DrawFrequencyArea(Freq);
  waittimer = millis() + 2000;
  while (millis() < waittimer) {
    DrawSigPathParams();
  }
  Freq = 500000000;
  SetFreq(Freq);
  Message("ADF4351 @ 500MHZ", RED);
  UpdateFreqArea = true;
  DrawFrequencyArea(Freq);
  waittimer = millis() + 2000;
  while (millis() < waittimer) {
    DrawSigPathParams();
  }
  Freq = 1000000000;
  SetFreq(Freq);
  Message("ADF4351 @ 1GHZ", RED);
  UpdateFreqArea = true;
  DrawFrequencyArea(Freq);
  waittimer = millis() + 2000;
  while (millis() < waittimer) {
    DrawSigPathParams();
  }
  Freq = 1500000000;
  SetFreq(Freq);
  Message("ADF4351 @ 1,5GHZ", RED);
  UpdateFreqArea = true;
  DrawFrequencyArea(Freq);
  waittimer = millis() + 2000;
  while (millis() < waittimer) {
    DrawSigPathParams();
  }
  Freq = 2000000000;
  SetFreq(Freq);
  Message("ADF4351 @ 2GHZ", RED);
  UpdateFreqArea = true;
  DrawFrequencyArea(Freq);
  waittimer = millis() + 2000;
  while (millis() < waittimer) {
    DrawSigPathParams();
  }
  Freq = 2500000000;
  SetFreq(Freq);
  Message("ADF4351 @ 2,5GHZ", RED);
  UpdateFreqArea = true;
  DrawFrequencyArea(Freq);
  waittimer = millis() + 2000;
  while (millis() < waittimer) {
    DrawSigPathParams();
  }
  Freq = 2900000000;
  SetFreq(Freq);
  Message("ADF4351 @ 2,9GHZ", RED);
  UpdateFreqArea = true;
  DrawFrequencyArea(Freq);
  waittimer = millis() + 5000;
  while (millis() < waittimer) {
    DrawSigPathParams();
  }
  Message("Frequency RAMP from 50 MHz to 3 GHZ in 10 MHz Steps", RED);
  SigPathAuto = true;
  Freq = 50000000;
  for (int i = 0; i < 299; i++) {
    SetFreq(Freq);
    UpdateFreqArea = true;
    DrawFrequencyArea(Freq);
    waittimer = millis() + 50;
    while (millis() < waittimer) {
      DrawSigPathParams();
    }
    Freq = Freq + 10000000;

  }
}

void CheckAnalog() {
  Serial.println(F("ANALOG BOARD-CHECK RUNNING"));
  Freq = 50000000;
  SetFreq(Freq);
  UpdateFreqArea = true;
  UpdateAmpArea = true;
  DrawFrequencyArea(Freq);
  DrawAmplitudeArea(100);
  DrawSigPathParams();
  Serial.println(F("Set Attenuator to 0"));
  SetAttenuator(0);
  Serial.print(F("Switching Filters: BYPASS | "));
  SetLPF(BYPASS, false, false);
  delay(5000);
  Serial.print(F("1500 MHZ LPF | "));
  SetLPF(LPF_1500, false, false);
  delay(5000);
  Serial.print(F("750 MHZ LPF | "));
  SetLPF(LPF_750, false, false);
  delay(5000);
  Serial.println(F("BYPASS"));
  SetLPF(BYPASS, false, false);
  Serial.println(F("DONE"));
}
