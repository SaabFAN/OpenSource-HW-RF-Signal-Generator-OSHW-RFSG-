/*
 * ADF4351Driver.cpp
 *
 *  Created on: 19.02.2019
 *      Author: voyag
 */

#include "ADF4351Driver.h"

ADF4351_Driver::ADF4351_Driver() {
	// TODO Auto-generated constructor stub
	ADF4351refin = 20000000; // Initialize reference-frequency with the 20 MHz default-frequency
	init_complete = false; // Initialize the flag that shows whether the chip is initialized with "false"
	current_freq = 40000000; // Initialized the Frequency-Variable with the default-Value: 40 MHz
	ChanStep = 1000;
	dBm = 3;				// Set the amplitude to +5 dBm
	output_enable = 1;// 1bit  OutPwr 1=on           0 = off  Outport Null freischalten
	aux_enable = 1;	// 1bit  aux OutEna 1=on       0 = off  Outport Aux freischalten
	aux_select = 1;		// 1bit  aux OutSel
	MTLD = 0;// 1bit | This controls the "Mute til lock detect"-Function of the chip. It disables the output if the internal PLL has not locked.
	VcoPwrDown = 0;		// 1bit 1=VCO off
	ADF4351_CS = PB14;		// Default-Value for the CS-Pin
	ADF4351_LE = PB13;		// Default-Value for the LE_Pin
}

ADF4351_Driver::~ADF4351_Driver() {
	// TODO Auto-generated destructor stub
}

bool ADF4351_Driver::Init(unsigned long reference_frequency, int stepSize,
		int CS_PIN, int LE_PIN) {
	Wire.begin();
	if (reference_frequency < 10000000 || reference_frequency > 40000000) {
		goto init_error;
	}
	if (CS_PIN != 0) {
		ADF4351_CS = CS_PIN;
	}
	if (LE_PIN != 0) {
		ADF4351_LE = LE_PIN;
	}
	ADF4351refin = reference_frequency;
	Serial.println(F("ADFMode = STATE_INIT"));
	if (init_complete == true) {
		current_freq = 40000000;// Chip was initialized before, reset the Frequency to default
	}
	ChanStep = stepSize;
	dBm = 3;				// Set the amplitude to +5 dBm
	output_enable = 1;// 1bit  OutPwr 1=on           0 = off  Outport Null freischalten
	aux_enable = 1;	// 1bit  aux OutEna 1=on       0 = off  Outport Aux freischalten
	aux_select = 1;		// 1bit  aux OutSel
	MTLD = 0;// 1bit | This controls the "Mute til lock detect"-Function of the chip. It disables the output if the internal PLL has not locked.
	VcoPwrDown = 0;		// 1bit 1=VCO off
	SetFreq(current_freq);// call the function that calculates the registers and programs the chip
	init_complete = true;	// Set init to true
	return init_complete;// Tell the function that called this that the chip is ready

	init_error: init_complete = false;
	return init_complete;
}

void ADF4351_Driver::SetMode(char mode) {
	switch (mode) {
	case STATE_POWERDOWN:
		output_enable = 0;// 1bit  OutPwr 1=on           0 = off  Outport Null freischalten
		aux_enable = 0;	// 1bit  aux OutEna 1=on       0 = off  Outport Aux freischalten
		aux_select = 0;		// 1bit  aux OutSel
		MTLD = 0;// 1bit | This controls the "Mute til lock detect"-Function of the chip. It disables the output if the internal PLL has not locked.
		VcoPwrDown = 1;		// 1bit 1=VCO off
		break;
	case STATE_STANDBY:
		output_enable = 0;// 1bit  OutPwr 1=on           0 = off  Outport Null freischalten
		aux_enable = 0;	// 1bit  aux OutEna 1=on       0 = off  Outport Aux freischalten
		aux_select = 0;		// 1bit  aux OutSel
		MTLD = 0;// 1bit | This controls the "Mute til lock detect"-Function of the chip. It disables the output if the internal PLL has not locked.
		VcoPwrDown = 0;		// 1bit 1=VCO off
		break;
	case STATE_VCO_CHECK:
		output_enable = 1;// 1bit  OutPwr 1=on           0 = off  Outport Null freischalten
		aux_enable = 1;	// 1bit  aux OutEna 1=on       0 = off  Outport Aux freischalten
		aux_select = 1;		// 1bit  aux OutSel
		MTLD = 0;// 1bit | This controls the "Mute til lock detect"-Function of the chip. It disables the output if the internal PLL has not locked.
		VcoPwrDown = 1;		// 1bit 1=VCO off
		break;
	case STATE_TEST:
		output_enable = 1;// 1bit  OutPwr 1=on           0 = off  Outport Null freischalten
		aux_enable = 1;	// 1bit  aux OutEna 1=on       0 = off  Outport Aux freischalten
		aux_select = 1;		// 1bit  aux OutSel
		MTLD = 0;// 1bit | This controls the "Mute til lock detect"-Function of the chip. It disables the output if the internal PLL has not locked.
		VcoPwrDown = 1;		// 1bit 1=VCO off
		break;
	case 0x00:
		output_enable = 0;// 1bit  OutPwr 1=on           0 = off  Outport Null freischalten
		aux_enable = 0;	// 1bit  aux OutEna 1=on       0 = off  Outport Aux freischalten
		aux_select = 0;		// 1bit  aux OutSel
		MTLD = 1;// 1bit | This controls the "Mute til lock detect"-Function of the chip. It disables the output if the internal PLL has not locked.
		VcoPwrDown = 1;		// 1bit 1=VCO off
		break;
	}
}

