

/*
   This is the Driver for the AD9910
   Codes:
   - 0x00 = OFF
   - 0x10 = PowerOnDefaults (Frequency = 10MHz, Output = ON)
   - 0x20 = Standby (Frequency = LastFrequency, Output = OFF)
   - 0x30 = DDS-Check (Frequency = 200MHz, Output = ON)
   - 0x40 = TEST ((Frequency = 100 MHz, Output = ON)

   Please consult datasheet for reference and register-maps.
   Unless otherwise noted, the values assigned to the variables are the default-values in the datasheet.
*/

// *** Constants to configure the DDS-Chip AD9910 ***
// Control-Registers are 4 bytes wide if not otherwise specified
const byte CFR1_ADDR = 0x00;   // Address for the CFR1-Register - Needs to be send in the InstructionWord
const byte CFR2_ADDR = 0x01;
const byte CFR3_ADDR = 0x02;
const byte AuxDAC_ADDR = 0x03;
const byte IO_UPD_Rate_ADDR = 0x04;
const byte FTW_ADDR = 0x07;
const byte POW_ADDR = 0x08;
const byte ASF_ADDR = 0x09;
const byte DIGRAMP_Limit_ADDR = 0xB;
const byte DIGRAMP_Step_ADDR = 0xC;
const byte DIGRAMP_Rate_ADDR = 0xD;
const byte SINGLETONE_PROFILE_0 = 0x0E;

// Register-Bit Locations
// CFR 1
const uint32_t RAM_ENABLE_LOC = 2147483648;
const uint32_t RAM_PLAYBACK_DESTINATION_LOC = 536870912;
const uint32_t MANUAL_OSK_CONTROL_LOC = 8388608;
const uint32_t INVERSE_SINC_FILTER_LOC = 4194304;
const uint32_t INTERNAL_PROFILE_CONTROL_LOC = 131072;
const uint32_t DDS_SINE_LOC = 65536;
const uint32_t LOAD_LRR_IOUPDATE_LOC = 32768;
const uint32_t AUTOCLEAR_DIGI_RAMP_ACCU_LOC = 16384;
const uint32_t AUTOCLEAR_PHASE_ACCU_LOC = 8192;
const uint32_t CLEAR_DIGI_RAMP_ACCU_LOC = 4096;
const uint32_t CLEAR_PHASE_ACCU_LOC = 2048;
const uint32_t LOAD_ARR_IOUPDATE_LOC = 1024;
const uint32_t OSK_ENABLE_LOC = 512;
const uint32_t SELECT_AUTO_OSK_LOC = 256;
const uint32_t DIGITAL_POWER_DOWN_LOC = 128;
const uint32_t DAC_POWER_DOWN_LOC = 64;
const uint32_t REFCLK_INPUT_POWER_DOWN_LOC = 32;
const uint32_t AUX_DAC_POWER_DOWN_LOC = 16;
const uint32_t EXTERNAL_POWER_DOWN_LOC = 8;
const uint32_t SDIO_INPUT_ONLY_LOC = 2; // Bit 1: Sets the way the SDIO-Pin works. 0 = I/O (default) | 1 = Input Only (Needs to be 1 if SPI is used!)
const uint32_t LSB_FIRST_LOC = 1; // Bit 0: Switches between MSBFIRST and LSBFIRST - set to "1" to avoid multiply by "0" - Result is the same: x * 1 = x

// CFR 2
const uint32_t ENABLE_AMPLITUDE_SCALE_CW_PROFILES_LOC = 16777216;
const uint32_t INTERNAL_IOUPDATE_ACTIVE_LOC = 8388608;
const uint32_t SYNC_CLK_ENABLE_LOC = 4194304; //
const uint32_t DIGI_RAMP_DESTINATION_LOC = 1048576; // 2 Bits
const uint32_t DIGI_RAMP_ENABLE_LOC = 524288;
const uint32_t DIGI_RAMP_NO_DWELL_HIGH_LOC = 262144;
const uint32_t DIGI_RAMP_NO_DWELL_LOW_LOC = 131072;
const uint32_t READ_EFFECTIVE_FTW_LOC = 65536;
const uint32_t IOUPDATE_RATE_CTRL_LOC = 16384;
const uint32_t PD_CLK_ENABLE_LOC = 2048; // Disabled, because PD_CLK-Pin is not used.
const uint32_t PD_CLK_INVERT_LOC = 1024;
const uint32_t TX_ENABLE_INVERT_LOC = 512;
const uint32_t MATCHED_LATENCY_ENABLE_LOC = 128;
const uint32_t DATA_ASSEMBLER_HOLD_LAST_VALUE_LOC = 64;
const uint32_t SYNC_TIMING_VALIDATION_ERROR_LOC = 32;
const uint32_t PARALLEL_DATA_PORT_ENABLE_LOC = 16;
const uint32_t FM_GAIN_LOC = 1;

