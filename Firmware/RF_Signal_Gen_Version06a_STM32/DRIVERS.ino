/*
   This File contains the Drivers for the Hardware
*/

/*
   ADF4351 SignalSource-Driver
*/

unsigned long ADF4351refin = 20000000;      // Reference-Frequency for the ADF4351 in Hz - Reference-Frequency = 10 Mhz (ATTENTION: The ADF4351 methods later require this value to be expressed in kHz!)
long ChanStep = 1000;      // Channel-Step = 10 kHz (Register-Value = kHz-Value * 100)
unsigned long Reg[6];      // Array for the ADF4351 Registers


// Variables from the SetFreq-Function to have them exposed for other functions
int ADFdbm = 3;    // Variable to configure the output-power of the ADF4351 - Default: +5dBm
int D_RF_ena = 1;            // 1bit  OutPwr 1=on           0 = off  Outport Null freischalten
int D_auxOutEna = 1;         // 1bit  aux OutEna 1=on       0 = off  Outport Aux freischalten
int D_auxOutSel = 1;         // 1bit  aux OutSel
int D_MTLD = 0;              // 1bit | This controls the "Mute til lock detect"-Function of the chip. It disables the output if the internal PLL has not locked.
int D_VcoPwrDown = 0;        // 1bit 1=VCO off

/*
   This subrouine sets up the ADF4351. It is also used to enable or disable the outputs and the VCO
   Codes:
   - 0x00 = OFF
   - 0x10 = PowerOnDefaults (Frequency = 400MHz, RF-Out = OFF, VCO = ON, AuxOut = OFF, AuxSelect = Divided ouput)
   - 0x20 = Standby (Frequency = LastFrequency, VCO On, RF-Out OFF, AuxOut = OFF, AuxSelect = Divided Output)
   - 0x30 = VCO-Check ((Frequency = 2200 MHz, VCO On, RF-Out OFF, AuxOut = ON, AuxSelect = VCO-Fundamental)
   - 0x40 = TEST ((Frequency = 1000 MHz, VCO On, RF-Out OFF, AuxOut = ON, AuxSelect = VCO-Fundamental)
   - 0xFF = PowerOn-Init with defaults (Same settings as Normal Operation)
*/
void SetupADF4351(int ADFMode) {
  switch (ADFMode) {
      Serial.println("ADFMode called");
    case STATE_POWERDOWN:
      Serial.println("ADFMode = STATE_POWERDOWN");
      D_RF_ena = 0;            // 1bit  OutPwr 1=on           0 = off  Outport Null freischalten
      D_auxOutEna = 0;         // 1bit  aux OutEna 1=on       0 = off  Outport Aux freischalten
      D_auxOutSel = 1;         // 1bit  aux OutSel
      D_MTLD = 0;              // 1bit | This controls the "Mute til lock detect"-Function of the chip. It disables the output if the internal PLL has not locked.
      D_VcoPwrDown = 1;        // 1bit 1=VCO off
      break;
    case STATE_NORM_OP:
      Serial.println("ADFMode = STATE_NORM_OP");
      ADFdbm = 3;              // 3bit  Output-Power set to +5dBm
      D_RF_ena = 1;            // 1bit  OutPwr 1=on           0 = off  Outport Null freischalten
      D_auxOutEna = 1;         // 1bit  aux OutEna 1=on       0 = off  Outport Aux freischalten
      D_auxOutSel = 0;         // 1bit  aux OutSel
      D_MTLD = 0;              // 1bit | This controls the "Mute til lock detect"-Function of the chip. It disables the output if the internal PLL has not locked.
      D_VcoPwrDown = 0;        // 1bit 1=VCO off
      break;
    case STATE_STANDBY:
      Serial.println("ADFMode = STATE_STANDBY");
      D_RF_ena = 0;            // 1bit  OutPwr 1=on           0 = off  Outport Null freischalten
      D_auxOutEna = 0;         // 1bit  aux OutEna 1=on       0 = off  Outport Aux freischalten
      D_auxOutSel = 1;         // 1bit  aux OutSel
      D_MTLD = 0;              // 1bit | This controls the "Mute til lock detect"-Function of the chip. It disables the output if the internal PLL has not locked.
      D_VcoPwrDown = 0;        // 1bit 1=VCO off
      break;
    case STATE_VCO_CHECK:
      Serial.println("ADFMode = STATE_VCO_CHECK");
      Freq = 2200000000;
      ADFdbm = 3;
      D_RF_ena = 1;            // 1bit  OutPwr 1=on           0 = off  Outport Null freischalten
      D_auxOutEna = 1;         // 1bit  aux OutEna 1=on       0 = off  Outport Aux freischalten
      D_auxOutSel = 1;         // 1bit  aux OutSel
      D_MTLD = 0;              // 1bit | This controls the "Mute til lock detect"-Function of the chip. It disables the output if the internal PLL has not locked.
      D_VcoPwrDown = 0;        // 1bit 1=VCO off
      SetFreqADF4351(Freq);
      break;
    case STATE_TEST:
      Serial.println("ADFMode = STATE_TEST");
      Freq = 1000000000;
      ADFdbm = 3;              // 3bit  Output-Power set to +5dBm
      D_RF_ena = 1;            // 1bit  OutPwr 1=on           0 = off  Outport Null freischalten
      D_auxOutEna = 1;         // 1bit  aux OutEna 1=on       0 = off  Outport Aux freischalten
      D_auxOutSel = 1;         // 1bit  aux OutSel
      D_MTLD = 0;              // 1bit | This controls the "Mute til lock detect"-Function of the chip. It disables the output if the internal PLL has not locked.
      D_VcoPwrDown = 0;        // 1bit 1=VCO off
      SetFreqADF4351(Freq);
      break;
    case STATE_INIT:
      Serial.println("ADFMode = STATE_INIT");
      Freq = 400000000;
      ADFdbm = 3;
      D_RF_ena = 1;            // 1bit  OutPwr 1=on           0 = off  Outport Null freischalten
      D_auxOutEna = 1;         // 1bit  aux OutEna 1=on       0 = off  Outport Aux freischalten
      D_auxOutSel = 1;         // 1bit  aux OutSel
      D_MTLD = 0;              // 1bit | This controls the "Mute til lock detect"-Function of the chip. It disables the output if the internal PLL has not locked.
      D_VcoPwrDown = 0;        // 1bit 1=VCO off
      SetFreqADF4351(Freq);
      break;
    default:
      Freq = 420000000;         // Frequency set to 420MHz
      ADFdbm = 3;              // Output-Power set to -4dBm
      D_RF_ena = 1;            // 1bit  OutPwr 1=on           0 = off  Outport Null freischalten
      D_auxOutEna = 1;         // 1bit  aux OutEna 1=on       0 = off  Outport Aux freischalten
      D_auxOutSel = 1;         // 1bit  aux OutSel
      D_MTLD = 0;              // 1bit | This controls the "Mute til lock detect"-Function of the chip. It disables the output if the internal PLL has not locked.
      D_VcoPwrDown = 0;        // 1bit 1=VCO off
      break;
  }
  Serial.println("ADFMode = STATE HAS BEEN SET");
}




