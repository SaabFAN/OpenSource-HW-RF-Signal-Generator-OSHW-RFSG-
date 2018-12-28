/*
    PIN MAPPING

    Here you can change your wire mapping between your keypad and PCF8574
    Default mapping is for sparkfun 4x3 keypad
*/

#define COL0  6  // P2 of PCF8574, col0 is usually pin 3 of 4x3 keypads
#define COL1  5  // P0 of PCF8574, col1 is usually pin 1 of 4x3 keypads
#define COL2  4  // P4 of PCF8574, col2 is usually pin 5 of 4x3 keypads
#define ROW0  0  // P1 of PCF8574, row0 is usually pin 2 of 4x3 keypads
#define ROW1  1  // P6 of PCF8574, row1 is usually pin 7 of 4x3 keypads
#define ROW2  2  // P5 of PCF8574, row2 is usually pin 6 of 4x3 keypads
#define ROW3  3  // P3 of PCF8574, row3 is usually pin 4 of 4x3 keypads


/*
    KEYPAD KEY MAPPING

    Default key mapping for 4x4 keypads, you can change it here if you have or
    like different keys
*/

const byte keymap[4][3] =
{
  1, 2, 3,
  4, 5, 6,
  7, 8, 9,
  11, 10, 12
};


/*
    VAR AND CONSTANTS DEFINITION. Don't change nothing here

*/

// Default row and col pin counts
int num_rows = 4;
int num_cols = 3;

// Current search row
//static int row_select;

// Current data set in PCF8574
static int current_data;

// Hex byte statement for each port of PCF8574
const int hex_data[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

// Hex data for each row of keypad in PCF8574
const int pcf8574_row_data[4] =
{
  hex_data[ROW1] | hex_data[ROW2] | hex_data[ROW3] |  hex_data[COL0] | hex_data[COL1] | hex_data[COL2] ,
  hex_data[ROW0] | hex_data[ROW2] | hex_data[ROW3] |  hex_data[COL0] | hex_data[COL1] | hex_data[COL2] ,
  hex_data[ROW0] | hex_data[ROW1] | hex_data[ROW3] |  hex_data[COL0] | hex_data[COL1] | hex_data[COL2] ,
  hex_data[ROW0] | hex_data[ROW1] | hex_data[ROW2] |  hex_data[COL0] | hex_data[COL1] | hex_data[COL2],
};

// Hex data for each col of keypad in PCF8574
int col[3] = {hex_data[COL0], hex_data[COL1], hex_data[COL2]};

/*
    PUBLIC METHODS
*/

void keypadInit()
{
  // All PCF8574 ports high
  Wire.beginTransmission(KEYBD_ADR);
  Wire.write(0xff);
  Wire.endTransmission();
  // Start with the first row
  //  row_select = 0;
}

char get_Key()
{
  static int temp_key;

  byte tmp_data;
  byte r;
  byte c;

  int key = '\0';

  // Search row low
  //  pcf8574_write(KEYBD_ADR, pcf8574_row_data[row_select]);

  for (r = 0; r < num_rows; r++) {
    pcf8574_write(KEYBD_ADR, pcf8574_row_data[r]);
    for (c = 0; c < num_cols; c++) {
      // Read pcf8574 port data
      tmp_data = pcf8574_byte_read(KEYBD_ADR);

      // XOR to compare obtained data and current data and know
      // if some column are low
      tmp_data ^= current_data;

      // Key pressed!
      if (col[c] == tmp_data) {
        temp_key = keymap[r][c];
        return '\0';
      }
    }
  }

  //  for (r = 0; r < num_cols; r++) {
  //    // Read pcf8574 port data
  //    tmp_data = pcf8574_byte_read(KEYBD_ADR);
  //
  //    // XOR to compare obtained data and current data and know
  //    // if some column are low
  //    tmp_data ^= current_data;
  //
  //    // Key pressed!
  //    if (col[r] == tmp_data) {
  //      temp_key = keymap[row_select][r];
  //      return '\0';
  //    }
  //  }

  // Key was pressed and then released
  if ((key == '\0') && (temp_key != '\0'))
  {
    key = temp_key;
    temp_key = '\0';
    return key;
  }

  // All PCF8574 ports high again
  pcf8574_write(KEYBD_ADR, 0xff);

  // Next row
  //  row_select++;
  //  if (row_select == num_rows) {
  //    row_select = 0;
  //  }

  return key;
}

/*
    PRIVATE METHODS
*/

void pcf8574_write(int addr, int data)
{
  current_data = data;

  Wire.beginTransmission(addr);
  Wire.write(data);
  Wire.endTransmission();
}

int pcf8574_byte_read(int addr)
{
  Wire.requestFrom(addr, 1);

  return Wire.read();
}