bool ADF4351_Driver::SetAmplitude(char amplitude) {
	bool amplitude_set = true;
	switch (amplitude) {
	case -4:
		dBm = 0;
		break;
	case -1:
		dBm = 1;
		break;
	case 2:
		dBm = 2;
		break;
	case 5:
		dBm = 3;
		break;
	default:
		amplitude_set = false;
		break;
	}
	return amplitude_set;
}

void ADF4351_Driver::SetFrequency(unsigned long frequency) {
	current_freq = frequency;	// Update the internal frequency variable
	SetFreq(current_freq);		// Program the chip with the new frequency
}

void ADF4351_Driver::SetPhase(float phase_angle) {

}

unsigned long ADF4351_Driver::GetFrequency() {
	return current_freq;
}

char ADF4351_Driver::GetAmplitude() {
	char amplitude;
	switch (dBm) {
	case 0:
		amplitude = -4;
		break;
	case 1:
		amplitude = -1;
		break;
	case 2:
		amplitude = 2;
		break;
	case 3:
		amplitude = 5;
		break;
	default:
		amplitude = 5;
		break;
	}
	return amplitude;
}

int ADF4351_Driver::GetPhase() {

}

bool ADF4351_Driver::CheckLock(){
	Wire.requestFrom(GPIO_Address, 1);
	unsigned char GPIO_PINS = Wire.read();
	if((GPIO_PINS & 0x04) == 1){
		PLL_LOCK = true;
	}
	else{
		PLL_LOCK = false;
	}
	return PLL_LOCK;
}

bool ADF4351_Driver::CheckMux(){
	Wire.requestFrom(GPIO_Address, 1);
		unsigned char GPIO_PINS = Wire.read();
		if((GPIO_PINS & 0x05) == 1){
			MUX_OUT = true;
		}
		else{
			MUX_OUT = false;
		}
	return MUX_OUT;
}