// CFR 3
const uint32_t DRV0_LOC = 268435456;              //
const uint32_t VCOSEL_LOC = 16777216;           //
const uint32_t ICP_LOC = 524288;              //
const uint32_t REFCLK_Div_Bypass_LOC = 32768;        //
const uint32_t REFCLK_Div_RESET_LOC = 16384;         //
const uint32_t PFD_RESET_LOC = 1024;                //
const uint32_t PLL_ENABLE_LOC = 256;                //
const uint32_t AD9910_PLL_DIVIDER_LOC = 2;            //

// *** Variables to configure the DDS-Chip AD9910 ***

// Register-Variables
uint32_t RegCFR1;              // Variable for Control Register 1 - 4 Bytes - See Datasheet for details
uint32_t RegCFR2;              // Variable for Control Register 2
uint32_t RegCFR3;              // Variable for Control Register 3
byte AuxDAC;                  // Stores the AUX-DAC Value
uint32_t IO_UPD_Rate;          // Stores value of the I/O Update Rate Register
uint32_t FTW;                  // Frequency Tuning Word - 32bit - Calculated by formula: FTW = ((2^32)*(fout/fclock))
uint16_t POW;                  // Phase Offset Word - 16bit Phase Offset Word
uint32_t ASF;                  // Amplitude Scale Factor - 32bits
uint32_t DIGRAMP_Limit;        // Limits of the Digital Ramp - Byte 7 - 4 = Upper Ramp Limit / Byte 3 - 0 = Lower Ramp Limit
uint32_t DIGRAMP_Step;         // Step of Digital Ramp - Byte 7 - 4 = Decrement Step Size / Byte 3 - 0 = Increment Step Size
uint16_t DIGRAMP_Rate;         // Rate of Diigtal Ramp - Byte 3 - 2 = Negative slope rate / Byte 1 - 0 = Positive Slope Rate

// CAL-Variables - Saves as OFFSET-Values to be added or subtracted
int ASF_OFFSET;
int FTW_OFFSET;

// CFR1-Values | CFR1 contains general settings
byte RAM_ENABLE = 0;                    // Bit 31
byte RAM_PLAYBACK_DESTINATION = 0;      // Bits 30 - 29: 0 = Frequency, 1 = Phase, 2 = Amplitude, 3 = Polar (Phase and Amplitude)
byte MANUAL_OSK_CONTROL = 1;            // Bit 23: Enables / Disables the Manual OSK-Control - NOT USED! PIN NOT CONNECTED
byte INVERSE_SINC_FILTER = 1;           // Bit 22: Enables/Disables the Inverse Sinc Filter
byte INTERNAL_PROFILE_CONTROL = 0;      // Bits 20 - 17: Selects the RAM-Profile
byte DDS_SINE = 0;                      // Bit 16: Selects the Sine / Cosine-Output
byte LOAD_LRR_IOUPDATE = 0;         // Bit 15: Sets the behavior of the digital ramp timer
byte AUTOCLEAR_DIGI_RAMP_ACCU = 0;
byte AUTOCLEAR_PHASE_ACCU = 0;
byte CLEAR_DIGI_RAMP_ACCU = 0;
byte CLEAR_PHASE_ACCU = 0;
byte LOAD_ARR_IOUPDATE = 0;
byte OSK_ENABLE = 0;
byte SELECT_AUTO_OSK = 0;
byte DIGITAL_POWER_DOWN = 0;
byte DAC_POWER_DOWN = 0;
byte REFCLK_INPUT_POWER_DOWN = 0;
byte AUX_DAC_POWER_DOWN = 0;
byte EXTERNAL_POWER_DOWN = 0;
const byte SDIO_INPUT_ONLY = 1; // Bit 1: Sets the way the SDIO-Pin works. 0 = I/O (default) | 1 = Input Only (Needs to be 1 if SPI is used!)
const byte LSB_FIRST = 0; // Bit 0: Switches between MSBFIRST and LSBFIRST

// CFR2-Values
byte ENABLE_AMPLITUDE_SCALE_CW_PROFILES = 1;
byte INTERNAL_IOUPDATE_ACTIVE = 0;
byte SYNC_CLK_ENABLE = 1; //
byte DIGI_RAMP_DESTINATION = 0; // 2 Bits
byte DIGI_RAMP_ENABLE = 0;
byte DIGI_RAMP_NO_DWELL_HIGH = 0;
byte DIGI_RAMP_NO_DWELL_LOW = 0;
byte READ_EFFECTIVE_FTW = 0;
byte IOUPDATE_RATE_CTRL = 0;
byte PD_CLK_ENABLE = 1;
byte PD_CLK_INVERT = 0;
byte TX_ENABLE_INVERT = 0;
byte MATCHED_LATENCY_ENABLE = 0;
byte DATA_ASSEMBLER_HOLD_LAST_VALUE = 0;
byte SYNC_TIMING_VALIDATION_ERROR = 0;
byte PARALLEL_DATA_PORT_ENABLE = 0;
byte FM_GAIN = 0;

