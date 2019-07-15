-- Copyright (C) 2018  Intel Corporation. All rights reserved.
-- Your use of Intel Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Intel Program License 
-- Subscription Agreement, the Intel Quartus Prime License Agreement,
-- the Intel FPGA IP License Agreement, or other applicable license
-- agreement, including, without limitation, that your use is for
-- the sole purpose of programming logic devices manufactured by
-- Intel and sold by Intel or its authorized distributors.  Please
-- refer to the applicable agreement for further details.

-- VENDOR "Altera"
-- PROGRAM "Quartus Prime"
-- VERSION "Version 18.1.0 Build 625 09/12/2018 SJ Lite Edition"

-- DATE "03/15/2019 20:44:32"

-- 
-- Device: Altera 5M1270ZT144C5 Package TQFP144
-- 

-- 
-- This VHDL file should be used for ModelSim-Altera (VHDL) only
-- 

LIBRARY IEEE;
LIBRARY MAXV;
USE IEEE.STD_LOGIC_1164.ALL;
USE MAXV.MAXV_COMPONENTS.ALL;

ENTITY 	ARSG_GlueLogic IS
    PORT (
	ADF4351_CLK : OUT std_logic;
	SPI_CLK : IN std_logic;
	ADF_CS : IN std_logic;
	ADF_SELECT : IN std_logic;
	ADF4351_MOSI : OUT std_logic;
	SPI_MOSI : IN std_logic;
	ADF4351_LE : OUT std_logic;
	ADF_LE : IN std_logic;
	ADF4351_CS : OUT std_logic;
	ADF5355_CLK : OUT std_logic;
	ADF5355_MOSI : OUT std_logic;
	ADF5355_LE : OUT std_logic;
	ADF5355_CS : OUT std_logic;
	TFT_CLK : OUT std_logic;
	TFT_CS : IN std_logic;
	TFT_MOSI : OUT std_logic;
	ATTEN_1dB : OUT std_logic;
	SCL : IN std_logic;
	SDA : INOUT std_logic;
	ATTEN_2dB : OUT std_logic;
	ATTEN_4dB : OUT std_logic;
	ATTEN_8dB : OUT std_logic;
	ATTEN_16dB : OUT std_logic;
	ATTEN_32dB_1 : OUT std_logic;
	ATTEN_32dB_2 : OUT std_logic;
	ATTEN_LE : OUT std_logic;
	SPI_MISO : OUT std_logic;
	TFT_MISO : IN std_logic;
	INT_OUT : OUT std_logic;
	i2c_InProgress : OUT std_logic;
	tx_done : OUT std_logic;
	TFT_DC_OUT : OUT std_logic;
	TFT_DC : IN std_logic;
	TFT_CS_OUT : OUT std_logic;
	TFT_RST_OUT : OUT std_logic;
	TFT_RST : IN std_logic;
	INT_VECT : OUT std_logic_vector(2 DOWNTO 0);
	ADF4351_LD : IN std_logic;
	ADF4351_MUX : IN std_logic;
	ADF5355_LD : IN std_logic;
	ADF5355_MUX : IN std_logic;
	CPLD_CS : IN std_logic;
	INT_TOUCH : IN std_logic;
	INT_KEYBD : IN std_logic
	);
END ARSG_GlueLogic;

-- Design Ports Information


