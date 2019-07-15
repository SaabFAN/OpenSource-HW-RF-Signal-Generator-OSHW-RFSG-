/*
   Funktions that control what is to be drawn on the display
*/


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
      DrawScreen_SigSource_CAL();
      SoftButton1Txt = F("ASF UP");
      SoftButton2Txt = F("ASF DN");
      SoftButton3Txt = F("FTW_UP");
      SoftButton4Txt = F("FTW_DN");
      SoftButton5Txt = F("EXIT"); // Go back and SAVE the OFFSETS for the AD9910-Values
      // Put the SigPathCal-Screen here
      break;

    case STATE_SIGPATH_MANUAL:
      DisplaySysMode(F("AGC_MANUAL-CTRL"), BLUE);
      DrawScreen_SigpathManual();
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
      DrawScreen_Sigpath_Comp();
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