// CFR3-Values | CFR3 configures internal PLL
byte DRV0 = B11;              // Setting for REFCLK_OUT Drive - Default: REFCLK_OUT OFF
byte VCOSEL = B101;           // Select the VCO - Default: VCO5 for a internal Clock of 920 - 1030 MHz
byte Icp = B111;              // Sets the Charge Pump Current - This value will require experimentation and may be stored in external NVRAM
byte REFCLK_Div_Bypass = 0;        // Controls the InputDivider-Bypass - Default: 0 (OFF)
byte REFCLK_Div_RESET = 1;         // Controls the InputDivider - Default: 0 (Divider is reset and not working)
byte PFD_RESET = 0;                // Enables / Disables the Phase Comparator - Default: 1 (Phase Comparator active, PLL working)
byte PLL_ENABLE = 1;                // Enables / Disables the PLL-Output - Default: true (PLL-Output to DDS-CLOCK
byte AD9910_PLL_DIVIDER = 25;            // The Divider for the DDS-CLOCK PLL - Default: 25 (40 MHz  * 25 = 1000 MHz) - Formula: PLL_Clock / RefClock = PLL_DIVIDER - PLL_CLOCK = 1000MHz
unsigned long DDSCLK = 1000000000UL;        // DDS-Clock in Hz

/*
   Modes for the AD9910:
   - 0x00 = PowerDown: Everything is powered down to conserve power
   - 0x10 = Normal Operation
   - 0x20 = Standby: Everything turned on, except for the DAC to allow for very fast power up
   - 0x30 = NOT USED
   - 0x40 = TestMode: 10MHz, Max Amplitude,
   - 0xFF = PowerOn-Initialization
*/