//
//void SetupADF4351(int ADFMode) {
//  switch (ADFMode) {
//      Serial.println(F("ADFMode called"));
//    case 0x00:
//      Serial.println(F("ADFMode = STATE_POWERDOWN"));
//      output_enable = 0;            // 1bit  OutPwr 1=on           0 = off  Outport Null freischalten
//      aux_enable = 0;         // 1bit  aux OutEna 1=on       0 = off  Outport Aux freischalten
//      aux_select = 1;         // 1bit  aux OutSel
//      MTLD = 0;              // 1bit | This controls the "Mute til lock detect"-Function of the chip. It disables the output if the internal PLL has not locked.
//      VcoPwrDown = 1;        // 1bit 1=VCO off
//      SetFreqADF4351(4200000000); // Send the values to the ADF - Frequency-Value set to 4.2 GHz to move any signal still coming out of the Chip outside the area of interest
//      break;
//    case 0x01:
//      Serial.println(F("ADFMode = STATE_NORM_OP"));
//      dBm = 3;              // 3bit  Output-Power set to +5dBm
//      output_enable = 1;            // 1bit  OutPwr 1=on           0 = off  Outport Null freischalten
//      aux_enable = 1;         // 1bit  aux OutEna 1=on       0 = off  Outport Aux freischalten
//      aux_select = 0;         // 1bit  aux OutSel
//      MTLD = 0;              // 1bit | This controls the "Mute til lock detect"-Function of the chip. It disables the output if the internal PLL has not locked.
//      VcoPwrDown = 0;        // 1bit 1=VCO off
//      SetFreqADF4351(Freq);   // Send the values to the ADF - Frequency-Value set to the "Freq"-Variable to have the ADF4351 running at that frequency when the frequency-path is being switched (Chip has more time to lock the PLL this way).
//      break;
//    case 0x02:
//      Serial.println(F("ADFMode = STATE_STANDBY"));
//      output_enable = 0;            // 1bit  OutPwr 1=on           0 = off  Outport Null freischalten
//      aux_enable = 0;         // 1bit  aux OutEna 1=on       0 = off  Outport Aux freischalten
//      aux_select = 1;         // 1bit  aux OutSel
//      MTLD = 0;              // 1bit | This controls the "Mute til lock detect"-Function of the chip. It disables the output if the internal PLL has not locked.
//      VcoPwrDown = 0;        // 1bit 1=VCO off
//      SetFreqADF4351(4200000000); // Send the values to the ADF - Frequency-Value set to 4.2 GHz to move any signal still coming out of the Chip outside the area of interest
//      break;
//    case 0xA0:
//      Serial.println(F("ADFMode = STATE_VCO_CHECK"));
//      Freq = 2200000000;
//      dBm = 3;
//      D_RF_ena = 1;            // 1bit  OutPwr 1=on           0 = off  Outport Null freischalten
//      D_auxOutEna = 1;         // 1bit  aux OutEna 1=on       0 = off  Outport Aux freischalten
//      D_auxOutSel = 1;         // 1bit  aux OutSel
//      D_MTLD = 0;              // 1bit | This controls the "Mute til lock detect"-Function of the chip. It disables the output if the internal PLL has not locked.
//      D_VcoPwrDown = 0;        // 1bit 1=VCO off
//      SetFreqADF4351(Freq);
//      break;
//    case 0xA1:
//      Serial.println(F("ADFMode = STATE_TEST"));
//      Freq = 1000000000;
//      ADFdbm = 3;              // 3bit  Output-Power set to +5dBm
//      D_RF_ena = 1;            // 1bit  OutPwr 1=on           0 = off  Outport Null freischalten
//      D_auxOutEna = 1;         // 1bit  aux OutEna 1=on       0 = off  Outport Aux freischalten
//      D_auxOutSel = 1;         // 1bit  aux OutSel
//      D_MTLD = 0;              // 1bit | This controls the "Mute til lock detect"-Function of the chip. It disables the output if the internal PLL has not locked.
//      D_VcoPwrDown = 0;        // 1bit 1=VCO off
//      SetFreqADF4351(Freq);
//      break;
//    case 0xFF:
//      Serial.println(F("ADFMode = STATE_INIT"));
//      Freq = 400000000;
//      ADFdbm = 3;
//      D_RF_ena = 1;            // 1bit  OutPwr 1=on           0 = off  Outport Null freischalten
//      D_auxOutEna = 1;         // 1bit  aux OutEna 1=on       0 = off  Outport Aux freischalten
//      D_auxOutSel = 1;         // 1bit  aux OutSel
//      D_MTLD = 0;              // 1bit | This controls the "Mute til lock detect"-Function of the chip. It disables the output if the internal PLL has not locked.
//      D_VcoPwrDown = 0;        // 1bit 1=VCO off
//      SetFreqADF4351(Freq);
//      break;
//    default:
//      Freq = 420000000;         // Frequency set to 420MHz
//      ADFdbm = 3;              // Output-Power set to -4dBm
//      D_RF_ena = 1;            // 1bit  OutPwr 1=on           0 = off  Outport Null freischalten
//      D_auxOutEna = 1;         // 1bit  aux OutEna 1=on       0 = off  Outport Aux freischalten
//      D_auxOutSel = 1;         // 1bit  aux OutSel
//      D_MTLD = 0;              // 1bit | This controls the "Mute til lock detect"-Function of the chip. It disables the output if the internal PLL has not locked.
//      D_VcoPwrDown = 0;        // 1bit 1=VCO off
//      SetFreqADF4351(Freq);
//      break;
//  }
//  Serial.println(F("ADFMode = STATE HAS BEEN SET"));
//}

