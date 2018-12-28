/*
 * This file contains the serial-control software. It's an adapted version of the Serial Control-Interface of the EINFEGA Game-Controller.
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

//void CheckSerial() {
//  if (Serial.available() > 0) {
//    // get incoming byte:
//    if (ConsoleModeActive == true) { // If ConsoleModeActive, set the Input-Mode to Console-Mode
//      ConsoleMode();
//    }
//    else {
//      SERIALMODE = Serial.read();
//#ifdef SerialDebug
//      Serial.println(SERIALMODE, HEX);
//      if (SERIALMODE == 0x52) {
//        SERIALMODE = 0x10;
//      }
//#endif
//    }
//  }
//  switch (SERIALMODE) {
//    case 0x10:
//#ifdef SerialDebug
//      Serial.println("Setting SYSMODE to 0x10");
//#endif
//      SYSMODE = 0x10;
//      break;
//    case CAL:
//      SYSMODE = 0xCAL;
//      break;
//    case AIN:
//      Serial.println(F("AIN-MODE Selected"));
//
//      while (Serial.available() > 0) {
//        AnalogCompareValue1 = Serial.parseInt();
//        AnalogCompareValue2 = Serial.parseInt();
//#ifdef SerialDebug
//        Serial.print(F("ACV1 = "));
//        Serial.print(AnalogCompareValue1, DEC);
//        Serial.print(F(" ACV2 = "));
//        Serial.println(AnalogCompareValue2, DEC);
//#endif
//      }
//      SYSMODE = AIN;
//      break;
//    case AIS:
//      Serial.println(F("AnalogIn-SteamingMode_LongAverage selected"));
//      SYSMODE = AIS;
//      break;
//    case AIF:
//      Serial.println(F("AnalogIn-SteamingMode_ShortAverage selected"));
//      SYSMODE = AIF;
//      break;
//    case AIT:
//      if (0xFD == Expansion0 || Expansion1 || Expansion2) {
//        SYSMODE = AIT;
//        Serial.println(F("FFT-Mode selected"));
//      }
//      else {
//        Serial.println(F("ERROR: FAST DAC-Module not installed"));
//        SYSMODE = 0x10;
//      }
//      break;
//    case AOU:
//      if (Serial.available() > 0) {
//        int AOU_ChanA = Serial.parseInt();
//        int AOU_ChanB = Serial.parseInt();
//        Serial.print(F("Channel A-Value: "));
//        Serial.print(AOU_ChanA, DEC);
//        Serial.print(F(" Channel B-Value: "));
//        Serial.println(AOU_ChanB, DEC);
//        SetAOUT(AOU_ChanA, 0);
//        SetAOUT(AOU_ChanB, 1);
//      }
//      SYSMODE = 0x10;
//      break;
//    case AOS:
//      Serial.println(F("AOS-mode not implemented yet"));
//      SYSMODE = 0x10;
//      break;
//    case AOP:
//      Serial.println(F("AOP-Mode not Implemented yet"));
//      break;
//    case SIO:
//      AD9833_OFF();
//      Serial.println(F("AD9833 disabled"));
//      SYSMODE = 0x10;
//      break;
//    case SIG:
//      Serial.print(F("AD9833 Enabled with Frequency: "));
//      long AD9833Frequency;
//      byte AD9833Wave;
//      word AD9833PhaseSIG;
//      AD_PhaseSelect0 = true;
//      if (Serial.available() > 0) {
//        AD9833Frequency = Serial.parseFloat();
//        AD9833Wave = Serial.parseInt();
//        AD9833PhaseSIG = Serial.parseInt();
//        AD9833_ON(AD9833Wave, AD9833Frequency, AD9833PhaseSIG);
//        Serial.print(AD9833Frequency, DEC);
//        Serial.print(F(" / PhaseAngle = "));
//        float PhaseAngleSIG = (((2 * pi) / 4096) * AD9833PhaseSIG);
//        Serial.print(PhaseAngleSIG, 4);
//        Serial.print(F(" / Waveform = "));
//        switch (AD9833Wave) {
//          case 0x00:
//            Serial.println(F("SINE"));
//            break;
//          case 0x01:
//            Serial.println(F("SQUARE"));
//            break;
//          case 0x02:
//            Serial.println(F("TRIANGLE"));
//            break;
//          case 0x03:
//            Serial.println(F("FAST SQUARE"));
//            break;
//        }
//      }
//      SYSMODE = 0x10;
//      break;
//    case AMP:
//      word AD9833PhaseAMP;
//      if (Serial.available() > 0) {
//        Serial.print(F("PSK_ON (Old): "));
//        Serial.print(PSK_ON);
//        AD9833PhaseAMP = Serial.parseInt();
//        switch (PSK_ON) {
//          case true:
//            PSK_ON = false;
//            Serial.println(F("PSK Disabled"));
//            break;
//          case false:
//            PSK_ON = true;
//            Serial.println(F("PSK Enabled"));
//            break;
//        }
//        Serial.print(F("AD9833 Phase-Angle: "));
//        float PhaseAngle = 2 * pi;
//        PhaseAngle = PhaseAngle * (AD9833PhaseAMP / 4096);
//        PhaseAngle = PhaseAngle * rad;
//        Serial.println(PhaseAngle, 4);
//        AD9833_PHASE(AD9833PhaseAMP);
//      }
//      break;
//    case AMT:
//      PSK_ON = false;
//      AD_PhaseSelect0 = true;
//      byte AM_ON;
//      long AM_Tone;
//      if (Serial.available() > 0) {
//        // get incoming byte:
//        AM_ON = Serial.parseInt();
//        Serial.print(F("AM_ON: "));
//        Serial.print(AM_ON, HEX);
//        AM_Tone = Serial.parseFloat();
//        Serial.print(F(" AM_TONE: "));
//        Serial.print(AM_Tone, DEC);
//      }
//      switch (AM_ON) {
//        case 0x00:
//          AD9833_AM(0, false);
//          Serial.println(F(" Amplitude Modulation deactivated"));
//          break;
//        case 0x01:
//          AD9833_AM(AM_Tone, true);
//          Serial.print(F(" Amplitude Modulation Enabled. AM-Tone (Hz): "));
//          Serial.println(AM_Tone);
//          break;
//      }
//      break;
//    //      SYSMODE = 0x10;
//    case AMF:
//      AD_PhaseSelect0 = true;
//      PSK_ON = false;
//      AD_PhaseSelect0 = true;
//      AD9833_AM(0, false);
//      break;
//    case AMD:
//      AD_PhaseSelect0 = true;
//      PSK_ON = false;
//      AD_PhaseSelect0 = true;
//      AD9833_AM(0, false);
//      break;
//    case DIG:
//      Serial.println(F("Digital Output-Mode"));
//      if (Serial.available() > 0) {
//        // get 2 incoming bytes:
//        FastGPIO_RD();
//        Serial.print(F("GPIO_PINS_A = "));
//        Serial.print(GPIO_PINS_A, HEX);
//        Serial.print(F(" GPIO_PINS_B = "));
//        Serial.print(GPIO_PINS_B, HEX);
//        Serial.read();
//        GPIO_PINS_A = Serial.read();
//        GPIO_PINS_B = Serial.read();
//        Serial.print(F(" GPIO_PINS_A = "));
//        Serial.print(GPIO_PINS_A, HEX);
//        Serial.print(F(" GPIO_PINS_B = "));
//        Serial.print(GPIO_PINS_B, HEX);
//        switch (PWR_EN) {
//          case 0x00:
//            bitClear(GPIO_PINS_B, 7);
//            bitClear(GPIO_PINS_B, 6);
//            break;
//          case 0x40:
//            bitSet(GPIO_PINS_B, 6);
//            break;
//          case 0x80:
//            bitSet(GPIO_PINS_B, 7);
//            break;
//          case 0xC0:
//            bitSet(GPIO_PINS_B, 6);
//            bitSet(GPIO_PINS_B, 7);
//            break;
//        }
//        Serial.print(F(" GPIO_PINS_A = "));
//        Serial.print(GPIO_PINS_A, HEX);
//        Serial.print(F(" GPIO_PINS_B = "));
//        Serial.println(GPIO_PINS_B, HEX);
//        FastGPIO_WR(GPIO_PINS_A, GPIO_PINS_B);
//      }
//      break;
//    case DIP:
//      PatPoint_Reset = true;
//      if (Serial.available() > 0) {
//        // get 64 incoming bytes:
//        for (byte i; i <= 63; i++) {
//          GPIO_PatternData[i] = Serial.read();
//        }
//        SYSMODE = DIP;
//      }
//      break;
//    case PWR:
//      Serial.println(F("PWR-SET Function"));
//      if (Serial.available() > 0) {
//        // get incoming byte:
//        byte PWR_5V = Serial.read();
//        byte PWR_12V = Serial.read();
//        Serial.print(F("PWR_5V = "));
//        Serial.print(PWR_5V, HEX);
//        Serial.print(F(" PWR_12V = "));
//        Serial.print(PWR_12V, HEX);
//        if (PWR_5V != 0x30) {
//          bitSet(PWR_EN, 6);
//        }
//        if (PWR_5V == 0x30) {
//          bitClear(PWR_EN, 6);
//        }
//        if (PWR_12V != 0x30) {
//          bitSet(PWR_EN, 7);
//        }
//        if (PWR_12V == 0x30) {
//          bitClear(PWR_EN, 7);
//        }
//        Serial.print(F(" PWR_EN = "));
//        Serial.println(PWR_EN, HEX);
//        PWR_Update();
//      }
//      else {
//        PWR_EN = 0x00;
//        PWR_Update();
//      }
//      break;
//    case REA:
//      break;
//    case WRI:
//      Serial.println(F("Not Implemented yet, use the dedicated functions for each Output instead."));
//      SYSMODE = 0x10;
//      break;
//    case CON:
//      Serial.println(F("CONSOLE-MODE ENABLED"));
//      Serial.println(F("Waiting for valid input"));
//      break;
//    case EXW:
//      Serial.println(F("Expansion-Modules not supported yet"));
//      SYSMODE = 0x10;
//      break;
//    case EXR:
//      Serial.println(F("Expansion-Modules not supported yet"));
//      SYSMODE = 0x10;
//      break;
//    case RES:
//      Serial.println(F("Resetting all Outputs to default"));
//      AD9833_OFF();
//      SetAOUT(0, 0);
//      SetAOUT(0, 1);
//      break;
//    case CNT:
//      SYSMODE = CNT;
//      break;
//    case FRQ:
//      SYSMODE = FRQ;
//      break;
//    case DEM:
//      Serial.println(F("Demo-Mode Enabled"));
//      SYSMODE = DEM;
//      break;
//    case CHK:
//      SYSMODE = CHK;
//      break;
//  }
//  SERIALMODE = 0x00;
//}