void SetupAD9910(int AD9910_Mode) {
  switch (AD9910_Mode) {
    case STATE_NORM_OP:
      DIGITAL_POWER_DOWN = 0;
      DAC_POWER_DOWN = 0;
      REFCLK_INPUT_POWER_DOWN = 0;
      AUX_DAC_POWER_DOWN = 0;
      SendCFR();
      break;
    case STATE_POWERDOWN:
      DIGITAL_POWER_DOWN = 1;
      DAC_POWER_DOWN = 1;
      REFCLK_INPUT_POWER_DOWN = 1;
      AUX_DAC_POWER_DOWN = 1;
      SendCFR();
      break;
    case STATE_STANDBY:
      DAC_POWER_DOWN = 1; // Disable the DDS-Output. All other components remain online
      SendCFR();
      break;
    case STATE_VCO_CHECK:
      Message("Not Implemented", YELLOW);
      break;
    case STATE_TEST:
      DIGITAL_POWER_DOWN = 0;
      DAC_POWER_DOWN = 0;
      REFCLK_INPUT_POWER_DOWN = 0;
      AUX_DAC_POWER_DOWN = 0;
      SendCFR();
      break;
    case 0xFF: // Initial Setup at system start
      Wire.beginTransmission(GPIO_ADR);
      Wire.write(0xBF); // Set AD9910_RST (Connected to I/O-Reset) to LOW (ACTIVE HIGH-input)
      Wire.endTransmission();
      delay(50);
      RegCFR1 = (unsigned long) (LSB_FIRST + SDIO_INPUT_ONLY * SDIO_INPUT_ONLY_LOC + EXTERNAL_POWER_DOWN * EXTERNAL_POWER_DOWN_LOC + AUX_DAC_POWER_DOWN * AUX_DAC_POWER_DOWN_LOC + REFCLK_INPUT_POWER_DOWN * REFCLK_INPUT_POWER_DOWN_LOC + DAC_POWER_DOWN * DAC_POWER_DOWN_LOC + DIGITAL_POWER_DOWN * DIGITAL_POWER_DOWN_LOC + SELECT_AUTO_OSK * SELECT_AUTO_OSK_LOC + OSK_ENABLE * OSK_ENABLE_LOC + LOAD_ARR_IOUPDATE * LOAD_ARR_IOUPDATE_LOC + CLEAR_PHASE_ACCU * CLEAR_PHASE_ACCU_LOC + CLEAR_DIGI_RAMP_ACCU * CLEAR_DIGI_RAMP_ACCU_LOC + AUTOCLEAR_PHASE_ACCU * AUTOCLEAR_PHASE_ACCU_LOC + AUTOCLEAR_DIGI_RAMP_ACCU * AUTOCLEAR_DIGI_RAMP_ACCU_LOC + LOAD_LRR_IOUPDATE * LOAD_LRR_IOUPDATE_LOC + DDS_SINE * DDS_SINE_LOC + INTERNAL_PROFILE_CONTROL * INTERNAL_PROFILE_CONTROL_LOC + INVERSE_SINC_FILTER * INVERSE_SINC_FILTER_LOC + MANUAL_OSK_CONTROL * MANUAL_OSK_CONTROL_LOC + RAM_PLAYBACK_DESTINATION * RAM_PLAYBACK_DESTINATION_LOC + RAM_ENABLE * RAM_ENABLE_LOC);
      Serial.print("RegCFR1 = 0x");
      Serial.println(RegCFR1, HEX);
      RegCFR2 = (unsigned long) (0 + FM_GAIN + PARALLEL_DATA_PORT_ENABLE * PARALLEL_DATA_PORT_ENABLE_LOC + SYNC_TIMING_VALIDATION_ERROR * SYNC_TIMING_VALIDATION_ERROR_LOC + DATA_ASSEMBLER_HOLD_LAST_VALUE * DATA_ASSEMBLER_HOLD_LAST_VALUE_LOC + MATCHED_LATENCY_ENABLE * MATCHED_LATENCY_ENABLE_LOC + TX_ENABLE_INVERT * TX_ENABLE_INVERT_LOC + PD_CLK_INVERT * PD_CLK_INVERT_LOC + PD_CLK_ENABLE * PD_CLK_ENABLE_LOC + IOUPDATE_RATE_CTRL * IOUPDATE_RATE_CTRL_LOC + READ_EFFECTIVE_FTW * READ_EFFECTIVE_FTW_LOC + DIGI_RAMP_NO_DWELL_LOW * DIGI_RAMP_NO_DWELL_LOW_LOC + DIGI_RAMP_NO_DWELL_HIGH * DIGI_RAMP_NO_DWELL_HIGH_LOC + DIGI_RAMP_ENABLE * DIGI_RAMP_ENABLE_LOC + DIGI_RAMP_DESTINATION * DIGI_RAMP_DESTINATION_LOC + SYNC_CLK_ENABLE * SYNC_CLK_ENABLE_LOC + INTERNAL_IOUPDATE_ACTIVE * INTERNAL_IOUPDATE_ACTIVE_LOC + ENABLE_AMPLITUDE_SCALE_CW_PROFILES * ENABLE_AMPLITUDE_SCALE_CW_PROFILES_LOC);
      Serial.print("RegCFR2 = 0x");
      Serial.println(RegCFR2, HEX);
      RegCFR3 = (unsigned long) (0 + AD9910_PLL_DIVIDER * AD9910_PLL_DIVIDER_LOC + PLL_ENABLE * PLL_ENABLE_LOC + PFD_RESET * PFD_RESET_LOC + REFCLK_Div_RESET * REFCLK_Div_RESET_LOC + REFCLK_Div_Bypass * REFCLK_Div_Bypass_LOC + Icp * ICP_LOC + VCOSEL * VCOSEL_LOC + DRV0 * DRV0_LOC);
      Serial.print("RegCFR3 = 0x");
      Serial.println(RegCFR3, HEX);
      FTW = round(4294967296UL / (DDSCLK / 4000000)); // Formula for calculating the FTW: FTW = ((2^32)*(fout/fclock)) // Frequency set to 1MHz
      AuxDAC = 0x7F;
      ASF = 0x3FFF;
      POW = 0x0000;
      WriteAD9910(CFR1_ADDR);
      WriteAD9910(CFR2_ADDR);
      WriteAD9910(CFR3_ADDR);
      WriteAD9910(AuxDAC_ADDR);
      WriteAD9910(FTW_ADDR);
      WriteAD9910(ASF_ADDR);
      SetFreqAD9910(1000000);
      Freq_Old = 1000000;
      break;
    default:
      break;
  }
}

/*
   The following subroutines calculate the Register-Contents for the AD9910 and send the data to it
*/

void SetFreqAD9910(double FreqAD9910) {
  FTW = round(4294967296UL / (DDSCLK / FreqAD9910)); // Formula for calculating the FTW: FTW = ((2^32)*(fout/fclock))
  Serial.print("FreqAD9910 = ");
  Serial.print(FreqAD9910, DEC);
  Serial.print(" FTW = ");
  Serial.println(FTW, DEC);
  WriteAD9910(SINGLETONE_PROFILE_0);
}

void SetPhaseOffsetAD9910(unsigned long PhaseOffsetAD9910) {
  POW = round(65536 * (PhaseOffsetAD9910 / 360));
  WriteAD9910(POW_ADDR);
}

