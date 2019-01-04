/*
   Setup, Variable declarations and main loop of the program
*/

// SPI-Library
#include <SPI.h>

// i2c-Library
#include <Wire.h>

// Display-Libraries
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Adafruit_HX8357.h>

// Touch-Library
#include <Adafruit_STMPE610.h>

// ADC-Library
#include <Adafruit_ADS1015.h>

// Setup-Data for TFT-Display
#define TFT_DC PA1 // Connect TFT_DC to D3
#define TFT_CS PA2  // Connect TFT_CS to D4
#define TFT_RST PA0 //
Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC); // Create Display-Object
Adafruit_STMPE610 touch = Adafruit_STMPE610(); // Create TouchController-Object

#define INT 16  // Interrupt-Pin: GPIO16

// Control-Signals for ADF4351
#define ADF4351_CS PB14
#define ADF4351_LE PB13
#define ADF4351_LD 0x10 // Bitmask for the second GPIO-Expander 
#define ADF4351_MUX 0x20 // Bitmask for the second GPIO-Expander

// Control-Signals for AD9910
#define AD9910_CS PA8
#define AD9910_IOUP PA9
#define AD9910_OSK PA10
#define AD9910_DRH PB15
#define AD9910_DRC PB5
#define AD9910_DRO PB8
#define AD9910_RSO PB9
#define AD9910_PLL 0x08 // Bitmask for the second GPIO-Expander 
#define AD9910_RST 0x40 // Bitmask for the second GPIO-Expander 

// Setup-Data for the ADC on the analog board
Adafruit_ADS1015 ads;     /* Use this for the 12-bit version */

const String SysVersion = "Firmware-Version STM32_0.6a";
// Starting with Version 0.6a, only REV. C RF-Boards are compatible!

// Assign HEX-Values to color-names
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define AMBER 0xFDC0

// i2c GPIO-Expander Addresses - ATTENTION: Addresses only valid for PCF8574! PCF8574A requires different addresses!
#define ATTEN_ADR 0x3E  // i2c-Address of GPIO-Expander that controls the Attenuator - 
#define KEYBD_ADR 0x3F  // i2c Address of GPIO-Expander connected to the Keyboard - ROW_0 | ROW_1 | ROW_2 | ROW_3 | COLUMN_0 | COLUMN_1 | COLUMN_2 | FREE
#define GPIO_ADR 0x3A  // i2c Address of the GPIO-Expander - INT/GPIO-BITMAP: INT0 | INT_KEYBD | FREE | ADF4351_LOCK | AD9910_LOCK | ADF4351_CS | AD9910_CS | AD9910_DU
#define ANALOG_ADR 0x24   // i2c-Address for the Analog Board - Controls the Signal-Path

// Other i2c-Device Addresses
#define PWR_METER_ADR 0xFF // Address of the ADC in the Power-Meter - 0xFF = Placeholder-Value
#define EXT_SRC_SEL_ADR 0xE0 // Address of the External Mixer / Signal-Source Board. This board contains the circuitry to select between several sources, including the AD9910 and a Mixer through which the Signal from the AnalogBoard can be routed to achieve Amplitude-Modulation. Commands to this board are described in the documentation of this board. 

// Setup-Data for the Keypad
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
byte keys[ROWS][COLS] = {
  {1, 2, 3},
  {4, 5, 6},
  {7, 8, 9},
  {11, 10, 12}
};
// Digitran keypad, bit numbers of PCF8574 i/o port
byte rowPins[ROWS] = {0, 1, 2, 3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5, 6}; //connect to the column pinouts of the keypad
//Keypad_I2C kpd( makeKeymap(keys), rowPins, colPins, ROWS, COLS, KEYBD_ADR, PCF8574 );

// System State codes - Valid System states for both the entire System, as well as the SignalSource-Modules:
const byte STATE_NORM_OP = 0x00; // Default-Screen, also called "Mode_Select_1"-Screen.
//const byte STATE_INT_WAITING = 0x01;
const byte STATE_MODE_SELECT_2 = 0x02; // Second Mode-Select Screen
const byte STATE_ADV_FUNCTIONS = 0x03;
const byte STATE_ADV_MODULATION = 0x04;
const byte STATE_ARBITRARY_WAVE = 0x05;
const byte STATE_SIGPATH_CTRL = 0x06;// SignalPath-Control

