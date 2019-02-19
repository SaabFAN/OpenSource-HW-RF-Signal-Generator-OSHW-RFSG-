/*
   Functions that draw stuff on the Display
*/

/*
   This subprogram calls the graphics library to write a message into the message-area on the screen. The message Area has the coordinates: 140X - 470X / 0Y - 40Y.
   The Message Types are color-coded:
   - Normal System-Messages: WHITE
   - Warning-Messages: YELLOW
   - Error-Messages: RED
*/

void Message(String message, int mcolor) { // "message" is displayed in the color specified by "mcolor"
  tft.setCursor(140, 0);
  tft.setTextColor(mcolor);
  tft.setTextSize(1);
  tft.setTextWrap(false);
  tft.fillRect(140, 0, 340, 15, BLACK);
  tft.println(message);
}

void DisplaySysMode(String message, int mcolor) {

  tft.setCursor(0, 0);
  tft.setTextColor(mcolor);
  tft.setTextSize(1);
  tft.setTextWrap(false);
  tft.fillRect(0, 0, 130, 12, BLACK);
  tft.println(message);
}

void ShowSysStatus() {
  tft.setCursor(0, 14);
  tft.setTextColor(AMBER);
  tft.setTextSize(1);
  tft.fillRect(0, 10, 480, 12, BLACK);
  tft.print(F(" InputMode = 0x"));
  tft.print(InputMode, HEX);
  tft.print(F(" MOD ENABLE: "));
  tft.print(ModulationEnable);
  tft.print(F(" OUTPUT ENABLE: "));
  tft.print(OutputEnable);
  tft.print(F(" KeyboardInput = "));
  tft.println(keyboardInput);
}

/*
   This Subprogram draws the SoftButtons during normal Opration
   Library calls put here for reference:
   void drawRoundRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t radius, uint16_t color);
   void fillRoundRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t radius, uint16_t color);

*/

void DrawButton (uint16_t XPosButt, uint16_t YPosButt, String ButtText, bool Highlight, uint16_t ButtColor, int TxtSize) {
  uint16_t TextX = XPosButt + 20;
  uint16_t TextY = YPosButt + 16;
  tft.setTextSize(2);
  tft.drawRoundRect(XPosButt, YPosButt, 150, 50, 5, ButtColor);
  XPosButt = XPosButt + 4;
  YPosButt = YPosButt + 3;
  switch (Highlight) {
    case false:
      tft.drawRoundRect(XPosButt, YPosButt, 142, 44, 4, ButtColor);
      tft.setCursor(TextX, TextY);
      tft.setTextColor(ButtColor);
      tft.println(ButtText);
      break;
    case true:
      tft.fillRoundRect(XPosButt, YPosButt, 142, 44, 4, ButtColor);
      tft.setCursor(TextX, TextY);
      tft.setTextColor(BLACK);
      tft.println(ButtText);
      break;
  }
}

void DrawFrequencyArea(unsigned long dispData) {
  if (UpdateFreqArea == true) {
    tft.drawRoundRect(2, 30, 290, 80, 2, AMBER);
    tft.setTextSize(2);
    float DispFrequency = dispData / 1000000.000;
    tft.setCursor(10, 40);
    tft.setTextColor(AMBER, BLACK);
    tft.println("Frequency");
    //  tft.println(" ");
    tft.setCursor(10, 70);
    int16_t  x1, y1;
    uint16_t w, h;
    tft.setTextSize(3);
    tft.getTextBounds(F("               "), 10, 70, &x1, &y1, &w, &h);
    tft.fillRect(x1, y1, w, h, BLACK);
#ifdef DISPLAY_DEBUG
    //tft.fillRect(x1, y1, w, h, GREEN);
    Serial.print(F(" DispFreq = "));
    Serial.println(DispFrequency, 6);
#endif
    if (InputMode == INPUT_ENTER_FREQ) {
      DispFrequency = keyboardInput;
      tft.print(DispFrequency);
    }
    else {
      tft.print(DispFrequency, 6);
      tft.println(" MHZ");
    }
    UpdateFreqArea = false;
  }
}

void DrawAmplitudeArea(unsigned long dispData) {
  if (UpdateAmpArea == true) {
    tft.drawRoundRect(2, 115, 290, 80, 2, BLACK);
    tft.drawRoundRect(2, 115, 290, 80, 2, AMBER);
    tft.setTextSize(2);
    float DispAmplitude = dispData;
    tft.setCursor(10, 130);
    tft.setTextColor(AMBER, BLACK);
    tft.println("Amplitude    ATTENUATOR");
    //  tft.println(" ");
    tft.setCursor(10, 160);
#ifdef DISPLAY_DEBUG

#endif

    if (InputMode == INPUT_ENTER_AMPLITUDE) {
      DispAmplitude = keyboardInput;
      tft.print(DispAmplitude);
    }
    else {
      switch (AmplitudeModeDB) {
        case true:
          tft.print((DispAmplitude - OUTPUT_DBM_OFFSET), 1);
          tft.print(" dBm");
          break;
        case false:
          DispAmplitude = DispAmplitude - OUTPUT_DBM_OFFSET;
          float DispAmplitude_mV = pow(10, ((DispAmplitude - 10) / 20));
          tft.print(DispAmplitude_mV, 6);
          // Put Code here to convert Amplitude dB into mV
          tft.print(" mVpp");
          break;
      }
    }
    tft.print(F("  "));
    tft.print(Atten);
    switch (AttenAuto) {
      case true:
        tft.println(F(" dB (Aut)"));
        break;
      case false:
        tft.println(F(" dB (Man)"));
        break;
    }

  }
  UpdateAmpArea = false;
}