ARCHITECTURE structure OF ARSG_GlueLogic IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_ADF4351_CLK : std_logic;
SIGNAL ww_SPI_CLK : std_logic;
SIGNAL ww_ADF_CS : std_logic;
SIGNAL ww_ADF_SELECT : std_logic;
SIGNAL ww_ADF4351_MOSI : std_logic;
SIGNAL ww_SPI_MOSI : std_logic;
SIGNAL ww_ADF4351_LE : std_logic;
SIGNAL ww_ADF_LE : std_logic;
SIGNAL ww_ADF4351_CS : std_logic;
SIGNAL ww_ADF5355_CLK : std_logic;
SIGNAL ww_ADF5355_MOSI : std_logic;
SIGNAL ww_ADF5355_LE : std_logic;
SIGNAL ww_ADF5355_CS : std_logic;
SIGNAL ww_TFT_CLK : std_logic;
SIGNAL ww_TFT_CS : std_logic;
SIGNAL ww_TFT_MOSI : std_logic;
SIGNAL ww_ATTEN_1dB : std_logic;
SIGNAL ww_SCL : std_logic;
SIGNAL ww_ATTEN_2dB : std_logic;
SIGNAL ww_ATTEN_4dB : std_logic;
SIGNAL ww_ATTEN_8dB : std_logic;
SIGNAL ww_ATTEN_16dB : std_logic;
SIGNAL ww_ATTEN_32dB_1 : std_logic;
SIGNAL ww_ATTEN_32dB_2 : std_logic;
SIGNAL ww_ATTEN_LE : std_logic;
SIGNAL ww_SPI_MISO : std_logic;
SIGNAL ww_TFT_MISO : std_logic;
SIGNAL ww_INT_OUT : std_logic;
SIGNAL ww_i2c_InProgress : std_logic;
SIGNAL ww_tx_done : std_logic;
SIGNAL ww_TFT_DC_OUT : std_logic;
SIGNAL ww_TFT_DC : std_logic;
SIGNAL ww_TFT_CS_OUT : std_logic;
SIGNAL ww_TFT_RST_OUT : std_logic;
SIGNAL ww_TFT_RST : std_logic;
SIGNAL ww_INT_VECT : std_logic_vector(2 DOWNTO 0);
SIGNAL ww_ADF4351_LD : std_logic;
SIGNAL ww_ADF4351_MUX : std_logic;
SIGNAL ww_ADF5355_LD : std_logic;
SIGNAL ww_ADF5355_MUX : std_logic;
SIGNAL ww_CPLD_CS : std_logic;
SIGNAL ww_INT_TOUCH : std_logic;
SIGNAL ww_INT_KEYBD : std_logic;
SIGNAL \ADF_CS~combout\ : std_logic;
SIGNAL \ADF_SELECT~combout\ : std_logic;
SIGNAL \SPI_CLK~combout\ : std_logic;
SIGNAL \inst17~combout\ : std_logic;
SIGNAL \SPI_MOSI~combout\ : std_logic;
SIGNAL \inst16~combout\ : std_logic;
SIGNAL \ADF_LE~combout\ : std_logic;
SIGNAL \inst18~combout\ : std_logic;
SIGNAL \inst17~0_combout\ : std_logic;
SIGNAL \inst7~combout\ : std_logic;
SIGNAL \inst14~combout\ : std_logic;
SIGNAL \inst6~combout\ : std_logic;
SIGNAL \inst7~0_combout\ : std_logic;
SIGNAL \TFT_CS~combout\ : std_logic;
SIGNAL \inst8~combout\ : std_logic;
SIGNAL \inst9~combout\ : std_logic;
SIGNAL \TFT_MISO~combout\ : std_logic;
SIGNAL \inst10~combout\ : std_logic;
SIGNAL \TFT_DC~combout\ : std_logic;
SIGNAL \inst11~combout\ : std_logic;
SIGNAL \TFT_RST~combout\ : std_logic;
SIGNAL \inst12~combout\ : std_logic;

BEGIN

