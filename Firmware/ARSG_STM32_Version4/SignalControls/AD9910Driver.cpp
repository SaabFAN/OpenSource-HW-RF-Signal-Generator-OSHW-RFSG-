/*
 * AD9910Driver.cpp
 *
 *  Created on: 16.03.2019
 *      Author: voyag
 */

#include "AD9910Driver.h"

// Debug-Modes
#define SPI_DEBUG
#define AD9910_DEBUG

// *** Constants to configure the DDS-Chip AD9910 ***
// Control-Registers are 4 chars wide if not otherwise specified
const char CFR1_ADDR = 0x00; // Address for the CFR1-Register - Needs to be send in the InstructionWord
const char CFR2_ADDR = 0x01;
const char CFR3_ADDR = 0x02;
const char AuxDAC_ADDR = 0x03;
const char IO_UPD_Rate_ADDR = 0x04;
const char FTW_ADDR = 0x07;
const char POW_ADDR = 0x08;
const char ASF_ADDR = 0x09;
const char DIGRAMP_Limit_ADDR = 0xB;
const char DIGRAMP_Step_ADDR = 0xC;
const char DIGRAMP_Rate_ADDR = 0xD;
const char SINGLETONE_PROFILE_0 = 0x0E;

// Register-Bit Locations
// CFR 1
const unsigned int RAM_ENABLE_LOC = 2147483648;
const unsigned int RAM_PLAYBACK_DESTINATION_LOC = 536870912;
const unsigned int MANUAL_OSK_CONTROL_LOC = 8388608;
const unsigned int INVERSE_SINC_FILTER_LOC = 4194304;
const unsigned int INTERNAL_PROFILE_CONTROL_LOC = 131072;
const unsigned int DDS_SINE_LOC = 65536;
const unsigned int LOAD_LRR_IOUPDATE_LOC = 32768;
const unsigned int AUTOCLEAR_DIGI_RAMP_ACCU_LOC = 16384;
const unsigned int AUTOCLEAR_PHASE_ACCU_LOC = 8192;
const unsigned int CLEAR_DIGI_RAMP_ACCU_LOC = 4096;
const unsigned int CLEAR_PHASE_ACCU_LOC = 2048;
const unsigned int LOAD_ARR_IOUPDATE_LOC = 1024;
const unsigned int OSK_ENABLE_LOC = 512;
const unsigned int SELECT_AUTO_OSK_LOC = 256;
const unsigned int DIGITAL_POWER_DOWN_LOC = 128;
const unsigned int DAC_POWER_DOWN_LOC = 64;
const unsigned int REFCLK_INPUT_POWER_DOWN_LOC = 32;
const unsigned int AUX_DAC_POWER_DOWN_LOC = 16;
const unsigned int EXTERNAL_POWER_DOWN_LOC = 8;
const unsigned int SDIO_INPUT_ONLY_LOC = 2; // Bit 1: Sets the way the SDIO-Pin works. 0 = I/O (default) | 1 = Input Only (Needs to be 1 if SPI is used!)
const unsigned int LSB_FIRST_LOC = 1; // Bit 0: Switches between MSBFIRST and LSBFIRST - set to "1" to avoid multiply by "0" - Result is the same: x * 1 = x

// CFR 2
const unsigned int ENABLE_AMPLITUDE_SCALE_CW_PROFILES_LOC = 16777216;
const unsigned int INTERNAL_IOUPDATE_ACTIVE_LOC = 8388608;
const unsigned int SYNC_CLK_ENABLE_LOC = 4194304; //
const unsigned int DIGI_RAMP_DESTINATION_LOC = 1048576; // 2 Bits
const unsigned int DIGI_RAMP_ENABLE_LOC = 524288;
const unsigned int DIGI_RAMP_NO_DWELL_HIGH_LOC = 262144;
const unsigned int DIGI_RAMP_NO_DWELL_LOW_LOC = 131072;
const unsigned int READ_EFFECTIVE_FTW_LOC = 65536;
const unsigned int IOUPDATE_RATE_CTRL_LOC = 16384;
const unsigned int PD_CLK_ENABLE_LOC = 2048; // Disabled, because PD_CLK-Pin is not used.
const unsigned int PD_CLK_INVERT_LOC = 1024;
const unsigned int TX_ENABLE_INVERT_LOC = 512;
const unsigned int MATCHED_LATENCY_ENABLE_LOC = 128;
const unsigned int DATA_ASSEMBLER_HOLD_LAST_VALUE_LOC = 64;
const unsigned int SYNC_TIMING_VALIDATION_ERROR_LOC = 32;
const unsigned int PARALLEL_DATA_PORT_ENABLE_LOC = 16;
const unsigned int FM_GAIN_LOC = 1;

