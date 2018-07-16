/*
   Button-Numbers:
*/

const byte SoftButton1 = 0x00;
const byte SoftButton2 = 0x10;
const byte SoftButton3 = 0x20;
const byte SoftButton4 = 0x30;
const byte CalContinue = 0xC0;

String SoftButton1Txt;  // Text for one of the side-buttons - Max Length: 8 characters
String SoftButton2Txt;
String SoftButton3Txt;
String SoftButton4Txt;
String SoftButton5Txt;

#define DISPLAY_DEBUG

void UpdateDisplay() {
  switch (SysStatus) {
    case STATE_NORM_OP:
      DisplaySysMode(F("MODE_SELECT 1"), BLUE);
      SoftButton1Txt = F("  FREQ  ");
      SoftButton2Txt = F("   AMP  ");
      SoftButton3Txt = F("   MOD  ");
      SoftButton4Txt = F("OUT ON/OFF");
      SoftButton5Txt = F("  MORE  ");
      DrawFrequencyArea(Freq);
      DrawAmplitudeArea(OUTPUT_dBm);
      DrawModulationArea(ModPara1, ModPara2, ModPara3, ModPara4);
      break;
    case STATE_MODE_SELECT_2:
      DisplaySysMode("MODE_SELECT 2", BLUE);
      SoftButton1Txt = F("ADV-FUNC");
      SoftButton2Txt = F("SIG-CTRL");
      SoftButton3Txt = F(" SYSTEM ");
      SoftButton4Txt = F("  DEMO  ");
      SoftButton5Txt = F("  BACK  ");
      DrawFrequencyArea(Freq);
      DrawAmplitudeArea(OUTPUT_dBm);
      DrawModulationArea(ModPara1, ModPara2, ModPara3, ModPara4);
      break;
    case STATE_ADV_MODULATION:
      DisplaySysMode(F("ADVANCED FUNCTIONS"), BLUE);
      Message(F("ERROR! Function not implemented yet"), AMBER);
      SoftButton1Txt = F("  BURST ");
      SoftButton2Txt = F("   RAMP ");
      SoftButton3Txt = F("ADV_MOD ");
      SoftButton4Txt = F("ARB_WAV ");
      SoftButton5Txt = F("  BACK  ");
      break;
    case STATE_ARBITRARY_WAVE:
      DisplaySysMode(F("ARBITRARY WAVEFORM-FUNCTIONS"), BLUE);
      Message(F("ERROR! Function not implemented yet"), AMBER);
      SoftButton1Txt = F("        ");
      SoftButton2Txt = F("        ");
      SoftButton3Txt = F("        ");
      SoftButton4Txt = F("        ");
      SoftButton5Txt = F("  BACK  ");
      DrawFrequencyArea(Freq);
      DrawAmplitudeArea(OUTPUT_dBm);
      DrawModulationArea(ModPara1, ModPara2, ModPara3, ModPara4);
      break;
    case STATE_SIGPATH_CTRL:
      DisplaySysMode(F("SignalPath-Control"), BLUE);
      SoftButton1Txt = F("FiltAuto");
      SoftButton2Txt = F(" Ext_Src");
      SoftButton3Txt = F(" Ext_AM ");
      SoftButton4Txt = F(" ATTEN  ");
      SoftButton5Txt = F("  BACK  ");
      // drawXBitmap(DATA FOR THE BITMAP THAT SHOWS THE FILTER-SETUP HERE);
      break;
    //      case STATE_SIGPATH_MANUAL || STATE_SIGPATH_CAL || STATE_SIGPATH_COMP ||  STATE_SIGSOURCE_CAL || STATE_CONFIG_1 || STATE_CONFIG_2 || STATE_CONFIG_3 || STATE_CONFIG_4 || STATE_CONFIG_5 || STATE_CONFIG_6:
    //
    case STATE_DEMO:
      DisplaySysMode(F("DEMO-MODE"), BLUE);
      Message(F("ERROR! Function not implemented yet"), AMBER);
      SoftButton1Txt = F("        ");
      SoftButton2Txt = F("        ");
      SoftButton3Txt = F("        ");
      SoftButton4Txt = F("        ");
      SoftButton5Txt = F("  BACK  ");
      DrawFrequencyArea(Freq);
      DrawAmplitudeArea(OUTPUT_dBm);
      DrawModulationArea(ModPara1, ModPara2, ModPara3, ModPara4);
      break;

    /*
     * *** CALIBRATION-SCREENS ***
    */
    case STATE_SIGSOURCE_CAL:
      DisplaySysMode(F("AD9910_CAL"), BLUE);
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
      SoftButton1Txt = F("ASF UP");
      SoftButton2Txt = F("ASF DN");
      SoftButton3Txt = F("FTW_UP");
      SoftButton4Txt = F("FTW_DN");
      SoftButton5Txt = F("EXIT"); // Go back and SAVE the OFFSETS for the AD9910-Values
      // Put the SigPathCal-Screen here
      break;

    case STATE_SIGPATH_MANUAL:
      DisplaySysMode(F("AGC_MANUAL-CTRL"), BLUE);
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
      SoftButton1Txt = F("LVL UP");
      SoftButton2Txt = F("LVL DN");
      SoftButton3Txt = F("BIAS_UP");
      SoftButton4Txt = F("BIAS_DN");
      SoftButton5Txt = F("EXIT"); // Go back and SAVE the BIAS and LEVEL-Value
      DrawSigPathParams();
      // Put the SigPathCal-Screen here
      break;

    case STATE_SIGPATH_COMP:
      DisplaySysMode(F("SIGPATH-CALIBRATION"), BLUE);
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
      SoftButton1Txt = F("CAL_REF");  // Program AD9910 to -10 dBm at 250 MHz
      SoftButton2Txt = F("CAL_DET");  // Save the current at RF-OUT to be +10 dBm Output-Power
      SoftButton3Txt = F("CAL_PATH"); // Run automatic CAL-Routine
      SoftButton4Txt = F("CAL_ADJ");  // Option to manually adjust the calibration
      SoftButton5Txt = F("EXIT");
      DrawSigPathParams();
      // Put the SigPaThCal-Screen here
      break;

    case STATE_SIGPATH_CAL:
      DisplaySysMode(F("SIGPATH-CAL"), BLUE);
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
      SoftButton1Txt = F("LVL UP");
      SoftButton2Txt = F("LVL DN");
      SoftButton3Txt = F("SAVE");
      SoftButton4Txt = F("NEXT");
      SoftButton5Txt = F("EXIT");
      DrawSigPathParams();
      // Put the SigPathCal-Screen here
      break;
    case STATE_TOUCH_CAL:

      DisplaySysMode(F("SIGPATH-CALIBRATION"), BLUE);
      // Put the SigPathCal-Screen here
      break;

    /*
     * *** CONFIG-SCREENS ***
    */
    case STATE_CONFIG_1:
      DisplaySysMode("TEST-PAGE 1", BLUE);
      SoftButton1Txt = " AD9910 ";
      SoftButton2Txt = " ADF4351";
      SoftButton3Txt = " ANALOG ";
      SoftButton4Txt = "  MORE  ";
      SoftButton5Txt = "  EXIT  ";
      DrawSigPathParams();
      break;
    case STATE_CONFIG_2:
      DisplaySysMode("TEST-PAGE 2", BLUE);
      SoftButton1Txt = "  ATTEN ";
      SoftButton2Txt = " RST KBD";
      SoftButton3Txt = "READ KEY";
      SoftButton4Txt = "  MORE  ";
      SoftButton5Txt = "  EXIT  ";
      DrawSigPathParams();
      break;
    case STATE_CONFIG_3:
      DisplaySysMode("CALIBRATION-OPTIONS", BLUE);
      SoftButton1Txt = "SIG-SETUP";
      SoftButton2Txt = " SIG-COMP";
      SoftButton3Txt = " SIG-CAL ";
      SoftButton4Txt = "  MORE  ";
      SoftButton5Txt = "  EXIT  ";
      DrawSigPathParams();
      break;
    case STATE_CONFIG_4:
      DisplaySysMode("CONFIG-PAGE 4", BLUE);
      SoftButton1Txt = "        ";
      SoftButton2Txt = "        ";
      SoftButton3Txt = "        ";
      SoftButton4Txt = "  MORE  ";
      SoftButton5Txt = "  EXIT  ";
      DrawSigPathParams();
      break;
    case STATE_CONFIG_5:
      DisplaySysMode("CONFIG-PAGE 5", BLUE);
      SoftButton1Txt = "        ";
      SoftButton2Txt = "        ";
      SoftButton3Txt = "        ";
      SoftButton4Txt = "  MORE  ";
      SoftButton5Txt = "  EXIT  ";
      DrawSigPathParams();
      break;
    case STATE_CONFIG_6:
      DisplaySysMode("DEBUG-OPTIONS", BLUE);
      SoftButton1Txt = "        ";
      SoftButton2Txt = "        ";
      SoftButton3Txt = "  DEBUG ";
      SoftButton4Txt = "  MORE  ";
      SoftButton5Txt = "  EXIT  ";
      DrawSigPathParams();
      break;

    /*
     * *** INPUT-SCREENS FOR DATA ***
    */
    case STATE_ENTER_FREQ:
      DisplaySysMode(F("Enter Frequency!"), BLUE);
      // Screen to enter the Frequency
      SoftButton1Txt = F("   GHz");
      SoftButton2Txt = F("   MHz");
      SoftButton3Txt = F("   kHz");
      SoftButton4Txt = F("    Hz");
      SoftButton5Txt = F("  BACK");

      DrawFrequencyArea(Freq);
      DrawAmplitudeArea(OUTPUT_dBm);
      DrawModulationArea(ModPara1, ModPara2, ModPara3, ModPara4);
      break;
    case STATE_ENTER_AMPLITUDE:
      DisplaySysMode(F("Enter Amplitude!"), BLUE);
      SoftButton1Txt = F("  +dBm");
      SoftButton2Txt = F("  -dBm");
      SoftButton3Txt = F("  mVpp");
      SoftButton4Txt = F(" Atten");
      SoftButton5Txt = F("  BACK");

      DrawFrequencyArea(Freq);
      DrawAmplitudeArea(OUTPUT_dBm);
      DrawModulationArea(ModPara1, ModPara2, ModPara3, ModPara4);
      // Screen to enter the Amplitude of the Signal
      break;
    case STATE_ENTER_MODULATION_TYPE:
      DisplaySysMode(F("Select Modulation"), BLUE);
      SoftButton1Txt = F("   AM");
      SoftButton2Txt = F("   FM");
      SoftButton3Txt = F("   PM");
      SoftButton4Txt = F("ENA/DIS");
      SoftButton5Txt = F("  BACK");

      DrawFrequencyArea(Freq);
      DrawAmplitudeArea(OUTPUT_dBm);
      DrawModulationArea(ModPara1, ModPara2, ModPara3, ModPara4);
      // Put the Modulation-Select Screen here
      break;
    case STATE_ENTER_AM_PARAMETERS:
      DisplaySysMode(F("AM-Parameter Setup"), BLUE);
      SoftButton1Txt = F("STRENGTH");
      SoftButton2Txt = F("    kHz ");
      SoftButton3Txt = F(" digPat ");
      SoftButton4Txt = F("        ");
      SoftButton5Txt = F("  BACK  ");
      // Put the AM-Settings here
      break;
    case STATE_ENTER_FM_PARAMETERS:
      DisplaySysMode(F("FM-Parameter Setup"), BLUE);
      SoftButton1Txt = F("  WIDTH ");
      SoftButton2Txt = F("    kHz ");
      SoftButton3Txt = F(" digPat ");
      SoftButton4Txt = F("        ");
      SoftButton5Txt = F("  BACK  ");
      // Put the AM-Settings here
      break;
    case STATE_ENTER_PM_PARAMETERS:
      DisplaySysMode(F("PM-Parameter Setup"), BLUE);
      SoftButton1Txt = F("  ANGLE ");
      SoftButton2Txt = F("    kHz ");
      SoftButton3Txt = F(" digPat ");
      SoftButton4Txt = F("        ");
      SoftButton5Txt = F("  BACK  ");
      // Put the AM-Settings here
      break;
    case STATE_ENTER_BURST:
      DisplaySysMode(F("BURST-Parameter Setup"), BLUE);
      SoftButton1Txt = F(" LENGTH ");
      SoftButton2Txt = F("    kHz ");
      SoftButton3Txt = F(" digPat ");
      SoftButton4Txt = F("    AMP ");
      SoftButton5Txt = F("  BACK  ");
      // Put the AM-Settings here
      break;
    case STATE_ENTER_RAMP:
      DisplaySysMode(F("RAMP-Parameter Setup"), BLUE);
      SoftButton1Txt = F(" LENGTH ");
      SoftButton2Txt = F("StartkHz");
      SoftButton3Txt = F(" StopkHz");
      SoftButton4Txt = F(" HighAMP");
      SoftButton5Txt = F("  BACK  ");
      // Put the AM-Settings here
      break;

    case STATE_ATTEN_CTRL_PAGE:
      DisplaySysMode(F("ATTENUATOR_CTRL"), BLUE);
      SoftButton1Txt = F("  AUTO  ");
      SoftButton2Txt = F("SET ATT ");
      SoftButton3Txt = F("   UP   ");
      SoftButton4Txt = F("  DOWN  ");
      SoftButton5Txt = F("  BACK  ");
      DrawFrequencyArea(Freq);
      DrawAmplitudeArea(OUTPUT_dBm);
      DrawModulationArea(ModPara1, ModPara2, ModPara3, ModPara4);
      // Put the AM-Settings here
      break;

  }
#ifdef DISPLAY_DEBUG
  ShowSysStatus();
#endif
  if (updateButtons == true) {
    DrawButton(330, 30, F(" "), true, BLACK, 2);
    DrawButton(330, 90, F(" "), true, BLACK, 2);
    DrawButton(330, 150, F(" "), true, BLACK, 2);
    DrawButton(330, 210, F(" "), true, BLACK, 2);
    DrawButton(330, 270, F(" "), true, BLACK, 2);
  }
  else {

  }
  DrawButton(330, 30, SoftButton1Txt, false, AMBER, 2);
  DrawButton(330, 90, SoftButton2Txt, false, AMBER, 2);
  DrawButton(330, 150, SoftButton3Txt, false, AMBER, 2);
  DrawButton(330, 210, SoftButton4Txt, false, AMBER, 2);
  DrawButton(330, 270, SoftButton5Txt, false, AMBER, 2);
  updateButtons = false;
  ClearScreen = false;
}

void UpdateDisplayPart(int dispPart) {
  switch (dispPart) {
    case INPUT_ENTER_FREQ:
      DrawFrequencyArea(keyboardInput);
      break;
  }
}

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
    Serial.println(DispFrequency);
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
    tft.setTextSize(2);
    tft.setCursor(10, 210);
    tft.setTextColor(AMBER, BLACK);
    tft.println(F("SigPath-Parameters"));
    tft.setCursor(10, 240);
  }
  float RF_out_volt = ADC_READ(ADC_RF_OUT_SENSE);
  float RF_lvl_volt = ADC_READ(ADC_RF_LEVEL_SENSE);
  tft.setTextSize(1);
  tft.print(F("RF-LvL_Sense: "));
  tft.print(RF_lvl_volt, 2);
  tft.print(F(" RF-Out_Sense: "));
  tft.println(RF_out_volt, 2);
  tft.print(F("RF-LvL_Set: "));
  tft.print(PWR_SET, DEC);
  tft.print(F(" AGC_AttenBIAS: "));
  tft.println(AGC_ATTEN_BIAS, DEC);
}