// Amplitude-Settings in mVpp or dB
// -2dBm is the maximum RF-Power that may be injected into the System. As the full scale output-current is 20mA, the maximum output-voltage is 1V = 500mVpp
void SetAmplitudeAD9910(float AmplitudeAD9910, bool Decibels) {
  switch (Decibels) {
    case true:
      ASF = round(pow(2, 14) * (AmplitudeAD9910 / log(20)));
      WriteAD9910(ASF_ADDR);
      break;
    case false:
      float AmpAD9910 = AmplitudeAD9910 / 1000; // Divide by 500 to get the scaling-factor
      ASF = round(pow(2, 14) * AmpAD9910); // Multiply the Scaling-factor with 2^14 /16384
      WriteAD9910(ASF_ADDR);
      break;
  }
}

// Function to set the CFR1 and CFR2-Registers - Excludes CFR3 because that register is set at system startup and remains unchanged after that.
void SendCFR() {
  RegCFR1 = (unsigned long)(LSB_FIRST + SDIO_INPUT_ONLY * SDIO_INPUT_ONLY_LOC + EXTERNAL_POWER_DOWN * EXTERNAL_POWER_DOWN_LOC + AUX_DAC_POWER_DOWN * AUX_DAC_POWER_DOWN_LOC + REFCLK_INPUT_POWER_DOWN * REFCLK_INPUT_POWER_DOWN_LOC + DAC_POWER_DOWN * DAC_POWER_DOWN_LOC + DIGITAL_POWER_DOWN * DIGITAL_POWER_DOWN_LOC + SELECT_AUTO_OSK * SELECT_AUTO_OSK_LOC + OSK_ENABLE * OSK_ENABLE_LOC + LOAD_ARR_IOUPDATE * LOAD_ARR_IOUPDATE_LOC + CLEAR_PHASE_ACCU * CLEAR_PHASE_ACCU_LOC + CLEAR_DIGI_RAMP_ACCU * CLEAR_DIGI_RAMP_ACCU_LOC + AUTOCLEAR_PHASE_ACCU * AUTOCLEAR_PHASE_ACCU_LOC + AUTOCLEAR_DIGI_RAMP_ACCU * AUTOCLEAR_DIGI_RAMP_ACCU_LOC + LOAD_LRR_IOUPDATE * LOAD_LRR_IOUPDATE_LOC + DDS_SINE * DDS_SINE_LOC + INTERNAL_PROFILE_CONTROL * INTERNAL_PROFILE_CONTROL_LOC + INVERSE_SINC_FILTER * INVERSE_SINC_FILTER_LOC + MANUAL_OSK_CONTROL * MANUAL_OSK_CONTROL_LOC + RAM_PLAYBACK_DESTINATION * RAM_PLAYBACK_DESTINATION_LOC + RAM_ENABLE * RAM_ENABLE_LOC);
  Serial.print("RegCFR1 = 0x");
  Serial.println(RegCFR1, HEX);
  RegCFR2 = (unsigned long)(0 + FM_GAIN + PARALLEL_DATA_PORT_ENABLE * PARALLEL_DATA_PORT_ENABLE_LOC + SYNC_TIMING_VALIDATION_ERROR * SYNC_TIMING_VALIDATION_ERROR_LOC + DATA_ASSEMBLER_HOLD_LAST_VALUE * DATA_ASSEMBLER_HOLD_LAST_VALUE_LOC + MATCHED_LATENCY_ENABLE * MATCHED_LATENCY_ENABLE_LOC + TX_ENABLE_INVERT * TX_ENABLE_INVERT_LOC + PD_CLK_INVERT * PD_CLK_INVERT_LOC + PD_CLK_ENABLE * PD_CLK_ENABLE_LOC + IOUPDATE_RATE_CTRL * IOUPDATE_RATE_CTRL_LOC + READ_EFFECTIVE_FTW * READ_EFFECTIVE_FTW_LOC + DIGI_RAMP_NO_DWELL_LOW * DIGI_RAMP_NO_DWELL_LOW_LOC + DIGI_RAMP_NO_DWELL_HIGH * DIGI_RAMP_NO_DWELL_HIGH_LOC + DIGI_RAMP_ENABLE * DIGI_RAMP_ENABLE_LOC + DIGI_RAMP_DESTINATION * DIGI_RAMP_DESTINATION_LOC + SYNC_CLK_ENABLE * SYNC_CLK_ENABLE_LOC + INTERNAL_IOUPDATE_ACTIVE * INTERNAL_IOUPDATE_ACTIVE_LOC + ENABLE_AMPLITUDE_SCALE_CW_PROFILES * ENABLE_AMPLITUDE_SCALE_CW_PROFILES_LOC);
  Serial.print("RegCFR2 = 0x");
  Serial.println(RegCFR2, HEX);
  WriteAD9910(CFR1_ADDR);
  WriteAD9910(CFR2_ADDR);
}