// CFR 3
const unsigned int DRV0_LOC = 268435456;              //
const unsigned int VCOSEL_LOC = 16777216;           //
const unsigned int ICP_LOC = 524288;              //
const unsigned int REFCLK_Div_Bypass_LOC = 32768;        //
const unsigned int REFCLK_Div_RESET_LOC = 16384;         //
const unsigned int PFD_RESET_LOC = 1024;                //
const unsigned int PLL_ENABLE_LOC = 256;                //
const unsigned int AD9910_PLL_DIVIDER_LOC = 2;            //

// *** Variables to configure the DDS-Chip AD9910 ***

// Register-Variables
unsigned int RegCFR1; // Variable for Control Register 1 - 4 chars - See Datasheet for details
unsigned int RegCFR2;              // Variable for Control Register 2
unsigned int RegCFR3;              // Variable for Control Register 3
char AuxDAC;                  // Stores the AUX-DAC Value
unsigned int IO_UPD_Rate;        // Stores value of the I/O Update Rate Register
unsigned long FTW; // Frequency Tuning Word - 32bit - Calculated by formula: FTW = ((2^32)*(fout/fclock))
unsigned short POW;               // Phase Offset Word - 16bit Phase Offset Word
unsigned int ASF;                  // Amplitude Scale Factor - 32bits
unsigned long DIGRAMP_Limit; // Limits of the Digital Ramp - char 7 - 4 = Upper Ramp Limit / char 3 - 0 = Lower Ramp Limit
unsigned long DIGRAMP_Step; // Step of Digital Ramp - char 7 - 4 = Decrement Step Size / char 3 - 0 = Increment Step Size
unsigned int DIGRAMP_Rate; // Rate of Diigtal Ramp - char 3 - 2 = Negative slope rate / char 1 - 0 = Positive Slope Rate

// CAL-Variables - Saves as OFFSET-Values to be added or subtracted
int ASF_OFFSET;
int FTW_OFFSET;

// CFR1-Values | CFR1 contains general settings
char RAM_ENABLE = 0;                    // Bit 31
char RAM_PLAYBACK_DESTINATION = 0; // Bits 30 - 29: 0 = Frequency, 1 = Phase, 2 = Amplitude, 3 = Polar (Phase and Amplitude)
char MANUAL_OSK_CONTROL = 1; // Bit 23: Enables / Disables the Manual OSK-Control - NOT USED! PIN NOT CONNECTED
char INVERSE_SINC_FILTER = 1; // Bit 22: Enables/Disables the Inverse Sinc Filter
char INTERNAL_PROFILE_CONTROL = 0;      // Bits 20 - 17: Selects the RAM-Profile
char DDS_SINE = 0;                   // Bit 16: Selects the Sine / Cosine-Output
char LOAD_LRR_IOUPDATE = 0; // Bit 15: Sets the behavior of the digital ramp timer
char AUTOCLEAR_DIGI_RAMP_ACCU = 0;
char AUTOCLEAR_PHASE_ACCU = 0;
char CLEAR_DIGI_RAMP_ACCU = 0;
char CLEAR_PHASE_ACCU = 0;
char LOAD_ARR_IOUPDATE = 0;
char OSK_ENABLE = 0;
char SELECT_AUTO_OSK = 0;
char DIGITAL_POWER_DOWN = 0;
char DAC_POWER_DOWN = 0;
char REFCLK_INPUT_POWER_DOWN = 0;
char AUX_DAC_POWER_DOWN = 0;
char EXTERNAL_POWER_DOWN = 0;
const char SDIO_INPUT_ONLY = 1; // Bit 1: Sets the way the SDIO-Pin works. 0 = I/O (default) | 1 = Input Only (Needs to be 1 if SPI is used!)
const char LSB_FIRST = 0; // Bit 0: Switches between MSBFIRST and LSBFIRST

// CFR2-Values
char ENABLE_AMPLITUDE_SCALE_CW_PROFILES = 1;
char INTERNAL_IOUPDATE_ACTIVE = 0;
char SYNC_CLK_ENABLE = 1; //
char DIGI_RAMP_DESTINATION = 0; // 2 Bits
char DIGI_RAMP_ENABLE = 0;
char DIGI_RAMP_NO_DWELL_HIGH = 0;
char DIGI_RAMP_NO_DWELL_LOW = 0;
char READ_EFFECTIVE_FTW = 0;
char IOUPDATE_RATE_CTRL = 0;
char PD_CLK_ENABLE = 1;
char PD_CLK_INVERT = 0;
char TX_ENABLE_INVERT = 0;
char MATCHED_LATENCY_ENABLE = 0;
char DATA_ASSEMBLER_HOLD_LAST_VALUE = 0;
char SYNC_TIMING_VALIDATION_ERROR = 0;
char PARALLEL_DATA_PORT_ENABLE = 0;
char FM_GAIN = 0;

