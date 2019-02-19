/*
   This file contains the subroutines for the Inputs
*/

/*
   GPIO-Functions
*/

void ReadGPIO() {

}

/*
   Keypad-Functions
*/
byte key;

bool numpress = false; // Indicate that Number was pressed. Needs to be cleared to accept a new keypress

void ReadKeybd() {
  if (InputMode == INPUT_NO_INPUT) {
    return;
  }
  else{
    ReadKeyboard();
  }
}

void ReadKeyboard() {
  key = get_Key();
  // key = Code to decode the byte "key" to a number and then call "num", IF the key pressed is not "*" or "#".

  if (key) {
    if (key == 11) {
      OutputEnable = !OutputEnable;
      return;
    }
    if (key == 12) {
      return;
    }
    else {
      if (numpress == false) {
        if (key == 10) {
          key = 0;
        }
        num(key);
        Serial.print(F("Key pressed: "));
        Serial.println(key);
        numpress = true; // Number has been pressed
        UpdateFreqArea = true;
        UpdateAmpArea = true;
        UpdateModArea = true;
        return;
      }
    }
  }
  else {
    numpress = false; // No Number has been pressed
    // Serial.println(F("KeyReleased"));
    return;
  }
}

void num(signed long n) {
  //Add a number
  keyboardInput = 10 * keyboardInput + n;
}

/*
   Touch-Functions
*/

// Touch-Position Variables
uint16_t x, y;
uint8_t z;
// Adjusted value of the Touch-Coordinates to fit the grid
uint16_t cx, cy;

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 3790
#define TS_MAXX 250
#define TS_MINY 3800
#define TS_MAXY 250

/*
   Touch-Calibration Routine
*/

void TouchInit() {
  touch.writeRegister8(STMPE_INT_STA, 0xFF); // reset all ints
}

void TouchCalibration() {

}

void ReadTouch() {

  if (touch.touched()) {
    // read x & y & z;
    while (! touch.bufferEmpty()) {
      //      Serial.print(touch.bufferSize());
      touch.readData(&x, &y, &z);
      //      Serial.print("->(");
      //      Serial.print(x); Serial.print(", ");
      //      Serial.print(y); Serial.print(", ");
      //      Serial.print(z);
      //      Serial.println(")");
      CalcPixelPos();
    }
    touch.writeRegister8(STMPE_INT_STA, 0xFF); // reset all ints
    updateButtons = true;
  }
  TouchButton();
  cx = 0; // Reset cx and cy to prevent overflow
  cy = 0;
}

void CalcPixelPos() {
  cy = map(x, TS_MINX, TS_MAXX, tft.height(), 0);
  cx = map(y, TS_MINY, TS_MAXY, 0, tft.width());
  //  Serial.print("Touch-Position: cx = ");
  //  Serial.print(cx); Serial.print(" , ");
  //  Serial.print("cy = "); Serial.print(cy);
  //  Serial.println(" ");
}

