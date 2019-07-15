/*
   This file contains the serial-control software. It's an adapted version of the Serial Control-Interface of the EINFEGA Game-Controller.
*/
//// System State codes - Valid System states for both the entire System, as well as the SignalSource-Modules:
//const byte STATE_NORM_OP = 0x00; // Default-Screen, also called "Mode_Select_1"-Screen.
//const byte STATE_INT_WAITING = 0x01;
//const byte STATE_MODE_SELECT_2 = 0x02; // Second Mode-Select Screen
//
//const byte STATE_POWERDOWN = 0x10;
//const byte STATE_COLDSTART = 0x11;
//const byte STATE_STANDBY = 0x20;
//const byte STATE_VCO_CHECK = 0x30;
//const byte STATE_TEST = 0x40;
//// Calibration and setup-Modes
//const byte STATE_CALIBRATION = 0xC0;
//const byte STATE_SIGSOURCE_CAL = 0xC1;
//const byte STATE_SIGPATH_CAL = 0xC2;
//const byte STATE_SIGPATH_COMP = 0xC3;
//const byte STATE_TOUCH_CAL = 0xCF;
//const byte STATE_CONFIG = 0xCF;
//const byte STATE_DEBUG = 0xD0;
//// Sys-States in which the system waits for an input
//const byte STATE_ENTER_FREQ = 0xE0;
//const byte STATE_ENTER_AMPLITUDE = 0xE1;
//const byte STATE_ENTER_MODULATION_TYPE = 0xE2;
//const byte STATE_ENTER_AM_PARAMETERS = 0xE3;
//const byte STATE_ENTER_FM_PARAMETERS = 0xE4;
//const byte STATE_ENTER_PM_PARAMETERS = 0xE5;
//const byte STATE_ENTER_RAMP = 0xEA;
//const byte STATE_ENTER_BURST = 0xEB;
//// Sys-State when the device is started:
//const byte STATE_INIT = 0xFF;
//

void CheckSerial() {
  if (Serial.available() > 0) {
    SERIALMODE = Serial.read();
  }
  else {
    SERIALMODE = 0x00;
    return;
  }
  switch (SERIALMODE) {
    case 'D':
      SERIALMODE = Serial.read();
      Serial.print(F("DEBUG_MODE - "));
      switch (SERIALMODE) {
        case 'A':
          Serial.println(F("AD9910"));
          for (int i = 0; i < 30; i++) {
            SetFreqAD9910(66000000);
            delay(1000);
          }
          break;
        case 'B':
          Serial.println(F("ADF4351"));
          for (int i = 0; i < 30; i++) {
            SetFreqADF4351(60000000);
            delay(1000);
          }
          break;
      }
      break;
    case 'R':
      nvic_sys_reset();
      break;
    case 'T':
      SERIALMODE = Serial.read();
      Serial.print(F("TEST_MODE - "));
      switch (SERIALMODE) {
        case 'A':
          Serial.println(F("AD9910"));
          break;
        case 'B':
          Serial.println(F("ADF4351"));
          CheckADF4351();
          break;
      }
      break;
    case 'S': // STATUS-Request
      ReportStatus();
      break;
    case 'C':
      Serial.println(F("CALIBRATION-MODE"));
      break;
    case 'F':
      Serial.print(F("Setting Frequency: "));
      uint32_t Freq_Serial = 0;
      if (Serial.available() > 0) {
        Freq_Serial = Serial.parseInt();
        if (Freq_Serial < 10.0 || Freq_Serial > 4400000000) {
          Serial.println(F("Out Of Range!"));
          return;
        }
        Serial.print(Freq_Serial, DEC);
        SetFreq(Freq_Serial);
      }
      break;
  }
  return;
}

void ReportStatus() {
  // Print all Variables to the Serial console to get a picture of the current system status
  Serial.println(F("==== SYSTEM STATUS ===="));
}