///////////////////////// Subroutine: Setze Frequenz ADF4351 ///////////////////////////
void SetFreqADF4351(unsigned long FreqADF4351)
{
  Serial.println(F("SetFreqADF4351_Step1"));
  FreqADF4351 = FreqADF4351 / 10;
  ConvertFreq(FreqADF4351, Reg);
  Serial.print(F("SetFreqADF4351_WriteReg5"));
  WriteADF2(5);
  delayMicroseconds(2500);
  Serial.print(", Reg4");
  WriteADF2(4);
  delayMicroseconds(2500);
  Serial.print(", Reg 3");
  WriteADF2(3);
  delayMicroseconds(2500);
  Serial.print(", Reg 2");
  WriteADF2(2);
  delayMicroseconds(2500);
  Serial.print(", Reg 1");
  WriteADF2(1);
  delayMicroseconds(2500);
  Serial.print(", Reg 0");
  WriteADF2(0);
  delayMicroseconds(2500);
  Serial.println(", WRITE COMPLETE");
}

////////////////////////// Teil-Subroutine ADF4351 ////////////////////////////
void WriteADF2(int idx)
{ // make 4 byte from integer for SPI-Transfer
  byte buf[4];
  for (int i = 0; i < 4; i++) {
    buf[i] = (byte)(Reg[idx] >> (i * 8));
  }
  WriteADF(buf[3], buf[2], buf[1], buf[0]);
}

/////////////////////////// Teil-Subroutine ADF4351 ////////////////////////////
int WriteADF(byte a1, byte a2, byte a3, byte a4) {
  byte ADF_DELAY = 0;
  // write over SPI to ADF4350
  digitalWrite(ADF4351_CS, LOW);  // Pull the CS-Pin of the ADF4351 LOW
  digitalWrite(ADF4351_LE, LOW);
  delayMicroseconds(1); // May not be necessary - Depending on how fast the CS-Signal is
  SPI.begin();
  SPI.beginTransaction(SPISettings(32000000, MSBFIRST, SPI_MODE0));
  SPI.write(a1);
  SPI.write(a2);
  SPI.write(a3);
  SPI.write(a4);
  SPI.endTransaction();
  digitalWrite(ADF4351_LE, HIGH);
  delayMicroseconds(5);
  digitalWrite(ADF4351_LE, LOW);
  digitalWrite(ADF4351_CS, HIGH);  // Pull the CS-Pin of the ADF4351 HIGH

}