ADF4351_CLK <= ww_ADF4351_CLK;
ww_SPI_CLK <= SPI_CLK;
ww_ADF_CS <= ADF_CS;
ww_ADF_SELECT <= ADF_SELECT;
ADF4351_MOSI <= ww_ADF4351_MOSI;
ww_SPI_MOSI <= SPI_MOSI;
ADF4351_LE <= ww_ADF4351_LE;
ww_ADF_LE <= ADF_LE;
ADF4351_CS <= ww_ADF4351_CS;
ADF5355_CLK <= ww_ADF5355_CLK;
ADF5355_MOSI <= ww_ADF5355_MOSI;
ADF5355_LE <= ww_ADF5355_LE;
ADF5355_CS <= ww_ADF5355_CS;
TFT_CLK <= ww_TFT_CLK;
ww_TFT_CS <= TFT_CS;
TFT_MOSI <= ww_TFT_MOSI;
ATTEN_1dB <= ww_ATTEN_1dB;
ww_SCL <= SCL;
ATTEN_2dB <= ww_ATTEN_2dB;
ATTEN_4dB <= ww_ATTEN_4dB;
ATTEN_8dB <= ww_ATTEN_8dB;
ATTEN_16dB <= ww_ATTEN_16dB;
ATTEN_32dB_1 <= ww_ATTEN_32dB_1;
ATTEN_32dB_2 <= ww_ATTEN_32dB_2;
ATTEN_LE <= ww_ATTEN_LE;
SPI_MISO <= ww_SPI_MISO;
ww_TFT_MISO <= TFT_MISO;
INT_OUT <= ww_INT_OUT;
i2c_InProgress <= ww_i2c_InProgress;
tx_done <= ww_tx_done;
TFT_DC_OUT <= ww_TFT_DC_OUT;
ww_TFT_DC <= TFT_DC;
TFT_CS_OUT <= ww_TFT_CS_OUT;
TFT_RST_OUT <= ww_TFT_RST_OUT;
ww_TFT_RST <= TFT_RST;
INT_VECT <= ww_INT_VECT;
ww_ADF4351_LD <= ADF4351_LD;
ww_ADF4351_MUX <= ADF4351_MUX;
ww_ADF5355_LD <= ADF5355_LD;
ww_ADF5355_MUX <= ADF5355_MUX;
ww_CPLD_CS <= CPLD_CS;
ww_INT_TOUCH <= INT_TOUCH;
ww_INT_KEYBD <= INT_KEYBD;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

-- Location: PIN_5,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\ADF_CS~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_ADF_CS,
	combout => \ADF_CS~combout\);

-- Location: PIN_8,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\ADF_SELECT~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_ADF_SELECT,
	combout => \ADF_SELECT~combout\);

-- Location: PIN_15,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\SPI_CLK~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_SPI_CLK,
	combout => \SPI_CLK~combout\);