//#define SPI_DEBUG
void WriteAD9910(byte  AD9910_INST) {
  digitalWrite(AD9910_CS, LOW); //Pull AD9910_CS LOW to select the chip
  byte buf[8]; // 64bit buffer to store individual bytes of the registers
#ifdef SPI_DEBUG
  //  RegCFR1 = 0x00800002;
  //  RegCFR2 = 0x01400820;
  //  RegCFR3 = 0x35384132;
  AuxDAC = 0x7F;
  ASF = 0x3FFF;
  POW = 0x0000;
  //FTW = 0x1999999A;
#endif
  SPI.begin();
  SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));
  SPI.transfer(AD9910_INST);
  switch (AD9910_INST) {
    case CFR1_ADDR:
      //      SPI.write32(RegCFR1); // DISABLE this line and ENABLE the following block on boards other than ESP8266 that do not have the "write32" function in their SPI-Library
      buf[0] = (byte) RegCFR1;
      buf[1] = (byte) (RegCFR1 >> 8);
      buf[2] = (byte) (RegCFR1 >> 16);
      buf[3] = (byte) (RegCFR1 >> 24);
#ifdef SPI_DEBUG
      Serial.println(F("BUFFER:"));
      Serial.print(F("buf[3] = 0x"));
      Serial.print(buf[3], HEX);
      Serial.print(F(" buf[2] = 0x"));
      Serial.print(buf[2], HEX);
      Serial.print(F(" buf[1] = 0x"));
      Serial.print(buf[1], HEX);
      Serial.print(F(" buf[0] = 0x"));
      Serial.println(buf[0], HEX);
#endif
      SPI.transfer(buf[3]);
      SPI.transfer(buf[2]);
      SPI.transfer(buf[1]);
      SPI.transfer(buf[0]);
      break;
    case CFR2_ADDR:
      //      SPI.write32(RegCFR2);
      buf[0] = (byte) RegCFR2;
      buf[1] = (byte) (RegCFR2 >> 8);
      buf[2] = (byte) (RegCFR2 >> 16);
      buf[3] = (byte) (RegCFR2 >> 24);
#ifdef SPI_DEBUG
      Serial.println(F("BUFFER:"));
      Serial.print(F("buf[3] = 0x"));
      Serial.print(buf[3], HEX);
      Serial.print(F(" buf[2] = 0x"));
      Serial.print(buf[2], HEX);
      Serial.print(F(" buf[1] = 0x"));
      Serial.print(buf[1], HEX);
      Serial.print(F(" buf[0] = 0x"));
      Serial.println(buf[0], HEX);
#endif
      SPI.transfer(buf[3]);
      SPI.transfer(buf[2]);
      SPI.transfer(buf[1]);
      SPI.transfer(buf[0]);
      break;
    case CFR3_ADDR:
      //      SPI.write32(RegCFR3);
      buf[0] = (byte) RegCFR3;
      buf[1] = (byte) (RegCFR3 >> 8);
      buf[2] = (byte) (RegCFR3 >> 16);
      buf[3] = (byte) (RegCFR3 >> 24);
#ifdef SPI_DEBUG
      Serial.println(F("BUFFER:"));
      Serial.print(F("buf[3] = 0x"));
      Serial.print(buf[3], HEX);
      Serial.print(F(" buf[2] = 0x"));
      Serial.print(buf[2], HEX);
      Serial.print(F(" buf[1] = 0x"));
      Serial.print(buf[1], HEX);
      Serial.print(F(" buf[0] = 0x"));
      Serial.println(buf[0], HEX);
#endif
      SPI.transfer(buf[3]);
      SPI.transfer(buf[2]);
      SPI.transfer(buf[1]);
      SPI.transfer(buf[0]);
      break;
    case AuxDAC_ADDR:
      SPI.transfer(0x00);
      SPI.transfer(0x00);
      SPI.transfer(0x00);
      SPI.transfer(AuxDAC);
      break;
    case IO_UPD_Rate_ADDR:
      //      SPI.write32(IO_UPD_Rate);
      buf[0] = (byte) IO_UPD_Rate;
      buf[1] = (byte) (IO_UPD_Rate >> 8);
      buf[2] = (byte) (IO_UPD_Rate >> 16);
      buf[3] = (byte) (IO_UPD_Rate >> 24);
#ifdef SPI_DEBUG
      Serial.println(F("BUFFER:"));
      Serial.print(F("buf[3] = 0x"));
      Serial.print(buf[3], HEX);
      Serial.print(F(" buf[2] = 0x"));
      Serial.print(buf[2], HEX);
      Serial.print(F(" buf[1] = 0x"));
      Serial.print(buf[1], HEX);
      Serial.print(F(" buf[0] = 0x"));
      Serial.println(buf[0], HEX);
#endif
      SPI.transfer(buf[3]);
      SPI.transfer(buf[2]);
      SPI.transfer(buf[1]);
      SPI.transfer(buf[0]);
      break;
    case FTW_ADDR:
      //      SPI.write32(FTW);
      buf[0] = (byte) FTW;
      buf[1] = (byte) (FTW >> 8);
      buf[2] = (byte) (FTW >> 16);
      buf[3] = (byte) (FTW >> 24);
#ifdef SPI_DEBUG
      Serial.println(F("BUFFER:"));
      Serial.print(F("buf[3] = 0x"));
      Serial.print(buf[3], HEX);
      Serial.print(F(" buf[2] = 0x"));
      Serial.print(buf[2], HEX);
      Serial.print(F(" buf[1] = 0x"));
      Serial.print(buf[1], HEX);
      Serial.print(F(" buf[0] = 0x"));
      Serial.println(buf[0], HEX);
#endif
      SPI.transfer(buf[3]);
      SPI.transfer(buf[2]);
      SPI.transfer(buf[1]);
      SPI.transfer(buf[0]);
      break;
    case POW_ADDR:
      SPI.transfer16(POW);      //      buf[0] = (byte) POW;
      //      buf[1] = (byte) POW >> 8;
      //      buf[2] = (byte) POW >> 16;
      //      buf[3] = (byte) POW >> 24;
      //SPI.transfer(buf[3]);
      //      SPI.transfer(buf[2]);
      //      SPI.transfer(buf[1]);
      //      SPI.transfer(buf[0]);
      break;
    case ASF_ADDR:
      //      SPI.write32(ASF);
      buf[0] = (byte) ASF;
      buf[1] = (byte) (ASF >> 8);
      buf[2] = (byte) (ASF >> 16);
      buf[3] = (byte) (ASF >> 24);
#ifdef SPI_DEBUG
      Serial.println(F("BUFFER:"));
      Serial.print(F("buf[3] = 0x"));
      Serial.print(buf[3], HEX);
      Serial.print(F(" buf[2] = 0x"));
      Serial.print(buf[2], HEX);
      Serial.print(F(" buf[1] = 0x"));
      Serial.print(buf[1], HEX);
      Serial.print(F(" buf[0] = 0x"));
      Serial.println(buf[0], HEX);
#endif
      SPI.transfer(buf[3]);
      SPI.transfer(buf[2]);
      SPI.transfer(buf[1]);
      SPI.transfer(buf[0]);
      break;
    case DIGRAMP_Limit_ADDR:
      buf[0] = (byte) DIGRAMP_Limit;
      buf[1] = (byte) (DIGRAMP_Limit >> 8);
      buf[2] = (byte) (DIGRAMP_Limit >> 16);
      buf[3] = (byte) (DIGRAMP_Limit >> 24);
      buf[4] = (byte) (DIGRAMP_Limit >> 32);
      buf[5] = (byte) (DIGRAMP_Limit >> 40);
      buf[6] = (byte) (DIGRAMP_Limit >> 48);
      buf[7] = (byte) (DIGRAMP_Limit >> 56);
      SPI.transfer(buf[7]);
      SPI.transfer(buf[6]);
      SPI.transfer(buf[5]);
      SPI.transfer(buf[4]);
      SPI.transfer(buf[3]);
      SPI.transfer(buf[2]);
      SPI.transfer(buf[1]);
      SPI.transfer(buf[0]);
      break;
    case DIGRAMP_Step_ADDR:
      buf[0] = (byte) DIGRAMP_Step;
      buf[1] = (byte) (DIGRAMP_Step >> 8);
      buf[2] = (byte) (DIGRAMP_Step >> 16);
      buf[3] = (byte) (DIGRAMP_Step >> 24);
      buf[4] = (byte) (DIGRAMP_Step >> 32);
      buf[5] = (byte) (DIGRAMP_Step >> 40);
      buf[6] = (byte) (DIGRAMP_Step >> 48);
      buf[7] = (byte) (DIGRAMP_Step >> 56);
      SPI.transfer(buf[7]);
      SPI.transfer(buf[6]);
      SPI.transfer(buf[5]);
      SPI.transfer(buf[4]);
      SPI.transfer(buf[3]);
      SPI.transfer(buf[2]);
      SPI.transfer(buf[1]);
      SPI.transfer(buf[0]);
      break;
    case DIGRAMP_Rate_ADDR:
      buf[0] = (byte) DIGRAMP_Rate;
      buf[1] = (byte) (DIGRAMP_Rate >> 8);
      buf[2] = (byte) (DIGRAMP_Rate >> 16);
      buf[3] = (byte) (DIGRAMP_Rate >> 24);
#ifdef SPI_DEBUG
      Serial.println(F("BUFFER:"));
      Serial.print(F("buf[3] = 0x"));
      Serial.print(buf[3], HEX);
      Serial.print(F(" buf[2] = 0x"));
      Serial.print(buf[2], HEX);
      Serial.print(F(" buf[1] = 0x"));
      Serial.print(buf[1], HEX);
      Serial.print(F(" buf[0] = 0x"));
      Serial.println(buf[0], HEX);
#endif
      SPI.transfer(buf[3]);
      SPI.transfer(buf[2]);
      SPI.transfer(buf[1]);
      SPI.transfer(buf[0]);
      break;
    case SINGLETONE_PROFILE_0:
      buf[0] = (byte) (ASF >> 0);
      buf[1] = (byte) (ASF >> 8);
      buf[2] = (byte) POW;
      buf[3] = (byte) (POW >> 8);
      buf[4] = (byte) FTW;
      buf[5] = (byte) (FTW >> 8);
      buf[6] = (byte) (FTW >> 16);
      buf[7] = (byte) (FTW >> 24);
#ifdef SPI_DEBUG
      Serial.println(F("BUFFER:"));
      Serial.print(F("buf[7] = 0x"));
      Serial.print(buf[7], HEX);
      Serial.print(F(" buf[6] = 0x"));
      Serial.print(buf[6], HEX);
      Serial.print(F(" buf[5] = 0x"));
      Serial.print(buf[5], HEX);
      Serial.print(F(" buf[4] = 0x"));
      Serial.println(buf[4], HEX);
      Serial.print(F("buf[3] = 0x"));
      Serial.print(buf[3], HEX);
      Serial.print(F(" buf[2] = 0x"));
      Serial.print(buf[2], HEX);
      Serial.print(F(" buf[1] = 0x"));
      Serial.print(buf[1], HEX);
      Serial.print(F(" buf[0] = 0x"));
      Serial.println(buf[0], HEX);
#endif
      SPI.transfer(buf[1]);
      SPI.transfer(buf[0]);
      SPI.transfer(buf[3]);
      SPI.transfer(buf[2]);
      SPI.transfer(buf[7]);
      SPI.transfer(buf[6]);
      SPI.transfer(buf[5]);
      SPI.transfer(buf[4]);
      break;
  }
  SPI.endTransaction();
  // now toggle the AD9910_DU-Pin
  digitalWrite(AD9910_IOUP, LOW);
  delayMicroseconds(1); // May not be necessary - Depending on how fast the GPIO-Expander is
  digitalWrite(AD9910_IOUP, HIGH); // Data is accepted at rising edge of AD9910_IOUP or AD9910_DU
  delayMicroseconds(1); // May not be necessary - Depending on how fast the GPIO-Expander is
  digitalWrite(AD9910_CS, HIGH); // Pull AD9910_CS HIGH to deselect the chip
}