void TouchButton() {
  switch (SysStatus) {
    case STATE_NORM_OP:
      if (cx > 330) {
        if (cy > 30 && cy < 80) {
          SysStatus = STATE_ENTER_FREQ;
          InputMode = INPUT_ENTER_FREQ;
          return;
        }
        if (cy > 90 && cy < 140) {
          SysStatus = STATE_ENTER_AMPLITUDE;
          return;
        }
        if (cy > 150 && cy < 200) {
          SysStatus = STATE_ENTER_MODULATION_TYPE;
          return;
        }
        if (cy > 210 && cy < 260) {
          OutputEnable = !OutputEnable;
          InputMode = INPUT_NO_INPUT;
          return;
        }
        if (cy > 270 && cy < 320) {
          SysStatus = STATE_MODE_SELECT_2;
          InputMode = INPUT_NO_INPUT;
          return;
        }
      }
      if (cx < 290) {
        if (cy > 30 && cy < 110) {
          SysStatus = STATE_ENTER_FREQ;
          InputMode = INPUT_ENTER_FREQ;
          return;
        }
        if (cy > 115 && cy < 195) {
          SysStatus = STATE_ENTER_AMPLITUDE;
          return;
        }
        if (cy > 200 && cy < 320) {
          SysStatus = STATE_ENTER_MODULATION_TYPE;
          return;
        }
      }
      break;
    case STATE_MODE_SELECT_2:
      if (cx > 330) {
        if (cy > 30 && cy < 80) {
          SysStatus = STATE_ADV_FUNCTIONS;
          InputMode = INPUT_NO_INPUT;
          return;
        }
        if (cy > 90 && cy < 140) {
          SysStatus = STATE_SIGPATH_CTRL;
          InputMode = INPUT_NO_INPUT;
          return;
        }
        if (cy > 150 && cy < 200) {
          SysStatus = STATE_CONFIG_1;
          ClearScreen = true;
          InputMode = INPUT_NO_INPUT;
          return;
        }
        if (cy > 210 && cy < 260) {
          SysStatus = STATE_DEMO;
          InputMode = INPUT_NO_INPUT;
          return;
        }
        if (cy > 270 && cy < 320) {
          //          Serial.print("SysStatus = ");
          //          Serial.print(SysStatus, HEX);
          SysStatus = 0x00;
          InputMode = INPUT_NO_INPUT;
          //          Serial.print(" SysStatus Now = ");
          //          Serial.println(SysStatus, HEX);
          return;
        }
      }
      if (cx < 290) {
        if (cy > 30 && cy < 110) {
          SysStatus = STATE_ENTER_FREQ;
          InputMode = INPUT_ENTER_FREQ;
          return;
        }
        if (cy > 115 && cy < 195) {
          SysStatus = STATE_ENTER_AMPLITUDE;
          return;
        }
        if (cy > 200 && cy < 320) {
          SysStatus = STATE_ENTER_MODULATION_TYPE;
          return;
        }
      }
    case STATE_ADV_FUNCTIONS:
      if (cx > 330) {
        if (cy > 30 && cy < 80) {
          SysStatus = STATE_ENTER_BURST;
          return;
        }
        if (cy > 90 && cy < 140) {
          SysStatus = STATE_ENTER_RAMP;
          return;
        }
        if (cy > 150 && cy < 200) {
          SysStatus = STATE_ADV_MODULATION;
          return;
        }
        if (cy > 210 && cy < 260) {
          SysStatus = STATE_ARBITRARY_WAVE;
          return;
        }
        if (cy > 270 && cy < 320) {
          SysStatus = STATE_MODE_SELECT_2;
          InputMode = INPUT_NO_INPUT;
          return;
        }
      }
      if (cx < 290) {
        if (cy > 30 && cy < 110) {
          return;
        }
      }
      break;

    case STATE_ADV_MODULATION:
      if (cx > 330) {
        if (cy > 30 && cy < 80) {
          return;
        }
        if (cy > 90 && cy < 140) {
          return;
        }
        if (cy > 150 && cy < 200) {
          return;
        }
        if (cy > 210 && cy < 260) {
          return;
        }
        if (cy > 270 && cy < 320) {
          SysStatus = STATE_MODE_SELECT_2;
          InputMode = INPUT_NO_INPUT;
          return;
        }
      }
      if (cx < 290) {
        return;
      }
      break;
    case STATE_ARBITRARY_WAVE:
      if (cx > 330) {
        if (cy > 30 && cy < 80) {
          return;
        }
        if (cy > 90 && cy < 140) {
          return;
        }
        if (cy > 150 && cy < 200) {
          return;
        }
        if (cy > 210 && cy < 260) {
          return;
        }
        if (cy > 270 && cy < 320) {
          SysStatus = STATE_MODE_SELECT_2;
          InputMode = INPUT_NO_INPUT;
          return;
        }
      }
      if (cx < 290) {
        if (cy > 30 && cy < 110) {
          return;
        }
        if (cy > 115 && cy < 195) {
          return;
        }
        if (cy > 200 && cy < 320) {
          return;
        }
      }
      break;
    case STATE_SIGPATH_CTRL:
      if (cx > 330) {
        if (cy > 30 && cy < 80) {
          SigPathAuto = !SigPathAuto;
          return;
        }
        if (cy > 90 && cy < 140) {
          ExtSource = !ExtSource;
          //          SetSignalSource(ExtSource);
          return;
        }
        if (cy > 150 && cy < 200) {
          ExtAM = !ExtAM;
          return;
        }
        if (cy > 210 && cy < 260) {
          //          AttenAuto = !AttenAuto;
          return;
        }
        if (cy > 270 && cy < 320) {
          SysStatus = STATE_MODE_SELECT_2;
          InputMode = INPUT_NO_INPUT;
          return;
        }
      }
      if (cx < 290) {
        if (cy > 30 && cy < 110) {
          // REPLACE THE COORDINATES WITH THE COORDINATE CORRESPONDING TO THE FILTER_MAP
          return;
        }
      }
      break;

    /*
     * *** CALIBRATION-MODE CONTROLS
    */

    case STATE_SIGPATH_MANUAL:
      if (cx > 330) {
        if (cy > 30 && cy < 80) {
          ASF_OFFSET++;
          SetAmplitudeAD9910(-10, true);
          UpdateDisplay();
          return;
        }
        if (cy > 90 && cy < 140) {
          ASF_OFFSET--;
          SetAmplitudeAD9910(-10, true);
          UpdateDisplay();
          return;
        }
        if (cy > 150 && cy < 200) {
          FTW_OFFSET++;
          SetFreqAD9910(Freq);
          UpdateDisplay();
          return;
        }
        if (cy > 210 && cy < 260) {
          FTW_OFFSET--;
          SetFreqAD9910(Freq);
          UpdateDisplay();
          return;
        }
        if (cy > 270 && cy < 320) {
          // SAVE OFFSET_Values to NV-RAM Address
          SysStatus = STATE_CONFIG_3;
          InputMode = INPUT_NO_INPUT;
          return;
        }
      }
      break;

    case STATE_SIGSOURCE_CAL:
      if (cx > 330) {
        if (cy > 30 && cy < 80) {
          ASF_OFFSET++;
          SetAmplitudeAD9910(-10, true);
          UpdateDisplay();
          return;
        }
        if (cy > 90 && cy < 140) {
          ASF_OFFSET--;
          SetAmplitudeAD9910(-10, true);
          UpdateDisplay();
          return;
        }
        if (cy > 150 && cy < 200) {
          FTW_OFFSET++;
          SetFreqAD9910(Freq);
          UpdateDisplay();
          return;
        }
        if (cy > 210 && cy < 260) {
          FTW_OFFSET--;
          SetFreqAD9910(Freq);
          UpdateDisplay();
          return;
        }
        if (cy > 270 && cy < 320) {
          // SAVE OFFSET_Values to NV-RAM Address
          SysStatus = STATE_CONFIG_3;
          InputMode = INPUT_NO_INPUT;
          return;
        }
      }
      break;
    case STATE_SIGPATH_CAL: // Setup-Screen for the SignalPath on the analog Board
      if (cx > 330) {
        if (cy > 30 && cy < 80) {
          //          SysStatus = STATE_ENTER_FREQ;
          return;
        }
        if (cy > 90 && cy < 140) {
          //          SysStatus = STATE_ENTER_AMPLITUDE;
          return;
        }
        if (cy > 150 && cy < 200) {
          //          SysStatus = STATE_ENTER_MODULATION_TYPE;
          return;
        }
        if (cy > 210 && cy < 260) {
          //          SysStatus = STATE_CONFIG;
          return;
        }
        if (cy > 270 && cy < 320) {

          SysStatus = STATE_CONFIG_3;
          InputMode = INPUT_NO_INPUT;
          return;
        }
      }
      break;
    case STATE_SIGPATH_COMP:
      if (cx > 330) {
        if (cy > 30 && cy < 80) {
          CalRef();
          return;
        }
        if (cy > 90 && cy < 140) {
          //          SysStatus = STATE_ENTER_AMPLITUDE;
          return;
        }
        if (cy > 150 && cy < 200) {
          //          SysStatus = STATE_ENTER_MODULATION_TYPE;
          return;
        }
        if (cy > 210 && cy < 260) {
          //          SysStatus = STATE_CONFIG;
          return;
        }
        if (cy > 270 && cy < 320) {
          SysStatus = STATE_CONFIG_3;
          InputMode = INPUT_NO_INPUT;
          return;
        }
      }
      break;
    case STATE_TOUCH_CAL:
      if (cx > 330) {
        if (cy > 30 && cy < 80) {
          //          SysStatus = STATE_ENTER_FREQ;
          return;
        }
        if (cy > 90 && cy < 140) {
          //          SysStatus = STATE_ENTER_AMPLITUDE;
          return;
        }
        if (cy > 150 && cy < 200) {
          //          SysStatus = STATE_ENTER_MODULATION_TYPE;
          return;
        }
        if (cy > 210 && cy < 260) {
          //          SysStatus = STATE_CONFIG;
          return;
        }
        if (cy > 270 && cy < 320) {
          SysStatus = STATE_CONFIG_4;
          InputMode = INPUT_NO_INPUT;
          return;
        }
      }
      break;

    /*
     * *** CONFIG-CONTROLS
    */

    case STATE_CONFIG_1:
      if (cx > 330) {
        if (cy > 30 && cy < 80) {
          CheckAD9910();
          return;
        }
        if (cy > 90 && cy < 140) {
          CheckADF4351();
          Message("ADF-Mode = CheckVCO", BLUE);
          return;
        }
        if (cy > 150 && cy < 200) {
          CheckAnalog();
          return;
        }
        if (cy > 210 && cy < 260) {
          SysStatus = STATE_CONFIG_2;
          return;
        }
        if (cy > 270 && cy < 320) {
          SysStatus = STATE_NORM_OP;
          InputMode = INPUT_NO_INPUT;
          return;
        }
      }
      break;
    case STATE_CONFIG_2:
      if (cx > 330) {
        if (cy > 30 && cy < 80) {
          byte AttenBackup = Atten;
          Message("Checking Attenuator - Please wait", CYAN);
          CheckAttenuator(false);
          Atten = AttenBackup;
          SetAttenuator(Atten);
          UpdateAmpArea = true;
          UpdateAmpArea = true;
          DrawAmplitudeArea(OUTPUT_dBm);
          Message(" ", BLACK);
          return;
        }
        if (cy > 90 && cy < 140) {
          Wire.requestFrom(GPIO_ADR, 1);
          byte GPIO_State = Wire.read();
          bitClear(GPIO_State, 7);
          Wire.beginTransmission(GPIO_ADR);
          Wire.write(GPIO_State);
          Wire.endTransmission();
          delay(100);
          bitSet(GPIO_State, 7);
          Wire.beginTransmission(GPIO_ADR);
          Wire.write(GPIO_State);
          Wire.endTransmission();
          return;
        }
        if (cy > 150 && cy < 200) {
          Serial.print(F("Keyboard_Controller-State: "));
          Wire.requestFrom(0x21, 6);
          Serial.print(Wire.read(), HEX);
          Serial.print(F(" | "));
          Serial.print(Wire.read(), HEX);
          Serial.print(F(" | "));
          Serial.print(Wire.read(), HEX);
          Serial.print(F(" | "));
          Serial.print(Wire.read(), HEX);
          Serial.print(F(" | "));
          Serial.print(Wire.read(), HEX);
          Serial.print(F(" | "));
          Serial.println(Wire.read(), HEX);
          return;
        }
        if (cy > 210 && cy < 260) {
          SysStatus = STATE_CONFIG_3;
          return;
        }
        if (cy > 270 && cy < 320) {
          SysStatus = STATE_NORM_OP;
          InputMode = INPUT_NO_INPUT;
          return;
        }
      }
      break;
    case STATE_CONFIG_3:
      if (cx > 330) {
        if (cy > 30 && cy < 80) {
          SysStatus = STATE_SIGPATH_MANUAL;
          return;
        }
        if (cy > 90 && cy < 140) {
          SysStatus = STATE_SIGPATH_COMP;
          return;
        }
        if (cy > 150 && cy < 200) {
          SysStatus = STATE_SIGPATH_CAL;
          return;
        }
        if (cy > 210 && cy < 260) {
          SysStatus = STATE_CONFIG_4;
          return;
        }
        if (cy > 270 && cy < 320) {
          SysStatus = STATE_NORM_OP;
          InputMode = INPUT_NO_INPUT;
          return;
        }
      }
      break;
    case STATE_CONFIG_4:
      if (cx > 330) {
        if (cy > 30 && cy < 80) {
          //          SysStatus = ;
          return;
        }
        if (cy > 90 && cy < 140) {
          //          SysStatus = ;
          return;
        }
        if (cy > 150 && cy < 200) {
          //          SysStatus = ;
          return;
        }
        if (cy > 210 && cy < 260) {
          SysStatus = STATE_CONFIG_5;
          return;
        }
        if (cy > 270 && cy < 320) {
          SysStatus = STATE_NORM_OP;
          InputMode = INPUT_NO_INPUT;
          return;
        }
      }
      break;
    case STATE_CONFIG_5:
      if (cx > 330) {
        if (cy > 30 && cy < 80) {
          //          SysStatus = ;
          return;
        }
        if (cy > 90 && cy < 140) {
          //          SysStatus = ;
          return;
        }
        if (cy > 150 && cy < 200) {
          //          SysStatus = ;
          return;
        }
        if (cy > 210 && cy < 260) {
          SysStatus = STATE_CONFIG_6;
          return;
        }
        if (cy > 270 && cy < 320) {
          SysStatus = STATE_NORM_OP;
          InputMode = INPUT_NO_INPUT;
          return;
        }
      }
      break;
    case STATE_CONFIG_6:
      if (cx > 330) {
        if (cy > 30 && cy < 80) {
          //          SysStatus = ;
          return;
        }
        if (cy > 90 && cy < 140) {
          //          SysStatus = ;
          return;
        }
        if (cy > 150 && cy < 200) {
          SysStatus = STATE_DEBUG;
          Message("DEBUG_MODE ACTIVE", RED);
          return;
        }
        if (cy > 210 && cy < 260) {
          SysStatus = STATE_CONFIG_1;
          return;
        }
        if (cy > 270 && cy < 320) {
          SysStatus = STATE_NORM_OP;
          InputMode = INPUT_NO_INPUT;
          return;
        }
      }
      break;

    case STATE_ENTER_FREQ:
      if (cx > 330) {
        if (cy > 30 && cy < 80) {
          if (keyboardInput >= 4) {
            Message(F("Error! Value out of valid range!"), RED);
            keyboardInput = 0;
            UpdateFreqArea = true;
            return;
          }
          SysStatus = STATE_NORM_OP;
          Freq = keyboardInput * 1000000000; // Multiply by 1 billion to scale the input-data to GHz
          SetFreq(Freq); // Update Frequency
          UpdateFreqArea = true;
          keyboardInput = 0;
          InputMode = INPUT_NO_INPUT;
          return;
        }
        if (cy > 90 && cy < 140) {
          if (keyboardInput >= 4400) {
            Message(F("Error! Value out of valid range!"), RED);
            keyboardInput = 0;
            UpdateFreqArea = true;
            return;
          }
          SysStatus = STATE_NORM_OP;
          Freq = keyboardInput * 1000000; // Multiply by 1 million to scale the input-data to MHz
          SetFreq(Freq);
          UpdateFreqArea = true;
          keyboardInput = 0;
          InputMode = INPUT_NO_INPUT;
          return;
        }
        if (cy > 150 && cy < 200) {
          if (keyboardInput >= 4400000) {
            Message(F("Error! Value out of valid range!"), RED);
            keyboardInput = 0;
            UpdateFreqArea = true;
            return;
          }
          SysStatus = STATE_NORM_OP;
          Freq = keyboardInput * 1000; // Multiply by 1000 to scale the input-data to kHz
          SetFreq(Freq);
          UpdateFreqArea = true;
          keyboardInput = 0;
          InputMode = INPUT_NO_INPUT;
          return;
        }
        if (cy > 210 && cy < 260) {
          if (keyboardInput >= 4300000000) {
            Message(F("Error! Value out of valid range!"), RED);
            keyboardInput = 0;
            UpdateFreqArea = true;
            return;
          }
          SysStatus = STATE_NORM_OP;
          Freq = keyboardInput;
          SetFreq(Freq);
          UpdateFreqArea = true;
          keyboardInput = 0;
          InputMode = INPUT_NO_INPUT;
          return;
        }
        if (cy > 270 && cy < 320) {
          keyboardInput = 0;
          InputMode = INPUT_NO_INPUT;
          SysStatus = STATE_NORM_OP;
          return;
        }
      }
      if (cx < 290) {
        if (cy > 30 && cy < 110) {
          SysStatus = STATE_ENTER_FREQ;
          InputMode = INPUT_ENTER_FREQ;
          return;
        }
        if (cy > 115 && cy < 195) {
          SysStatus = STATE_ENTER_AMPLITUDE;
          return;
        }
        if (cy > 200 && cy < 320) {
          SysStatus = STATE_ENTER_MODULATION_TYPE;
          return;
        }
      }

    case STATE_ENTER_AMPLITUDE:
      if (cx > 330) {
        if (cy > 30 && cy < 80) {
          SysStatus = STATE_NORM_OP;
          OUTPUT_dBm = keyboardInput + OUTPUT_DBM_OFFSET; // Multiply by 1 billion to scale the input-data to GHz
          SetAmplitude(OUTPUT_dBm); // Update Amplitude
          AmplitudeModeDB = true;
          UpdateAmpArea = true;
          keyboardInput = 0;
          InputMode = INPUT_NO_INPUT;
          return;
        }
        if (cy > 90 && cy < 140) {
          SysStatus = STATE_NORM_OP;
          OUTPUT_dBm = (0 - keyboardInput) * OUTPUT_DBM_OFFSET; // Multiply by 1 million to scale the input-data to MHz
          SetAmplitude(OUTPUT_dBm); // Update Amplitude
          AmplitudeModeDB = true;
          UpdateAmpArea = true;
          keyboardInput = 0;
          InputMode = INPUT_NO_INPUT;
          return;
        }
        if (cy > 150 && cy < 200) {
          SysStatus = STATE_NORM_OP;
          float keyboardInputFloat = float(keyboardInput);
          OUTPUT_dBm = 10 + (20 * (log(keyboardInputFloat)));
          SetAmplitude(OUTPUT_dBm); // Update Amplitude
          AmplitudeModeDB = false;
          UpdateAmpArea = true;
          keyboardInput = 0;
          InputMode = INPUT_NO_INPUT;
          return;
        }
        if (cy > 210 && cy < 260) {
          SysStatus = STATE_ATTEN_CTRL_PAGE;
          return;
        }
        if (cy > 270 && cy < 320) {
          keyboardInput = 0;
          InputMode = INPUT_NO_INPUT;
          SysStatus = STATE_NORM_OP;
          return;
        }
      }
      if (cx < 290) {
        if (cy > 30 && cy < 110) {
          SysStatus = STATE_ENTER_FREQ;
          InputMode = INPUT_ENTER_FREQ;
          return;
        }
        if (cy > 115 && cy < 195) {
          SysStatus = STATE_ENTER_AMPLITUDE;
          return;
        }
        if (cy > 200 && cy < 320) {
          SysStatus = STATE_ENTER_MODULATION_TYPE;
          return;
        }
      }

    case STATE_ENTER_MODULATION_TYPE:
      if (cx > 330) {
        if (cy > 30 && cy < 80) {
          SysStatus = STATE_ENTER_AM_PARAMETERS;
          return;
        }
        if (cy > 90 && cy < 140) {
          SysStatus = STATE_ENTER_FM_PARAMETERS;
          return;
        }
        if (cy > 150 && cy < 200) {
          SysStatus = STATE_ENTER_PM_PARAMETERS;
          return;
        }
        if (cy > 210 && cy < 260) {
          // Enable / Disable Modulation
          ModulationEnable = !ModulationEnable;
          return;
        }
        if (cy > 270 && cy < 320) {
          keyboardInput = 0;
          InputMode = INPUT_NO_INPUT;
          SysStatus = STATE_NORM_OP;
          return;
        }
      }
      if (cx < 290) {
        if (cy > 30 && cy < 110) {
          SysStatus = STATE_ENTER_FREQ;
          InputMode = INPUT_ENTER_FREQ;
          return;
        }
        if (cy > 115 && cy < 195) {
          SysStatus = STATE_ENTER_AMPLITUDE;
          return;
        }
        if (cy > 200 && cy < 320) {
          SysStatus = STATE_ENTER_MODULATION_TYPE;
          return;
        }
      }
      break;


    case STATE_ATTEN_CTRL_PAGE:
      if (cx > 330) {
        if (cy > 30 && cy < 80) {
          AttenAuto = !AttenAuto;
          UpdateAmpArea = true;
          return;
        }
        if (cy > 90 && cy < 140) {
          // Not Implemented
          return;
        }
        if (cy > 150 && cy < 200) {
          if (AttenAuto == false) {
            Atten++;
            SetAttenuator(Atten);
          }
          UpdateAmpArea = true;
          return;
        }
        if (cy > 210 && cy < 260) {
          if (AttenAuto == false) {
            Atten--;
            SetAttenuator(Atten);
          }
          UpdateAmpArea = true;
          return;
        }
        if (cy > 270 && cy < 320) {
          keyboardInput = 0;
          InputMode = INPUT_NO_INPUT;
          SysStatus = STATE_ENTER_AMPLITUDE;
          UpdateAmpArea = true;
          return;
        }
      }
      break;
    //
    default:
      Message(F("ERROR! Unimplemented Mode"), RED);

      tft.setCursor(0, 0);
      tft.setTextColor(MAGENTA);
      tft.setTextSize(1);
      tft.setTextWrap(false);
      tft.fillRect(0, 0, 130, 15, BLACK);
      tft.print(F("SysStatus = "));
      tft.println(SysStatus, HEX);
      delay(4000);
      SysStatus = STATE_NORM_OP;
      UpdateFreqArea = true;
      UpdateAmpArea = true;
      UpdateModArea = true;
      updateButtons = true;
      break;
  }
}