////////////////////////////// Teil-Subroutine ADF4351 //////////////////////////
void ConvertFreq(double freq, unsigned long R[])
{
  // PLL-Reg-R0         =  32bit
  // Registerselect        3bit
  // int F_Frac = 4;       // 12bit
  // int N_Int = 92;       // 16bit
  // reserved           // 1bit

  // PLL-Reg-R1         =  32bit
  // Registerselect        3bit
  // int M_Mod = 5;        // 12bit
  int P_Phase = 1;         // 12bit bei 2x12bit hintereinander pow()-bug !!
  int Prescal = 0;         // 1bit geht nicht ???
  int PhaseAdj = 0;        // 1bit geht auch nicht ???
  // reserved              // 3bit

  // PLL-Reg-R2         =  32bit
  // Registerselect        3bit
  int U1_CountRes = 0;     // 1bit
  int U2_Cp3state = 0;     // 1bit
  int U3_PwrDown = 0;      // 1bit
  int U4_PDpola = 1;       // 1bit
  int U5_LPD = 0;          // 1bit
  int U6_LPF = 1;          // 1bit 1=Integer, 0=Frac not spported yet
  int CP_ChgPump = 7;      // 4bit
  int D1_DoublBuf = 0;     // 1bit
  //  int R_Counter = 1;   // 10bit
  //  int RD1_Rdiv2 = 0;   // 1bit
  //  int RD2refdoubl = 0; // 1bit
  int M_Muxout = 6;        // 3bit  MUX-Output control. Set to DIGITAL LOCK DETECT
  int LoNoisSpur = 0;      // 2bit
  // reserved              // 1bit

  // PLL-Reg-R3         =  32bit
  // Registerselect        3bit
  int D_Clk_div = 150;     // 12bit
  int C_Clk_mode = 0;      // 2bit
  //  reserved             // 1bit
  int F1_Csr = 0;          // 1bit
  //  reserved             // 2bit
  int F2_ChgChan = 0;      // 1bit
  int F3_ADB = 0;          // 1bit
  int F4_BandSel = 0;      // 1bit
  //  reserved             // 8bit

  // PLL-Reg-R4         =  32bit
  // Registerselect        3bit
  int D_out_PWR = (ADFdbm);      // 2bit  OutPwr 0-3 3= +5dBm   Power out 1
  // int D_RF_ena = 1;            // 1bit  OutPwr 1=on           0 = off  Outport Null freischalten
  int D_auxOutPwr = (ADFdbm);    // 2bit  aux OutPwr 0-3        Power out 2
  // int D_auxOutEna = 1;         // 1bit  aux OutEna 1=on       0 = off  Outport Aux freischalten
  // int D_auxOutSel = 1;         // 1bit  aux OutSel
  // int D_MTLD = 0;              // 1bit
  // int D_VcoPwrDown = 0;        // 1bit 1=VCO off

  //  int B_BandSelClk = 200; // 8bit
  int D_RfDivSel = 3;      // 3bit 3=70cm 4=2m
  int D_FeedBck = 1;       // 1bit
  // reserved              // 8bit

  // PLL-Reg-R5         =  32bit
  // Registerselect        // 3bit
  // reserved              // 16bit
  // reserved     11       // 2bit
  // reserved              // 1bit
  int D_LdPinMod = 1;      // 2bit muss 1 sein
  // reserved              // 8bit

  // Referenz Freg Calc
  int R_Counter = 2;       // 10bit war 1
  int RD1_Rdiv2 = 1;       // 1bit  war 0
  int RD2refdoubl = 0;     // 1bit
  int B_BandSelClk = 200;  // 8bit
  //  int F4_BandSel = 0;  // 1bit

  // int F4_BandSel = 10.0 * B_BandSelClk / PFDFreq;
  long RFout = freq;       // VCO-Frequenz

  // calc bandselect und RF-div
  int outdiv = 1;
  if (RFout >= 220000000) {
    outdiv = 1;
    D_RfDivSel = 0;
  }
  if (RFout < 220000000) {
    outdiv = 2;
    D_RfDivSel = 1;
  }
  if (RFout < 110000000) {
    outdiv = 4;
    D_RfDivSel = 2;
  }
  if (RFout < 55000000) {
    outdiv = 8;
    D_RfDivSel = 3;
  }
  if (RFout < 27500000) {
    outdiv = 16;
    D_RfDivSel = 4;
  }
  if (RFout < 13800000) {
    outdiv = 32;
    D_RfDivSel = 5;
  }
  if (RFout < 6900000) {
    outdiv = 64;
    D_RfDivSel = 6;
  }

  float PFDFreq = ADF4351refin * ((1.0 + RD2refdoubl) / (R_Counter * (1.0 + RD1_Rdiv2))); //Referenzfrequenz
  float N = ((RFout) * outdiv) / (PFDFreq / 10) ;
  int N_Int = N;
  long M_Mod = PFDFreq * (100000 / ChanStep) / 100000;
  int F_Frac = round((N - N_Int) * M_Mod);

  R[0] = (unsigned long)(0 + F_Frac * pow(2, 3) + N_Int * pow(2, 15)); // Programs the Register R0: Bit 31 = RESERVED, Bit 30 - 15 = N_Int, Bit 14 - 3 = F_Frac, Bit 2 - 0 = ControlBits (filled with 0)
  R[1] = (unsigned long)(1 + M_Mod * pow(2, 3) + P_Phase * pow(2, 15) + Prescal * pow(2, 27) + PhaseAdj * pow(2, 28));
  //  R[1] = (R[1])+1; // Registerselect adjust ?? because unpossible 2x12bit in pow() funktion
  R[2] = (unsigned long)(2 + U1_CountRes * pow(2, 3) + U2_Cp3state * pow(2, 4) + U3_PwrDown * pow(2, 5) + U4_PDpola * pow(2, 6) + U5_LPD * pow(2, 7) + U6_LPF * pow(2, 8) + CP_ChgPump * pow(2, 9) + D1_DoublBuf * pow(2, 13) + R_Counter * pow(2, 14) + RD1_Rdiv2 * pow(2, 24) + RD2refdoubl * pow(2, 25) + M_Muxout * pow(2, 26) + LoNoisSpur * pow(2, 29));
  R[3] = (unsigned long)(3 + D_Clk_div * pow(2, 3) + C_Clk_mode * pow(2, 15) + 0 * pow(2, 17) + F1_Csr * pow(2, 18) + 0 * pow(2, 19) + F2_ChgChan * pow(2, 21) +  F3_ADB * pow(2, 22) + F4_BandSel * pow(2, 23) + 0 * pow(2, 24));
  R[4] = (unsigned long)(4 + D_out_PWR * pow(2, 3) + D_RF_ena * pow(2, 5) + D_auxOutPwr * pow(2, 6) + D_auxOutEna * pow(2, 8) + D_auxOutSel * pow(2, 9) + D_MTLD * pow(2, 10) + D_VcoPwrDown * pow(2, 11) + B_BandSelClk * pow(2, 12) + D_RfDivSel * pow(2, 20) + D_FeedBck * pow(2, 23));
  R[5] = (unsigned long)(5 + 0 * pow(2, 3) + 3 * pow(2, 19) + 0 * pow(2, 21) + D_LdPinMod * pow(2, 22));
}

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
uint32_t RegCFR1 = 0x00;              // Variable for Control Register 1 - 4 Bytes - See Datasheet for details
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
byte MANUAL_OSK_CONTROL = 0;            // Bit 23: Enables / Disables the Manual OSK-Control - NOT USED! PIN NOT CONNECTED
byte INVERSE_SINC_FILTER = 0;           // Bit 22: Enables/Disables the Inverse Sinc Filter
byte INTERNAL_PROFILE_CONTROL = 0;      // Bits 20 - 17: Selects the RAM-Profile
byte DDS_SINE = 1;                      // Bit 16: Selects the Sine / Cosine-Output
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
byte ENABLE_AMPLITUDE_SCALE_CW_PROFILES = 0;
byte INTERNAL_IOUPDATE_ACTIVE = 0;
byte SYNC_CLK_ENABLE = 0; //
byte DIGI_RAMP_DESTINATION = 0; // 2 Bits
byte DIGI_RAMP_ENABLE = 0;
byte DIGI_RAMP_NO_DWELL_HIGH = 0;
byte DIGI_RAMP_NO_DWELL_LOW = 0;
byte READ_EFFECTIVE_FTW = 0;
byte IOUPDATE_RATE_CTRL = 0;
byte PD_CLK_ENABLE = 0; // Disabled, because PD_CLK-Pin is not used.
byte PD_CLK_INVERT = 0;
byte TX_ENABLE_INVERT = 0;
byte MATCHED_LATENCY_ENABLE = 0;
byte DATA_ASSEMBLER_HOLD_LAST_VALUE = 0;
byte SYNC_TIMING_VALIDATION_ERROR = 0;
byte PARALLEL_DATA_PORT_ENABLE = 0;
byte FM_GAIN = 0;