const byte STATE_POWERDOWN = 0x10;
const byte STATE_COLDSTART = 0x11;
const byte STATE_STANDBY = 0x20;
const byte STATE_VCO_CHECK = 0x30;
const byte STATE_TEST = 0x40;
// Calibration and setup-Modes
const byte STATE_SIGPATH_MANUAL = 0xC0;
const byte STATE_SIGSOURCE_CAL = 0xC1;
const byte STATE_SIGPATH_CAL = 0xC2;
const byte STATE_SIGPATH_COMP = 0xC3;
const byte STATE_TOUCH_CAL = 0xC4;
const byte STATE_CONFIG_1 = 0xCA; // Basic System Settings
const byte STATE_CONFIG_2 = 0xCB;
const byte STATE_CONFIG_3 = 0xCC;
const byte STATE_CONFIG_4 = 0xCD;
const byte STATE_CONFIG_5 = 0xCE; // NV-RAM Control & Calibration
const byte STATE_CONFIG_6 = 0xCF;
const byte STATE_DEBUG = 0xD0;
const byte STATE_DEMO = 0xD1;
// Sys-States in which the system waits for an input
const byte STATE_ENTER_FREQ = 0xE0;
const byte STATE_ENTER_AMPLITUDE = 0xE1;
const byte STATE_ENTER_MODULATION_TYPE = 0xE2;
const byte STATE_ENTER_AM_PARAMETERS = 0xE3;
const byte STATE_ENTER_FM_PARAMETERS = 0xE4;
const byte STATE_ENTER_PM_PARAMETERS = 0xE5;
const byte STATE_ENTER_RAMP = 0xEA;
const byte STATE_ENTER_BURST = 0xEB;
const byte STATE_ENTER_DIG_PATTERN = 0xEC;
const byte STATE_ATTEN_CTRL_PAGE = 0xED;

// Sys-State when the device is started:
const byte STATE_INIT = 0xFF;

// InputMode Codes - 255 possible Input-Modes available
const byte INPUT_ENTER_FREQ = 0x00;
const byte INPUT_ENTER_AMPLITUDE = 0x01;
// Requesting the Parameters for the Modulation Edit-Mode.
const byte INPUT_ENTER_MODPARA1 = 0x10;
const byte INPUT_ENTER_MODPARA2 =  0x11;
const byte INPUT_ENTER_MODPARA3 = 0x12;
const byte INPUT_ENTER_MODPARA4  = 0x13;
// Requesting the Parameters for the Burst Edit-Mode.
const byte INPUT_ENTER_BURSTPARA1 = 0x20;
const byte INPUT_ENTER_BURSTPARA2 = 0x21;
const byte INPUT_ENTER_BURSTPARA3 = 0x22;
const byte INPUT_ENTER_BURSTPARA4 = 0x23;
// Requesting the Parameters for the Ramp Edit-Mode.
const byte INPUT_ENTER_RAMPPARA1 = 0x30;
const byte INPUT_ENTER_RAMPPARA2 = 0x31;
const byte INPUT_ENTER_RAMPPARA3 = 0x32;
const byte INPUT_ENTER_RAMPPARA4 = 0x33;
// Requesting the data for the digital pattern
const byte INPUT_DIG_PATTERN = 0xD0;
// Mode in which no input is expected
const byte INPUT_NO_INPUT = 0xFF;

// Modulation-Codes - Selects which modulation-Mode is active
const byte NO_MOD_SELECTED = 0x00;
const byte AM_SELECT = 0x01;
const byte FM_SELECT = 0x02;
const byte PM_SELECT = 0x03;

// System State variable - Initialized with the "ColdStart-Value" 0x11
volatile byte SysStatus = 0x11;
volatile byte InputMode = 0xFF;

/*
    NVRAM - Memory-Map:
    0x000 - 0x0F0 = CAL-DATA: 12bit DAC-Calibration Data for PWR_SET-DAC is stored for every 25MHz-Step Starting at 400MHz and going up to 3GHz (120 16bit-Words)
    0x0F2 - 0x1E2 = CAL-DATA: 12bit DAC-Calibration Data for AGC_ATTEN_BIAS is stored for every 25MHz-Step Starting at 400MHz and going up to 3GHz (120 16bit Words)
    0x200 - 0x203 = CAL-DATA: 32bit Measured Voltage at the RF_OUT-Detector at an output-Power of +10dBm.
    0x400 - 0x5AE = User-Config / User-Data
    0x5B0 - 0x5FE = System Configuration / Setup-Data / Touch Calibration-Data. If 0x5B0 is set to 0xFFFF, the System is being started for the first time.
    0x600 - 0x7FE = Sweep-Settings
*/

