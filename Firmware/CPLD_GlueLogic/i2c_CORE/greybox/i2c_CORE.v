// Copyright (C) 2018  Intel Corporation. All rights reserved.
// Your use of Intel Corporation's design tools, logic functions 
// and other software and tools, and its AMPP partner logic 
// functions, and any output files from any of the foregoing 
// (including device programming or simulation files), and any 
// associated documentation or information are expressly subject 
// to the terms and conditions of the Intel Program License 
// Subscription Agreement, the Intel Quartus Prime License Agreement,
// the Intel FPGA IP License Agreement, or other applicable license
// agreement, including, without limitation, that your use is for
// the sole purpose of programming logic devices manufactured by
// Intel and sold by Intel or its authorized distributors.  Please
// refer to the applicable agreement for further details.

// VENDOR "Altera"
// PROGRAM "Quartus Prime"
// VERSION "Version 18.1.0 Build 625 09/12/2018 SJ Lite Edition"

// DATE "03/15/2019 16:44:45"

// 
// Device: Altera 5M1270ZT144C5 Package TQFP144
// 

// 
// This greybox netlist file is for third party Synthesis Tools
// for timing and resource estimation only.
// 


module i2c_CORE (
	a0,
	a1,
	a2,
	global_reset,
	osc,
	scl,
	sda)/* synthesis synthesis_greybox=0 */;
input 	a0;
input 	a1;
input 	a2;
input 	global_reset;
output 	osc;
inout 	scl;
inout 	sda;

wire gnd;
wire vcc;
wire unknown;

assign gnd = 1'b0;
assign vcc = 1'b1;
// unknown value (1'bx) is not needed for this tool. Default to 1'b0
assign unknown = 1'b0;

wire \ufm_i2c_0|ufm_osc ;
wire \ufm_i2c_0|sda_out_wire~combout ;
wire \ufm_i2c_0|sda_oe~combout ;
wire \ufm_i2c_0|clock_oe~combout ;
wire \~GND~combout ;
wire \ufm_i2c_0|wire_maxii_io3_combout ;
wire \ufm_i2c_0|scl_wire ;


i2c_CORE_i2c_CORE_ufm_i2c_0 ufm_i2c_0(
	.ufm_osc(\ufm_i2c_0|ufm_osc ),
	.a1(a1),
	.a2(a2),
	.sda_out_wire1(\ufm_i2c_0|sda_out_wire~combout ),
	.sda_oe1(\ufm_i2c_0|sda_oe~combout ),
	.clock_oe1(\ufm_i2c_0|clock_oe~combout ),
	.GND_port(\~GND~combout ),
	.sda(\ufm_i2c_0|wire_maxii_io3_combout ),
	.scl(\ufm_i2c_0|scl_wire ));