void DrawModulationArea(unsigned long disData1, unsigned long dispData2, unsigned long dispData3, unsigned long dispData4) {
  if (UpdateModArea == true) {
    tft.fillRect(3, 201, 288, 118, BLACK);
    tft.drawRoundRect(2, 200, 290, 120, 2, AMBER);
    tft.setTextSize(2);
    tft.setCursor(10, 210);
    tft.setTextColor(AMBER, BLACK);
    tft.println("Modulation");
    tft.setCursor(10, 240);
#ifdef DISPLAY_DEBUG
#endif
  }
  UpdateModArea = false; // Modulation-Area updated, no further Updates needed until something changes (UpdateModArea set to True by different function)
}


void DrawSigPathParams() {
  if (ClearScreen == true) {
    tft.fillRect(3, 201, 288, 118, BLACK);
    tft.drawRoundRect(2, 200, 290, 120, 2, AMBER);
  }
  tft.setTextSize(2);
  tft.setCursor(10, 260);
  tft.setTextColor(AMBER, BLACK);
  tft.println(F("SigPath-Parameters"));
  tft.setCursor(10, 290);
  float RF_out_volt = ADC_READ(ADC_RF_OUT_SENSE);
  float RF_lvl_volt = ADC_READ(ADC_RF_LEVEL_SENSE);
  tft.setTextSize(1);
  tft.print(F("RF-LvL_Sense: "));
  tft.print(RF_lvl_volt, 2);
  tft.print(F(" RF-Out_Sense: "));
  tft.println(RF_out_volt, 2);
  tft.setCursor(10, 300);
  tft.print(F("RF-LvL_Set: "));
  tft.print(PWR_SET, DEC);
  tft.print(F(" AGC_AttenBIAS: "));
  tft.println(AGC_ATTEN_BIAS, DEC);
  tft.setCursor(10, 310);
  tft.print(F("Millis = "));
  tft.print(millis());
  tft.print(F(" RF_PATH = "));
  tft.print(SIGPATH_CTRL, HEX);
}

void DrawScreen_SigSource_CAL() {
  tft.drawRoundRect(10, 20, 160, 200, 4, AMBER);
  tft.setCursor(20, 30);
  tft.setTextColor(AMBER);
  tft.setTextSize(2);
  tft.print(F("Time since Startup:"));
  int16_t  x4, y4;
  uint16_t w4, h4;
  tft.getTextBounds(F("                "), 10, 70, &x4, &y4, &w4, &h4);
  tft.fillRect(x4, y4, w4, h4, BLACK);
  tft.print((millis() / 1000)); // Display time since Startup in Seconds
  tft.println(F(" Seconds"));
  // Put Method to display CAL-Information here
}

void DrawScreen_SigpathManual() {
  tft.drawRoundRect(10, 20, 160, 200, 4, AMBER);
  tft.setCursor(20, 30);
  tft.setTextColor(AMBER);
  tft.setTextSize(2);
  tft.print(F("Time since Startup:"));
  int16_t  x0, y0;
  uint16_t w0, h0;
  tft.getTextBounds(F("                "), 10, 70, &x0, &y0, &w0, &h0);
  tft.fillRect(x0, y0, w0, h0, BLACK);
  tft.print((millis() / 1000)); // Display time since Startup in Seconds
  tft.println(F(" Seconds"));
  // Put Method to display CAL-Information here
}

void DrawScreen_Sigpath_Comp() {
  tft.drawRoundRect(10, 20, 160, 200, 4, AMBER);
  tft.setCursor(20, 30);
  tft.setTextColor(AMBER);
  tft.setTextSize(2);
  tft.print(F("Time since Startup:"));
  int16_t  x1, y1;
  uint16_t w1, h1;
  tft.getTextBounds(F("                "), 10, 70, &x1, &y1, &w1, &h1);
  tft.fillRect(x1, y1, w1, h1, BLACK);
  tft.print((millis() / 1000)); // Display time since Startup in Seconds
  tft.println(F(" Seconds"));
  // Put Method to display CAL-Information here
}

void DrawScreen_Sigpath_Cal() {
  tft.drawRoundRect(10, 20, 160, 200, 4, AMBER);
  tft.setCursor(20, 30);
  tft.setTextColor(AMBER);
  tft.setTextSize(2);
  tft.print(F("Time since Startup:"));
  int16_t  x2, y2;
  uint16_t w2, h2;
  tft.getTextBounds(F("                "), 10, 70, &x2, &y2, &w2, &h2);
  tft.fillRect(x2, y2, w2, h2, BLACK);
  tft.print((millis() / 1000)); // Display time since Startup in Seconds
  tft.println(F(" Seconds"));
  // Put Method to display CAL-Information here
}
