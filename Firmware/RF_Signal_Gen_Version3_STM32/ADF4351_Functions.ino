// Variables for programming the ADF4351

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
