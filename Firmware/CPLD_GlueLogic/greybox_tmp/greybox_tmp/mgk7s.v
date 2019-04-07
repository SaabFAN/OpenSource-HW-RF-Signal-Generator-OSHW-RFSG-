//dcfifo CBX_SINGLE_OUTPUT_FILE="ON" CLOCKS_ARE_SYNCHRONIZED="TRUE" INTENDED_DEVICE_FAMILY=""MAX V"" LPM_NUMWORDS=8 LPM_SHOWAHEAD="OFF" LPM_TYPE="dcfifo" LPM_WIDTH=32 LPM_WIDTHU=3 OVERFLOW_CHECKING="ON" UNDERFLOW_CHECKING="ON" USE_EAB="OFF" aclr data q rdclk rdempty rdreq rdusedw wrclk wrfull wrreq wrusedw
//VERSION_BEGIN 18.1 cbx_mgl 2018:09:12:13:10:36:SJ cbx_stratixii 2018:09:12:13:04:24:SJ cbx_util_mgl 2018:09:12:13:04:24:SJ  VERSION_END
// synthesis VERILOG_INPUT_VERSION VERILOG_2001
// altera message_off 10463



// Copyright (C) 2018  Intel Corporation. All rights reserved.
//  Your use of Intel Corporation's design tools, logic functions 
//  and other software and tools, and its AMPP partner logic 
//  functions, and any output files from any of the foregoing 
//  (including device programming or simulation files), and any 
//  associated documentation or information are expressly subject 
//  to the terms and conditions of the Intel Program License 
//  Subscription Agreement, the Intel Quartus Prime License Agreement,
//  the Intel FPGA IP License Agreement, or other applicable license
//  agreement, including, without limitation, that your use is for
//  the sole purpose of programming logic devices manufactured by
//  Intel and sold by Intel or its authorized distributors.  Please
//  refer to the applicable agreement for further details.



//synthesis_resources = dcfifo 1 
//synopsys translate_off
`timescale 1 ps / 1 ps
//synopsys translate_on
module  mgk7s
	( 
	aclr,
	data,
	q,
	rdclk,
	rdempty,
	rdreq,
	rdusedw,
	wrclk,
	wrfull,
	wrreq,
	wrusedw) /* synthesis synthesis_clearbox=1 */;
	input   aclr;
	input   [31:0]  data;
	output   [31:0]  q;
	input   rdclk;
	output   rdempty;
	input   rdreq;
	output   [2:0]  rdusedw;
	input   wrclk;
	output   wrfull;
	input   wrreq;
	output   [2:0]  wrusedw;

	wire  [31:0]   wire_mgl_prim1_q;
	wire  wire_mgl_prim1_rdempty;
	wire  [2:0]   wire_mgl_prim1_rdusedw;
	wire  wire_mgl_prim1_wrfull;
	wire  [2:0]   wire_mgl_prim1_wrusedw;

	dcfifo   mgl_prim1
	( 
	.aclr(aclr),
	.data(data),
	.q(wire_mgl_prim1_q),
	.rdclk(rdclk),
	.rdempty(wire_mgl_prim1_rdempty),
	.rdreq(rdreq),
	.rdusedw(wire_mgl_prim1_rdusedw),
	.wrclk(wrclk),
	.wrfull(wire_mgl_prim1_wrfull),
	.wrreq(wrreq),
	.wrusedw(wire_mgl_prim1_wrusedw));
	defparam
		mgl_prim1.clocks_are_synchronized = "TRUE",
		mgl_prim1.intended_device_family = ""MAX V"",
		mgl_prim1.lpm_numwords = 8,
		mgl_prim1.lpm_showahead = "OFF",
		mgl_prim1.lpm_type = "dcfifo",
		mgl_prim1.lpm_width = 32,
		mgl_prim1.lpm_widthu = 3,
		mgl_prim1.overflow_checking = "ON",
		mgl_prim1.underflow_checking = "ON",
		mgl_prim1.use_eab = "OFF";
	assign
		q = wire_mgl_prim1_q,
		rdempty = wire_mgl_prim1_rdempty,
		rdusedw = wire_mgl_prim1_rdusedw,
		wrfull = wire_mgl_prim1_wrfull,
		wrusedw = wire_mgl_prim1_wrusedw;
endmodule //mgk7s
//VALID FILE