/*
   DRIVERS FOR THE HARDWARE ON THE ANALOG-BOARD
*/
//#define SetAttenDEBUG
//#define SetAttenDEBUG2


// Driver for the Attenuator, controlled by one GPIO-Controller
// Bitmap for the Attenuator: Latch_Enable(LE) | 32dB | 32dB | 16dB | 8dB | 4dB | 2dB | 1dB
void SetAttenuator(byte Attenuation) {

#ifdef SetAttenDEBUG
  Serial.print(F("Attenuation = "));
  Serial.print(Attenuation, HEX);
#endif
if( Attenuation > 96){
  Attenuation = 95; // Set Attenuation to 95, as there's no 
}
  if (Attenuation > 63) {
    Attenuation = Attenuation - 32; // Subtract 32 and set the "64"-Bit manually, as any attenuation higher than 64 requires bits 5 and 6 to be HIGH
    bitSet(Attenuation, 6);
  }
  bitClear(Attenuation, 7); // Make sure the LE-Pin is LOW

#ifdef SetAttenDEBUG
  Serial.print(F("Attenuation = "));
  Serial.println(Attenuation, HEX);
#endif

  Wire.beginTransmission(ATTEN_ADR);
  Wire.write(Attenuation);
  Wire.endTransmission();
  bitSet(Attenuation, 7); // Set LE-Pin HIGH
  Wire.beginTransmission(ATTEN_ADR);
  Wire.write(Attenuation);
  Wire.endTransmission();
  bitClear(Attenuation, 7); // Set LE-Pin LOW again
  Wire.beginTransmission(ATTEN_ADR);
  Wire.write(Attenuation);
  Wire.endTransmission();
}