// CFR3-Values | CFR3 configures internal PLL
char DRV0 = 0b11;      // Setting for REFCLK_OUT Drive - Default: REFCLK_OUT OFF
char VCOSEL = 0b101; // Select the VCO - Default: VCO5 for a internal Clock of 920 - 1030 MHz
char Icp = 0b111; // Sets the Charge Pump Current - This value will require experimentation and may be stored in external NVRAM
char REFCLK_Div_Bypass = 0; // Controls the InputDivider-Bypass - Default: 0 (OFF)
char REFCLK_Div_RESET = 1; // Controls the InputDivider - Default: 0 (Divider is reset and not working)
char PFD_RESET = 0; // Enables / Disables the Phase Comparator - Default: 1 (Phase Comparator active, PLL working)
char PLL_ENABLE = 1; // Enables / Disables the PLL-Output - Default: true (PLL-Output to DDS-CLOCK
char AD9910_PLL_DIVIDER = 25; // The Divider for the DDS-CLOCK PLL - Default: 25 (40 MHz  * 25 = 1000 MHz) - Formula: PLL_Clock / RefClock = PLL_DIVIDER - PLL_CLOCK = 1000MHz
float DDSCLK = 1000000000.0;        // DDS-Clock in Hz

/*
 Modes for the AD9910:
 - 0x00 = PowerDown: Everything is powered down to conserve power
 - 0x10 = Normal Operation
 - 0x20 = Standby: Everything turned on, except for the DAC to allow for very fast power up
 - 0x30 = NOT USED
 - 0x40 = TestMode: 10MHz, Max Amplitude,
 - 0xFF = PowerOn-Initialization
 */

AD9910Driver::AD9910Driver() {
	// TODO Auto-generated constructor stub

}

AD9910Driver::~AD9910Driver() {
	// TODO Auto-generated destructor stub
}

bool AD9910Driver::Init(unsigned long reference_frequency, char GPIO_ADR) {
	Serial.print(F("AD9910 Init - GPIO_ADR = : "));
	bool init_complete;
	_GPIO_ADR = GPIO_ADR;
	Serial.print(_GPIO_ADR, HEX);
	Serial.print(F(" | Setting CPU-Pins"));
	pinMode(AD9910_CS, OUTPUT);
	pinMode(AD9910_IOUP, OUTPUT);
	pinMode(AD9910_OSK, OUTPUT);
	pinMode(AD9910_DRH, OUTPUT);
	pinMode(AD9910_DRC, OUTPUT);
	pinMode(AD9910_DRO, INPUT);
	pinMode(AD9910_RSO, INPUT);
	digitalWrite(AD9910_CS, HIGH);
	digitalWrite(AD9910_IOUP, HIGH);
	digitalWrite(AD9910_OSK, LOW);
	digitalWrite(AD9910_DRH, LOW);
	digitalWrite(AD9910_DRC, LOW);
	AD9910_PLL_DIVIDER = (DDSCLK / reference_frequency);
	Serial.print(F("AD9910_PLL_DIVIDER = "));
	Serial.println(AD9910_PLL_DIVIDER, DEC);
	Wire.beginTransmission(_GPIO_ADR);
	Wire.write(0xFF); // Reset AD9910
	Wire.endTransmission();
	Serial.print(F(" Setting GPIO-Expander-Pins to 0xBF - Readback: 0x"));
	Wire.beginTransmission(_GPIO_ADR);
	delay(50);
	Wire.write(0xBF); // Set AD9910_RST (Connected to I/O-Reset) to LOW (ACTIVE HIGH-input)
	Wire.endTransmission();
	Wire.requestFrom(_GPIO_ADR, 1);
	Serial.println(Wire.read(), HEX);
	delay(50);
	SetMode('C');
#ifdef AD9910_DEBUG
	Dump();
#endif
	SetAmplitude(10, true);
	SetFrequency(10000000);
	Serial.print(F("Check GPIO-Expander again: Readback = 0x"));
	Wire.requestFrom(_GPIO_ADR, 1);
	char readback = Wire.read();
	if (bitRead(readback, 3) == 1) {
		init_complete = true;
	} else {
		init_complete = false;
	}
	Serial.println(readback, HEX);
	return init_complete;
}

