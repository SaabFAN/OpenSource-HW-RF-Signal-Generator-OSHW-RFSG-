// megafunction wizard: %MAX II/MAX V oscillator%
// GENERATION: STANDARD
// VERSION: WM1.0
// MODULE: ALTUFM_OSC 

// ============================================================
// File Name: INT_OSC.v
// Megafunction Name(s):
// 			ALTUFM_OSC
//
// Simulation Library Files(s):
// 			maxv
// ============================================================
// ************************************************************
// THIS IS A WIZARD-GENERATED FILE. DO NOT EDIT THIS FILE!
//
// 18.1.0 Build 625 09/12/2018 SJ Lite Edition
// ************************************************************


//Copyright (C) 2018  Intel Corporation. All rights reserved.
//Your use of Intel Corporation's design tools, logic functions 
//and other software and tools, and its AMPP partner logic 
//functions, and any output files from any of the foregoing 
//(including device programming or simulation files), and any 
//associated documentation or information are expressly subject 
//to the terms and conditions of the Intel Program License 
//Subscription Agreement, the Intel Quartus Prime License Agreement,
//the Intel FPGA IP License Agreement, or other applicable license
//agreement, including, without limitation, that your use is for
//the sole purpose of programming logic devices manufactured by
//Intel and sold by Intel or its authorized distributors.  Please
//refer to the applicable agreement for further details.


//altufm_osc OSC_FREQUENCY=188679 osc oscena DEVICE_FAMILY="MAX V"
//VERSION_BEGIN 18.1 cbx_altufm_osc 2018:09:12:13:04:24:SJ cbx_maxii 2018:09:12:13:04:24:SJ cbx_mgl 2018:09:12:13:10:36:SJ cbx_stratixii 2018:09:12:13:04:24:SJ cbx_util_mgl 2018:09:12:13:04:24:SJ  VERSION_END
// synthesis VERILOG_INPUT_VERSION VERILOG_2001
// altera message_off 10463


//synthesis_resources = maxv_ufm 1 
//synopsys translate_off
`timescale 1 ps / 1 ps
//synopsys translate_on
module  INT_OSC_altufm_osc
	( 
	osc,
	oscena) /* synthesis synthesis_clearbox=1 */;
	output   osc;
	input   oscena;

	wire  wire_maxii_ufm_block1_osc;

	maxv_ufm   maxii_ufm_block1
	( 
	.arclk(1'b0),
	.ardin(1'b0),
	.arshft(1'b0),
	.bgpbusy(),
	.busy(),
	.drclk(1'b0),
	.drdin(1'b0),
	.drdout(),
	.drshft(1'b1),
	.osc(wire_maxii_ufm_block1_osc),
	.oscena(oscena)
	`ifndef FORMAL_VERIFICATION
	// synopsys translate_off
	`endif
	,
	.erase(1'b0),
	.program(1'b0)
	`ifndef FORMAL_VERIFICATION
	// synopsys translate_on
	`endif
	// synopsys translate_off
	,
	.ctrl_bgpbusy(1'b0),
	.devclrn(1'b1),
	.devpor(1'b1),
	.sbdin(1'b0),
	.sbdout()
	// synopsys translate_on
	);
	defparam
		maxii_ufm_block1.address_width = 9,
		maxii_ufm_block1.osc_sim_setting = 188679,
		maxii_ufm_block1.lpm_type = "maxv_ufm";
	assign
		osc = wire_maxii_ufm_block1_osc;
endmodule //INT_OSC_altufm_osc
//VALID FILE


// synopsys translate_off
`timescale 1 ps / 1 ps
// synopsys translate_on
module INT_OSC (
	oscena,
	osc)/* synthesis synthesis_clearbox = 1 */;

	input	  oscena;
	output	  osc;

	wire  sub_wire0;
	wire  osc = sub_wire0;

	INT_OSC_altufm_osc	INT_OSC_altufm_osc_component (
				.oscena (oscena),
				.osc (sub_wire0));

endmodule

// ============================================================
// CNX file retrieval info
// ============================================================
// Retrieval info: LIBRARY: altera_mf altera_mf.altera_mf_components.all
// Retrieval info: PRIVATE: INTENDED_DEVICE_FAMILY STRING "MAX V"
// Retrieval info: CONSTANT: INTENDED_DEVICE_FAMILY STRING "UNUSED"
// Retrieval info: CONSTANT: LPM_HINT STRING "UNUSED"
// Retrieval info: CONSTANT: LPM_TYPE STRING "altufm_osc"
// Retrieval info: CONSTANT: OSC_FREQUENCY NUMERIC "188679"
// Retrieval info: USED_PORT: osc 0 0 0 0 OUTPUT NODEFVAL "osc"
// Retrieval info: CONNECT: osc 0 0 0 0 @osc 0 0 0 0
// Retrieval info: USED_PORT: oscena 0 0 0 0 INPUT NODEFVAL "oscena"
// Retrieval info: CONNECT: @oscena 0 0 0 0 oscena 0 0 0 0
// Retrieval info: GEN_FILE: TYPE_NORMAL INT_OSC.vhd TRUE FALSE
// Retrieval info: GEN_FILE: TYPE_NORMAL INT_OSC.qip TRUE FALSE
// Retrieval info: GEN_FILE: TYPE_NORMAL INT_OSC.bsf TRUE TRUE
// Retrieval info: GEN_FILE: TYPE_NORMAL INT_OSC_inst.vhd TRUE TRUE
// Retrieval info: GEN_FILE: TYPE_NORMAL INT_OSC.inc TRUE TRUE
// Retrieval info: GEN_FILE: TYPE_NORMAL INT_OSC.cmp TRUE TRUE
// Retrieval info: PRIVATE: SYNTH_WRAPPER_GEN_POSTFIX NUMERIC "1"
// Retrieval info: LIB_FILE: maxv