/////////////////////////// Subroutine: Setze Frequenz ADF4351 ///////////////////////////
void ADF4351_Driver::SetFreq(unsigned long FreqADF4351) {
	Serial.println(F("SetFreqADF4351_Step1"));
	FreqADF4351 = FreqADF4351 / 10;
	CalculateRegisters(FreqADF4351, Reg);
	Serial.print(F("SetFreqADF4351_WriteReg5"));
	PrepareDataBuffer(5);
	delayMicroseconds(2500);
	Serial.print(", Reg4");
	PrepareDataBuffer(4);
	delayMicroseconds(2500);
	Serial.print(", Reg 3");
	PrepareDataBuffer(3);
	delayMicroseconds(2500);
	Serial.print(", Reg 2");
	PrepareDataBuffer(2);
	delayMicroseconds(2500);
	Serial.print(", Reg 1");
	PrepareDataBuffer(1);
	delayMicroseconds(2500);
	Serial.print(", Reg 0");
	PrepareDataBuffer(0);
	delayMicroseconds(2500);
	Serial.println(", WRITE COMPLETE");
}
//
//////////////////////////// Teil-Subroutine ADF4351 ////////////////////////////
void ADF4351_Driver::PrepareDataBuffer(int idx) { // make 4 byte from integer for SPI-Transfer
	byte buf[4];
	for (int i = 0; i < 4; i++) {
		buf[i] = (byte) (Reg[idx] >> (i * 8));
	}
	TransmitData(buf[3], buf[2], buf[1], buf[0]);
}
//
///////////////////////////// Teil-Subroutine ADF4351 ////////////////////////////
void ADF4351_Driver::TransmitData(byte a1, byte a2, byte a3, byte a4) {
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
//
//////////////////////////////// Teil-Subroutine ADF4351 //////////////////////////
void ADF4351_Driver::CalculateRegisters(unsigned long freq, unsigned long R[]) {
	long RFout = freq;       // VCO-Frequenz
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

	float PFDFreq = ADF4351refin
			* ((1.0 + RD2refdoubl) / (R_Counter * (1.0 + RD1_Rdiv2))); //Referenzfrequenz
	float N = ((RFout) * outdiv) / (PFDFreq / 10);
	int N_Int = N;
	long M_Mod = PFDFreq * (100000 / ChanStep) / 100000;
	int F_Frac = round((N - N_Int) * M_Mod);

	R[0] = (unsigned long) (0 + F_Frac * pow(2, 3) + N_Int * pow(2, 15)); // Programs the Register R0: Bit 31 = RESERVED, Bit 30 - 15 = N_Int, Bit 14 - 3 = F_Frac, Bit 2 - 0 = ControlBits (filled with 0)
	R[1] = (unsigned long) (1 + M_Mod * pow(2, 3) + P_Phase * pow(2, 15)
			+ Prescal * pow(2, 27) + PhaseAdj * pow(2, 28));
	R[2] = (unsigned long) (2 + U1_CountRes * pow(2, 3)
			+ U2_Cp3state * pow(2, 4) + U3_PwrDown * pow(2, 5)
			+ U4_PDpola * pow(2, 6) + U5_LPD * pow(2, 7) + U6_LPF * pow(2, 8)
			+ CP_ChgPump * pow(2, 9) + D1_DoublBuf * pow(2, 13)
			+ R_Counter * pow(2, 14) + RD1_Rdiv2 * pow(2, 24)
			+ RD2refdoubl * pow(2, 25) + M_Muxout * pow(2, 26)
			+ LoNoisSpur * pow(2, 29));
	R[3] = (unsigned long) (3 + D_Clk_div * pow(2, 3) + C_Clk_mode * pow(2, 15)
			+ 0 * pow(2, 17) + F1_Csr * pow(2, 18) + 0 * pow(2, 19)
			+ F2_ChgChan * pow(2, 21) + F3_ADB * pow(2, 22)
			+ F4_BandSel * pow(2, 23) + 0 * pow(2, 24));
	R[4] = (unsigned long) (4 + dBm * pow(2, 3) + output_enable * pow(2, 5)
			+ dBm * pow(2, 6) + aux_enable * pow(2, 8) + aux_select * pow(2, 9)
			+ MTLD * pow(2, 10) + VcoPwrDown * pow(2, 11)
			+ B_BandSelClk * pow(2, 12) + D_RfDivSel * pow(2, 20)
			+ D_FeedBck * pow(2, 23));
	R[5] = (unsigned long) (5 + 0 * pow(2, 3) + 3 * pow(2, 19) + 0 * pow(2, 21)
			+ D_LdPinMod * pow(2, 22));
}