void AD9910Driver::SetMode(char mode) {
	Serial.print(F("Setting AD9910-Registers to: "));
	switch (mode) {
	case 'P':	// Power Down-Mode
#ifdef SPI_DEBUG
		Serial.println(F("POWER DOWN"));
#endif
		DIGITAL_POWER_DOWN = 1;
		DAC_POWER_DOWN = 1;
		REFCLK_INPUT_POWER_DOWN = 1;
		AUX_DAC_POWER_DOWN = 1;
		SendCFR();
		break;
		break;
	case 'C':	// ColdStart
		Serial.print(F("COLD START: "));
		RegCFR1 = (unsigned long) (LSB_FIRST
				+ SDIO_INPUT_ONLY * SDIO_INPUT_ONLY_LOC
				+ EXTERNAL_POWER_DOWN * EXTERNAL_POWER_DOWN_LOC
				+ AUX_DAC_POWER_DOWN * AUX_DAC_POWER_DOWN_LOC
				+ REFCLK_INPUT_POWER_DOWN * REFCLK_INPUT_POWER_DOWN_LOC
				+ DAC_POWER_DOWN * DAC_POWER_DOWN_LOC
				+ DIGITAL_POWER_DOWN * DIGITAL_POWER_DOWN_LOC
				+ SELECT_AUTO_OSK * SELECT_AUTO_OSK_LOC
				+ OSK_ENABLE * OSK_ENABLE_LOC
				+ LOAD_ARR_IOUPDATE * LOAD_ARR_IOUPDATE_LOC
				+ CLEAR_PHASE_ACCU * CLEAR_PHASE_ACCU_LOC
				+ CLEAR_DIGI_RAMP_ACCU * CLEAR_DIGI_RAMP_ACCU_LOC
				+ AUTOCLEAR_PHASE_ACCU * AUTOCLEAR_PHASE_ACCU_LOC
				+ AUTOCLEAR_DIGI_RAMP_ACCU * AUTOCLEAR_DIGI_RAMP_ACCU_LOC
				+ LOAD_LRR_IOUPDATE * LOAD_LRR_IOUPDATE_LOC
				+ DDS_SINE * DDS_SINE_LOC
				+ INTERNAL_PROFILE_CONTROL * INTERNAL_PROFILE_CONTROL_LOC
				+ INVERSE_SINC_FILTER * INVERSE_SINC_FILTER_LOC
				+ MANUAL_OSK_CONTROL * MANUAL_OSK_CONTROL_LOC
				+ RAM_PLAYBACK_DESTINATION * RAM_PLAYBACK_DESTINATION_LOC
				+ RAM_ENABLE * RAM_ENABLE_LOC);
		Serial.print("RegCFR1 = 0x");
		Serial.print(RegCFR1, HEX);
		RegCFR2 = (unsigned long) (0 + FM_GAIN
				+ PARALLEL_DATA_PORT_ENABLE * PARALLEL_DATA_PORT_ENABLE_LOC
				+ SYNC_TIMING_VALIDATION_ERROR
						* SYNC_TIMING_VALIDATION_ERROR_LOC
				+ DATA_ASSEMBLER_HOLD_LAST_VALUE
						* DATA_ASSEMBLER_HOLD_LAST_VALUE_LOC
				+ MATCHED_LATENCY_ENABLE * MATCHED_LATENCY_ENABLE_LOC
				+ TX_ENABLE_INVERT * TX_ENABLE_INVERT_LOC
				+ PD_CLK_INVERT * PD_CLK_INVERT_LOC
				+ PD_CLK_ENABLE * PD_CLK_ENABLE_LOC
				+ IOUPDATE_RATE_CTRL * IOUPDATE_RATE_CTRL_LOC
				+ READ_EFFECTIVE_FTW * READ_EFFECTIVE_FTW_LOC
				+ DIGI_RAMP_NO_DWELL_LOW * DIGI_RAMP_NO_DWELL_LOW_LOC
				+ DIGI_RAMP_NO_DWELL_HIGH * DIGI_RAMP_NO_DWELL_HIGH_LOC
				+ DIGI_RAMP_ENABLE * DIGI_RAMP_ENABLE_LOC
				+ DIGI_RAMP_DESTINATION * DIGI_RAMP_DESTINATION_LOC
				+ SYNC_CLK_ENABLE * SYNC_CLK_ENABLE_LOC
				+ INTERNAL_IOUPDATE_ACTIVE * INTERNAL_IOUPDATE_ACTIVE_LOC
				+ ENABLE_AMPLITUDE_SCALE_CW_PROFILES
						* ENABLE_AMPLITUDE_SCALE_CW_PROFILES_LOC);
		Serial.print(" RegCFR2 = 0x");
		Serial.print(RegCFR2, HEX);
		RegCFR3 = (unsigned long) (0
				+ AD9910_PLL_DIVIDER * AD9910_PLL_DIVIDER_LOC
				+ PLL_ENABLE * PLL_ENABLE_LOC + PFD_RESET * PFD_RESET_LOC
				+ REFCLK_Div_RESET * REFCLK_Div_RESET_LOC
				+ REFCLK_Div_Bypass * REFCLK_Div_Bypass_LOC + Icp * ICP_LOC
				+ VCOSEL * VCOSEL_LOC + DRV0 * DRV0_LOC);
		Serial.print(" RegCFR3 = 0x");
		Serial.println(RegCFR3, HEX);
		FTW = round(4294967296UL * (4000000 / DDSCLK)); // Formula for calculating the FTW: FTW = ((2^32)*(fout/fclock)) // Frequency set to 1MHz
		AuxDAC = 0x7F;
		ASF = 0x2FFF;
		POW = 0x0000;
		WriteAD9910(CFR1_ADDR);
		WriteAD9910(CFR2_ADDR);
		WriteAD9910(CFR3_ADDR);
		WriteAD9910(AuxDAC_ADDR);
		WriteAD9910(FTW_ADDR);
		WriteAD9910(ASF_ADDR);
		SetFrequency(1000000);
		freq_Old = 1000000;
		break;
		break;
	case 'S':	// Standby-Mode
#ifdef SPI_DEBUG
		Serial.println(F("STANDBY"));
#endif
		DAC_POWER_DOWN = 1; // Disable the DDS-Output. All other components remain online
		SendCFR();
		break;
		break;
	case 'T':	// Test-Mode
#ifdef SPI_DEBUG
		Serial.println(F("TEST"));
#endif
		DIGITAL_POWER_DOWN = 0;
		DAC_POWER_DOWN = 0;
		REFCLK_INPUT_POWER_DOWN = 0;
		AUX_DAC_POWER_DOWN = 0;
		SendCFR();
		break;
		break;
	case 'N':	// Normal-Mode
#ifdef SPI_DEBUG
		Serial.println(F("NORMAL"));
#endif
		DIGITAL_POWER_DOWN = 0;
		DAC_POWER_DOWN = 0;
		REFCLK_INPUT_POWER_DOWN = 0;
		AUX_DAC_POWER_DOWN = 0;
		SendCFR();
		break;
		break;
	}
}

