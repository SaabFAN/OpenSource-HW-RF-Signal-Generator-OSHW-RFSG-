/*
 * ADF4351Driver.h
 *
 * This is the driver for the ADF4351 Module as used in the ARSG Signal-Generator. It compatible with all STM32F103C based CPU-Boards.
 *
 *
 *  Created on: 19.02.2019
 *      Author: voyag
 */

#ifndef ADF4351DRIVER_H_
#define ADF4351DRIVER_H_

#include "Arduino.h"
#include "SPI.h"
#include "Wire.h"

#define STATE_POWERDOWN 0x10
#define STATE_COLDSTART 0x11
#define STATE_STANDBY 0x20
#define STATE_VCO_CHECK 0x30
#define STATE_TEST 0x40
#define GPIO_Address 0x3A

class ADF4351_Driver {
public:
	ADF4351_Driver();
	virtual ~ADF4351_Driver();
	bool Init(unsigned long reference_frequency, int stepSize, int CS_PIN, int LE_PIN);	// This sets up the driver and initializes the ADF4351-Chip. i2c_address is the address of the GPIO-Expander that is connected to the Lock Detect and Mux-Outputs.
	void SetMode(char mode);
	void Configure(int selector, int value);
	bool SetAmplitude(char amplitude);
	void SetFrequency(unsigned long frequency);
	void SetPhase(float phase_angle);
	bool CheckLock();
	bool CheckMux();
	unsigned long GetFrequency();
	char GetAmplitude();
	int GetPhase();
private:
	unsigned long ADF4351refin; // Reference-Frequency for the ADF4351 in Hz - Reference-Frequency = 10 Mhz (ATTENTION: The ADF4351 methods later require this value to be expressed in kHz!)
	unsigned long current_freq; // Variable that stores the currently set frequency
	int phase = 1;	// variable that stores the currently set phase value - Default: 1
	long ChanStep;	// Channel-Step = 10 kHz (Register-Value = kHz-Value * 100)
	bool init_complete;
	int ADF4351_CS;
	int ADF4351_LE;
	bool PLL_LOCK;
	bool MUX_OUT;

	// Configuration-Values of the Chip
	unsigned long Reg[6];		// Array for the ADF4351 Registers

	int dBm = 3;// Variable to configure the output-power of the ADF4351 - Default: +5dBm
	int output_enable = 1;// 1bit  OutPwr 1=on           0 = off  Outport Null freischalten
	int aux_enable = 1;	// 1bit  aux OutEna 1=on       0 = off  Outport Aux freischalten
	int aux_select = 1;		// 1bit  aux OutSel
	int MTLD = 0;// 1bit | This controls the "Mute til lock detect"-Function of the chip. It disables the output if the internal PLL has not locked.
	int VcoPwrDown = 0;		// 1bit 1=VCO off
	// PLL-Reg-R0         =  32bit
	// Registerselect        3bit
	// int F_Frac = 4;       // 12bit
	// int N_Int = 92;       // 16bit
	// reserved           // 1bit

	// PLL-Reg-R1         =  32bit
	// Registerselect        3bit
	// int M_Mod = 5;        // 12bit Modulus value - calculated by the
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
	int M_Muxout = 6;    // 3bit  MUX-Output control. Set to DIGITAL LOCK DETECT
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
	int D_out_PWR = (dBm);      // 2bit  OutPwr 0-3 3= +5dBm   Power out 1
	// int D_RF_ena = 1;            // 1bit  OutPwr 1=on           0 = off  Outport Null freischalten
	int D_auxOutPwr = (dBm);    // 2bit  aux OutPwr 0-3        Power out 2
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

	// calc bandselect und RF-div
	int outdiv = 1;
	void CalculateRegisters(unsigned long freq, unsigned long R[]);
	void PrepareDataBuffer(int idx);
	void SetFreq(unsigned long FreqADF4351);
	void TransmitData(byte a1, byte a2, byte a3, byte a4);
};

#endif /* ADF4351DRIVER_H_ */