const byte PWR_SET_CAL_START = 0x000;
const byte AGC_BIAS_CAL_START = 0x0F2;
const byte REF_OUT_CAL_NVRAM = 0x200;
const byte USER_CONFIG_START = 0x400;
const byte SYSCONFIG_START = 0x05B0;
const byte SWEEP_SETTINGS_START = 0x600;
const byte NVRAM_ADR_END = 0x7FF;

/*
 * Error-Codes for the Error-Handler
 */

const byte DATA_ERROR_SIGPATH = 0xA0;
const byte DAC_OVERFLOW = 0xDA;


// *** Variables to configure frequency ***
double Freq = 400000000;     // Frequency-Variable in Hz - Default Value at Startup: 400MHz (ATTENTION: The ADF4351 methods require this value to be expressed in kHz!)
double Freq_Old = 400000000; // Previous selected frequency in Hz

// *** Constants and Variables to configure Analog Board ***
// DACs and ADC-Addresses
const byte SIGPATH_ADC = 0x48;
const byte RF_DAC_ADR = 0x60;
// ADC_Channels
const byte ADC_RF_OUT_SENSE = 0;
const byte ADC_RF_LEVEL_SENSE = 3;
//DAC_Channels
#define AGC_BIAS_SET MCP4728::DAC_CH::A
#define AGC_LVL_SET MCP4728::DAC_CH::B
#define RF_DAC_AUX1 MCP4728::DAC_CH::C
#define RF_DAC_AUX2 MCP4728::DAC_CH::D
// Filter-Codes
const byte BYPASS = 0x00;
const byte LPF_750 = 0x10;
const byte LPF_1500 = 0x20;
// Variables
int PWR_SET; // 12bit-Value with a Vref of 5V to control the DAC that sets the AGC
int AGC_ATTEN_BIAS; // 12bit-Value with a Vref of 5V to control the DAC that sets the AGC-BIAS
int AD9910_AMP_OFFSET;
byte SIGPATH_CTRL = B00100101; // Controls the Output of the GPIO-Expander on the Analog board.
bool AttenAuto = true;
int Atten = 95;             // Attenuation-Variable - Default: 95dB Attenuation
float OUTPUT_dBm = 0;         // Output-Power - 0 = Minimal output-amplitude. Can be adjusted in steps of 0.1 dBm.
float OUTPUT_DBM_OFFSET = 100.00; // Offset-Value for the Output-Amplitude in dBm by +100, because the minimal possible output is -100dBm <-- ATTENTION! SUBJECT TO CHANGE, PENDING TESTING OF ANALOG SIGNAL CHAIN!
bool AmplitudeModeDB = true; // Show the Amplitude in dBm or mV
bool SigPathAuto = true;
bool ExtSource = false;
bool ExtAM = false;
bool ExtMixerBoardAvail = false;
volatile bool OutputEnable = true;
byte LPF_Select = 0x10;
float RF_OUT_REF = 0x00;  // Voltage present at ADC_RF_OUT_SENSE-Channel @ +10 dBm Output-Power
//float RF_OUT_sense;
//float RF-LvL_sense; // Voltages at the RF-Detectors on analog Board

// *** Variables to configure Modulation-Parameters ***
unsigned long ModPara1 = 0; // Modulation-Strength (Amplitude, Frequency-Width, Phase-Angle
unsigned long ModPara2 = 0; // Modulation-Frequency (khz) - does not apply if digital Pattern is active
unsigned long ModPara3 = 0; // Additional Modulation-Parameter for Advanced Modulation-Mode
unsigned long ModPara4 = 0; // Additional Modulation-Parameter for Advanced Modulation-Mode
byte DigPatternData[128]; // Initialize the array to store the data for the digital pattern.
byte ModulationType = 0x00;
volatile bool ModulationEnable = false;