void AD9910Driver::Configure(int selector, int value) {

}
// Amplitude-Settings in mVpp or dB
// -2dBm is the maximum RF-Power that may be injected into the System. As the full scale output-current is 20mA, the maximum output-voltage is 1V = 500mVpp
bool AD9910Driver::SetAmplitude(float amplitude, bool Decibels) {
	Serial.println(F("Setting AD9910 Amplitude"));
	float ASF_helper;
	switch (Decibels) {
	case true:
		ASF_helper = amplitude / log(20);
		ASF = round(pow(2, 14) * ASF_helper);
		if(ASF >= 0x3FFF){
			ASF = 0x3FFF;
		}
		WriteAD9910(ASF_ADDR);
		break;
	case false:
		float AmpAD9910 = amplitude / 1000; // Divide by 1000 to get the scaling-factor
		ASF = round(pow(2, 14) * AmpAD9910); // Multiply the Scaling-factor with 2^14
		if(ASF >= 0x3FFF){
			ASF = 0x3FFF;
		}
		WriteAD9910(ASF_ADDR);
		break;
	}
	return true;
}

void AD9910Driver::SetFrequency(unsigned long frequency) {
	float FTW_StageOne = frequency / DDSCLK;
	float FTW_StageTwo = 4294967296.0 * FTW_StageOne;
	FTW_StageTwo = round(FTW_StageTwo);
	FTW = (unsigned long)FTW_StageTwo; // Formula for calculating the FTW: FTW = ((2^32)*(fout/fclock))
#ifdef SPI_DEBUG
	Serial.print("FreqAD9910 = ");
	Serial.print(frequency, DEC);
	Serial.print(F(" | DDSCLK = "));
	Serial.print(DDSCLK, DEC);
	Serial.print(F(" | FreqAD9910 / DDSCLK = "));
	Serial.print(FTW_StageOne, DEC);
	Serial.print(F(" | FTW = "));
	Serial.println(FTW, DEC);
#endif
	WriteAD9910(SINGLETONE_PROFILE_0);
#ifdef SPI_DEBUG
	Dump();
	Serial.print(F("AD9910-PLL LOCKED = 0x"));
	Serial.println(CheckLock(), HEX);
#endif
}

bool AD9910Driver::CheckLock() {
	Wire.requestFrom(_GPIO_ADR, 1);
	char data = Wire.read();
	if (bitRead(data, 3) == 1) {
		return true;
	} else {
		return false;
	}
}

bool AD9910Driver::CheckMux() {

}
unsigned long AD9910Driver::GetFrequency() {

}
char AD9910Driver::GetAmplitude() {

}
int AD9910Driver::GetPhase() {

}

/*
 The following subroutines calculate the Register-Contents for the AD9910 and send the data to it
 */

void AD9910Driver::SetPhase(unsigned long phaseOffset) {
#ifdef SPI_DEBUG
	Serial.println(F("SetPhase(): "));
#endif
	POW = round(65536 * (phaseOffset / 360));
	WriteAD9910(POW_ADDR);
}