// CFR3-Values | CFR3 configures internal PLL
byte DRV0 = B00;              // Setting for REFCLK_OUT Drive - Default: REFCLK_OUT OFF
byte VCOSEL = B101;           // Select the VCO - Default: VCO5 for a internal Clock of 920 - 1030 MHz
byte Icp = B111;              // Sets the Charge Pump Current - This value will require experimentation and may be stored in external NVRAM
byte REFCLK_Div_Bypass = 0;        // Controls the InputDivider-Bypass - Default: 0 (OFF)
byte REFCLK_Div_RESET = 0;         // Controls the InputDivider - Default: 0 (Divider is reset and not working)
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

void SetupAD9910(int ADFMode) {
  switch (ADFMode) {
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
      RegCFR1 = (LSB_FIRST + SDIO_INPUT_ONLY * SDIO_INPUT_ONLY_LOC + EXTERNAL_POWER_DOWN * EXTERNAL_POWER_DOWN_LOC + AUX_DAC_POWER_DOWN * AUX_DAC_POWER_DOWN_LOC + REFCLK_INPUT_POWER_DOWN * REFCLK_INPUT_POWER_DOWN_LOC + DAC_POWER_DOWN * DAC_POWER_DOWN_LOC + DIGITAL_POWER_DOWN * DIGITAL_POWER_DOWN_LOC + SELECT_AUTO_OSK * SELECT_AUTO_OSK_LOC + OSK_ENABLE * OSK_ENABLE_LOC + LOAD_ARR_IOUPDATE * LOAD_ARR_IOUPDATE_LOC + CLEAR_PHASE_ACCU * CLEAR_PHASE_ACCU_LOC + CLEAR_DIGI_RAMP_ACCU * CLEAR_DIGI_RAMP_ACCU_LOC + AUTOCLEAR_PHASE_ACCU * AUTOCLEAR_PHASE_ACCU_LOC + AUTOCLEAR_DIGI_RAMP_ACCU * AUTOCLEAR_DIGI_RAMP_ACCU_LOC + LOAD_LRR_IOUPDATE * LOAD_LRR_IOUPDATE_LOC + DDS_SINE * DDS_SINE_LOC + INTERNAL_PROFILE_CONTROL * INTERNAL_PROFILE_CONTROL_LOC + INVERSE_SINC_FILTER * INVERSE_SINC_FILTER_LOC + MANUAL_OSK_CONTROL * MANUAL_OSK_CONTROL_LOC + RAM_PLAYBACK_DESTINATION * RAM_PLAYBACK_DESTINATION_LOC + RAM_ENABLE * RAM_ENABLE_LOC);
      Serial.print("RegCFR1 = 0x");
      Serial.println(RegCFR1, HEX);
      RegCFR2 = (0 + FM_GAIN + PARALLEL_DATA_PORT_ENABLE * PARALLEL_DATA_PORT_ENABLE_LOC + SYNC_TIMING_VALIDATION_ERROR * SYNC_TIMING_VALIDATION_ERROR_LOC + DATA_ASSEMBLER_HOLD_LAST_VALUE * DATA_ASSEMBLER_HOLD_LAST_VALUE_LOC + MATCHED_LATENCY_ENABLE * MATCHED_LATENCY_ENABLE_LOC + TX_ENABLE_INVERT * TX_ENABLE_INVERT_LOC + PD_CLK_INVERT * PD_CLK_INVERT_LOC + PD_CLK_ENABLE * PD_CLK_ENABLE_LOC + IOUPDATE_RATE_CTRL * IOUPDATE_RATE_CTRL_LOC + READ_EFFECTIVE_FTW * READ_EFFECTIVE_FTW_LOC + DIGI_RAMP_NO_DWELL_LOW * DIGI_RAMP_NO_DWELL_LOW_LOC + DIGI_RAMP_NO_DWELL_HIGH * DIGI_RAMP_NO_DWELL_HIGH_LOC + DIGI_RAMP_ENABLE * DIGI_RAMP_ENABLE_LOC + DIGI_RAMP_DESTINATION * DIGI_RAMP_DESTINATION_LOC + SYNC_CLK_ENABLE * SYNC_CLK_ENABLE_LOC + INTERNAL_IOUPDATE_ACTIVE * INTERNAL_IOUPDATE_ACTIVE_LOC + ENABLE_AMPLITUDE_SCALE_CW_PROFILES * ENABLE_AMPLITUDE_SCALE_CW_PROFILES_LOC);
      Serial.print("RegCFR2 = 0x");
      Serial.println(RegCFR2, HEX);
      RegCFR3 = (0 + AD9910_PLL_DIVIDER * AD9910_PLL_DIVIDER_LOC + PLL_ENABLE * PLL_ENABLE_LOC + PFD_RESET * PFD_RESET_LOC + REFCLK_Div_RESET * REFCLK_Div_RESET_LOC + REFCLK_Div_Bypass * REFCLK_Div_Bypass_LOC + Icp * ICP_LOC + VCOSEL * VCOSEL_LOC + DRV0 * DRV0_LOC);
      Serial.print("RegCFR3 = 0x");
      Serial.println(RegCFR3, HEX);
      FTW = round(4294967296UL / (DDSCLK / 1000000)); // Formula for calculating the FTW: FTW = ((2^32)*(fout/fclock)) // Frequency set to 1MHz
      ASF = 32768;  // Amplitude Scale Factor set to full Amplitude
      POW = 0; // No Phase Offset
      WriteAD9910(CFR1_ADDR);
      WriteAD9910(CFR2_ADDR);
      WriteAD9910(CFR3_ADDR);
      WriteAD9910(FTW_ADDR);
      WriteAD9910(ASF_ADDR);
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
  Serial.print("FTW = ");
  Serial.println(FTW, DEC);
  WriteAD9910(FTW_ADDR);
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

void WriteAD9910(byte  AD9910_INST) {
  Wire.beginTransmission(GPIO_ADR);
  Wire.write(B11000101); // INT/GPIO-BITMAP: INT0 | INT 1 | FREE | ADF4351_LOCK | AD9910_LOCK | ADF4351_CS | AD9910_CS | AD9910_DU - Pull AD9910_CS LOW to select the chip
  Wire.endTransmission();
  delayMicroseconds(1); // May not be necessary - Depending on how fast the CS-Signal is
  byte buf[8]; // 64bit buffer to store individual bytes of the registers
  SPI.begin();
  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  SPI.transfer(AD9910_INST);
  switch (AD9910_INST) {
    case CFR1_ADDR:
      //      SPI.write32(RegCFR1); // DISABLE this line and ENABLE the following block on boards other than ESP8266 that do not have the "write32" function in their SPI-Library
      buf[0] = (byte) RegCFR1;
      buf[1] = (byte) RegCFR1 >> 8;
      buf[2] = (byte) RegCFR1 >> 16;
      buf[3] = (byte) RegCFR1 >> 24;
      SPI.write(buf[3]);
      SPI.write(buf[2]);
      SPI.write(buf[1]);
      SPI.write(buf[0]);
      break;
    case CFR2_ADDR:
      //      SPI.write32(RegCFR2);
      buf[0] = (byte) RegCFR2;
      buf[1] = (byte) RegCFR2 >> 8;
      buf[2] = (byte) RegCFR2 >> 16;
      buf[3] = (byte) RegCFR2 >> 24;
      SPI.write(buf[3]);
      SPI.write(buf[2]);
      SPI.write(buf[1]);
      SPI.write(buf[0]);
      break;
    case CFR3_ADDR:
      //      SPI.write32(RegCFR3);
      buf[0] = (byte) RegCFR3;
      buf[1] = (byte) RegCFR3 >> 8;
      buf[2] = (byte) RegCFR3 >> 16;
      buf[3] = (byte) RegCFR3 >> 24;
      SPI.write(buf[3]);
      SPI.write(buf[2]);
      SPI.write(buf[1]);
      SPI.write(buf[0]);
      break;
    case AuxDAC_ADDR:
      SPI.write(AuxDAC);
      break;
    case IO_UPD_Rate_ADDR:
      //      SPI.write32(IO_UPD_Rate);
      buf[0] = (byte) IO_UPD_Rate;
      buf[1] = (byte) IO_UPD_Rate >> 8;
      buf[2] = (byte) IO_UPD_Rate >> 16;
      buf[3] = (byte) IO_UPD_Rate >> 24;
      SPI.write(buf[3]);
      SPI.write(buf[2]);
      SPI.write(buf[1]);
      SPI.write(buf[0]);
      break;
    case FTW_ADDR:
      //      SPI.write32(FTW);
      buf[0] = (byte) FTW;
      buf[1] = (byte) FTW >> 8;
      buf[2] = (byte) FTW >> 16;
      buf[3] = (byte) FTW >> 24;
      SPI.write(buf[3]);
      SPI.write(buf[2]);
      SPI.write(buf[1]);
      SPI.write(buf[0]);
      break;
    case POW_ADDR:
      SPI.transfer16(POW);      //      buf[0] = (byte) POW;
      //      buf[1] = (byte) POW >> 8;
      //      buf[2] = (byte) POW >> 16;
      //      buf[3] = (byte) POW >> 24;
      //      SPI.write(buf[3]);
      //      SPI.write(buf[2]);
      //      SPI.write(buf[1]);
      //      SPI.write(buf[0]);
      break;
    case ASF_ADDR:
      //      SPI.write32(ASF);
      buf[0] = (byte) ASF;
      buf[1] = (byte) ASF >> 8;
      buf[2] = (byte) ASF >> 16;
      buf[3] = (byte) ASF >> 24;
      SPI.write(buf[3]);
      SPI.write(buf[2]);
      SPI.write(buf[1]);
      SPI.write(buf[0]);
      break;
    case DIGRAMP_Limit_ADDR:
      buf[0] = (byte) DIGRAMP_Limit;
      buf[1] = (byte) DIGRAMP_Limit >> 8;
      buf[2] = (byte) DIGRAMP_Limit >> 16;
      buf[3] = (byte) DIGRAMP_Limit >> 24;
      buf[4] = (byte) DIGRAMP_Limit >> 32;
      buf[5] = (byte) DIGRAMP_Limit >> 40;
      buf[6] = (byte) DIGRAMP_Limit >> 48;
      buf[7] = (byte) DIGRAMP_Limit >> 56;
      SPI.write(buf[7]);
      SPI.write(buf[6]);
      SPI.write(buf[5]);
      SPI.write(buf[4]);
      SPI.write(buf[3]);
      SPI.write(buf[2]);
      SPI.write(buf[1]);
      SPI.write(buf[0]);
      break;
    case DIGRAMP_Step_ADDR:
      buf[0] = (byte) DIGRAMP_Step;
      buf[1] = (byte) DIGRAMP_Step >> 8;
      buf[2] = (byte) DIGRAMP_Step >> 16;
      buf[3] = (byte) DIGRAMP_Step >> 24;
      buf[4] = (byte) DIGRAMP_Step >> 32;
      buf[5] = (byte) DIGRAMP_Step >> 40;
      buf[6] = (byte) DIGRAMP_Step >> 48;
      buf[7] = (byte) DIGRAMP_Step >> 56;
      SPI.write(buf[7]);
      SPI.write(buf[6]);
      SPI.write(buf[5]);
      SPI.write(buf[4]);
      SPI.write(buf[3]);
      SPI.write(buf[2]);
      SPI.write(buf[1]);
      SPI.write(buf[0]);
      break;
    case DIGRAMP_Rate_ADDR:
      buf[0] = (byte) DIGRAMP_Rate;
      buf[1] = (byte) DIGRAMP_Rate >> 8;
      buf[2] = (byte) DIGRAMP_Rate >> 16;
      buf[3] = (byte) DIGRAMP_Rate >> 24;
      SPI.write(buf[3]);
      SPI.write(buf[2]);
      SPI.write(buf[1]);
      SPI.write(buf[0]);
      break;
  }
  SPI.endTransaction();
  // now toggle the AD9910_DU-Pin
  Wire.beginTransmission(GPIO_ADR);
  Wire.write(B11000100); // INT/GPIO-BITMAP: INT0 | INT 1 | FREE | ADF4351_LOCK | AD9910_LOCK | ADF4351_CS | AD9910_CS | AD9910_DU - Keep AD9910_CS LOW, Pull AD9910_DU LOW
  Wire.endTransmission();
  delayMicroseconds(1); // May not be necessary - Depending on how fast the GPIO-Expander is
  Wire.beginTransmission(GPIO_ADR);
  Wire.write(B11000101); // INT/GPIO-BITMAP: INT0 | INT 1 | FREE | ADF4351_LOCK | AD9910_LOCK | ADF4351_CS | AD9910_CS | AD9910_DU - Keep AD9910_CS LOW, Pull AD9910_DU HIGH - Data is accepted on rising edge of AD9910_DU
  Wire.endTransmission();
  delayMicroseconds(1); // May not be necessary - Depending on how fast the GPIO-Expander is
  Wire.beginTransmission(GPIO_ADR);
  Wire.write(B11000111); // INT/GPIO-BITMAP: INT0 | INT 1 | FREE | ADF4351_LOCK | AD9910_LOCK | ADF4351_CS | AD9910_CS | AD9910_DU - Pull AD9910_CS HIGH to deselect the chip
  Wire.endTransmission();
  delayMicroseconds(1); // May not be necessary - Depending on how fast the CS-Signal is
}

// Function to set the CFR1 and CFR2-Registers - Excludes CFR3 because that register is set at system startup and remains unchanged after that.
void SendCFR() {
  RegCFR1 = (LSB_FIRST + SDIO_INPUT_ONLY * SDIO_INPUT_ONLY_LOC + EXTERNAL_POWER_DOWN * EXTERNAL_POWER_DOWN_LOC + AUX_DAC_POWER_DOWN * AUX_DAC_POWER_DOWN_LOC + REFCLK_INPUT_POWER_DOWN * REFCLK_INPUT_POWER_DOWN_LOC + DAC_POWER_DOWN * DAC_POWER_DOWN_LOC + DIGITAL_POWER_DOWN * DIGITAL_POWER_DOWN_LOC + SELECT_AUTO_OSK * SELECT_AUTO_OSK_LOC + OSK_ENABLE * OSK_ENABLE_LOC + LOAD_ARR_IOUPDATE * LOAD_ARR_IOUPDATE_LOC + CLEAR_PHASE_ACCU * CLEAR_PHASE_ACCU_LOC + CLEAR_DIGI_RAMP_ACCU * CLEAR_DIGI_RAMP_ACCU_LOC + AUTOCLEAR_PHASE_ACCU * AUTOCLEAR_PHASE_ACCU_LOC + AUTOCLEAR_DIGI_RAMP_ACCU * AUTOCLEAR_DIGI_RAMP_ACCU_LOC + LOAD_LRR_IOUPDATE * LOAD_LRR_IOUPDATE_LOC + DDS_SINE * DDS_SINE_LOC + INTERNAL_PROFILE_CONTROL * INTERNAL_PROFILE_CONTROL_LOC + INVERSE_SINC_FILTER * INVERSE_SINC_FILTER_LOC + MANUAL_OSK_CONTROL * MANUAL_OSK_CONTROL_LOC + RAM_PLAYBACK_DESTINATION * RAM_PLAYBACK_DESTINATION_LOC + RAM_ENABLE * RAM_ENABLE_LOC);
  Serial.print("RegCFR1 = 0x");
  Serial.println(RegCFR1, HEX);
  RegCFR2 = (0 + FM_GAIN + PARALLEL_DATA_PORT_ENABLE * PARALLEL_DATA_PORT_ENABLE_LOC + SYNC_TIMING_VALIDATION_ERROR * SYNC_TIMING_VALIDATION_ERROR_LOC + DATA_ASSEMBLER_HOLD_LAST_VALUE * DATA_ASSEMBLER_HOLD_LAST_VALUE_LOC + MATCHED_LATENCY_ENABLE * MATCHED_LATENCY_ENABLE_LOC + TX_ENABLE_INVERT * TX_ENABLE_INVERT_LOC + PD_CLK_INVERT * PD_CLK_INVERT_LOC + PD_CLK_ENABLE * PD_CLK_ENABLE_LOC + IOUPDATE_RATE_CTRL * IOUPDATE_RATE_CTRL_LOC + READ_EFFECTIVE_FTW * READ_EFFECTIVE_FTW_LOC + DIGI_RAMP_NO_DWELL_LOW * DIGI_RAMP_NO_DWELL_LOW_LOC + DIGI_RAMP_NO_DWELL_HIGH * DIGI_RAMP_NO_DWELL_HIGH_LOC + DIGI_RAMP_ENABLE * DIGI_RAMP_ENABLE_LOC + DIGI_RAMP_DESTINATION * DIGI_RAMP_DESTINATION_LOC + SYNC_CLK_ENABLE * SYNC_CLK_ENABLE_LOC + INTERNAL_IOUPDATE_ACTIVE * INTERNAL_IOUPDATE_ACTIVE_LOC + ENABLE_AMPLITUDE_SCALE_CW_PROFILES * ENABLE_AMPLITUDE_SCALE_CW_PROFILES_LOC);
  Serial.print("RegCFR2 = 0x");
  Serial.println(RegCFR2, HEX);
  WriteAD9910(CFR1_ADDR);
  WriteAD9910(CFR2_ADDR);
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

  if (Attenuation > 63) {
    Attenuation = Attenuation - 32;
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

void DAC_Setup() {
  // Read the Status of the DAC and write it to the serial console for debugging-purposes
  Serial.println(F("Reading all registers of the DAC"));
  Wire.requestFrom(RF_DAC_ADR, 24);
  byte dac_data[24];
  byte dac_data_pointer = 0;
  while (Wire.available()) {
    dac_data[dac_data_pointer] = Wire.read();
    dac_data_pointer++;
  }
  Serial.print(F("Channel A: ")); Serial.print(dac_data[0], HEX); Serial.print(F(" ")); Serial.print(dac_data[1], HEX); Serial.print(F(" ")); Serial.println(dac_data[2], HEX);
  Serial.print(F("Channel A EEPROM: ")); Serial.print(dac_data[3], HEX); Serial.print(F(" ")); Serial.print(dac_data[4], HEX); Serial.print(F(" ")); Serial.println(dac_data[5], HEX);

  Serial.print(F("Channel B: ")); Serial.print(dac_data[6], HEX); Serial.print(F(" ")); Serial.print(dac_data[7], HEX); Serial.print(F(" ")); Serial.println(dac_data[8], HEX);
  Serial.print(F("Channel B EEPROM: ")); Serial.print(dac_data[9], HEX); Serial.print(F(" ")); Serial.print(dac_data[10], HEX); Serial.print(F(" ")); Serial.println(dac_data[11], HEX);

  Serial.print(F("Channel C: ")); Serial.print(dac_data[12], HEX); Serial.print(F(" ")); Serial.print(dac_data[13], HEX); Serial.print(F(" ")); Serial.println(dac_data[14], HEX);
  Serial.print(F("Channel C EEPROM: ")); Serial.print(dac_data[15], HEX); Serial.print(F(" ")); Serial.print(dac_data[16], HEX); Serial.print(F(" ")); Serial.println(dac_data[17], HEX);

  Serial.print(F("Channel D: ")); Serial.print(dac_data[18], HEX); Serial.print(F(" ")); Serial.print(dac_data[19], HEX); Serial.print(F(" ")); Serial.println(dac_data[20], HEX);
  Serial.print(F("Channel D EEPROM: ")); Serial.print(dac_data[21], HEX); Serial.print(F(" ")); Serial.print(dac_data[22], HEX); Serial.print(F(" ")); Serial.println(dac_data[23], HEX);

  Serial.println(F("Setting up the DAC for normal Operation: VREF = INTERNAL, GAIN = 1, POWERDOWN-RESISTOR = 100kOhm, OUTPUT-VALUE = 0x888"));
  /*
    BITMAPs for the bytes during sequential write:
    Byte 0: C2 (0), C1 (1), C0 (0), W1 (1), W2 (0), DAC1 (0), DAC0 (0), !UDAC (0) = Select SEQUENTIAL WRITE (C2, C1, C0, W1, W0), starting at DAC-Channel 0, UPDATE Immediately
      Byte 1: VREF (1), PD1 (0), PD0 (0), Gx (0), 4 bit DAC-Data = Select INTERNAL VREF and ENABLE Outputs with a GAIN of 1, then transmit the 4 most siginificant bits of the Output-Value
      Byte 2: 8bits DAC-Data = Transmit the remaining 8 bits of DAC-Data
  */
  dac_data[0] = 0x50; dac_data[1] = 0x88; dac_data[2] = 0x88;
  Wire.beginTransmission(RF_DAC_ADR);
  Wire.write(dac_data[0]);
  for (int i = 0; i < 3; i++) {
    Wire.write(dac_data[1]);
    Wire.write(dac_data[2]);
  }
  Wire.endTransmission();
}

void SetAGC_LVL(int lvl) {
  if (lvl >  0x0FFF) {
    ErrorMode(DAC_OVERFLOW, false);
    lvl = 0x0FFF;
  }
  byte buf[2];
  buf[1] = lvl; // add 0x1000 to the value to set the bits that select DAC-Channel 1
  buf[0]  = lvl >> 8;
  // FastWrite-Command to set DAC: Bit 15, 14 = 0 (Fast Write), Bit 13, 12 = 0 (DAC Enabled), Bit 11 - 0 = 12bit DAC-Value
  Wire.beginTransmission(RF_DAC_ADR);
  Wire.write(0x5A);
  Wire.write(buf[0]);
  Wire.write(buf[1]);
  Wire.endTransmission();
}

void SetAGC_BIAS(int bias) {
  if (bias >  0x0FFF) {
    ErrorMode(DAC_OVERFLOW, false);
    bias = 0x0FFF;
  }
  byte buf[2];
  buf[1] = bias;
  buf[0]  = bias >> 8;
  // FastWrite-Command to set DAC: Bit 15, 14 = 0 (Fast Write), Bit 13, 12 = 0 (DAC Enabled), Bit 11 - 0 = 12bit DAC-Value
  Wire.beginTransmission(RF_DAC_ADR);
  Wire.write(0x58);
  Wire.write(buf[0]);
  Wire.write(buf[1]);
  Wire.endTransmission();
}

void SetMixpath(bool mixpath) {
  switch (mixpath) {
    case true:

      break;
    case false:

      break;
  }
  Serial.print(F("SIGPATH_CTRL = 0x"));
  Serial.println(SIGPATH_CTRL, HEX);
  Wire.beginTransmission(ANALOG_ADR);
  Wire.write(SIGPATH_CTRL);
  Wire.endTransmission();
}

int ADC_READ(byte ADC_CHANNEL) { // Returns the voltage present at the selected input of the ADC in millivolt
  switch (ADC_CHANNEL) {
    case ADC_RF_OUT_SENSE:
      ads.setGain(GAIN_TWO);
      break;
    case ADC_RF_LEVEL_SENSE:
      ads.setGain(GAIN_ONE);
  }
  int ADC_Value = ads.readADC_SingleEnded(ADC_CHANNEL);
  int ADC_Volt = 0;
  switch (ADC_CHANNEL) {
    case ADC_RF_OUT_SENSE:
      ADC_Volt = ADC_Value * 1; // Scale the ADC-Value to the Vref and the selected gain (Gain = 1): 1bit = 2mV
      break;
    case ADC_RF_LEVEL_SENSE:
      ADC_Volt = ADC_Value * 2; // Scale the ADC-Value to the Vref and the selected gain (Gain = 2): 1bit = 4mV
      break;
  }
  return ADC_Value;
}