maxv_lcell \~GND (
	.clk(gnd),
	.dataa(vcc),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\~GND~combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \~GND .lut_mask = "0000";
defparam \~GND .operation_mode = "normal";
defparam \~GND .output_mode = "comb_only";
defparam \~GND .register_cascade_mode = "off";
defparam \~GND .sum_lutc_input = "datac";
defparam \~GND .synch_mode = "off";

maxv_io \ufm_i2c_0|maxii_io3~I (
	.datain(\ufm_i2c_0|sda_out_wire~combout ),
	.oe(\ufm_i2c_0|sda_oe~combout ),
	.combout(\ufm_i2c_0|wire_maxii_io3_combout ),
	.padio(sda));
defparam \ufm_i2c_0|maxii_io3~I .open_drain_output = "true";
defparam \ufm_i2c_0|maxii_io3~I .operation_mode = "bidir";

maxv_io \ufm_i2c_0|maxii_io2~I (
	.datain(gnd),
	.oe(\ufm_i2c_0|clock_oe~combout ),
	.combout(\ufm_i2c_0|scl_wire ),
	.padio(scl));
defparam \ufm_i2c_0|maxii_io2~I .open_drain_output = "true";
defparam \ufm_i2c_0|maxii_io2~I .operation_mode = "bidir";

assign osc = \ufm_i2c_0|ufm_osc ;

endmodule

module i2c_CORE_i2c_CORE_ufm_i2c_0 (
	ufm_osc,
	a1,
	a2,
	sda_out_wire1,
	sda_oe1,
	clock_oe1,
	GND_port,
	sda,
	scl)/* synthesis synthesis_greybox=0 */;
output 	ufm_osc;
input 	a1;
input 	a2;
output 	sda_out_wire1;
output 	sda_oe1;
output 	clock_oe1;
input 	GND_port;
input 	sda;
input 	scl;

wire gnd;
wire vcc;
wire unknown;

assign gnd = 1'b0;
assign vcc = 1'b1;
// unknown value (1'bx) is not needed for this tool. Default to 1'b0
assign unknown = 1'b0;

wire \stage_cntr|auto_generated|counter2a[1]~regout ;
wire \stage_cntr|auto_generated|counter2a[0]~regout ;
wire \general_cntr|auto_generated|counter2a[2]~regout ;
wire \general_cntr|auto_generated|counter2a[3]~regout ;
wire \general_cntr|auto_generated|counter2a[0]~regout ;
wire \general_cntr|auto_generated|counter2a[1]~regout ;
wire \dev_add_reg[1]~regout ;
wire \dev_add_reg[5]~regout ;
wire \dev_add_reg[3]~regout ;
wire \dev_add_reg[6]~regout ;
wire \dev_add_reg[4]~regout ;
wire \dev_add_reg[2]~regout ;
wire \cmpr4|auto_generated|aneb_result_wire[0]~combout ;
wire \data_pad_cntr|auto_generated|counter2a[3]~regout ;
wire \data_pad_cntr|auto_generated|counter2a[2]~regout ;
wire \data_pad_cntr|auto_generated|counter2a[1]~regout ;
wire \data_pad_cntr|auto_generated|counter2a[0]~regout ;
wire \comb~1_combout ;
wire \comb~2_combout ;
wire \er_wr_cntr|auto_generated|counter2a[0]~regout ;
wire \er_wr_cntr|auto_generated|counter2a[1]~regout ;
wire \comb~4_combout ;
wire \comb~5_combout ;
wire \comb~6_combout ;
wire \comb~7_combout ;
wire wire_maxii_ufm_block1_drdout;
wire wire_maxii_ufm_block1_busy;
wire wire_maxii_ufm_block1_bgpbusy;
wire \clr_drclk_reg~0_combout ;
wire \fin_devadd_reg_ena~0_combout ;
wire \sda_indly_reg~regout ;
wire \sda_indly_reg2~regout ;
wire \fin_devadd_reg~regout ;
wire \dev_add_reg[0]~regout ;
wire \ncount8~0_combout ;
wire \rd_addr_reg[0]~regout ;
wire \erase_add_match~0_combout ;
wire \rd_addr_reg[1]~regout ;
wire \rd_addr_reg[2]~regout ;
wire \rd_addr_reg[3]~regout ;
wire \rd_addr_reg[4]~regout ;
wire \rd_addr_reg[5]~regout ;
wire \rd_addr_reg[6]~regout ;
wire \erase_add_match~1_combout ;
wire \erase_add_match~2_combout ;
wire \ena_write_reg~0_combout ;
wire \start_din_reg~2_combout ;
wire \ack_sa_reg~0_combout ;
wire \add_en_reg~1_combout ;
wire \ack_data_reg~regout ;
wire \start_wr_reg~0_combout ;
wire \start_wr_reg~regout ;
wire \data_pad_complete~0_combout ;
wire \wire_start_prog_reg_clrn~0_combout ;
wire \wire_start_prog_reg_clrn~1_combout ;
wire \start_prog_reg~regout ;
wire \ufm_program~0_combout ;
wire \eradd_match_reg~regout ;
wire \eradd_match_reg2~regout ;
wire \start_er_reg~regout ;
wire \busy_det_reg~regout ;
wire \busy_det_reg2~regout ;
wire \busy_dea_reg~regout ;
wire \end_write_reg~regout ;
wire \end_write_reg2~regout ;
wire \data_suc_reg~regout ;
wire \stop_detect_reg~regout ;
wire \stop_det_da_reg~regout ;
wire \stop_det_da_reg2~regout ;
wire \stop_rst_reg~regout ;
wire \stop_rst_reg2~regout ;
wire \stop_det_rst~combout ;
wire \ena_write_reg~regout ;
wire \start_detect_reg~0_combout ;
wire \start_detect_reg~regout ;
wire \rstart_clr_reg~regout ;
wire \rstart_clr_reg2~regout ;
wire \wire_rstart_det_reg_clrn~0_combout ;
wire \rstart_det_reg~regout ;
wire \rstart_det_da_reg~regout ;
wire \rstart_det_da_reg2~regout ;
wire \comb~0_combout ;
wire \rd_wr_reg~regout ;
wire \wire_din_en_reg_ena~0_combout ;
wire \count9~0_combout ;
wire \end_din_reg~regout ;
wire \wire_din_en_reg_clrn~0_combout ;
wire \din_en_reg~regout ;
wire \end_datpd_reg~regout ;
wire \ufm_drdin~combout ;
wire \ack_sa_reg~regout ;
wire \start_rd_reg~regout ;
wire \ena_drclk_reg~regout ;
wire \clr_drclk_reg~regout ;
wire \strd_drclk_reg~regout ;
wire \reach_cnt9_reg~regout ;
wire \gcntr_aclr_reg~regout ;
wire \gcntr_aclr_int_reg~regout ;
wire \gcntr_aclr_reg2~regout ;
wire \wire_bgpbsy_rdreg_ena~0_combout ;
wire \bgpbsy_rdreg~regout ;
wire \ufm_drclk~0_combout ;
wire \start_din_reg~regout ;
wire \ufm_drclk~1_combout ;
wire \start_datpd_reg~regout ;
wire \ufm_drclk~2_combout ;
wire \drshft_reg~regout ;
wire \a0_dly_reg~regout ;
wire \comb~3_combout ;
wire \memadd_shft_reg~regout ;
wire \add_en_reg~regout ;
wire \end_memadd_reg~regout ;
wire \ufm_ardin~0_combout ;
wire \ufm_ardin~combout ;
wire \gen_cntr2_reg~regout ;
wire \start_memadd_reg~regout ;
wire \do_memadd_reg~regout ;
wire \do_memadd_reg2~regout ;
wire \ufm_arclk~0_combout ;
wire \sda_oe~0_combout ;
wire \ufm_arclk~combout ;
wire \ufm_arshft~combout ;
wire \ufm_program~0_wirecell_combout ;
wire \start_er_reg~_wirecell_combout ;
wire \drdout_reg~regout ;
wire \wire_read_nack_reg_ena~0_combout ;
wire \read_nack_reg~regout ;
wire \read_oe_reg~regout ;
wire \sda_oe~1_combout ;
wire \ack_ma_reg~regout ;
wire \bgpend_det_reg~regout ;


i2c_CORE_lpm_compare_1 cmpr4(
	.a1(a1),
	.dev_add_reg_1(\dev_add_reg[1]~regout ),
	.dev_add_reg_5(\dev_add_reg[5]~regout ),
	.dev_add_reg_3(\dev_add_reg[3]~regout ),
	.dev_add_reg_6(\dev_add_reg[6]~regout ),
	.dev_add_reg_4(\dev_add_reg[4]~regout ),
	.a2(a2),
	.dev_add_reg_2(\dev_add_reg[2]~regout ),
	.aneb_result_wire_0(\cmpr4|auto_generated|aneb_result_wire[0]~combout ));

i2c_CORE_a_graycounter_3 stage_cntr(
	.counter2a_1(\stage_cntr|auto_generated|counter2a[1]~regout ),
	.counter2a_0(\stage_cntr|auto_generated|counter2a[0]~regout ),
	.comb(\comb~0_combout ),
	.clk_en(\comb~2_combout ),
	.clock(scl));

i2c_CORE_a_graycounter_2 general_cntr(
	.counter2a_2(\general_cntr|auto_generated|counter2a[2]~regout ),
	.counter2a_3(\general_cntr|auto_generated|counter2a[3]~regout ),
	.counter2a_0(\general_cntr|auto_generated|counter2a[0]~regout ),
	.counter2a_1(\general_cntr|auto_generated|counter2a[1]~regout ),
	.comb(\comb~4_combout ),
	.clk_en(\comb~5_combout ),
	.clock(scl));

i2c_CORE_a_graycounter_1 er_wr_cntr(
	.stop_det_da_reg2(\stop_det_da_reg2~regout ),
	.clock(\end_write_reg2~regout ),
	.counter2a_0(\er_wr_cntr|auto_generated|counter2a[0]~regout ),
	.counter2a_1(\er_wr_cntr|auto_generated|counter2a[1]~regout ),
	.clk_en(\comb~7_combout ));

i2c_CORE_a_graycounter data_pad_cntr(
	.clock(ufm_osc),
	.ena_write_reg(\ena_write_reg~regout ),
	.end_write_reg2(\end_write_reg2~regout ),
	.counter2a_3(\data_pad_cntr|auto_generated|counter2a[3]~regout ),
	.counter2a_2(\data_pad_cntr|auto_generated|counter2a[2]~regout ),
	.counter2a_1(\data_pad_cntr|auto_generated|counter2a[1]~regout ),
	.counter2a_0(\data_pad_cntr|auto_generated|counter2a[0]~regout ),
	.data_pad_complete(\data_pad_complete~0_combout ),
	.clk_en(\comb~6_combout ));

maxv_lcell \dev_add_reg[1] (
	.clk(scl),
	.dataa(\dev_add_reg[1]~regout ),
	.datab(\dev_add_reg[0]~regout ),
	.datac(\start_detect_reg~regout ),
	.datad(\fin_devadd_reg~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\dev_add_reg[1]~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam \dev_add_reg[1] .lut_mask = "aaca";
defparam \dev_add_reg[1] .operation_mode = "normal";
defparam \dev_add_reg[1] .output_mode = "reg_only";
defparam \dev_add_reg[1] .register_cascade_mode = "off";
defparam \dev_add_reg[1] .sum_lutc_input = "datac";
defparam \dev_add_reg[1] .synch_mode = "off";
defparam \dev_add_reg[1] .x_on_violation = "off";

maxv_lcell \dev_add_reg[5] (
	.clk(scl),
	.dataa(\dev_add_reg[5]~regout ),
	.datab(\dev_add_reg[4]~regout ),
	.datac(\start_detect_reg~regout ),
	.datad(\fin_devadd_reg~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\dev_add_reg[5]~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam \dev_add_reg[5] .lut_mask = "aaca";
defparam \dev_add_reg[5] .operation_mode = "normal";
defparam \dev_add_reg[5] .output_mode = "reg_only";
defparam \dev_add_reg[5] .register_cascade_mode = "off";
defparam \dev_add_reg[5] .sum_lutc_input = "datac";
defparam \dev_add_reg[5] .synch_mode = "off";
defparam \dev_add_reg[5] .x_on_violation = "off";

maxv_lcell \dev_add_reg[3] (
	.clk(scl),
	.dataa(\dev_add_reg[3]~regout ),
	.datab(\dev_add_reg[2]~regout ),
	.datac(\start_detect_reg~regout ),
	.datad(\fin_devadd_reg~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\dev_add_reg[3]~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam \dev_add_reg[3] .lut_mask = "aaca";
defparam \dev_add_reg[3] .operation_mode = "normal";
defparam \dev_add_reg[3] .output_mode = "reg_only";
defparam \dev_add_reg[3] .register_cascade_mode = "off";
defparam \dev_add_reg[3] .sum_lutc_input = "datac";
defparam \dev_add_reg[3] .synch_mode = "off";
defparam \dev_add_reg[3] .x_on_violation = "off";

maxv_lcell \dev_add_reg[6] (
	.clk(scl),
	.dataa(\dev_add_reg[6]~regout ),
	.datab(\dev_add_reg[5]~regout ),
	.datac(\start_detect_reg~regout ),
	.datad(\fin_devadd_reg~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\dev_add_reg[6]~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam \dev_add_reg[6] .lut_mask = "aaca";
defparam \dev_add_reg[6] .operation_mode = "normal";
defparam \dev_add_reg[6] .output_mode = "reg_only";
defparam \dev_add_reg[6] .register_cascade_mode = "off";
defparam \dev_add_reg[6] .sum_lutc_input = "datac";
defparam \dev_add_reg[6] .synch_mode = "off";
defparam \dev_add_reg[6] .x_on_violation = "off";

maxv_lcell \dev_add_reg[4] (
	.clk(scl),
	.dataa(\dev_add_reg[4]~regout ),
	.datab(\dev_add_reg[3]~regout ),
	.datac(\start_detect_reg~regout ),
	.datad(\fin_devadd_reg~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\dev_add_reg[4]~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam \dev_add_reg[4] .lut_mask = "aaca";
defparam \dev_add_reg[4] .operation_mode = "normal";
defparam \dev_add_reg[4] .output_mode = "reg_only";
defparam \dev_add_reg[4] .register_cascade_mode = "off";
defparam \dev_add_reg[4] .sum_lutc_input = "datac";
defparam \dev_add_reg[4] .synch_mode = "off";
defparam \dev_add_reg[4] .x_on_violation = "off";

maxv_lcell \dev_add_reg[2] (
	.clk(scl),
	.dataa(\dev_add_reg[2]~regout ),
	.datab(\dev_add_reg[1]~regout ),
	.datac(\start_detect_reg~regout ),
	.datad(\fin_devadd_reg~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\dev_add_reg[2]~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam \dev_add_reg[2] .lut_mask = "aaca";
defparam \dev_add_reg[2] .operation_mode = "normal";
defparam \dev_add_reg[2] .output_mode = "reg_only";
defparam \dev_add_reg[2] .register_cascade_mode = "off";
defparam \dev_add_reg[2] .sum_lutc_input = "datac";
defparam \dev_add_reg[2] .synch_mode = "off";
defparam \dev_add_reg[2] .x_on_violation = "off";

maxv_lcell \comb~1 (
	.clk(gnd),
	.dataa(\rd_wr_reg~regout ),
	.datab(\stage_cntr|auto_generated|counter2a[1]~regout ),
	.datac(vcc),
	.datad(\stage_cntr|auto_generated|counter2a[0]~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\comb~1_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \comb~1 .lut_mask = "99ff";
defparam \comb~1 .operation_mode = "normal";
defparam \comb~1 .output_mode = "comb_only";
defparam \comb~1 .register_cascade_mode = "off";
defparam \comb~1 .sum_lutc_input = "datac";
defparam \comb~1 .synch_mode = "off";

maxv_lcell \comb~2 (
	.clk(gnd),
	.dataa(\count9~0_combout ),
	.datab(\start_detect_reg~regout ),
	.datac(\comb~1_combout ),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\comb~2_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \comb~2 .lut_mask = "8080";
defparam \comb~2 .operation_mode = "normal";
defparam \comb~2 .output_mode = "comb_only";
defparam \comb~2 .register_cascade_mode = "off";
defparam \comb~2 .sum_lutc_input = "datac";
defparam \comb~2 .synch_mode = "off";

maxv_lcell \comb~4 (
	.clk(gnd),
	.dataa(\rstart_det_da_reg2~regout ),
	.datab(\stop_det_da_reg2~regout ),
	.datac(\gcntr_aclr_int_reg~regout ),
	.datad(\gcntr_aclr_reg2~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\comb~4_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \comb~4 .lut_mask = "eefe";
defparam \comb~4 .operation_mode = "normal";
defparam \comb~4 .output_mode = "comb_only";
defparam \comb~4 .register_cascade_mode = "off";
defparam \comb~4 .sum_lutc_input = "datac";
defparam \comb~4 .synch_mode = "off";

maxv_lcell \comb~5 (
	.clk(gnd),
	.dataa(\start_detect_reg~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(\bgpbsy_rdreg~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\comb~5_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \comb~5 .lut_mask = "00aa";
defparam \comb~5 .operation_mode = "normal";
defparam \comb~5 .output_mode = "comb_only";
defparam \comb~5 .register_cascade_mode = "off";
defparam \comb~5 .sum_lutc_input = "datac";
defparam \comb~5 .synch_mode = "off";

maxv_lcell \comb~6 (
	.clk(gnd),
	.dataa(\ena_write_reg~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(\data_pad_complete~0_combout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\comb~6_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \comb~6 .lut_mask = "00aa";
defparam \comb~6 .operation_mode = "normal";
defparam \comb~6 .output_mode = "comb_only";
defparam \comb~6 .register_cascade_mode = "off";
defparam \comb~6 .sum_lutc_input = "datac";
defparam \comb~6 .synch_mode = "off";

maxv_lcell \comb~7 (
	.clk(gnd),
	.dataa(\start_prog_reg~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(wire_maxii_ufm_block1_bgpbusy),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\comb~7_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \comb~7 .lut_mask = "00aa";
defparam \comb~7 .operation_mode = "normal";
defparam \comb~7 .output_mode = "comb_only";
defparam \comb~7 .register_cascade_mode = "off";
defparam \comb~7 .sum_lutc_input = "datac";
defparam \comb~7 .synch_mode = "off";

maxv_ufm maxii_ufm_block1(
	.drdin(\ufm_drdin~combout ),
	.drclk(\ufm_drclk~2_combout ),
	.drshft(!\drshft_reg~regout ),
	.ardin(\ufm_ardin~combout ),
	.arclk(\ufm_arclk~combout ),
	.arshft(\ufm_arshft~combout ),
	.program(!\ufm_program~0_wirecell_combout ),
	.erase(!\start_er_reg~_wirecell_combout ),
	.oscena(!GND_port),
	.sbdin(gnd),
	.drdout(wire_maxii_ufm_block1_drdout),
	.busy(wire_maxii_ufm_block1_busy),
	.osc(ufm_osc),
	.sbdout(),
	.bgpbusy(wire_maxii_ufm_block1_bgpbusy));
defparam maxii_ufm_block1.address_width = 9;
defparam maxii_ufm_block1.erase_time = 500000000;
defparam maxii_ufm_block1.init_file = "none";
defparam maxii_ufm_block1.osc_sim_setting = 180000;
defparam maxii_ufm_block1.program_time = 1600000;

maxv_lcell sda_out_wire(
	.clk(gnd),
	.dataa(\cmpr4|auto_generated|aneb_result_wire[0]~combout ),
	.datab(\sda_oe~0_combout ),
	.datac(\drdout_reg~regout ),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(sda_out_wire1),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam sda_out_wire.lut_mask = "eaea";
defparam sda_out_wire.operation_mode = "normal";
defparam sda_out_wire.output_mode = "comb_only";
defparam sda_out_wire.register_cascade_mode = "off";
defparam sda_out_wire.sum_lutc_input = "datac";
defparam sda_out_wire.synch_mode = "off";

maxv_lcell sda_oe(
	.clk(gnd),
	.dataa(\ack_sa_reg~regout ),
	.datab(\sda_oe~1_combout ),
	.datac(\ack_data_reg~regout ),
	.datad(\ack_ma_reg~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(sda_oe1),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam sda_oe.lut_mask = "fffe";
defparam sda_oe.operation_mode = "normal";
defparam sda_oe.output_mode = "comb_only";
defparam sda_oe.register_cascade_mode = "off";
defparam sda_oe.sum_lutc_input = "datac";
defparam sda_oe.synch_mode = "off";

maxv_lcell clock_oe(
	.clk(gnd),
	.dataa(\bgpbsy_rdreg~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(\bgpend_det_reg~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(clock_oe1),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam clock_oe.lut_mask = "00aa";
defparam clock_oe.operation_mode = "normal";
defparam clock_oe.output_mode = "comb_only";
defparam clock_oe.register_cascade_mode = "off";
defparam clock_oe.sum_lutc_input = "datac";
defparam clock_oe.synch_mode = "off";

maxv_lcell \clr_drclk_reg~0 (
	.clk(gnd),
	.dataa(\general_cntr|auto_generated|counter2a[2]~regout ),
	.datab(\general_cntr|auto_generated|counter2a[1]~regout ),
	.datac(\general_cntr|auto_generated|counter2a[3]~regout ),
	.datad(\general_cntr|auto_generated|counter2a[0]~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\clr_drclk_reg~0_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \clr_drclk_reg~0 .lut_mask = "0002";
defparam \clr_drclk_reg~0 .operation_mode = "normal";
defparam \clr_drclk_reg~0 .output_mode = "comb_only";
defparam \clr_drclk_reg~0 .register_cascade_mode = "off";
defparam \clr_drclk_reg~0 .sum_lutc_input = "datac";
defparam \clr_drclk_reg~0 .synch_mode = "off";

maxv_lcell \fin_devadd_reg_ena~0 (
	.clk(gnd),
	.dataa(\clr_drclk_reg~0_combout ),
	.datab(vcc),
	.datac(\stage_cntr|auto_generated|counter2a[1]~regout ),
	.datad(\stage_cntr|auto_generated|counter2a[0]~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\fin_devadd_reg_ena~0_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \fin_devadd_reg_ena~0 .lut_mask = "000a";
defparam \fin_devadd_reg_ena~0 .operation_mode = "normal";
defparam \fin_devadd_reg_ena~0 .output_mode = "comb_only";
defparam \fin_devadd_reg_ena~0 .register_cascade_mode = "off";
defparam \fin_devadd_reg_ena~0 .sum_lutc_input = "datac";
defparam \fin_devadd_reg_ena~0 .synch_mode = "off";

maxv_lcell sda_indly_reg(
	.clk(ufm_osc),
	.dataa(sda),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\sda_indly_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam sda_indly_reg.lut_mask = "aaaa";
defparam sda_indly_reg.operation_mode = "normal";
defparam sda_indly_reg.output_mode = "reg_only";
defparam sda_indly_reg.register_cascade_mode = "off";
defparam sda_indly_reg.sum_lutc_input = "datac";
defparam sda_indly_reg.synch_mode = "off";
defparam sda_indly_reg.x_on_violation = "off";

maxv_lcell sda_indly_reg2(
	.clk(ufm_osc),
	.dataa(\sda_indly_reg~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\sda_indly_reg2~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam sda_indly_reg2.lut_mask = "aaaa";
defparam sda_indly_reg2.operation_mode = "normal";
defparam sda_indly_reg2.output_mode = "reg_only";
defparam sda_indly_reg2.register_cascade_mode = "off";
defparam sda_indly_reg2.sum_lutc_input = "datac";
defparam sda_indly_reg2.synch_mode = "off";
defparam sda_indly_reg2.x_on_violation = "off";

maxv_lcell fin_devadd_reg(
	.clk(!scl),
	.dataa(\fin_devadd_reg~regout ),
	.datab(\clr_drclk_reg~0_combout ),
	.datac(\stage_cntr|auto_generated|counter2a[1]~regout ),
	.datad(\stage_cntr|auto_generated|counter2a[0]~regout ),
	.aclr(\comb~0_combout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\fin_devadd_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam fin_devadd_reg.lut_mask = "aaae";
defparam fin_devadd_reg.operation_mode = "normal";
defparam fin_devadd_reg.output_mode = "reg_only";
defparam fin_devadd_reg.register_cascade_mode = "off";
defparam fin_devadd_reg.sum_lutc_input = "datac";
defparam fin_devadd_reg.synch_mode = "off";
defparam fin_devadd_reg.x_on_violation = "off";

maxv_lcell \dev_add_reg[0] (
	.clk(scl),
	.dataa(\dev_add_reg[0]~regout ),
	.datab(sda),
	.datac(\start_detect_reg~regout ),
	.datad(\fin_devadd_reg~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\dev_add_reg[0]~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam \dev_add_reg[0] .lut_mask = "aaca";
defparam \dev_add_reg[0] .operation_mode = "normal";
defparam \dev_add_reg[0] .output_mode = "reg_only";
defparam \dev_add_reg[0] .register_cascade_mode = "off";
defparam \dev_add_reg[0] .sum_lutc_input = "datac";
defparam \dev_add_reg[0] .synch_mode = "off";
defparam \dev_add_reg[0] .x_on_violation = "off";

maxv_lcell \ncount8~0 (
	.clk(gnd),
	.dataa(\general_cntr|auto_generated|counter2a[2]~regout ),
	.datab(\general_cntr|auto_generated|counter2a[3]~regout ),
	.datac(\general_cntr|auto_generated|counter2a[1]~regout ),
	.datad(\general_cntr|auto_generated|counter2a[0]~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\ncount8~0_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \ncount8~0 .lut_mask = "0008";
defparam \ncount8~0 .operation_mode = "normal";
defparam \ncount8~0 .output_mode = "comb_only";
defparam \ncount8~0 .register_cascade_mode = "off";
defparam \ncount8~0 .sum_lutc_input = "datac";
defparam \ncount8~0 .synch_mode = "off";

maxv_lcell \rd_addr_reg[0] (
	.clk(scl),
	.dataa(\rd_addr_reg[0]~regout ),
	.datab(sda),
	.datac(\wire_din_en_reg_ena~0_combout ),
	.datad(\ncount8~0_combout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\rd_addr_reg[0]~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam \rd_addr_reg[0] .lut_mask = "aaca";
defparam \rd_addr_reg[0] .operation_mode = "normal";
defparam \rd_addr_reg[0] .output_mode = "reg_only";
defparam \rd_addr_reg[0] .register_cascade_mode = "off";
defparam \rd_addr_reg[0] .sum_lutc_input = "datac";
defparam \rd_addr_reg[0] .synch_mode = "off";
defparam \rd_addr_reg[0] .x_on_violation = "off";

maxv_lcell \erase_add_match~0 (
	.clk(gnd),
	.dataa(vcc),
	.datab(vcc),
	.datac(\dev_add_reg[0]~regout ),
	.datad(\rd_addr_reg[0]~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\erase_add_match~0_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \erase_add_match~0 .lut_mask = "000f";
defparam \erase_add_match~0 .operation_mode = "normal";
defparam \erase_add_match~0 .output_mode = "comb_only";
defparam \erase_add_match~0 .register_cascade_mode = "off";
defparam \erase_add_match~0 .sum_lutc_input = "datac";
defparam \erase_add_match~0 .synch_mode = "off";

maxv_lcell \rd_addr_reg[1] (
	.clk(scl),
	.dataa(\rd_addr_reg[1]~regout ),
	.datab(\rd_addr_reg[0]~regout ),
	.datac(\wire_din_en_reg_ena~0_combout ),
	.datad(\ncount8~0_combout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\rd_addr_reg[1]~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam \rd_addr_reg[1] .lut_mask = "aaca";
defparam \rd_addr_reg[1] .operation_mode = "normal";
defparam \rd_addr_reg[1] .output_mode = "reg_only";
defparam \rd_addr_reg[1] .register_cascade_mode = "off";
defparam \rd_addr_reg[1] .sum_lutc_input = "datac";
defparam \rd_addr_reg[1] .synch_mode = "off";
defparam \rd_addr_reg[1] .x_on_violation = "off";

maxv_lcell \rd_addr_reg[2] (
	.clk(scl),
	.dataa(\rd_addr_reg[2]~regout ),
	.datab(\rd_addr_reg[1]~regout ),
	.datac(\wire_din_en_reg_ena~0_combout ),
	.datad(\ncount8~0_combout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\rd_addr_reg[2]~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam \rd_addr_reg[2] .lut_mask = "aaca";
defparam \rd_addr_reg[2] .operation_mode = "normal";
defparam \rd_addr_reg[2] .output_mode = "reg_only";
defparam \rd_addr_reg[2] .register_cascade_mode = "off";
defparam \rd_addr_reg[2] .sum_lutc_input = "datac";
defparam \rd_addr_reg[2] .synch_mode = "off";
defparam \rd_addr_reg[2] .x_on_violation = "off";

maxv_lcell \rd_addr_reg[3] (
	.clk(scl),
	.dataa(\rd_addr_reg[3]~regout ),
	.datab(\rd_addr_reg[2]~regout ),
	.datac(\wire_din_en_reg_ena~0_combout ),
	.datad(\ncount8~0_combout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\rd_addr_reg[3]~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam \rd_addr_reg[3] .lut_mask = "aaca";
defparam \rd_addr_reg[3] .operation_mode = "normal";
defparam \rd_addr_reg[3] .output_mode = "reg_only";
defparam \rd_addr_reg[3] .register_cascade_mode = "off";
defparam \rd_addr_reg[3] .sum_lutc_input = "datac";
defparam \rd_addr_reg[3] .synch_mode = "off";
defparam \rd_addr_reg[3] .x_on_violation = "off";

maxv_lcell \rd_addr_reg[4] (
	.clk(scl),
	.dataa(\rd_addr_reg[4]~regout ),
	.datab(\rd_addr_reg[3]~regout ),
	.datac(\wire_din_en_reg_ena~0_combout ),
	.datad(\ncount8~0_combout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\rd_addr_reg[4]~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam \rd_addr_reg[4] .lut_mask = "aaca";
defparam \rd_addr_reg[4] .operation_mode = "normal";
defparam \rd_addr_reg[4] .output_mode = "reg_only";
defparam \rd_addr_reg[4] .register_cascade_mode = "off";
defparam \rd_addr_reg[4] .sum_lutc_input = "datac";
defparam \rd_addr_reg[4] .synch_mode = "off";
defparam \rd_addr_reg[4] .x_on_violation = "off";

maxv_lcell \rd_addr_reg[5] (
	.clk(scl),
	.dataa(\rd_addr_reg[5]~regout ),
	.datab(\rd_addr_reg[4]~regout ),
	.datac(\wire_din_en_reg_ena~0_combout ),
	.datad(\ncount8~0_combout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\rd_addr_reg[5]~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam \rd_addr_reg[5] .lut_mask = "aaca";
defparam \rd_addr_reg[5] .operation_mode = "normal";
defparam \rd_addr_reg[5] .output_mode = "reg_only";
defparam \rd_addr_reg[5] .register_cascade_mode = "off";
defparam \rd_addr_reg[5] .sum_lutc_input = "datac";
defparam \rd_addr_reg[5] .synch_mode = "off";
defparam \rd_addr_reg[5] .x_on_violation = "off";

maxv_lcell \rd_addr_reg[6] (
	.clk(scl),
	.dataa(\rd_addr_reg[6]~regout ),
	.datab(\rd_addr_reg[5]~regout ),
	.datac(\wire_din_en_reg_ena~0_combout ),
	.datad(\ncount8~0_combout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\rd_addr_reg[6]~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam \rd_addr_reg[6] .lut_mask = "aaca";
defparam \rd_addr_reg[6] .operation_mode = "normal";
defparam \rd_addr_reg[6] .output_mode = "reg_only";
defparam \rd_addr_reg[6] .register_cascade_mode = "off";
defparam \rd_addr_reg[6] .sum_lutc_input = "datac";
defparam \rd_addr_reg[6] .synch_mode = "off";
defparam \rd_addr_reg[6] .x_on_violation = "off";

maxv_lcell \erase_add_match~1 (
	.clk(gnd),
	.dataa(\rd_addr_reg[3]~regout ),
	.datab(\rd_addr_reg[4]~regout ),
	.datac(\rd_addr_reg[5]~regout ),
	.datad(\rd_addr_reg[6]~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\erase_add_match~1_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \erase_add_match~1 .lut_mask = "0001";
defparam \erase_add_match~1 .operation_mode = "normal";
defparam \erase_add_match~1 .output_mode = "comb_only";
defparam \erase_add_match~1 .register_cascade_mode = "off";
defparam \erase_add_match~1 .sum_lutc_input = "datac";
defparam \erase_add_match~1 .synch_mode = "off";

maxv_lcell \erase_add_match~2 (
	.clk(gnd),
	.dataa(\erase_add_match~0_combout ),
	.datab(\erase_add_match~1_combout ),
	.datac(\rd_addr_reg[1]~regout ),
	.datad(\rd_addr_reg[2]~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\erase_add_match~2_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \erase_add_match~2 .lut_mask = "0008";
defparam \erase_add_match~2 .operation_mode = "normal";
defparam \erase_add_match~2 .output_mode = "comb_only";
defparam \erase_add_match~2 .register_cascade_mode = "off";
defparam \erase_add_match~2 .sum_lutc_input = "datac";
defparam \erase_add_match~2 .synch_mode = "off";

maxv_lcell \ena_write_reg~0 (
	.clk(gnd),
	.dataa(vcc),
	.datab(vcc),
	.datac(wire_maxii_ufm_block1_busy),
	.datad(wire_maxii_ufm_block1_bgpbusy),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\ena_write_reg~0_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \ena_write_reg~0 .lut_mask = "000f";
defparam \ena_write_reg~0 .operation_mode = "normal";
defparam \ena_write_reg~0 .output_mode = "comb_only";
defparam \ena_write_reg~0 .register_cascade_mode = "off";
defparam \ena_write_reg~0 .sum_lutc_input = "datac";
defparam \ena_write_reg~0 .synch_mode = "off";

maxv_lcell \start_din_reg~2 (
	.clk(gnd),
	.dataa(\stage_cntr|auto_generated|counter2a[1]~regout ),
	.datab(\stage_cntr|auto_generated|counter2a[0]~regout ),
	.datac(vcc),
	.datad(\rd_wr_reg~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\start_din_reg~2_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \start_din_reg~2 .lut_mask = "0088";
defparam \start_din_reg~2 .operation_mode = "normal";
defparam \start_din_reg~2 .output_mode = "comb_only";
defparam \start_din_reg~2 .register_cascade_mode = "off";
defparam \start_din_reg~2 .sum_lutc_input = "datac";
defparam \start_din_reg~2 .synch_mode = "off";

maxv_lcell \ack_sa_reg~0 (
	.clk(gnd),
	.dataa(\ncount8~0_combout ),
	.datab(vcc),
	.datac(wire_maxii_ufm_block1_bgpbusy),
	.datad(\cmpr4|auto_generated|aneb_result_wire[0]~combout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\ack_sa_reg~0_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \ack_sa_reg~0 .lut_mask = "000a";
defparam \ack_sa_reg~0 .operation_mode = "normal";
defparam \ack_sa_reg~0 .output_mode = "comb_only";
defparam \ack_sa_reg~0 .register_cascade_mode = "off";
defparam \ack_sa_reg~0 .sum_lutc_input = "datac";
defparam \ack_sa_reg~0 .synch_mode = "off";

maxv_lcell \add_en_reg~1 (
	.clk(gnd),
	.dataa(vcc),
	.datab(vcc),
	.datac(\rd_wr_reg~regout ),
	.datad(\cmpr4|auto_generated|aneb_result_wire[0]~combout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\add_en_reg~1_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \add_en_reg~1 .lut_mask = "000f";
defparam \add_en_reg~1 .operation_mode = "normal";
defparam \add_en_reg~1 .output_mode = "comb_only";
defparam \add_en_reg~1 .register_cascade_mode = "off";
defparam \add_en_reg~1 .sum_lutc_input = "datac";
defparam \add_en_reg~1 .synch_mode = "off";

maxv_lcell ack_data_reg(
	.clk(!scl),
	.dataa(\start_din_reg~2_combout ),
	.datab(\ack_sa_reg~0_combout ),
	.datac(\ack_data_reg~regout ),
	.datad(\add_en_reg~1_combout ),
	.aclr(\comb~0_combout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\ack_data_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam ack_data_reg.lut_mask = "88f8";
defparam ack_data_reg.operation_mode = "normal";
defparam ack_data_reg.output_mode = "reg_only";
defparam ack_data_reg.register_cascade_mode = "off";
defparam ack_data_reg.sum_lutc_input = "datac";
defparam ack_data_reg.synch_mode = "off";
defparam ack_data_reg.x_on_violation = "off";

maxv_lcell \start_wr_reg~0 (
	.clk(gnd),
	.dataa(\er_wr_cntr|auto_generated|counter2a[0]~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(\er_wr_cntr|auto_generated|counter2a[1]~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\start_wr_reg~0_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \start_wr_reg~0 .lut_mask = "00aa";
defparam \start_wr_reg~0 .operation_mode = "normal";
defparam \start_wr_reg~0 .output_mode = "comb_only";
defparam \start_wr_reg~0 .register_cascade_mode = "off";
defparam \start_wr_reg~0 .sum_lutc_input = "datac";
defparam \start_wr_reg~0 .synch_mode = "off";

maxv_lcell start_wr_reg(
	.clk(!ufm_osc),
	.dataa(\start_wr_reg~regout ),
	.datab(\erase_add_match~2_combout ),
	.datac(\start_wr_reg~0_combout ),
	.datad(wire_maxii_ufm_block1_bgpbusy),
	.aclr(\end_write_reg2~regout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\start_wr_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam start_wr_reg.lut_mask = "aaea";
defparam start_wr_reg.operation_mode = "normal";
defparam start_wr_reg.output_mode = "reg_only";
defparam start_wr_reg.register_cascade_mode = "off";
defparam start_wr_reg.sum_lutc_input = "datac";
defparam start_wr_reg.synch_mode = "off";
defparam start_wr_reg.x_on_violation = "off";

maxv_lcell \data_pad_complete~0 (
	.clk(gnd),
	.dataa(\data_pad_cntr|auto_generated|counter2a[3]~regout ),
	.datab(\data_pad_cntr|auto_generated|counter2a[2]~regout ),
	.datac(\data_pad_cntr|auto_generated|counter2a[1]~regout ),
	.datad(\data_pad_cntr|auto_generated|counter2a[0]~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\data_pad_complete~0_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \data_pad_complete~0 .lut_mask = "0008";
defparam \data_pad_complete~0 .operation_mode = "normal";
defparam \data_pad_complete~0 .output_mode = "comb_only";
defparam \data_pad_complete~0 .register_cascade_mode = "off";
defparam \data_pad_complete~0 .sum_lutc_input = "datac";
defparam \data_pad_complete~0 .synch_mode = "off";

maxv_lcell \wire_start_prog_reg_clrn~0 (
	.clk(gnd),
	.dataa(wire_maxii_ufm_block1_bgpbusy),
	.datab(\er_wr_cntr|auto_generated|counter2a[1]~regout ),
	.datac(\er_wr_cntr|auto_generated|counter2a[0]~regout ),
	.datad(\end_write_reg2~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\wire_start_prog_reg_clrn~0_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \wire_start_prog_reg_clrn~0 .lut_mask = "eac0";
defparam \wire_start_prog_reg_clrn~0 .operation_mode = "normal";
defparam \wire_start_prog_reg_clrn~0 .output_mode = "comb_only";
defparam \wire_start_prog_reg_clrn~0 .register_cascade_mode = "off";
defparam \wire_start_prog_reg_clrn~0 .sum_lutc_input = "datac";
defparam \wire_start_prog_reg_clrn~0 .synch_mode = "off";

maxv_lcell \wire_start_prog_reg_clrn~1 (
	.clk(gnd),
	.dataa(\wire_start_prog_reg_clrn~0_combout ),
	.datab(\busy_dea_reg~regout ),
	.datac(vcc),
	.datad(\erase_add_match~2_combout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\wire_start_prog_reg_clrn~1_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \wire_start_prog_reg_clrn~1 .lut_mask = "aacc";
defparam \wire_start_prog_reg_clrn~1 .operation_mode = "normal";
defparam \wire_start_prog_reg_clrn~1 .output_mode = "comb_only";
defparam \wire_start_prog_reg_clrn~1 .register_cascade_mode = "off";
defparam \wire_start_prog_reg_clrn~1 .sum_lutc_input = "datac";
defparam \wire_start_prog_reg_clrn~1 .synch_mode = "off";

maxv_lcell start_prog_reg(
	.clk(ufm_osc),
	.dataa(\data_pad_complete~0_combout ),
	.datab(\start_prog_reg~regout ),
	.datac(\ena_write_reg~regout ),
	.datad(\ena_write_reg~0_combout ),
	.aclr(\wire_start_prog_reg_clrn~1_combout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\start_prog_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam start_prog_reg.lut_mask = "accc";
defparam start_prog_reg.operation_mode = "normal";
defparam start_prog_reg.output_mode = "reg_only";
defparam start_prog_reg.register_cascade_mode = "off";
defparam start_prog_reg.sum_lutc_input = "datac";
defparam start_prog_reg.synch_mode = "off";
defparam start_prog_reg.x_on_violation = "off";

maxv_lcell \ufm_program~0 (
	.clk(gnd),
	.dataa(\start_wr_reg~regout ),
	.datab(\start_prog_reg~regout ),
	.datac(vcc),
	.datad(\erase_add_match~2_combout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\ufm_program~0_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \ufm_program~0 .lut_mask = "aacc";
defparam \ufm_program~0 .operation_mode = "normal";
defparam \ufm_program~0 .output_mode = "comb_only";
defparam \ufm_program~0 .register_cascade_mode = "off";
defparam \ufm_program~0 .sum_lutc_input = "datac";
defparam \ufm_program~0 .synch_mode = "off";

maxv_lcell eradd_match_reg(
	.clk(!ufm_osc),
	.dataa(\erase_add_match~2_combout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\eradd_match_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam eradd_match_reg.lut_mask = "aaaa";
defparam eradd_match_reg.operation_mode = "normal";
defparam eradd_match_reg.output_mode = "reg_only";
defparam eradd_match_reg.register_cascade_mode = "off";
defparam eradd_match_reg.sum_lutc_input = "datac";
defparam eradd_match_reg.synch_mode = "off";
defparam eradd_match_reg.x_on_violation = "off";

maxv_lcell eradd_match_reg2(
	.clk(!ufm_osc),
	.dataa(\eradd_match_reg~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\eradd_match_reg2~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam eradd_match_reg2.lut_mask = "aaaa";
defparam eradd_match_reg2.operation_mode = "normal";
defparam eradd_match_reg2.output_mode = "reg_only";
defparam eradd_match_reg2.register_cascade_mode = "off";
defparam eradd_match_reg2.sum_lutc_input = "datac";
defparam eradd_match_reg2.synch_mode = "off";
defparam eradd_match_reg2.x_on_violation = "off";

maxv_lcell start_er_reg(
	.clk(!ufm_osc),
	.dataa(\start_prog_reg~regout ),
	.datab(\eradd_match_reg2~regout ),
	.datac(wire_maxii_ufm_block1_bgpbusy),
	.datad(\er_wr_cntr|auto_generated|counter2a[0]~regout ),
	.aclr(\end_write_reg2~regout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\start_er_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam start_er_reg.lut_mask = "0008";
defparam start_er_reg.operation_mode = "normal";
defparam start_er_reg.output_mode = "reg_only";
defparam start_er_reg.register_cascade_mode = "off";
defparam start_er_reg.sum_lutc_input = "datac";
defparam start_er_reg.synch_mode = "off";
defparam start_er_reg.x_on_violation = "off";

maxv_lcell busy_det_reg(
	.clk(ufm_osc),
	.dataa(wire_maxii_ufm_block1_busy),
	.datab(\busy_det_reg~regout ),
	.datac(\ufm_program~0_combout ),
	.datad(\start_er_reg~regout ),
	.aclr(\end_write_reg2~regout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\busy_det_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam busy_det_reg.lut_mask = "aaac";
defparam busy_det_reg.operation_mode = "normal";
defparam busy_det_reg.output_mode = "reg_only";
defparam busy_det_reg.register_cascade_mode = "off";
defparam busy_det_reg.sum_lutc_input = "datac";
defparam busy_det_reg.synch_mode = "off";
defparam busy_det_reg.x_on_violation = "off";

maxv_lcell busy_det_reg2(
	.clk(ufm_osc),
	.dataa(\busy_det_reg~regout ),
	.datab(\busy_det_reg2~regout ),
	.datac(\ufm_program~0_combout ),
	.datad(\start_er_reg~regout ),
	.aclr(\end_write_reg2~regout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\busy_det_reg2~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam busy_det_reg2.lut_mask = "aaac";
defparam busy_det_reg2.operation_mode = "normal";
defparam busy_det_reg2.output_mode = "reg_only";
defparam busy_det_reg2.register_cascade_mode = "off";
defparam busy_det_reg2.sum_lutc_input = "datac";
defparam busy_det_reg2.synch_mode = "off";
defparam busy_det_reg2.x_on_violation = "off";

maxv_lcell busy_dea_reg(
	.clk(!\busy_det_reg2~regout ),
	.dataa(\ufm_program~0_combout ),
	.datab(\start_er_reg~regout ),
	.datac(\busy_dea_reg~regout ),
	.datad(vcc),
	.aclr(\end_write_reg2~regout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\busy_dea_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam busy_dea_reg.lut_mask = "fefe";
defparam busy_dea_reg.operation_mode = "normal";
defparam busy_dea_reg.output_mode = "reg_only";
defparam busy_dea_reg.register_cascade_mode = "off";
defparam busy_dea_reg.sum_lutc_input = "datac";
defparam busy_dea_reg.synch_mode = "off";
defparam busy_dea_reg.x_on_violation = "off";

maxv_lcell end_write_reg(
	.clk(ufm_osc),
	.dataa(\busy_dea_reg~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\end_write_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam end_write_reg.lut_mask = "aaaa";
defparam end_write_reg.operation_mode = "normal";
defparam end_write_reg.output_mode = "reg_only";
defparam end_write_reg.register_cascade_mode = "off";
defparam end_write_reg.sum_lutc_input = "datac";
defparam end_write_reg.synch_mode = "off";
defparam end_write_reg.x_on_violation = "off";

maxv_lcell end_write_reg2(
	.clk(ufm_osc),
	.dataa(\end_write_reg~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\end_write_reg2~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam end_write_reg2.lut_mask = "aaaa";
defparam end_write_reg2.operation_mode = "normal";
defparam end_write_reg2.output_mode = "reg_only";
defparam end_write_reg2.register_cascade_mode = "off";
defparam end_write_reg2.sum_lutc_input = "datac";
defparam end_write_reg2.synch_mode = "off";
defparam end_write_reg2.x_on_violation = "off";

maxv_lcell data_suc_reg(
	.clk(scl),
	.dataa(\data_suc_reg~regout ),
	.datab(\stage_cntr|auto_generated|counter2a[1]~regout ),
	.datac(\stage_cntr|auto_generated|counter2a[0]~regout ),
	.datad(\ack_data_reg~regout ),
	.aclr(\end_write_reg2~regout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\data_suc_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam data_suc_reg.lut_mask = "eaaa";
defparam data_suc_reg.operation_mode = "normal";
defparam data_suc_reg.output_mode = "reg_only";
defparam data_suc_reg.register_cascade_mode = "off";
defparam data_suc_reg.sum_lutc_input = "datac";
defparam data_suc_reg.synch_mode = "off";
defparam data_suc_reg.x_on_violation = "off";

maxv_lcell stop_detect_reg(
	.clk(\sda_indly_reg2~regout ),
	.dataa(\stop_detect_reg~regout ),
	.datab(scl),
	.datac(\ena_write_reg~regout ),
	.datad(\start_er_reg~regout ),
	.aclr(\stop_det_rst~combout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\stop_detect_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam stop_detect_reg.lut_mask = "aaae";
defparam stop_detect_reg.operation_mode = "normal";
defparam stop_detect_reg.output_mode = "reg_only";
defparam stop_detect_reg.register_cascade_mode = "off";
defparam stop_detect_reg.sum_lutc_input = "datac";
defparam stop_detect_reg.synch_mode = "off";
defparam stop_detect_reg.x_on_violation = "off";

maxv_lcell stop_det_da_reg(
	.clk(ufm_osc),
	.dataa(\stop_detect_reg~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\stop_det_da_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam stop_det_da_reg.lut_mask = "aaaa";
defparam stop_det_da_reg.operation_mode = "normal";
defparam stop_det_da_reg.output_mode = "reg_only";
defparam stop_det_da_reg.register_cascade_mode = "off";
defparam stop_det_da_reg.sum_lutc_input = "datac";
defparam stop_det_da_reg.synch_mode = "off";
defparam stop_det_da_reg.x_on_violation = "off";

maxv_lcell stop_det_da_reg2(
	.clk(ufm_osc),
	.dataa(\stop_det_da_reg~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\stop_det_da_reg2~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam stop_det_da_reg2.lut_mask = "aaaa";
defparam stop_det_da_reg2.operation_mode = "normal";
defparam stop_det_da_reg2.output_mode = "reg_only";
defparam stop_det_da_reg2.register_cascade_mode = "off";
defparam stop_det_da_reg2.sum_lutc_input = "datac";
defparam stop_det_da_reg2.synch_mode = "off";
defparam stop_det_da_reg2.x_on_violation = "off";

maxv_lcell stop_rst_reg(
	.clk(ufm_osc),
	.dataa(\stop_det_da_reg2~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\stop_rst_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam stop_rst_reg.lut_mask = "aaaa";
defparam stop_rst_reg.operation_mode = "normal";
defparam stop_rst_reg.output_mode = "reg_only";
defparam stop_rst_reg.register_cascade_mode = "off";
defparam stop_rst_reg.sum_lutc_input = "datac";
defparam stop_rst_reg.synch_mode = "off";
defparam stop_rst_reg.x_on_violation = "off";

maxv_lcell stop_rst_reg2(
	.clk(ufm_osc),
	.dataa(\stop_rst_reg~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\stop_rst_reg2~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam stop_rst_reg2.lut_mask = "aaaa";
defparam stop_rst_reg2.operation_mode = "normal";
defparam stop_rst_reg2.output_mode = "reg_only";
defparam stop_rst_reg2.register_cascade_mode = "off";
defparam stop_rst_reg2.sum_lutc_input = "datac";
defparam stop_rst_reg2.synch_mode = "off";
defparam stop_rst_reg2.x_on_violation = "off";

maxv_lcell stop_det_rst(
	.clk(gnd),
	.dataa(\stop_rst_reg~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(\stop_rst_reg2~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\stop_det_rst~combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam stop_det_rst.lut_mask = "00aa";
defparam stop_det_rst.operation_mode = "normal";
defparam stop_det_rst.output_mode = "comb_only";
defparam stop_det_rst.register_cascade_mode = "off";
defparam stop_det_rst.sum_lutc_input = "datac";
defparam stop_det_rst.synch_mode = "off";

maxv_lcell ena_write_reg(
	.clk(!ufm_osc),
	.dataa(\ena_write_reg~0_combout ),
	.datab(\data_suc_reg~regout ),
	.datac(\ena_write_reg~regout ),
	.datad(\stop_det_rst~combout ),
	.aclr(\end_write_reg2~regout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\ena_write_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam ena_write_reg.lut_mask = "88a0";
defparam ena_write_reg.operation_mode = "normal";
defparam ena_write_reg.output_mode = "reg_only";
defparam ena_write_reg.register_cascade_mode = "off";
defparam ena_write_reg.sum_lutc_input = "datac";
defparam ena_write_reg.synch_mode = "off";
defparam ena_write_reg.x_on_violation = "off";

maxv_lcell \start_detect_reg~0 (
	.clk(gnd),
	.dataa(vcc),
	.datab(\erase_add_match~2_combout ),
	.datac(\ena_write_reg~regout ),
	.datad(\start_prog_reg~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\start_detect_reg~0_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \start_detect_reg~0 .lut_mask = "03cf";
defparam \start_detect_reg~0 .operation_mode = "normal";
defparam \start_detect_reg~0 .output_mode = "comb_only";
defparam \start_detect_reg~0 .register_cascade_mode = "off";
defparam \start_detect_reg~0 .sum_lutc_input = "datac";
defparam \start_detect_reg~0 .synch_mode = "off";

maxv_lcell start_detect_reg(
	.clk(!\sda_indly_reg2~regout ),
	.dataa(\start_detect_reg~regout ),
	.datab(scl),
	.datac(\start_detect_reg~0_combout ),
	.datad(wire_maxii_ufm_block1_bgpbusy),
	.aclr(\stop_det_da_reg2~regout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\start_detect_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam start_detect_reg.lut_mask = "aaea";
defparam start_detect_reg.operation_mode = "normal";
defparam start_detect_reg.output_mode = "reg_only";
defparam start_detect_reg.register_cascade_mode = "off";
defparam start_detect_reg.sum_lutc_input = "datac";
defparam start_detect_reg.synch_mode = "off";
defparam start_detect_reg.x_on_violation = "off";

maxv_lcell rstart_clr_reg(
	.clk(ufm_osc),
	.dataa(\rstart_det_da_reg2~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\rstart_clr_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam rstart_clr_reg.lut_mask = "aaaa";
defparam rstart_clr_reg.operation_mode = "normal";
defparam rstart_clr_reg.output_mode = "reg_only";
defparam rstart_clr_reg.register_cascade_mode = "off";
defparam rstart_clr_reg.sum_lutc_input = "datac";
defparam rstart_clr_reg.synch_mode = "off";
defparam rstart_clr_reg.x_on_violation = "off";

maxv_lcell rstart_clr_reg2(
	.clk(ufm_osc),
	.dataa(\rstart_clr_reg~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\rstart_clr_reg2~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam rstart_clr_reg2.lut_mask = "aaaa";
defparam rstart_clr_reg2.operation_mode = "normal";
defparam rstart_clr_reg2.output_mode = "reg_only";
defparam rstart_clr_reg2.register_cascade_mode = "off";
defparam rstart_clr_reg2.sum_lutc_input = "datac";
defparam rstart_clr_reg2.synch_mode = "off";
defparam rstart_clr_reg2.x_on_violation = "off";

maxv_lcell \wire_rstart_det_reg_clrn~0 (
	.clk(gnd),
	.dataa(\stop_det_da_reg2~regout ),
	.datab(\rstart_clr_reg~regout ),
	.datac(vcc),
	.datad(\rstart_clr_reg2~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\wire_rstart_det_reg_clrn~0_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \wire_rstart_det_reg_clrn~0 .lut_mask = "aaee";
defparam \wire_rstart_det_reg_clrn~0 .operation_mode = "normal";
defparam \wire_rstart_det_reg_clrn~0 .output_mode = "comb_only";
defparam \wire_rstart_det_reg_clrn~0 .register_cascade_mode = "off";
defparam \wire_rstart_det_reg_clrn~0 .sum_lutc_input = "datac";
defparam \wire_rstart_det_reg_clrn~0 .synch_mode = "off";

maxv_lcell rstart_det_reg(
	.clk(!\sda_indly_reg2~regout ),
	.dataa(\rstart_det_reg~regout ),
	.datab(scl),
	.datac(\start_detect_reg~regout ),
	.datad(vcc),
	.aclr(\wire_rstart_det_reg_clrn~0_combout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\rstart_det_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam rstart_det_reg.lut_mask = "eaea";
defparam rstart_det_reg.operation_mode = "normal";
defparam rstart_det_reg.output_mode = "reg_only";
defparam rstart_det_reg.register_cascade_mode = "off";
defparam rstart_det_reg.sum_lutc_input = "datac";
defparam rstart_det_reg.synch_mode = "off";
defparam rstart_det_reg.x_on_violation = "off";

maxv_lcell rstart_det_da_reg(
	.clk(ufm_osc),
	.dataa(\rstart_det_reg~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\rstart_det_da_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam rstart_det_da_reg.lut_mask = "aaaa";
defparam rstart_det_da_reg.operation_mode = "normal";
defparam rstart_det_da_reg.output_mode = "reg_only";
defparam rstart_det_da_reg.register_cascade_mode = "off";
defparam rstart_det_da_reg.sum_lutc_input = "datac";
defparam rstart_det_da_reg.synch_mode = "off";
defparam rstart_det_da_reg.x_on_violation = "off";

maxv_lcell rstart_det_da_reg2(
	.clk(ufm_osc),
	.dataa(\rstart_det_da_reg~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\rstart_det_da_reg2~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam rstart_det_da_reg2.lut_mask = "aaaa";
defparam rstart_det_da_reg2.operation_mode = "normal";
defparam rstart_det_da_reg2.output_mode = "reg_only";
defparam rstart_det_da_reg2.register_cascade_mode = "off";
defparam rstart_det_da_reg2.sum_lutc_input = "datac";
defparam rstart_det_da_reg2.synch_mode = "off";
defparam rstart_det_da_reg2.x_on_violation = "off";

maxv_lcell \comb~0 (
	.clk(gnd),
	.dataa(vcc),
	.datab(vcc),
	.datac(\rstart_det_da_reg2~regout ),
	.datad(\stop_det_da_reg2~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\comb~0_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \comb~0 .lut_mask = "fff0";
defparam \comb~0 .operation_mode = "normal";
defparam \comb~0 .output_mode = "comb_only";
defparam \comb~0 .register_cascade_mode = "off";
defparam \comb~0 .sum_lutc_input = "datac";
defparam \comb~0 .synch_mode = "off";

maxv_lcell rd_wr_reg(
	.clk(scl),
	.dataa(\rd_wr_reg~regout ),
	.datab(sda),
	.datac(\fin_devadd_reg_ena~0_combout ),
	.datad(\cmpr4|auto_generated|aneb_result_wire[0]~combout ),
	.aclr(\comb~0_combout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\rd_wr_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam rd_wr_reg.lut_mask = "aaca";
defparam rd_wr_reg.operation_mode = "normal";
defparam rd_wr_reg.output_mode = "reg_only";
defparam rd_wr_reg.register_cascade_mode = "off";
defparam rd_wr_reg.sum_lutc_input = "datac";
defparam rd_wr_reg.synch_mode = "off";
defparam rd_wr_reg.x_on_violation = "off";

maxv_lcell \wire_din_en_reg_ena~0 (
	.clk(gnd),
	.dataa(\stage_cntr|auto_generated|counter2a[0]~regout ),
	.datab(vcc),
	.datac(\rd_wr_reg~regout ),
	.datad(\stage_cntr|auto_generated|counter2a[1]~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\wire_din_en_reg_ena~0_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \wire_din_en_reg_ena~0 .lut_mask = "000a";
defparam \wire_din_en_reg_ena~0 .operation_mode = "normal";
defparam \wire_din_en_reg_ena~0 .output_mode = "comb_only";
defparam \wire_din_en_reg_ena~0 .register_cascade_mode = "off";
defparam \wire_din_en_reg_ena~0 .sum_lutc_input = "datac";
defparam \wire_din_en_reg_ena~0 .synch_mode = "off";

maxv_lcell \count9~0 (
	.clk(gnd),
	.dataa(\general_cntr|auto_generated|counter2a[2]~regout ),
	.datab(\general_cntr|auto_generated|counter2a[3]~regout ),
	.datac(\general_cntr|auto_generated|counter2a[0]~regout ),
	.datad(\general_cntr|auto_generated|counter2a[1]~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\count9~0_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \count9~0 .lut_mask = "0080";
defparam \count9~0 .operation_mode = "normal";
defparam \count9~0 .output_mode = "comb_only";
defparam \count9~0 .register_cascade_mode = "off";
defparam \count9~0 .sum_lutc_input = "datac";
defparam \count9~0 .synch_mode = "off";

maxv_lcell end_din_reg(
	.clk(!scl),
	.dataa(\end_din_reg~regout ),
	.datab(\start_din_reg~2_combout ),
	.datac(\ncount8~0_combout ),
	.datad(vcc),
	.aclr(\comb~0_combout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\end_din_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam end_din_reg.lut_mask = "eaea";
defparam end_din_reg.operation_mode = "normal";
defparam end_din_reg.output_mode = "reg_only";
defparam end_din_reg.register_cascade_mode = "off";
defparam end_din_reg.sum_lutc_input = "datac";
defparam end_din_reg.synch_mode = "off";
defparam end_din_reg.x_on_violation = "off";

maxv_lcell \wire_din_en_reg_clrn~0 (
	.clk(gnd),
	.dataa(\end_din_reg~regout ),
	.datab(\rstart_det_da_reg2~regout ),
	.datac(\stop_det_da_reg2~regout ),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\wire_din_en_reg_clrn~0_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \wire_din_en_reg_clrn~0 .lut_mask = "fefe";
defparam \wire_din_en_reg_clrn~0 .operation_mode = "normal";
defparam \wire_din_en_reg_clrn~0 .output_mode = "comb_only";
defparam \wire_din_en_reg_clrn~0 .register_cascade_mode = "off";
defparam \wire_din_en_reg_clrn~0 .sum_lutc_input = "datac";
defparam \wire_din_en_reg_clrn~0 .synch_mode = "off";

maxv_lcell din_en_reg(
	.clk(!scl),
	.dataa(\din_en_reg~regout ),
	.datab(\wire_din_en_reg_ena~0_combout ),
	.datac(\count9~0_combout ),
	.datad(\cmpr4|auto_generated|aneb_result_wire[0]~combout ),
	.aclr(\wire_din_en_reg_clrn~0_combout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\din_en_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam din_en_reg.lut_mask = "aaea";
defparam din_en_reg.operation_mode = "normal";
defparam din_en_reg.output_mode = "reg_only";
defparam din_en_reg.register_cascade_mode = "off";
defparam din_en_reg.sum_lutc_input = "datac";
defparam din_en_reg.synch_mode = "off";
defparam din_en_reg.x_on_violation = "off";

maxv_lcell end_datpd_reg(
	.clk(!ufm_osc),
	.dataa(\data_pad_complete~0_combout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(\end_write_reg2~regout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\end_datpd_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam end_datpd_reg.lut_mask = "aaaa";
defparam end_datpd_reg.operation_mode = "normal";
defparam end_datpd_reg.output_mode = "reg_only";
defparam end_datpd_reg.register_cascade_mode = "off";
defparam end_datpd_reg.sum_lutc_input = "datac";
defparam end_datpd_reg.synch_mode = "off";
defparam end_datpd_reg.x_on_violation = "off";

maxv_lcell ufm_drdin(
	.clk(gnd),
	.dataa(\din_en_reg~regout ),
	.datab(sda),
	.datac(\ena_write_reg~regout ),
	.datad(\end_datpd_reg~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\ufm_drdin~combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam ufm_drdin.lut_mask = "88f8";
defparam ufm_drdin.operation_mode = "normal";
defparam ufm_drdin.output_mode = "comb_only";
defparam ufm_drdin.register_cascade_mode = "off";
defparam ufm_drdin.sum_lutc_input = "datac";
defparam ufm_drdin.synch_mode = "off";

maxv_lcell ack_sa_reg(
	.clk(!scl),
	.dataa(\ack_sa_reg~0_combout ),
	.datab(vcc),
	.datac(\stage_cntr|auto_generated|counter2a[1]~regout ),
	.datad(\stage_cntr|auto_generated|counter2a[0]~regout ),
	.aclr(\comb~0_combout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\ack_sa_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam ack_sa_reg.lut_mask = "000a";
defparam ack_sa_reg.operation_mode = "normal";
defparam ack_sa_reg.output_mode = "reg_only";
defparam ack_sa_reg.register_cascade_mode = "off";
defparam ack_sa_reg.sum_lutc_input = "datac";
defparam ack_sa_reg.synch_mode = "off";
defparam ack_sa_reg.x_on_violation = "off";

maxv_lcell start_rd_reg(
	.clk(scl),
	.dataa(\start_rd_reg~regout ),
	.datab(\rd_wr_reg~regout ),
	.datac(\ack_sa_reg~regout ),
	.datad(\cmpr4|auto_generated|aneb_result_wire[0]~combout ),
	.aclr(\stop_det_da_reg2~regout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\start_rd_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam start_rd_reg.lut_mask = "aaea";
defparam start_rd_reg.operation_mode = "normal";
defparam start_rd_reg.output_mode = "reg_only";
defparam start_rd_reg.register_cascade_mode = "off";
defparam start_rd_reg.sum_lutc_input = "datac";
defparam start_rd_reg.synch_mode = "off";
defparam start_rd_reg.x_on_violation = "off";

maxv_lcell ena_drclk_reg(
	.clk(!scl),
	.dataa(\ncount8~0_combout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\ena_drclk_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam ena_drclk_reg.lut_mask = "aaaa";
defparam ena_drclk_reg.operation_mode = "normal";
defparam ena_drclk_reg.output_mode = "reg_only";
defparam ena_drclk_reg.register_cascade_mode = "off";
defparam ena_drclk_reg.sum_lutc_input = "datac";
defparam ena_drclk_reg.synch_mode = "off";
defparam ena_drclk_reg.x_on_violation = "off";

maxv_lcell clr_drclk_reg(
	.clk(!scl),
	.dataa(\clr_drclk_reg~0_combout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\clr_drclk_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam clr_drclk_reg.lut_mask = "aaaa";
defparam clr_drclk_reg.operation_mode = "normal";
defparam clr_drclk_reg.output_mode = "reg_only";
defparam clr_drclk_reg.register_cascade_mode = "off";
defparam clr_drclk_reg.sum_lutc_input = "datac";
defparam clr_drclk_reg.synch_mode = "off";
defparam clr_drclk_reg.x_on_violation = "off";

maxv_lcell strd_drclk_reg(
	.clk(scl),
	.dataa(\strd_drclk_reg~regout ),
	.datab(\rd_wr_reg~regout ),
	.datac(\ena_drclk_reg~regout ),
	.datad(\cmpr4|auto_generated|aneb_result_wire[0]~combout ),
	.aclr(\clr_drclk_reg~regout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\strd_drclk_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam strd_drclk_reg.lut_mask = "aaea";
defparam strd_drclk_reg.operation_mode = "normal";
defparam strd_drclk_reg.output_mode = "reg_only";
defparam strd_drclk_reg.register_cascade_mode = "off";
defparam strd_drclk_reg.sum_lutc_input = "datac";
defparam strd_drclk_reg.synch_mode = "off";
defparam strd_drclk_reg.x_on_violation = "off";

maxv_lcell reach_cnt9_reg(
	.clk(!scl),
	.dataa(\count9~0_combout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\reach_cnt9_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam reach_cnt9_reg.lut_mask = "aaaa";
defparam reach_cnt9_reg.operation_mode = "normal";
defparam reach_cnt9_reg.output_mode = "reg_only";
defparam reach_cnt9_reg.register_cascade_mode = "off";
defparam reach_cnt9_reg.sum_lutc_input = "datac";
defparam reach_cnt9_reg.synch_mode = "off";
defparam reach_cnt9_reg.x_on_violation = "off";

maxv_lcell gcntr_aclr_reg(
	.clk(ufm_osc),
	.dataa(\reach_cnt9_reg~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\gcntr_aclr_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam gcntr_aclr_reg.lut_mask = "aaaa";
defparam gcntr_aclr_reg.operation_mode = "normal";
defparam gcntr_aclr_reg.output_mode = "reg_only";
defparam gcntr_aclr_reg.register_cascade_mode = "off";
defparam gcntr_aclr_reg.sum_lutc_input = "datac";
defparam gcntr_aclr_reg.synch_mode = "off";
defparam gcntr_aclr_reg.x_on_violation = "off";

maxv_lcell gcntr_aclr_int_reg(
	.clk(ufm_osc),
	.dataa(\gcntr_aclr_reg~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\gcntr_aclr_int_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam gcntr_aclr_int_reg.lut_mask = "aaaa";
defparam gcntr_aclr_int_reg.operation_mode = "normal";
defparam gcntr_aclr_int_reg.output_mode = "reg_only";
defparam gcntr_aclr_int_reg.register_cascade_mode = "off";
defparam gcntr_aclr_int_reg.sum_lutc_input = "datac";
defparam gcntr_aclr_int_reg.synch_mode = "off";
defparam gcntr_aclr_int_reg.x_on_violation = "off";

maxv_lcell gcntr_aclr_reg2(
	.clk(ufm_osc),
	.dataa(\gcntr_aclr_int_reg~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\gcntr_aclr_reg2~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam gcntr_aclr_reg2.lut_mask = "aaaa";
defparam gcntr_aclr_reg2.operation_mode = "normal";
defparam gcntr_aclr_reg2.output_mode = "reg_only";
defparam gcntr_aclr_reg2.register_cascade_mode = "off";
defparam gcntr_aclr_reg2.sum_lutc_input = "datac";
defparam gcntr_aclr_reg2.synch_mode = "off";
defparam gcntr_aclr_reg2.x_on_violation = "off";

maxv_lcell \wire_bgpbsy_rdreg_ena~0 (
	.clk(gnd),
	.dataa(\stage_cntr|auto_generated|counter2a[0]~regout ),
	.datab(\gcntr_aclr_int_reg~regout ),
	.datac(\stage_cntr|auto_generated|counter2a[1]~regout ),
	.datad(\gcntr_aclr_reg2~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\wire_bgpbsy_rdreg_ena~0_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \wire_bgpbsy_rdreg_ena~0 .lut_mask = "0008";
defparam \wire_bgpbsy_rdreg_ena~0 .operation_mode = "normal";
defparam \wire_bgpbsy_rdreg_ena~0 .output_mode = "comb_only";
defparam \wire_bgpbsy_rdreg_ena~0 .register_cascade_mode = "off";
defparam \wire_bgpbsy_rdreg_ena~0 .sum_lutc_input = "datac";
defparam \wire_bgpbsy_rdreg_ena~0 .synch_mode = "off";

maxv_lcell bgpbsy_rdreg(
	.clk(!ufm_osc),
	.dataa(wire_maxii_ufm_block1_bgpbusy),
	.datab(\bgpbsy_rdreg~regout ),
	.datac(\rd_wr_reg~regout ),
	.datad(\wire_bgpbsy_rdreg_ena~0_combout ),
	.aclr(\stop_det_da_reg2~regout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\bgpbsy_rdreg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam bgpbsy_rdreg.lut_mask = "accc";
defparam bgpbsy_rdreg.operation_mode = "normal";
defparam bgpbsy_rdreg.output_mode = "reg_only";
defparam bgpbsy_rdreg.register_cascade_mode = "off";
defparam bgpbsy_rdreg.sum_lutc_input = "datac";
defparam bgpbsy_rdreg.synch_mode = "off";
defparam bgpbsy_rdreg.x_on_violation = "off";

maxv_lcell \ufm_drclk~0 (
	.clk(gnd),
	.dataa(\rd_wr_reg~regout ),
	.datab(\start_rd_reg~regout ),
	.datac(\strd_drclk_reg~regout ),
	.datad(\bgpbsy_rdreg~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\ufm_drclk~0_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \ufm_drclk~0 .lut_mask = "0080";
defparam \ufm_drclk~0 .operation_mode = "normal";
defparam \ufm_drclk~0 .output_mode = "comb_only";
defparam \ufm_drclk~0 .register_cascade_mode = "off";
defparam \ufm_drclk~0 .sum_lutc_input = "datac";
defparam \ufm_drclk~0 .synch_mode = "off";

maxv_lcell start_din_reg(
	.clk(scl),
	.dataa(\stage_cntr|auto_generated|counter2a[1]~regout ),
	.datab(\stage_cntr|auto_generated|counter2a[0]~regout ),
	.datac(\rd_wr_reg~regout ),
	.datad(\cmpr4|auto_generated|aneb_result_wire[0]~combout ),
	.aclr(\wire_din_en_reg_clrn~0_combout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\start_din_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam start_din_reg.lut_mask = "0008";
defparam start_din_reg.operation_mode = "normal";
defparam start_din_reg.output_mode = "reg_only";
defparam start_din_reg.register_cascade_mode = "off";
defparam start_din_reg.sum_lutc_input = "datac";
defparam start_din_reg.synch_mode = "off";
defparam start_din_reg.x_on_violation = "off";

maxv_lcell \ufm_drclk~1 (
	.clk(gnd),
	.dataa(scl),
	.datab(\ufm_drclk~0_combout ),
	.datac(\start_din_reg~regout ),
	.datad(\rd_wr_reg~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\ufm_drclk~1_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \ufm_drclk~1 .lut_mask = "88a8";
defparam \ufm_drclk~1 .operation_mode = "normal";
defparam \ufm_drclk~1 .output_mode = "comb_only";
defparam \ufm_drclk~1 .register_cascade_mode = "off";
defparam \ufm_drclk~1 .sum_lutc_input = "datac";
defparam \ufm_drclk~1 .synch_mode = "off";

maxv_lcell start_datpd_reg(
	.clk(ufm_osc),
	.dataa(\ena_write_reg~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(\end_write_reg2~regout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\start_datpd_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam start_datpd_reg.lut_mask = "aaaa";
defparam start_datpd_reg.operation_mode = "normal";
defparam start_datpd_reg.output_mode = "reg_only";
defparam start_datpd_reg.register_cascade_mode = "off";
defparam start_datpd_reg.sum_lutc_input = "datac";
defparam start_datpd_reg.synch_mode = "off";
defparam start_datpd_reg.x_on_violation = "off";

maxv_lcell \ufm_drclk~2 (
	.clk(gnd),
	.dataa(\ufm_drclk~1_combout ),
	.datab(ufm_osc),
	.datac(\start_datpd_reg~regout ),
	.datad(\end_datpd_reg~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\ufm_drclk~2_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \ufm_drclk~2 .lut_mask = "aaea";
defparam \ufm_drclk~2 .operation_mode = "normal";
defparam \ufm_drclk~2 .output_mode = "comb_only";
defparam \ufm_drclk~2 .register_cascade_mode = "off";
defparam \ufm_drclk~2 .sum_lutc_input = "datac";
defparam \ufm_drclk~2 .synch_mode = "off";

maxv_lcell drshft_reg(
	.clk(!scl),
	.dataa(\rd_wr_reg~regout ),
	.datab(\ncount8~0_combout ),
	.datac(vcc),
	.datad(vcc),
	.aclr(\stop_det_da_reg2~regout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\drshft_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam drshft_reg.lut_mask = "8888";
defparam drshft_reg.operation_mode = "normal";
defparam drshft_reg.output_mode = "reg_only";
defparam drshft_reg.register_cascade_mode = "off";
defparam drshft_reg.sum_lutc_input = "datac";
defparam drshft_reg.synch_mode = "off";
defparam drshft_reg.x_on_violation = "off";

maxv_lcell a0_dly_reg(
	.clk(!scl),
	.dataa(\dev_add_reg[0]~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\a0_dly_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam a0_dly_reg.lut_mask = "aaaa";
defparam a0_dly_reg.operation_mode = "normal";
defparam a0_dly_reg.output_mode = "reg_only";
defparam a0_dly_reg.register_cascade_mode = "off";
defparam a0_dly_reg.sum_lutc_input = "datac";
defparam a0_dly_reg.synch_mode = "off";
defparam a0_dly_reg.x_on_violation = "off";

maxv_lcell \comb~3 (
	.clk(gnd),
	.dataa(vcc),
	.datab(vcc),
	.datac(\rd_wr_reg~regout ),
	.datad(\stage_cntr|auto_generated|counter2a[1]~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\comb~3_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \comb~3 .lut_mask = "000f";
defparam \comb~3 .operation_mode = "normal";
defparam \comb~3 .output_mode = "comb_only";
defparam \comb~3 .register_cascade_mode = "off";
defparam \comb~3 .sum_lutc_input = "datac";
defparam \comb~3 .synch_mode = "off";

maxv_lcell memadd_shft_reg(
	.clk(!scl),
	.dataa(\memadd_shft_reg~regout ),
	.datab(\comb~3_combout ),
	.datac(\ncount8~0_combout ),
	.datad(\stage_cntr|auto_generated|counter2a[0]~regout ),
	.aclr(\comb~0_combout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\memadd_shft_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam memadd_shft_reg.lut_mask = "aaea";
defparam memadd_shft_reg.operation_mode = "normal";
defparam memadd_shft_reg.output_mode = "reg_only";
defparam memadd_shft_reg.register_cascade_mode = "off";
defparam memadd_shft_reg.sum_lutc_input = "datac";
defparam memadd_shft_reg.synch_mode = "off";
defparam memadd_shft_reg.x_on_violation = "off";

maxv_lcell add_en_reg(
	.clk(!scl),
	.dataa(\memadd_shft_reg~regout ),
	.datab(vcc),
	.datac(\rd_wr_reg~regout ),
	.datad(\cmpr4|auto_generated|aneb_result_wire[0]~combout ),
	.aclr(\comb~0_combout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\add_en_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam add_en_reg.lut_mask = "000a";
defparam add_en_reg.operation_mode = "normal";
defparam add_en_reg.output_mode = "reg_only";
defparam add_en_reg.register_cascade_mode = "off";
defparam add_en_reg.sum_lutc_input = "datac";
defparam add_en_reg.synch_mode = "off";
defparam add_en_reg.x_on_violation = "off";

maxv_lcell end_memadd_reg(
	.clk(!scl),
	.dataa(\end_memadd_reg~regout ),
	.datab(\wire_din_en_reg_ena~0_combout ),
	.datac(\ncount8~0_combout ),
	.datad(vcc),
	.aclr(\comb~0_combout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\end_memadd_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam end_memadd_reg.lut_mask = "eaea";
defparam end_memadd_reg.operation_mode = "normal";
defparam end_memadd_reg.output_mode = "reg_only";
defparam end_memadd_reg.register_cascade_mode = "off";
defparam end_memadd_reg.sum_lutc_input = "datac";
defparam end_memadd_reg.synch_mode = "off";
defparam end_memadd_reg.x_on_violation = "off";

maxv_lcell \ufm_ardin~0 (
	.clk(gnd),
	.dataa(sda),
	.datab(vcc),
	.datac(vcc),
	.datad(\end_memadd_reg~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\ufm_ardin~0_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \ufm_ardin~0 .lut_mask = "00aa";
defparam \ufm_ardin~0 .operation_mode = "normal";
defparam \ufm_ardin~0 .output_mode = "comb_only";
defparam \ufm_ardin~0 .register_cascade_mode = "off";
defparam \ufm_ardin~0 .sum_lutc_input = "datac";
defparam \ufm_ardin~0 .synch_mode = "off";

maxv_lcell ufm_ardin(
	.clk(gnd),
	.dataa(\a0_dly_reg~regout ),
	.datab(\add_en_reg~regout ),
	.datac(\ufm_ardin~0_combout ),
	.datad(\ack_sa_reg~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\ufm_ardin~combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam ufm_ardin.lut_mask = "eac0";
defparam ufm_ardin.operation_mode = "normal";
defparam ufm_ardin.output_mode = "comb_only";
defparam ufm_ardin.register_cascade_mode = "off";
defparam ufm_ardin.sum_lutc_input = "datac";
defparam ufm_ardin.synch_mode = "off";

maxv_lcell gen_cntr2_reg(
	.clk(!scl),
	.dataa(\general_cntr|auto_generated|counter2a[2]~regout ),
	.datab(\stage_cntr|auto_generated|counter2a[1]~regout ),
	.datac(\stage_cntr|auto_generated|counter2a[0]~regout ),
	.datad(vcc),
	.aclr(\comb~0_combout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\gen_cntr2_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam gen_cntr2_reg.lut_mask = "a8a8";
defparam gen_cntr2_reg.operation_mode = "normal";
defparam gen_cntr2_reg.output_mode = "reg_only";
defparam gen_cntr2_reg.register_cascade_mode = "off";
defparam gen_cntr2_reg.sum_lutc_input = "datac";
defparam gen_cntr2_reg.synch_mode = "off";
defparam gen_cntr2_reg.x_on_violation = "off";

maxv_lcell start_memadd_reg(
	.clk(scl),
	.dataa(\start_memadd_reg~regout ),
	.datab(\ack_sa_reg~regout ),
	.datac(vcc),
	.datad(\rd_wr_reg~regout ),
	.aclr(\comb~0_combout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\start_memadd_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam start_memadd_reg.lut_mask = "aaee";
defparam start_memadd_reg.operation_mode = "normal";
defparam start_memadd_reg.output_mode = "reg_only";
defparam start_memadd_reg.register_cascade_mode = "off";
defparam start_memadd_reg.sum_lutc_input = "datac";
defparam start_memadd_reg.synch_mode = "off";
defparam start_memadd_reg.x_on_violation = "off";

maxv_lcell do_memadd_reg(
	.clk(ufm_osc),
	.dataa(\start_memadd_reg~regout ),
	.datab(vcc),
	.datac(\end_memadd_reg~regout ),
	.datad(\cmpr4|auto_generated|aneb_result_wire[0]~combout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\do_memadd_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam do_memadd_reg.lut_mask = "000a";
defparam do_memadd_reg.operation_mode = "normal";
defparam do_memadd_reg.output_mode = "reg_only";
defparam do_memadd_reg.register_cascade_mode = "off";
defparam do_memadd_reg.sum_lutc_input = "datac";
defparam do_memadd_reg.synch_mode = "off";
defparam do_memadd_reg.x_on_violation = "off";

maxv_lcell do_memadd_reg2(
	.clk(ufm_osc),
	.dataa(\do_memadd_reg~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\do_memadd_reg2~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam do_memadd_reg2.lut_mask = "aaaa";
defparam do_memadd_reg2.operation_mode = "normal";
defparam do_memadd_reg2.output_mode = "reg_only";
defparam do_memadd_reg2.register_cascade_mode = "off";
defparam do_memadd_reg2.sum_lutc_input = "datac";
defparam do_memadd_reg2.synch_mode = "off";
defparam do_memadd_reg2.x_on_violation = "off";

maxv_lcell \ufm_arclk~0 (
	.clk(gnd),
	.dataa(scl),
	.datab(vcc),
	.datac(vcc),
	.datad(\rd_wr_reg~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\ufm_arclk~0_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \ufm_arclk~0 .lut_mask = "00aa";
defparam \ufm_arclk~0 .operation_mode = "normal";
defparam \ufm_arclk~0 .output_mode = "comb_only";
defparam \ufm_arclk~0 .register_cascade_mode = "off";
defparam \ufm_arclk~0 .sum_lutc_input = "datac";
defparam \ufm_arclk~0 .synch_mode = "off";

maxv_lcell \sda_oe~0 (
	.clk(gnd),
	.dataa(\rd_wr_reg~regout ),
	.datab(\stage_cntr|auto_generated|counter2a[1]~regout ),
	.datac(\stage_cntr|auto_generated|counter2a[0]~regout ),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\sda_oe~0_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \sda_oe~0 .lut_mask = "a8a8";
defparam \sda_oe~0 .operation_mode = "normal";
defparam \sda_oe~0 .output_mode = "comb_only";
defparam \sda_oe~0 .register_cascade_mode = "off";
defparam \sda_oe~0 .sum_lutc_input = "datac";
defparam \sda_oe~0 .synch_mode = "off";

maxv_lcell ufm_arclk(
	.clk(gnd),
	.dataa(\gen_cntr2_reg~regout ),
	.datab(\do_memadd_reg2~regout ),
	.datac(\ufm_arclk~0_combout ),
	.datad(\sda_oe~0_combout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\ufm_arclk~combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam ufm_arclk.lut_mask = "eac0";
defparam ufm_arclk.operation_mode = "normal";
defparam ufm_arclk.output_mode = "comb_only";
defparam ufm_arclk.register_cascade_mode = "off";
defparam ufm_arclk.sum_lutc_input = "datac";
defparam ufm_arclk.synch_mode = "off";

maxv_lcell ufm_arshft(
	.clk(gnd),
	.dataa(\memadd_shft_reg~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(\end_memadd_reg~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\ufm_arshft~combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam ufm_arshft.lut_mask = "00aa";
defparam ufm_arshft.operation_mode = "normal";
defparam ufm_arshft.output_mode = "comb_only";
defparam ufm_arshft.register_cascade_mode = "off";
defparam ufm_arshft.sum_lutc_input = "datac";
defparam ufm_arshft.synch_mode = "off";

maxv_lcell \ufm_program~0_wirecell (
	.clk(gnd),
	.dataa(\ufm_program~0_combout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\ufm_program~0_wirecell_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \ufm_program~0_wirecell .lut_mask = "5555";
defparam \ufm_program~0_wirecell .operation_mode = "normal";
defparam \ufm_program~0_wirecell .output_mode = "comb_only";
defparam \ufm_program~0_wirecell .register_cascade_mode = "off";
defparam \ufm_program~0_wirecell .sum_lutc_input = "datac";
defparam \ufm_program~0_wirecell .synch_mode = "off";

maxv_lcell \start_er_reg~_wirecell (
	.clk(gnd),
	.dataa(\start_er_reg~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\start_er_reg~_wirecell_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \start_er_reg~_wirecell .lut_mask = "5555";
defparam \start_er_reg~_wirecell .operation_mode = "normal";
defparam \start_er_reg~_wirecell .output_mode = "comb_only";
defparam \start_er_reg~_wirecell .register_cascade_mode = "off";
defparam \start_er_reg~_wirecell .sum_lutc_input = "datac";
defparam \start_er_reg~_wirecell .synch_mode = "off";

maxv_lcell drdout_reg(
	.clk(!scl),
	.dataa(wire_maxii_ufm_block1_drdout),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\drdout_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam drdout_reg.lut_mask = "aaaa";
defparam drdout_reg.operation_mode = "normal";
defparam drdout_reg.output_mode = "reg_only";
defparam drdout_reg.register_cascade_mode = "off";
defparam drdout_reg.sum_lutc_input = "datac";
defparam drdout_reg.synch_mode = "off";
defparam drdout_reg.x_on_violation = "off";

maxv_lcell \wire_read_nack_reg_ena~0 (
	.clk(gnd),
	.dataa(\stage_cntr|auto_generated|counter2a[0]~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(\stage_cntr|auto_generated|counter2a[1]~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\wire_read_nack_reg_ena~0_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \wire_read_nack_reg_ena~0 .lut_mask = "00aa";
defparam \wire_read_nack_reg_ena~0 .operation_mode = "normal";
defparam \wire_read_nack_reg_ena~0 .output_mode = "comb_only";
defparam \wire_read_nack_reg_ena~0 .register_cascade_mode = "off";
defparam \wire_read_nack_reg_ena~0 .sum_lutc_input = "datac";
defparam \wire_read_nack_reg_ena~0 .synch_mode = "off";

maxv_lcell read_nack_reg(
	.clk(scl),
	.dataa(sda),
	.datab(\read_nack_reg~regout ),
	.datac(\wire_read_nack_reg_ena~0_combout ),
	.datad(\ncount8~0_combout ),
	.aclr(\comb~0_combout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\read_nack_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam read_nack_reg.lut_mask = "accc";
defparam read_nack_reg.operation_mode = "normal";
defparam read_nack_reg.output_mode = "reg_only";
defparam read_nack_reg.register_cascade_mode = "off";
defparam read_nack_reg.sum_lutc_input = "datac";
defparam read_nack_reg.synch_mode = "off";
defparam read_nack_reg.x_on_violation = "off";

maxv_lcell read_oe_reg(
	.clk(!scl),
	.dataa(\ncount8~0_combout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(\comb~0_combout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\read_oe_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam read_oe_reg.lut_mask = "aaaa";
defparam read_oe_reg.operation_mode = "normal";
defparam read_oe_reg.output_mode = "reg_only";
defparam read_oe_reg.register_cascade_mode = "off";
defparam read_oe_reg.sum_lutc_input = "datac";
defparam read_oe_reg.synch_mode = "off";
defparam read_oe_reg.x_on_violation = "off";

maxv_lcell \sda_oe~1 (
	.clk(gnd),
	.dataa(\sda_oe~0_combout ),
	.datab(\bgpbsy_rdreg~regout ),
	.datac(\read_nack_reg~regout ),
	.datad(\read_oe_reg~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\sda_oe~1_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \sda_oe~1 .lut_mask = "0002";
defparam \sda_oe~1 .operation_mode = "normal";
defparam \sda_oe~1 .output_mode = "comb_only";
defparam \sda_oe~1 .register_cascade_mode = "off";
defparam \sda_oe~1 .sum_lutc_input = "datac";
defparam \sda_oe~1 .synch_mode = "off";

maxv_lcell ack_ma_reg(
	.clk(!scl),
	.dataa(\wire_din_en_reg_ena~0_combout ),
	.datab(\ncount8~0_combout ),
	.datac(vcc),
	.datad(\cmpr4|auto_generated|aneb_result_wire[0]~combout ),
	.aclr(\comb~0_combout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\ack_ma_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam ack_ma_reg.lut_mask = "0088";
defparam ack_ma_reg.operation_mode = "normal";
defparam ack_ma_reg.output_mode = "reg_only";
defparam ack_ma_reg.register_cascade_mode = "off";
defparam ack_ma_reg.sum_lutc_input = "datac";
defparam ack_ma_reg.synch_mode = "off";
defparam ack_ma_reg.x_on_violation = "off";

maxv_lcell bgpend_det_reg(
	.clk(!wire_maxii_ufm_block1_bgpbusy),
	.dataa(\bgpbsy_rdreg~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(vcc),
	.aclr(\stop_det_da_reg2~regout ),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\bgpend_det_reg~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam bgpend_det_reg.lut_mask = "aaaa";
defparam bgpend_det_reg.operation_mode = "normal";
defparam bgpend_det_reg.output_mode = "reg_only";
defparam bgpend_det_reg.register_cascade_mode = "off";
defparam bgpend_det_reg.sum_lutc_input = "datac";
defparam bgpend_det_reg.synch_mode = "off";
defparam bgpend_det_reg.x_on_violation = "off";

endmodule

module i2c_CORE_a_graycounter (
	clock,
	ena_write_reg,
	end_write_reg2,
	counter2a_3,
	counter2a_2,
	counter2a_1,
	counter2a_0,
	data_pad_complete,
	clk_en)/* synthesis synthesis_greybox=0 */;
input 	clock;
input 	ena_write_reg;
input 	end_write_reg2;
output 	counter2a_3;
output 	counter2a_2;
output 	counter2a_1;
output 	counter2a_0;
input 	data_pad_complete;
input 	clk_en;

wire gnd;
wire vcc;
wire unknown;

assign gnd = 1'b0;
assign vcc = 1'b1;
// unknown value (1'bx) is not needed for this tool. Default to 1'b0
assign unknown = 1'b0;



i2c_CORE_a_graycounter_1sf auto_generated(
	.clock(clock),
	.ena_write_reg(ena_write_reg),
	.end_write_reg2(end_write_reg2),
	.counter2a_3(counter2a_3),
	.counter2a_2(counter2a_2),
	.counter2a_1(counter2a_1),
	.counter2a_0(counter2a_0),
	.data_pad_complete(data_pad_complete),
	.clk_en(clk_en));

endmodule

module i2c_CORE_a_graycounter_1sf (
	clock,
	ena_write_reg,
	end_write_reg2,
	counter2a_3,
	counter2a_2,
	counter2a_1,
	counter2a_0,
	data_pad_complete,
	clk_en)/* synthesis synthesis_greybox=0 */;
input 	clock;
input 	ena_write_reg;
input 	end_write_reg2;
output 	counter2a_3;
output 	counter2a_2;
output 	counter2a_1;
output 	counter2a_0;
input 	data_pad_complete;
input 	clk_en;

wire gnd;
wire vcc;
wire unknown;

assign gnd = 1'b0;
assign vcc = 1'b1;
// unknown value (1'bx) is not needed for this tool. Default to 1'b0
assign unknown = 1'b0;

wire \parity1~regout ;
wire \cntr_cout[2]~combout ;
wire \_~0_combout ;
wire \_~1_combout ;


maxv_lcell \counter2a[3] (
	.clk(clock),
	.dataa(counter2a_3),
	.datab(data_pad_complete),
	.datac(\cntr_cout[2]~combout ),
	.datad(ena_write_reg),
	.aclr(end_write_reg2),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(counter2a_3),
	.cout(),
	.cout0(),
	.cout1());
defparam \counter2a[3] .lut_mask = "a9aa";
defparam \counter2a[3] .operation_mode = "normal";
defparam \counter2a[3] .output_mode = "reg_only";
defparam \counter2a[3] .register_cascade_mode = "off";
defparam \counter2a[3] .sum_lutc_input = "datac";
defparam \counter2a[3] .synch_mode = "off";
defparam \counter2a[3] .x_on_violation = "off";

maxv_lcell \counter2a[2] (
	.clk(clock),
	.dataa(counter2a_2),
	.datab(counter2a_1),
	.datac(clk_en),
	.datad(\_~0_combout ),
	.aclr(end_write_reg2),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(counter2a_2),
	.cout(),
	.cout0(),
	.cout1());
defparam \counter2a[2] .lut_mask = "6aaa";
defparam \counter2a[2] .operation_mode = "normal";
defparam \counter2a[2] .output_mode = "reg_only";
defparam \counter2a[2] .register_cascade_mode = "off";
defparam \counter2a[2] .sum_lutc_input = "datac";
defparam \counter2a[2] .synch_mode = "off";
defparam \counter2a[2] .x_on_violation = "off";

maxv_lcell \counter2a[1] (
	.clk(clock),
	.dataa(counter2a_1),
	.datab(\_~1_combout ),
	.datac(data_pad_complete),
	.datad(ena_write_reg),
	.aclr(end_write_reg2),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(counter2a_1),
	.cout(),
	.cout0(),
	.cout1());
defparam \counter2a[1] .lut_mask = "06aa";
defparam \counter2a[1] .operation_mode = "normal";
defparam \counter2a[1] .output_mode = "reg_only";
defparam \counter2a[1] .register_cascade_mode = "off";
defparam \counter2a[1] .sum_lutc_input = "datac";
defparam \counter2a[1] .synch_mode = "off";
defparam \counter2a[1] .x_on_violation = "off";

maxv_lcell \counter2a[0] (
	.clk(clock),
	.dataa(counter2a_0),
	.datab(\parity1~regout ),
	.datac(data_pad_complete),
	.datad(ena_write_reg),
	.aclr(end_write_reg2),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(counter2a_0),
	.cout(),
	.cout0(),
	.cout1());
defparam \counter2a[0] .lut_mask = "09aa";
defparam \counter2a[0] .operation_mode = "normal";
defparam \counter2a[0] .output_mode = "reg_only";
defparam \counter2a[0] .register_cascade_mode = "off";
defparam \counter2a[0] .sum_lutc_input = "datac";
defparam \counter2a[0] .synch_mode = "off";
defparam \counter2a[0] .x_on_violation = "off";

maxv_lcell parity1(
	.clk(clock),
	.dataa(counter2a_1),
	.datab(counter2a_0),
	.datac(counter2a_3),
	.datad(counter2a_2),
	.aclr(end_write_reg2),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(clk_en),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\parity1~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam parity1.lut_mask = "9669";
defparam parity1.operation_mode = "normal";
defparam parity1.output_mode = "reg_only";
defparam parity1.register_cascade_mode = "off";
defparam parity1.sum_lutc_input = "datac";
defparam parity1.synch_mode = "off";
defparam parity1.x_on_violation = "off";

maxv_lcell \cntr_cout[2] (
	.clk(gnd),
	.dataa(counter2a_1),
	.datab(counter2a_0),
	.datac(vcc),
	.datad(\parity1~regout ),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\cntr_cout[2]~combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \cntr_cout[2] .lut_mask = "eeff";
defparam \cntr_cout[2] .operation_mode = "normal";
defparam \cntr_cout[2] .output_mode = "comb_only";
defparam \cntr_cout[2] .register_cascade_mode = "off";
defparam \cntr_cout[2] .sum_lutc_input = "datac";
defparam \cntr_cout[2] .synch_mode = "off";

maxv_lcell \_~0 (
	.clk(gnd),
	.dataa(\parity1~regout ),
	.datab(vcc),
	.datac(vcc),
	.datad(counter2a_0),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\_~0_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \_~0 .lut_mask = "00aa";
defparam \_~0 .operation_mode = "normal";
defparam \_~0 .output_mode = "comb_only";
defparam \_~0 .register_cascade_mode = "off";
defparam \_~0 .sum_lutc_input = "datac";
defparam \_~0 .synch_mode = "off";

maxv_lcell \_~1 (
	.clk(gnd),
	.dataa(counter2a_0),
	.datab(\parity1~regout ),
	.datac(vcc),
	.datad(vcc),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\_~1_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \_~1 .lut_mask = "8888";
defparam \_~1 .operation_mode = "normal";
defparam \_~1 .output_mode = "comb_only";
defparam \_~1 .register_cascade_mode = "off";
defparam \_~1 .sum_lutc_input = "datac";
defparam \_~1 .synch_mode = "off";

endmodule

module i2c_CORE_a_graycounter_1 (
	stop_det_da_reg2,
	clock,
	counter2a_0,
	counter2a_1,
	clk_en)/* synthesis synthesis_greybox=0 */;
input 	stop_det_da_reg2;
input 	clock;
output 	counter2a_0;
output 	counter2a_1;
input 	clk_en;

wire gnd;
wire vcc;
wire unknown;

assign gnd = 1'b0;
assign vcc = 1'b1;
// unknown value (1'bx) is not needed for this tool. Default to 1'b0
assign unknown = 1'b0;



i2c_CORE_a_graycounter_vrf auto_generated(
	.stop_det_da_reg2(stop_det_da_reg2),
	.clock(clock),
	.counter2a_0(counter2a_0),
	.counter2a_1(counter2a_1),
	.clk_en(clk_en));

endmodule

module i2c_CORE_a_graycounter_vrf (
	stop_det_da_reg2,
	clock,
	counter2a_0,
	counter2a_1,
	clk_en)/* synthesis synthesis_greybox=0 */;
input 	stop_det_da_reg2;
input 	clock;
output 	counter2a_0;
output 	counter2a_1;
input 	clk_en;

wire gnd;
wire vcc;
wire unknown;

assign gnd = 1'b0;
assign vcc = 1'b1;
// unknown value (1'bx) is not needed for this tool. Default to 1'b0
assign unknown = 1'b0;

wire \parity1~regout ;


maxv_lcell \counter2a[0] (
	.clk(clock),
	.dataa(counter2a_0),
	.datab(\parity1~regout ),
	.datac(vcc),
	.datad(vcc),
	.aclr(stop_det_da_reg2),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(clk_en),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(counter2a_0),
	.cout(),
	.cout0(),
	.cout1());
defparam \counter2a[0] .lut_mask = "9999";
defparam \counter2a[0] .operation_mode = "normal";
defparam \counter2a[0] .output_mode = "reg_only";
defparam \counter2a[0] .register_cascade_mode = "off";
defparam \counter2a[0] .sum_lutc_input = "datac";
defparam \counter2a[0] .synch_mode = "off";
defparam \counter2a[0] .x_on_violation = "off";

maxv_lcell \counter2a[1] (
	.clk(clock),
	.dataa(counter2a_1),
	.datab(\parity1~regout ),
	.datac(vcc),
	.datad(vcc),
	.aclr(stop_det_da_reg2),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(clk_en),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(counter2a_1),
	.cout(),
	.cout0(),
	.cout1());
defparam \counter2a[1] .lut_mask = "6666";
defparam \counter2a[1] .operation_mode = "normal";
defparam \counter2a[1] .output_mode = "reg_only";
defparam \counter2a[1] .register_cascade_mode = "off";
defparam \counter2a[1] .sum_lutc_input = "datac";
defparam \counter2a[1] .synch_mode = "off";
defparam \counter2a[1] .x_on_violation = "off";

maxv_lcell parity1(
	.clk(clock),
	.dataa(vcc),
	.datab(vcc),
	.datac(counter2a_1),
	.datad(counter2a_0),
	.aclr(stop_det_da_reg2),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(clk_en),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\parity1~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam parity1.lut_mask = "f00f";
defparam parity1.operation_mode = "normal";
defparam parity1.output_mode = "reg_only";
defparam parity1.register_cascade_mode = "off";
defparam parity1.sum_lutc_input = "datac";
defparam parity1.synch_mode = "off";
defparam parity1.x_on_violation = "off";

endmodule

module i2c_CORE_a_graycounter_2 (
	counter2a_2,
	counter2a_3,
	counter2a_0,
	counter2a_1,
	comb,
	clk_en,
	clock)/* synthesis synthesis_greybox=0 */;
output 	counter2a_2;
output 	counter2a_3;
output 	counter2a_0;
output 	counter2a_1;
input 	comb;
input 	clk_en;
input 	clock;

wire gnd;
wire vcc;
wire unknown;

assign gnd = 1'b0;
assign vcc = 1'b1;
// unknown value (1'bx) is not needed for this tool. Default to 1'b0
assign unknown = 1'b0;



i2c_CORE_a_graycounter_1sf_1 auto_generated(
	.counter2a_2(counter2a_2),
	.counter2a_3(counter2a_3),
	.counter2a_0(counter2a_0),
	.counter2a_1(counter2a_1),
	.comb(comb),
	.clk_en(clk_en),
	.clock(clock));

endmodule

module i2c_CORE_a_graycounter_1sf_1 (
	counter2a_2,
	counter2a_3,
	counter2a_0,
	counter2a_1,
	comb,
	clk_en,
	clock)/* synthesis synthesis_greybox=0 */;
output 	counter2a_2;
output 	counter2a_3;
output 	counter2a_0;
output 	counter2a_1;
input 	comb;
input 	clk_en;
input 	clock;

wire gnd;
wire vcc;
wire unknown;

assign gnd = 1'b0;
assign vcc = 1'b1;
// unknown value (1'bx) is not needed for this tool. Default to 1'b0
assign unknown = 1'b0;

wire \parity1~regout ;


maxv_lcell \counter2a[2] (
	.clk(clock),
	.dataa(counter2a_2),
	.datab(counter2a_0),
	.datac(counter2a_1),
	.datad(\parity1~regout ),
	.aclr(comb),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(clk_en),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(counter2a_2),
	.cout(),
	.cout0(),
	.cout1());
defparam \counter2a[2] .lut_mask = "9aaa";
defparam \counter2a[2] .operation_mode = "normal";
defparam \counter2a[2] .output_mode = "reg_only";
defparam \counter2a[2] .register_cascade_mode = "off";
defparam \counter2a[2] .sum_lutc_input = "datac";
defparam \counter2a[2] .synch_mode = "off";
defparam \counter2a[2] .x_on_violation = "off";

maxv_lcell \counter2a[3] (
	.clk(clock),
	.dataa(\parity1~regout ),
	.datab(counter2a_1),
	.datac(counter2a_0),
	.datad(counter2a_3),
	.aclr(comb),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(clk_en),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(counter2a_3),
	.cout(),
	.cout0(),
	.cout1());
defparam \counter2a[3] .lut_mask = "fd02";
defparam \counter2a[3] .operation_mode = "normal";
defparam \counter2a[3] .output_mode = "reg_only";
defparam \counter2a[3] .register_cascade_mode = "off";
defparam \counter2a[3] .sum_lutc_input = "datac";
defparam \counter2a[3] .synch_mode = "off";
defparam \counter2a[3] .x_on_violation = "off";

maxv_lcell \counter2a[0] (
	.clk(clock),
	.dataa(counter2a_0),
	.datab(\parity1~regout ),
	.datac(vcc),
	.datad(vcc),
	.aclr(comb),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(clk_en),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(counter2a_0),
	.cout(),
	.cout0(),
	.cout1());
defparam \counter2a[0] .lut_mask = "9999";
defparam \counter2a[0] .operation_mode = "normal";
defparam \counter2a[0] .output_mode = "reg_only";
defparam \counter2a[0] .register_cascade_mode = "off";
defparam \counter2a[0] .sum_lutc_input = "datac";
defparam \counter2a[0] .synch_mode = "off";
defparam \counter2a[0] .x_on_violation = "off";

maxv_lcell \counter2a[1] (
	.clk(clock),
	.dataa(vcc),
	.datab(counter2a_1),
	.datac(counter2a_0),
	.datad(\parity1~regout ),
	.aclr(comb),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(clk_en),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(counter2a_1),
	.cout(),
	.cout0(),
	.cout1());
defparam \counter2a[1] .lut_mask = "3ccc";
defparam \counter2a[1] .operation_mode = "normal";
defparam \counter2a[1] .output_mode = "reg_only";
defparam \counter2a[1] .register_cascade_mode = "off";
defparam \counter2a[1] .sum_lutc_input = "datac";
defparam \counter2a[1] .synch_mode = "off";
defparam \counter2a[1] .x_on_violation = "off";

maxv_lcell parity1(
	.clk(clock),
	.dataa(counter2a_2),
	.datab(counter2a_1),
	.datac(counter2a_3),
	.datad(counter2a_0),
	.aclr(comb),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(clk_en),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\parity1~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam parity1.lut_mask = "9669";
defparam parity1.operation_mode = "normal";
defparam parity1.output_mode = "reg_only";
defparam parity1.register_cascade_mode = "off";
defparam parity1.sum_lutc_input = "datac";
defparam parity1.synch_mode = "off";
defparam parity1.x_on_violation = "off";

endmodule

module i2c_CORE_a_graycounter_3 (
	counter2a_1,
	counter2a_0,
	comb,
	clk_en,
	clock)/* synthesis synthesis_greybox=0 */;
output 	counter2a_1;
output 	counter2a_0;
input 	comb;
input 	clk_en;
input 	clock;

wire gnd;
wire vcc;
wire unknown;

assign gnd = 1'b0;
assign vcc = 1'b1;
// unknown value (1'bx) is not needed for this tool. Default to 1'b0
assign unknown = 1'b0;



i2c_CORE_a_graycounter_vrf_1 auto_generated(
	.counter2a_1(counter2a_1),
	.counter2a_0(counter2a_0),
	.comb(comb),
	.clk_en(clk_en),
	.clock(clock));

endmodule

module i2c_CORE_a_graycounter_vrf_1 (
	counter2a_1,
	counter2a_0,
	comb,
	clk_en,
	clock)/* synthesis synthesis_greybox=0 */;
output 	counter2a_1;
output 	counter2a_0;
input 	comb;
input 	clk_en;
input 	clock;

wire gnd;
wire vcc;
wire unknown;

assign gnd = 1'b0;
assign vcc = 1'b1;
// unknown value (1'bx) is not needed for this tool. Default to 1'b0
assign unknown = 1'b0;

wire \parity1~regout ;


maxv_lcell \counter2a[1] (
	.clk(!clock),
	.dataa(vcc),
	.datab(counter2a_1),
	.datac(\parity1~regout ),
	.datad(clk_en),
	.aclr(comb),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(counter2a_1),
	.cout(),
	.cout0(),
	.cout1());
defparam \counter2a[1] .lut_mask = "3ccc";
defparam \counter2a[1] .operation_mode = "normal";
defparam \counter2a[1] .output_mode = "reg_only";
defparam \counter2a[1] .register_cascade_mode = "off";
defparam \counter2a[1] .sum_lutc_input = "datac";
defparam \counter2a[1] .synch_mode = "off";
defparam \counter2a[1] .x_on_violation = "off";

maxv_lcell \counter2a[0] (
	.clk(!clock),
	.dataa(counter2a_0),
	.datab(\parity1~regout ),
	.datac(vcc),
	.datad(clk_en),
	.aclr(comb),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(counter2a_0),
	.cout(),
	.cout0(),
	.cout1());
defparam \counter2a[0] .lut_mask = "99aa";
defparam \counter2a[0] .operation_mode = "normal";
defparam \counter2a[0] .output_mode = "reg_only";
defparam \counter2a[0] .register_cascade_mode = "off";
defparam \counter2a[0] .sum_lutc_input = "datac";
defparam \counter2a[0] .synch_mode = "off";
defparam \counter2a[0] .x_on_violation = "off";

maxv_lcell parity1(
	.clk(!clock),
	.dataa(vcc),
	.datab(vcc),
	.datac(counter2a_1),
	.datad(counter2a_0),
	.aclr(comb),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(clk_en),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(),
	.regout(\parity1~regout ),
	.cout(),
	.cout0(),
	.cout1());
defparam parity1.lut_mask = "f00f";
defparam parity1.operation_mode = "normal";
defparam parity1.output_mode = "reg_only";
defparam parity1.register_cascade_mode = "off";
defparam parity1.sum_lutc_input = "datac";
defparam parity1.synch_mode = "off";
defparam parity1.x_on_violation = "off";

endmodule

module i2c_CORE_lpm_compare_1 (
	a1,
	dev_add_reg_1,
	dev_add_reg_5,
	dev_add_reg_3,
	dev_add_reg_6,
	dev_add_reg_4,
	a2,
	dev_add_reg_2,
	aneb_result_wire_0)/* synthesis synthesis_greybox=0 */;
input 	a1;
input 	dev_add_reg_1;
input 	dev_add_reg_5;
input 	dev_add_reg_3;
input 	dev_add_reg_6;
input 	dev_add_reg_4;
input 	a2;
input 	dev_add_reg_2;
output 	aneb_result_wire_0;

wire gnd;
wire vcc;
wire unknown;

assign gnd = 1'b0;
assign vcc = 1'b1;
// unknown value (1'bx) is not needed for this tool. Default to 1'b0
assign unknown = 1'b0;



i2c_CORE_cmpr_f4d auto_generated(
	.a1(a1),
	.dev_add_reg_1(dev_add_reg_1),
	.dev_add_reg_5(dev_add_reg_5),
	.dev_add_reg_3(dev_add_reg_3),
	.dev_add_reg_6(dev_add_reg_6),
	.dev_add_reg_4(dev_add_reg_4),
	.a2(a2),
	.dev_add_reg_2(dev_add_reg_2),
	.aneb_result_wire_0(aneb_result_wire_0));

endmodule

module i2c_CORE_cmpr_f4d (
	a1,
	dev_add_reg_1,
	dev_add_reg_5,
	dev_add_reg_3,
	dev_add_reg_6,
	dev_add_reg_4,
	a2,
	dev_add_reg_2,
	aneb_result_wire_0)/* synthesis synthesis_greybox=0 */;
input 	a1;
input 	dev_add_reg_1;
input 	dev_add_reg_5;
input 	dev_add_reg_3;
input 	dev_add_reg_6;
input 	dev_add_reg_4;
input 	a2;
input 	dev_add_reg_2;
output 	aneb_result_wire_0;

wire gnd;
wire vcc;
wire unknown;

assign gnd = 1'b0;
assign vcc = 1'b1;
// unknown value (1'bx) is not needed for this tool. Default to 1'b0
assign unknown = 1'b0;

wire \data_wire[0]~0_combout ;
wire \aneb_result_wire[0]~0_combout ;


maxv_lcell \aneb_result_wire[0] (
	.clk(gnd),
	.dataa(\data_wire[0]~0_combout ),
	.datab(\aneb_result_wire[0]~0_combout ),
	.datac(a2),
	.datad(dev_add_reg_2),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(aneb_result_wire_0),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \aneb_result_wire[0] .lut_mask = "effe";
defparam \aneb_result_wire[0] .operation_mode = "normal";
defparam \aneb_result_wire[0] .output_mode = "comb_only";
defparam \aneb_result_wire[0] .register_cascade_mode = "off";
defparam \aneb_result_wire[0] .sum_lutc_input = "datac";
defparam \aneb_result_wire[0] .synch_mode = "off";

maxv_lcell \data_wire[0]~0 (
	.clk(gnd),
	.dataa(vcc),
	.datab(vcc),
	.datac(a1),
	.datad(dev_add_reg_1),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\data_wire[0]~0_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \data_wire[0]~0 .lut_mask = "0ff0";
defparam \data_wire[0]~0 .operation_mode = "normal";
defparam \data_wire[0]~0 .output_mode = "comb_only";
defparam \data_wire[0]~0 .register_cascade_mode = "off";
defparam \data_wire[0]~0 .sum_lutc_input = "datac";
defparam \data_wire[0]~0 .synch_mode = "off";

maxv_lcell \aneb_result_wire[0]~0 (
	.clk(gnd),
	.dataa(dev_add_reg_5),
	.datab(dev_add_reg_3),
	.datac(dev_add_reg_6),
	.datad(dev_add_reg_4),
	.aclr(gnd),
	.aload(gnd),
	.sclr(gnd),
	.sload(gnd),
	.ena(vcc),
	.cin(gnd),
	.cin0(gnd),
	.cin1(vcc),
	.inverta(gnd),
	.regcascin(gnd),
	.combout(\aneb_result_wire[0]~0_combout ),
	.regout(),
	.cout(),
	.cout0(),
	.cout1());
defparam \aneb_result_wire[0]~0 .lut_mask = "efff";
defparam \aneb_result_wire[0]~0 .operation_mode = "normal";
defparam \aneb_result_wire[0]~0 .output_mode = "comb_only";
defparam \aneb_result_wire[0]~0 .register_cascade_mode = "off";
defparam \aneb_result_wire[0]~0 .sum_lutc_input = "datac";
defparam \aneb_result_wire[0]~0 .synch_mode = "off";

endmodule