// Function to set the CFR1 and CFR2-Registers - Excludes CFR3 because that register is set at system startup and remains unchanged after that.
void AD9910Driver::SendCFR() {
#ifdef SPI_DEBUG
	Serial.print(F("SendCFR(): "));
#endif
	RegCFR1 = (unsigned long) (LSB_FIRST + SDIO_INPUT_ONLY * SDIO_INPUT_ONLY_LOC
			+ EXTERNAL_POWER_DOWN * EXTERNAL_POWER_DOWN_LOC
			+ AUX_DAC_POWER_DOWN * AUX_DAC_POWER_DOWN_LOC
			+ REFCLK_INPUT_POWER_DOWN * REFCLK_INPUT_POWER_DOWN_LOC
			+ DAC_POWER_DOWN * DAC_POWER_DOWN_LOC
			+ DIGITAL_POWER_DOWN * DIGITAL_POWER_DOWN_LOC
			+ SELECT_AUTO_OSK * SELECT_AUTO_OSK_LOC
			+ OSK_ENABLE * OSK_ENABLE_LOC
			+ LOAD_ARR_IOUPDATE * LOAD_ARR_IOUPDATE_LOC
			+ CLEAR_PHASE_ACCU * CLEAR_PHASE_ACCU_LOC
			+ CLEAR_DIGI_RAMP_ACCU * CLEAR_DIGI_RAMP_ACCU_LOC
			+ AUTOCLEAR_PHASE_ACCU * AUTOCLEAR_PHASE_ACCU_LOC
			+ AUTOCLEAR_DIGI_RAMP_ACCU * AUTOCLEAR_DIGI_RAMP_ACCU_LOC
			+ LOAD_LRR_IOUPDATE * LOAD_LRR_IOUPDATE_LOC
			+ DDS_SINE * DDS_SINE_LOC
			+ INTERNAL_PROFILE_CONTROL * INTERNAL_PROFILE_CONTROL_LOC
			+ INVERSE_SINC_FILTER * INVERSE_SINC_FILTER_LOC
			+ MANUAL_OSK_CONTROL * MANUAL_OSK_CONTROL_LOC
			+ RAM_PLAYBACK_DESTINATION * RAM_PLAYBACK_DESTINATION_LOC
			+ RAM_ENABLE * RAM_ENABLE_LOC);
#ifdef SPI_DEBUG
	Serial.print("RegCFR1 = 0x");
	Serial.print(RegCFR1, HEX);
#endif
	RegCFR2 = (unsigned long) (0 + FM_GAIN
			+ PARALLEL_DATA_PORT_ENABLE * PARALLEL_DATA_PORT_ENABLE_LOC
			+ SYNC_TIMING_VALIDATION_ERROR * SYNC_TIMING_VALIDATION_ERROR_LOC
			+ DATA_ASSEMBLER_HOLD_LAST_VALUE
					* DATA_ASSEMBLER_HOLD_LAST_VALUE_LOC
			+ MATCHED_LATENCY_ENABLE * MATCHED_LATENCY_ENABLE_LOC
			+ TX_ENABLE_INVERT * TX_ENABLE_INVERT_LOC
			+ PD_CLK_INVERT * PD_CLK_INVERT_LOC
			+ PD_CLK_ENABLE * PD_CLK_ENABLE_LOC
			+ IOUPDATE_RATE_CTRL * IOUPDATE_RATE_CTRL_LOC
			+ READ_EFFECTIVE_FTW * READ_EFFECTIVE_FTW_LOC
			+ DIGI_RAMP_NO_DWELL_LOW * DIGI_RAMP_NO_DWELL_LOW_LOC
			+ DIGI_RAMP_NO_DWELL_HIGH * DIGI_RAMP_NO_DWELL_HIGH_LOC
			+ DIGI_RAMP_ENABLE * DIGI_RAMP_ENABLE_LOC
			+ DIGI_RAMP_DESTINATION * DIGI_RAMP_DESTINATION_LOC
			+ SYNC_CLK_ENABLE * SYNC_CLK_ENABLE_LOC
			+ INTERNAL_IOUPDATE_ACTIVE * INTERNAL_IOUPDATE_ACTIVE_LOC
			+ ENABLE_AMPLITUDE_SCALE_CW_PROFILES
					* ENABLE_AMPLITUDE_SCALE_CW_PROFILES_LOC);
#ifdef SPI_DEBUG
	Serial.print(" RegCFR2 = 0x");
	Serial.println(RegCFR2, HEX);
#endif
	WriteAD9910(CFR1_ADDR);
	WriteAD9910(CFR2_ADDR);
}

