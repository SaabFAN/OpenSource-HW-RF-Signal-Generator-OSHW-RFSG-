-- megafunction wizard: %MAX II/MAX V oscillator%
-- GENERATION: STANDARD
-- VERSION: WM1.0
-- MODULE: ALTUFM_OSC 

-- ============================================================
-- File Name: INT_OSC.vhd
-- Megafunction Name(s):
-- 			ALTUFM_OSC
--
-- Simulation Library Files(s):
-- 			maxv
-- ============================================================
-- ************************************************************
-- THIS IS A WIZARD-GENERATED FILE. DO NOT EDIT THIS FILE!
--
-- 18.1.0 Build 625 09/12/2018 SJ Lite Edition
-- ************************************************************


--Copyright (C) 2018  Intel Corporation. All rights reserved.
--Your use of Intel Corporation's design tools, logic functions 
--and other software and tools, and its AMPP partner logic 
--functions, and any output files from any of the foregoing 
--(including device programming or simulation files), and any 
--associated documentation or information are expressly subject 
--to the terms and conditions of the Intel Program License 
--Subscription Agreement, the Intel Quartus Prime License Agreement,
--the Intel FPGA IP License Agreement, or other applicable license
--agreement, including, without limitation, that your use is for
--the sole purpose of programming logic devices manufactured by
--Intel and sold by Intel or its authorized distributors.  Please
--refer to the applicable agreement for further details.


--altufm_osc CBX_AUTO_BLACKBOX="ALL" OSC_FREQUENCY=188679 osc oscena DEVICE_FAMILY="MAX V"
--VERSION_BEGIN 18.1 cbx_altufm_osc 2018:09:12:13:04:24:SJ cbx_maxii 2018:09:12:13:04:24:SJ cbx_mgl 2018:09:12:13:10:36:SJ cbx_stratixii 2018:09:12:13:04:24:SJ cbx_util_mgl 2018:09:12:13:04:24:SJ  VERSION_END

 LIBRARY maxv;
 USE maxv.all;

--synthesis_resources = maxv_ufm 1 
 LIBRARY ieee;
 USE ieee.std_logic_1164.all;

 ENTITY  INT_OSC_altufm_osc_7v7 IS 
	 PORT 
	 ( 
		 osc	:	OUT  STD_LOGIC;
		 oscena	:	IN  STD_LOGIC
	 ); 
 END INT_OSC_altufm_osc_7v7;

 ARCHITECTURE RTL OF INT_OSC_altufm_osc_7v7 IS

	 SIGNAL  wire_gnd	:	STD_LOGIC;
	 SIGNAL  wire_vcc	:	STD_LOGIC;
	 SIGNAL  wire_maxii_ufm_block1_osc	:	STD_LOGIC;
	 COMPONENT  maxv_ufm
	 GENERIC 
	 (
		ADDRESS_WIDTH	:	NATURAL := 9;
		ERASE_TIME	:	NATURAL := 500000000;
		INIT_FILE	:	STRING := "UNUSED";
		OSC_SIM_SETTING	:	NATURAL := 180000;
		PROGRAM_TIME	:	NATURAL := 1600000;
		lpm_type	:	STRING := "maxv_ufm"
	 );
	 PORT
	 ( 
		arclk	:	IN STD_LOGIC := '0';
		ardin	:	IN STD_LOGIC := '0';
		arshft	:	IN STD_LOGIC := '1';
		bgpbusy	:	OUT STD_LOGIC;
		busy	:	OUT STD_LOGIC;
		drclk	:	IN STD_LOGIC := '0';
		drdin	:	IN STD_LOGIC := '0';
		drdout	:	OUT STD_LOGIC;
		drshft	:	IN STD_LOGIC := '1';
		erase	:	IN STD_LOGIC := '0';
		osc	:	OUT STD_LOGIC;
		oscena	:	IN STD_LOGIC := '0';
		program	:	IN STD_LOGIC := '0'
	 ); 
	 END COMPONENT;
 BEGIN

	wire_gnd <= '0';
	wire_vcc <= '1';
	osc <= wire_maxii_ufm_block1_osc;
	maxii_ufm_block1 :  maxv_ufm
	  GENERIC MAP (
		ADDRESS_WIDTH => 9,
		OSC_SIM_SETTING => 188679
	  )
	  PORT MAP ( 
		arclk => wire_gnd,
		ardin => wire_gnd,
		arshft => wire_gnd,
		drclk => wire_gnd,
		drdin => wire_gnd,
		drshft => wire_vcc,
		osc => wire_maxii_ufm_block1_osc,
		oscena => oscena
	  );

 END RTL; --INT_OSC_altufm_osc_7v7
--VALID FILE


LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY INT_OSC IS
	PORT
	(
		oscena		: IN STD_LOGIC ;
		osc		: OUT STD_LOGIC 
	);
END INT_OSC;


ARCHITECTURE RTL OF int_osc IS

	SIGNAL sub_wire0	: STD_LOGIC ;



	COMPONENT INT_OSC_altufm_osc_7v7
	PORT (
			oscena	: IN STD_LOGIC ;
			osc	: OUT STD_LOGIC 
	);
	END COMPONENT;

BEGIN
	osc    <= sub_wire0;

	INT_OSC_altufm_osc_7v7_component : INT_OSC_altufm_osc_7v7
	PORT MAP (
		oscena => oscena,
		osc => sub_wire0
	);



END RTL;

-- ============================================================
-- CNX file retrieval info
-- ============================================================
-- Retrieval info: LIBRARY: altera_mf altera_mf.altera_mf_components.all
-- Retrieval info: PRIVATE: INTENDED_DEVICE_FAMILY STRING "MAX V"
-- Retrieval info: CONSTANT: INTENDED_DEVICE_FAMILY STRING "UNUSED"
-- Retrieval info: CONSTANT: LPM_HINT STRING "UNUSED"
-- Retrieval info: CONSTANT: LPM_TYPE STRING "altufm_osc"
-- Retrieval info: CONSTANT: OSC_FREQUENCY NUMERIC "188679"
-- Retrieval info: USED_PORT: osc 0 0 0 0 OUTPUT NODEFVAL "osc"
-- Retrieval info: CONNECT: osc 0 0 0 0 @osc 0 0 0 0
-- Retrieval info: USED_PORT: oscena 0 0 0 0 INPUT NODEFVAL "oscena"
-- Retrieval info: CONNECT: @oscena 0 0 0 0 oscena 0 0 0 0
-- Retrieval info: GEN_FILE: TYPE_NORMAL INT_OSC.vhd TRUE FALSE
-- Retrieval info: GEN_FILE: TYPE_NORMAL INT_OSC.qip TRUE FALSE
-- Retrieval info: GEN_FILE: TYPE_NORMAL INT_OSC.bsf TRUE TRUE
-- Retrieval info: GEN_FILE: TYPE_NORMAL INT_OSC_inst.vhd TRUE TRUE
-- Retrieval info: GEN_FILE: TYPE_NORMAL INT_OSC.inc TRUE TRUE
-- Retrieval info: GEN_FILE: TYPE_NORMAL INT_OSC.cmp TRUE TRUE
-- Retrieval info: PRIVATE: SYNTH_WRAPPER_GEN_POSTFIX NUMERIC "1"
-- Retrieval info: LIB_FILE: maxv