-- Location: LC_X4_Y7_N4
inst17 : maxv_lcell
-- Equation(s):
-- \inst17~combout\ = ((\ADF_CS~combout\ & (\ADF_SELECT~combout\ & \SPI_CLK~combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "c000",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \ADF_CS~combout\,
	datac => \ADF_SELECT~combout\,
	datad => \SPI_CLK~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst17~combout\);

-- Location: PIN_13,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\SPI_MOSI~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_SPI_MOSI,
	combout => \SPI_MOSI~combout\);

-- Location: LC_X4_Y7_N5
inst16 : maxv_lcell
-- Equation(s):
-- \inst16~combout\ = ((\SPI_MOSI~combout\ & (\ADF_SELECT~combout\ & \ADF_CS~combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "c000",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \SPI_MOSI~combout\,
	datac => \ADF_SELECT~combout\,
	datad => \ADF_CS~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst16~combout\);

-- Location: PIN_6,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\ADF_LE~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_ADF_LE,
	combout => \ADF_LE~combout\);

-- Location: LC_X4_Y7_N8
inst18 : maxv_lcell
-- Equation(s):
-- \inst18~combout\ = ((\ADF_CS~combout\ & (\ADF_SELECT~combout\ & \ADF_LE~combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "c000",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \ADF_CS~combout\,
	datac => \ADF_SELECT~combout\,
	datad => \ADF_LE~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst18~combout\);

-- Location: LC_X4_Y7_N7
\inst17~0\ : maxv_lcell
-- Equation(s):
-- \inst17~0_combout\ = (((\ADF_SELECT~combout\ & \ADF_CS~combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f000",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \ADF_SELECT~combout\,
	datad => \ADF_CS~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst17~0_combout\);

-- Location: LC_X4_Y7_N3
inst7 : maxv_lcell
-- Equation(s):
-- \inst7~combout\ = ((\ADF_CS~combout\ & (!\ADF_SELECT~combout\ & \SPI_CLK~combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0c00",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \ADF_CS~combout\,
	datac => \ADF_SELECT~combout\,
	datad => \SPI_CLK~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst7~combout\);

-- Location: LC_X4_Y7_N0
inst14 : maxv_lcell
-- Equation(s):
-- \inst14~combout\ = ((\SPI_MOSI~combout\ & (!\ADF_SELECT~combout\ & \ADF_CS~combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0c00",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \SPI_MOSI~combout\,
	datac => \ADF_SELECT~combout\,
	datad => \ADF_CS~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst14~combout\);

-- Location: LC_X4_Y7_N9
inst6 : maxv_lcell
-- Equation(s):
-- \inst6~combout\ = ((\ADF_CS~combout\ & (!\ADF_SELECT~combout\ & \ADF_LE~combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0c00",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \ADF_CS~combout\,
	datac => \ADF_SELECT~combout\,
	datad => \ADF_LE~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst6~combout\);

-- Location: LC_X4_Y7_N6
\inst7~0\ : maxv_lcell
-- Equation(s):
-- \inst7~0_combout\ = (((!\ADF_SELECT~combout\ & \ADF_CS~combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0f00",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \ADF_SELECT~combout\,
	datad => \ADF_CS~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst7~0_combout\);

-- Location: PIN_22,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\TFT_CS~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_TFT_CS,
	combout => \TFT_CS~combout\);

-- Location: LC_X4_Y7_N1
inst8 : maxv_lcell
-- Equation(s):
-- \inst8~combout\ = (((\TFT_CS~combout\ & \SPI_CLK~combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f000",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \TFT_CS~combout\,
	datad => \SPI_CLK~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst8~combout\);

-- Location: LC_X4_Y7_N2
inst9 : maxv_lcell
-- Equation(s):
-- \inst9~combout\ = (((\TFT_CS~combout\ & \SPI_MOSI~combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f000",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \TFT_CS~combout\,
	datad => \SPI_MOSI~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst9~combout\);

-- Location: PIN_140,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\TFT_MISO~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_TFT_MISO,
	combout => \TFT_MISO~combout\);

-- Location: LC_X1_Y9_N6
inst10 : maxv_lcell
-- Equation(s):
-- \inst10~combout\ = (((\TFT_CS~combout\ & \TFT_MISO~combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f000",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \TFT_CS~combout\,
	datad => \TFT_MISO~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst10~combout\);

-- Location: PIN_21,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\TFT_DC~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_TFT_DC,
	combout => \TFT_DC~combout\);

-- Location: LC_X1_Y9_N3
inst11 : maxv_lcell
-- Equation(s):
-- \inst11~combout\ = ((\TFT_DC~combout\ & (\TFT_CS~combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "c0c0",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datab => \TFT_DC~combout\,
	datac => \TFT_CS~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst11~combout\);

-- Location: PIN_23,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\TFT_RST~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_TFT_RST,
	combout => \TFT_RST~combout\);

-- Location: LC_X1_Y9_N4
inst12 : maxv_lcell
-- Equation(s):
-- \inst12~combout\ = (((\TFT_CS~combout\ & \TFT_RST~combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "f000",
	operation_mode => "normal",
	output_mode => "comb_only",
	register_cascade_mode => "off",
	sum_lutc_input => "datac",
	synch_mode => "off")
-- pragma translate_on
PORT MAP (
	datac => \TFT_CS~combout\,
	datad => \TFT_RST~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	combout => \inst12~combout\);

-- Location: PIN_98,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\ADF4351_CLK~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => \inst17~combout\,
	oe => VCC,
	padio => ww_ADF4351_CLK);

-- Location: PIN_97,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\ADF4351_MOSI~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => \inst16~combout\,
	oe => VCC,
	padio => ww_ADF4351_MOSI);

-- Location: PIN_96,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\ADF4351_LE~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => \inst18~combout\,
	oe => VCC,
	padio => ww_ADF4351_LE);

-- Location: PIN_95,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\ADF4351_CS~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => \inst17~0_combout\,
	oe => VCC,
	padio => ww_ADF4351_CS);

-- Location: PIN_84,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\ADF5355_CLK~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => \inst7~combout\,
	oe => VCC,
	padio => ww_ADF5355_CLK);

-- Location: PIN_85,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\ADF5355_MOSI~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => \inst14~combout\,
	oe => VCC,
	padio => ww_ADF5355_MOSI);

-- Location: PIN_86,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\ADF5355_LE~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => \inst6~combout\,
	oe => VCC,
	padio => ww_ADF5355_LE);

-- Location: PIN_87,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\ADF5355_CS~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => \inst7~0_combout\,
	oe => VCC,
	padio => ww_ADF5355_CS);

-- Location: PIN_139,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\TFT_CLK~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => \inst8~combout\,
	oe => VCC,
	padio => ww_TFT_CLK);

-- Location: PIN_141,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\TFT_MOSI~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => \inst9~combout\,
	oe => VCC,
	padio => ww_TFT_MOSI);

-- Location: PIN_72,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\ATTEN_1dB~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => GND,
	oe => VCC,
	padio => ww_ATTEN_1dB);

-- Location: PIN_2,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\SCL~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_SCL);

-- Location: PIN_71,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\ATTEN_2dB~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => GND,
	oe => VCC,
	padio => ww_ATTEN_2dB);

-- Location: PIN_70,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\ATTEN_4dB~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => GND,
	oe => VCC,
	padio => ww_ATTEN_4dB);

-- Location: PIN_69,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\ATTEN_8dB~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => GND,
	oe => VCC,
	padio => ww_ATTEN_8dB);

-- Location: PIN_68,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\ATTEN_16dB~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => GND,
	oe => VCC,
	padio => ww_ATTEN_16dB);

-- Location: PIN_67,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\ATTEN_32dB_1~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => GND,
	oe => VCC,
	padio => ww_ATTEN_32dB_1);

-- Location: PIN_66,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\ATTEN_32dB_2~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => GND,
	oe => VCC,
	padio => ww_ATTEN_32dB_2);

-- Location: PIN_63,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\ATTEN_LE~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => GND,
	oe => VCC,
	padio => ww_ATTEN_LE);

-- Location: PIN_14,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\SPI_MISO~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => \inst10~combout\,
	oe => VCC,
	padio => ww_SPI_MISO);