void AD9910Driver::WriteAD9910(char AD9910_INST) {
	char buf[8]; // 64bit buffer to store individual chars of the registers
#ifdef SPI_DEBUG
	Serial.print(F("WriteAD9910(): "));
//  RegCFR1 = 0x00800002;
//  RegCFR2 = 0x01400820;
//  RegCFR3 = 0x35384132;
	AuxDAC = 0x7F;
//	ASF = 0x3FFF;
	POW = 0x0000;
//FTW = 0x1999999A;
#endif
	digitalWrite(AD9910_CS, LOW); //Pull AD9910_CS LOW to select the chip
	pinMode(PA6, INPUT_PULLUP);
//	SPI.setClockDivider(SPI_CLOCK_DIV2);
	SPI.beginTransaction(SPISettings(24000000, MSBFIRST, SPI_MODE0));
	SPI.transfer(AD9910_INST);
	switch (AD9910_INST) {
	case CFR1_ADDR:
		//      SPI.write32(RegCFR1); // DISABLE this line and ENABLE the following block on boards other than ESP8266 that do not have the "write32" function in their SPI-Library
		buf[0] = (char) RegCFR1;
		buf[1] = (char) (RegCFR1 >> 8);
		buf[2] = (char) (RegCFR1 >> 16);
		buf[3] = (char) (RegCFR1 >> 24);
#ifdef SPI_DEBUG
		Serial.print(F("BUFFER_RegCFR1: "));
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
		buf[0] = (char) RegCFR2;
		buf[1] = (char) (RegCFR2 >> 8);
		buf[2] = (char) (RegCFR2 >> 16);
		buf[3] = (char) (RegCFR2 >> 24);
#ifdef SPI_DEBUG
		Serial.print(F("BUFFER_RegCFR2: "));
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
		buf[0] = (char) RegCFR3;
		buf[1] = (char) (RegCFR3 >> 8);
		buf[2] = (char) (RegCFR3 >> 16);
		buf[3] = (char) (RegCFR3 >> 24);
#ifdef SPI_DEBUG
		Serial.print(F("BUFFER_RegCFR3: "));
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
		buf[0] = (char) IO_UPD_Rate;
		buf[1] = (char) (IO_UPD_Rate >> 8);
		buf[2] = (char) (IO_UPD_Rate >> 16);
		buf[3] = (char) (IO_UPD_Rate >> 24);
#ifdef SPI_DEBUG
		Serial.print(F("BUFFER_IO_UPD_Rate: "));
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
		buf[0] = (char) FTW;
		buf[1] = (char) (FTW >> 8);
		buf[2] = (char) (FTW >> 16);
		buf[3] = (char) (FTW >> 24);
#ifdef SPI_DEBUG
		Serial.print(F("BUFFER_FTW: "));
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
		SPI.transfer16(POW);      //      buf[0] = (char) POW;
		//      buf[1] = (char) POW >> 8;
		//      buf[2] = (char) POW >> 16;
		//      buf[3] = (char) POW >> 24;
		//SPI.transfer(buf[3]);
		//      SPI.transfer(buf[2]);
		//      SPI.transfer(buf[1]);
		//      SPI.transfer(buf[0]);
		break;
	case ASF_ADDR:
		//      SPI.write32(ASF);
		buf[0] = (char) ASF;
		buf[1] = (char) (ASF >> 8);
		buf[2] = (char) (ASF >> 16);
		buf[3] = (char) (ASF >> 24);
#ifdef SPI_DEBUG
		Serial.print(F("BUFFER_ASF: "));
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
		buf[0] = (char) DIGRAMP_Limit;
		buf[1] = (char) (DIGRAMP_Limit >> 8);
		buf[2] = (char) (DIGRAMP_Limit >> 16);
		buf[3] = (char) (DIGRAMP_Limit >> 24);
		buf[4] = (char) (DIGRAMP_Limit >> 32);
		buf[5] = (char) (DIGRAMP_Limit >> 40);
		buf[6] = (char) (DIGRAMP_Limit >> 48);
		buf[7] = (char) (DIGRAMP_Limit >> 56);
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
		buf[0] = (char) DIGRAMP_Step;
		buf[1] = (char) (DIGRAMP_Step >> 8);
		buf[2] = (char) (DIGRAMP_Step >> 16);
		buf[3] = (char) (DIGRAMP_Step >> 24);
		buf[4] = (char) (DIGRAMP_Step >> 32);
		buf[5] = (char) (DIGRAMP_Step >> 40);
		buf[6] = (char) (DIGRAMP_Step >> 48);
		buf[7] = (char) (DIGRAMP_Step >> 56);
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
		buf[0] = (char) DIGRAMP_Rate;
		buf[1] = (char) (DIGRAMP_Rate >> 8);
		buf[2] = (char) (DIGRAMP_Rate >> 16);
		buf[3] = (char) (DIGRAMP_Rate >> 24);
#ifdef SPI_DEBUG
		Serial.print(F("BUFFER_DIGRAMP_Rate: "));
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
		buf[0] = (char) (ASF >> 0);
		buf[1] = (char) (ASF >> 8);
		buf[2] = (char) POW;
		buf[3] = (char) (POW >> 8);
		buf[4] = (char) FTW;
		buf[5] = (char) (FTW >> 8);
		buf[6] = (char) (FTW >> 16);
		buf[7] = (char) (FTW >> 24);
#ifdef SPI_DEBUG
		Serial.print(F("BUFFER_SingleTone_Profile: "));
		Serial.print(F("buf[7] = 0x"));
		Serial.print(buf[7], HEX);
		Serial.print(F(" buf[6] = 0x"));
		Serial.print(buf[6], HEX);
		Serial.print(F(" buf[5] = 0x"));
		Serial.print(buf[5], HEX);
		Serial.print(F(" buf[4] = 0x"));
		Serial.print(buf[4], HEX);
		Serial.print(F(" buf[3] = 0x"));
		Serial.print(buf[3], HEX);
		Serial.print(F(" buf[2] = 0x"));
		Serial.print(buf[2], HEX);
		Serial.print(F(" buf[1] = 0x"));
		Serial.print(buf[1], HEX);
		Serial.print(F(" buf[0] = 0x"));
		Serial.println(buf[0], HEX);
		Serial.print(F("ASF = "));
		Serial.print(ASF, HEX);
		Serial.print(F(" POW = "));
		Serial.print(POW, HEX);
		Serial.print(F(" FTW = 0x"));
		Serial.print(FTW, HEX);
		Serial.print(F(" = "));
		Serial.print(FTW, DEC);
		Serial.println(F(" DEC"));
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
	delayMicroseconds(15); // May not be necessary - Depending on how fast the GPIO-Expander is
	digitalWrite(AD9910_IOUP, HIGH); // Data is accepted at rising edge of AD9910_IOUP or AD9910_DU
	delayMicroseconds(15); // May not be necessary - Depending on how fast the GPIO-Expander is
	digitalWrite(AD9910_CS, HIGH); // Pull AD9910_CS HIGH to deselect the chip
}

void AD9910Driver::Dump() {
	// Read all registers and dump them to the Serial Console
	digitalWrite(AD9910_CS, LOW); //Pull AD9910_CS LOW to select the chip
	Serial.println(F("AD9910 Register-Dump: "));
	pinMode(PA6, INPUT_PULLUP);
	Serial.print(F("CFR1 = 0x"));
//	SPI.setClockDivider(SPI_CLOCK_DIV4);
	SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));
	SPI.transfer(0x80);
	char data[8];
	for (char i = 0; i < 4; i++) {
		data[i] = SPI.transfer(0x00);
	}
	for (char i = 0; i < 3; i++) {
		Serial.print(data[i], HEX);
	}
	Serial.println(data[3], HEX);
	digitalWrite(AD9910_CS, HIGH); // Register read and sent to serial console, turn CS off for a moment
	Serial.print(F("CFR2 = 0x"));
	digitalWrite(AD9910_CS, LOW); //Pull AD9910_CS LOW to select the chip
	SPI.transfer(0x81);
	for (char i = 0; i < 4; i++) {
		data[i] = SPI.transfer(0x00);
	}
	for (char i = 0; i < 3; i++) {
		Serial.print(data[i], HEX);
	}
	Serial.println(data[3], HEX);
	digitalWrite(AD9910_CS, HIGH); // Register read and sent to serial console, turn CS off for a moment
	Serial.print(F("CFR3 = 0x"));
	digitalWrite(AD9910_CS, LOW); //Pull AD9910_CS LOW to select the chip
	SPI.transfer(0x82);
	for (char i = 0; i < 3; i++) {
		data[i] = SPI.transfer(0x00);
	}
	for (char i = 0; i < 3; i++) {
		Serial.print(data[i], HEX);
	}
	Serial.println(data[3], HEX);
	digitalWrite(AD9910_CS, HIGH); // Register read and sent to serial console, turn CS off for a moment
	Serial.print(F("SingleToneProfile = 0x"));
	digitalWrite(AD9910_CS, LOW); //Pull AD9910_CS LOW to select the chip
	SPI.transfer(0x8E);
	for (char i = 0; i < 8; i++) {
		data[i] = SPI.transfer(0x00);
	}
	for (char i = 0; i < 7; i++) {
		Serial.print(data[i], HEX);
	}
	Serial.println(data[7], HEX);
	digitalWrite(AD9910_CS, HIGH); //Pull AD9910_CS LOW to select the chip
	SPI.endTransaction();
}