// *** Variables for various tasks ***
boolean ClearScreen = true;
byte interruptSource = 0; // Stores the Interrupt-Source
byte intgpio = 0xFF; // Stores the current state of the IO-Pins of the INTGPIO-Expander - Initialized with 0xFF
boolean UpdateFreqArea = true; // Shows that the Frequency-Area needs to be Updated
boolean UpdateAmpArea = true; // Shows that the Amplitude-Area needs to be Updated
boolean UpdateModArea = true; // Shows that the Modulation-Area needs to be Updated
unsigned long keyboardInput; // Stores the input made via the Keypad
bool updateButtons = true;

void setup() {
  SysStatus = STATE_INIT;
  Serial.begin(9600);
  Serial.println(F("*** SERIAL INTERFACE - RF SIGNAL-GENERATOR ***"));

  Serial.println(F("Defining Pins"));
  pinMode(TFT_DC, OUTPUT);
  pinMode(TFT_CS, OUTPUT);
  pinMode(INT, INPUT);
  pinMode(ADF4351_CS, OUTPUT);
  pinMode(AD9910_CS, OUTPUT);
  pinMode(AD9910_IOUP, OUTPUT);
  pinMode(AD9910_OSK, OUTPUT);
  pinMode(AD9910_DRH, OUTPUT);
  pinMode(AD9910_DRC, OUTPUT);
  pinMode(AD9910_DRO, INPUT);
  pinMode(AD9910_RSO, INPUT);

  Serial.println(F("Set all pins HIGH"));
  digitalWrite(ADF4351_CS, HIGH);
  digitalWrite(ADF4351_LE, HIGH);
  digitalWrite(AD9910_CS, HIGH);
  digitalWrite(AD9910_IOUP, HIGH);
  digitalWrite(AD9910_OSK, LOW);
  digitalWrite(AD9910_DRH, LOW);
  digitalWrite(AD9910_DRC, LOW);
  digitalWrite(TFT_DC, HIGH); // Make sure to Deselect TFT_DC
  digitalWrite(TFT_CS, HIGH); // Make sure to Deselect TFT_CS
  Serial.println(F("WAIT until system is powered for 2 seconds to allow all components to come online"));
  while (millis() <= 2000) {
    digitalWrite(PC13, HIGH);
    digitalWrite(PC13, HIGH);
    digitalWrite(PC13, HIGH);
    digitalWrite(PC13, HIGH);
    digitalWrite(PC13, HIGH);
    digitalWrite(PC13, LOW);
    digitalWrite(PC13, LOW);
    digitalWrite(PC13, LOW);
    digitalWrite(PC13, LOW);
    digitalWrite(PC13, LOW);
  }

  Serial.println(F("SPI Init"));
  SPI.begin();

  Serial.println(F("i2c Init"));
  Wire.begin();

  Serial.println(F("DISPLAY-Setup"));
  tft.begin(HX8357D);
  tft.fillScreen(BLACK);
  tft.setRotation(1);
  delay(50);
  Serial.println(F("DISPLAY-TEST"));
  TestDisplay();
  delay(0); // Delay added to yield Processor-Core to the WiFi-Code
  Serial.println(F("Show Splashscreen"));
  Splash();
  delay(2000); // Delay added to yield Processor-Core to the WiFi-Code
  tft.setTextColor(BLACK);
  tft.setCursor(10, 25);
  tft.setTextSize(1);
  tft.println(F("DISPLAY-TEST COMPLETE"));

  Serial.println(SysVersion);
  tft.println(SysVersion);

  tft.println(F("Touch Init"));
  Serial.println(F("Touch Init"));
  if (! touch.begin()) {
    Serial.println(F("STMPE610 not found!"));
    tft.println(F("STMPE610 not found!"));
    ErrorMode(0x10, true);
  }
  TouchInit();
  delay(500);

  tft.println(F("Keypad Init"));
  Serial.println(F("Keypad Init"));
  keypadInit();
  delay(500);

  tft.println(F("Setting up GPIO-Receiver"));
  Serial.println(F("Setting up GPIO-Receiver"));
  Wire.beginTransmission(GPIO_ADR);
  Wire.write(0xFF); // Set all Interrupt-Inputs HIGH, as all the Signals are Active LOW
  Wire.endTransmission();
  delay(500);

  Serial.println(F("Reading CAL-Data from the NV-RAM"));
  tft.println(F("Reading CAL-Data from the NV-RAM"));
  if (ReadNVData(0x5B0) == 0xFFFF) {
    Serial.println(F("SYSTEM UNCAL"));
    tft.println(F("SYSTEM UNCAL"));
    delay(500);
  }
  if (ReadNVData(0x5B0 == 0x00)) {
    Serial.println(F("No CAL-RAM installed"));
    tft.println(F("No CAL-RAM installed"));
    delay(500);
  }
  else {
    ReadCalData();
  }
  delay(1000);

  Serial.println(F("ADS1015 INIT"));
  tft.println(F("ADS1015 INIT"));
  ads.begin();
  ads.setGain(GAIN_ONE); // Set the ADC_Gain to ONE, which means the resolution is 2mV / LSbit
  delay(500);

  Serial.println(F("MCP4728 INIT"));
  tft.println(F("MCP4728 INIT"));
  DAC_Setup();
  delay(500);

  Serial.println(F("AD9910 INIT"));
  tft.println(F("AD9910 INIT"));
  SetupAD9910(STATE_INIT);
  delay(500); // Delay added to yield Processor-Core to the WiFi-Code

  Serial.println(F("ADF4351 INIT"));
  tft.println(F("ADF4351 INIT"));
  SetupADF4351(STATE_INIT);
  delay(500);

  Serial.println(F("Setting up analog board with default value --- "));
  tft.println(F("Setting up analog board with default value --- "));
  SetLPF(BYPASS, false, false);
  delay(500);
  CheckAttenuator(true);
  SetAttenuator(0x00);
  delay(500);
  SetAmplitude(OUTPUT_dBm);
  delay(500);
  tft.println(F("Looking for the External_Source/Mixer-Board-Option"));
  Serial.println(F("Looking for the External_Source/Mixer-Board-Option"));
  Wire.beginTransmission(EXT_SRC_SEL_ADR);
  Wire.write(0x1D);
  Wire.endTransmission();
  delay(1500);
  Wire.requestFrom(EXT_SRC_SEL_ADR, 1);
  byte EXT_SRC_SEL_ADR_Response = Wire.read();
  if (EXT_SRC_SEL_ADR_Response != 0xAC) {
    tft.println(F("NOT FOUND - ASSUMING AD9910 CONNECTED DIRECTLY"));
    Serial.println(F("NOT FOUND - ASSUMING AD9910 CONNECTED DIRECTLY"));
    ExtMixerBoardAvail = false;
  }
  else {
    tft.println(F("FOUND!"));
    Serial.println(F("FOUND!"));
    ExtMixerBoardAvail = true;
  }
  delay(500);

  Serial.println(F("SIGNAL PATH-TEST"));
  tft.println(F("SIGNAL PATH-TEST"));
  SignalPathTest();
  delay(1000);

  //  byte keypressed_Setup = ReadKeyboard();
  //  if (keypressed_Setup == 0xCF) {
  //    SysStatus = STATE_TOUCH_CAL;
  //    Serial.println(F("#-Key pressed - Starting Touch-Calibration"));
  //    TouchCalibration();
  //  }
  //
  //  if (keypressed_Setup == 0xFF) {
  //    SysStatus = STATE_DEBUG;
  //    Serial.println(F("*-Key pressed - Starting Touch-Calibration"));
  //  }
  //  else {
  SysStatus = STATE_NORM_OP;
  //  }
  tft.setTextSize(5);
  tft.println(F("READY!"));
  delay(1000);

  tft.fillScreen(BLACK);
  Freq = 100000000; // Set frequency to 287.234,912 kHz to check if Calculation in Display-Function is correct
  SetFreq(Freq);
  UpdateDisplay();
  Serial.print(F("Frequency = "));
  Serial.print(Freq, DEC);
  Serial.println(F(" Hz"));
  Serial.println(F("READY"));
}

void loop() {
  //  CheckSerial();
  ReadTouch(); // Only here for debug-purposes! Remove once Interrupt-System is running!
  ReadKeybd();
  ReadGPIO();
  switch (SysStatus) {
    case STATE_DEBUG:
      SetFreq(60000000);
      delay(5000);
      SetFreq(50000000);
      delay(5000);
      // Put some code here to escape Debug-Mode
      break;
    case STATE_NORM_OP:
      UpdateDisplay();
      DrawSigPathParams();
      break;
    default:
      UpdateDisplay();
      DrawSigPathParams();
      break;
  }
  switch (ModulationEnable) {
    case true:
      break;
    case false:
      break;
  }
}
