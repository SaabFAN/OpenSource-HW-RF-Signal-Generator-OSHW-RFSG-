/* *** FUNCTIONS THAT CONCERN THE NVRAM ***
    NVRAM is located on the Analog-Board, has a size of 2KBytes and contains:
    - CAL-Data
    - User-Config
    - Setup-Data
    - Sweep-Configurations


    Memory-Map:
    0x000 - 0x0F0 = CAL-DATA: 12bit DAC-Calibration Data for PWR_SET-DAC is stored for every 25MHz-Step Starting at 400MHz and going up to 3GHz (120 16bit-Words)
    0x0F2 - 0x1E2 = CAL-DATA: 12bit DAC-Calibration Data for AGC_ATTEN_BIAS is stored for every 25MHz-Step Starting at 400MHz and going up to 3GHz (120 16bit Words)
    0x200 - 0x201 = CAL-DATA: 12bit Measured Voltage at the RF_OUT-Detector at an output-Power of +10dBm.
    0x400 - 0x5AE = User-Config / User-Data
    0x5B0 - 0x5FE = System Configuration / Setup-Data / Touch Calibration-Data. If 0x5B0 is set to 0xFFFF, the System is being started for the first time.
    0x600 - 0x7FE = Sweep-Settings
*/

const byte NVRAM_ADDR = 0x50; // FM24C16 NV-RAM sitting at Address 0x50 with all Address-Lines pulled LOW - FM24CL16 has always the Address 0x50

void WriteNVData(int NV_DATA, int NV_ADDR) {
  byte bufLength = 2;
  // Function to increase bufLength for Addresses that save values larger than 2 Bytes
  byte buf[bufLength];
  for (byte i = 0; i <= bufLength; i++) {
    buf[i] = NV_DATA >> (8 * i);
  }
  // Function to adjust NVRAM_ADDR to access different pages
  byte NVRAM_ADDR_OFFSET = NV_ADDR % 0xFF;
  Wire.beginTransmission(NVRAM_ADDR + NVRAM_ADDR_OFFSET);
  Wire.write(NV_ADDR);
  for (byte i = 0; i <= bufLength; i++) {
    Wire.write(buf[i]);
  }
  Wire.endTransmission();
}

//void WriteNVDataBurst(int NV_DATA[], int NV_ADDR, int burstlength){
//  byte bufLength = 2;
//  // Function to increase bufLength for Addresses that save values larger than 2 Bytes
//  byte buf[bufLength];
//  for (byte i = 0; i <= bufLength; i++){
//
//  }
//  // Function to adjust NVRAM_ADDR to access different pages
//    Wire.beginTransmission(NVRAM_ADDR);
//  Wire.write(NV_ADDR);
//  for (byte i = 0; i <= bufLength; i++){
//   Wire.write(buf[i]);
//  }
//  Wire.endTransmission();
//}

int ReadNVData(int NV_ADDR) {
  byte NVRAM_ADDR_OFFSET = NV_ADDR % 0xFF;
  int NV_DATA;
  Wire.requestFrom(NVRAM_ADDR + NVRAM_ADDR_OFFSET, 2);
  NV_DATA = Wire.read() << 8;
  NV_DATA = NV_DATA + Wire.read();
  return NV_DATA;
}

void ReadNVDataBurst(int NV_ADDR, byte burstLength, byte ReadNV_Target) { // Burst-Read. Requires Start-Address, burst-length and Target-Array
  byte NVRAM_ADDR_OFFSET = NV_ADDR % 0xFF;
  Wire.requestFrom(NVRAM_ADDR + NVRAM_ADDR_OFFSET, burstLength);
}

void ReadCalData() {
  RF_OUT_REF = ReadNVData(REF_OUT_CAL_NVRAM);
}