-- Location: PIN_29,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\INT_OUT~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => GND,
	oe => VCC,
	padio => ww_INT_OUT);

-- Location: PIN_7,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\i2c_InProgress~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => GND,
	oe => VCC,
	padio => ww_i2c_InProgress);

-- Location: PIN_1,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\tx_done~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => GND,
	oe => VCC,
	padio => ww_tx_done);

-- Location: PIN_142,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\TFT_DC_OUT~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => \inst11~combout\,
	oe => VCC,
	padio => ww_TFT_DC_OUT);

-- Location: PIN_143,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\TFT_CS_OUT~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => \TFT_CS~combout\,
	oe => VCC,
	padio => ww_TFT_CS_OUT);

-- Location: PIN_144,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\TFT_RST_OUT~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => \inst12~combout\,
	oe => VCC,
	padio => ww_TFT_RST_OUT);

-- Location: PIN_32,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\INT_VECT[2]~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => GND,
	oe => VCC,
	padio => ww_INT_VECT(2));

-- Location: PIN_31,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\INT_VECT[1]~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => GND,
	oe => VCC,
	padio => ww_INT_VECT(1));

-- Location: PIN_30,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\INT_VECT[0]~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "output")
-- pragma translate_on
PORT MAP (
	datain => GND,
	oe => VCC,
	padio => ww_INT_VECT(0));

-- Location: PIN_94,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\ADF4351_LD~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_ADF4351_LD);

-- Location: PIN_93,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\ADF4351_MUX~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_ADF4351_MUX);

-- Location: PIN_88,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\ADF5355_LD~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_ADF5355_LD);

-- Location: PIN_81,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\ADF5355_MUX~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_ADF5355_MUX);

-- Location: PIN_4,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\CPLD_CS~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_CPLD_CS);

-- Location: PIN_111,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\INT_TOUCH~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_INT_TOUCH);

-- Location: PIN_112,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\INT_KEYBD~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	operation_mode => "input")
-- pragma translate_on
PORT MAP (
	oe => GND,
	padio => ww_INT_KEYBD);

-- Location: PIN_3,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 16mA
\SDA~I\ : maxv_io
-- pragma translate_off
GENERIC MAP (
	open_drain_output => "true",
	operation_mode => "bidir")
-- pragma translate_on
PORT MAP (
	datain => VCC,
	oe => VCC,
	padio => SDA);
END structure;


