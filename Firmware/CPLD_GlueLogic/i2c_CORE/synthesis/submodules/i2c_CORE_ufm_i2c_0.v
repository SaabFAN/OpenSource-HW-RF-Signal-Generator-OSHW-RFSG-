//altufm_i2c ACCESS_MODE="READ_WRITE" CBX_AUTO_BLACKBOX="ALL" CBX_SINGLE_OUTPUT_FILE="ON" DEVICE_FAMILY="MAX V" ERASE_METHOD="MEM_ADD" ERASE_TIME=500000000 FIXED_DEVICE_ADD="1010" MEM_ADD_ERASE0="00000000" MEM_ADD_ERASE1="01000000" MEM_PROTECT="FULL" MEMORY_SIZE="4K" OSC_FREQUENCY=180000 PAGE_WRITE_SIZE=16 PORT_GLOBAL_RESET="USED" PROGRAM_TIME=1600000 WRITE_MODE="SINGLE_BYTE" a0 a1 a2 global_reset osc scl sda ALTERA_INTERNAL_OPTIONS=X_ON_VIOLATION_OPTION=OFF;AUTO_CLOCK_ENABLE_RECOGNITION=OFF
//VERSION_BEGIN 18.1 cbx_a_gray2bin 2018:09:12:13:04:24:SJ cbx_a_graycounter 2018:09:12:13:04:24:SJ cbx_altufm_i2c 2018:09:12:13:04:24:SJ cbx_cycloneii 2018:09:12:13:04:24:SJ cbx_lpm_add_sub 2018:09:12:13:04:24:SJ cbx_lpm_compare 2018:09:12:13:04:24:SJ cbx_lpm_counter 2018:09:12:13:04:24:SJ cbx_lpm_decode 2018:09:12:13:04:24:SJ cbx_lpm_mux 2018:09:12:13:04:24:SJ cbx_maxii 2018:09:12:13:04:24:SJ cbx_mgl 2018:09:12:13:10:36:SJ cbx_nadder 2018:09:12:13:04:24:SJ cbx_stratix 2018:09:12:13:04:24:SJ cbx_stratixii 2018:09:12:13:04:24:SJ cbx_util_mgl 2018:09:12:13:04:24:SJ  VERSION_END
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



//synthesis_resources = a_graycounter 4 lpm_compare 3 lut 99 maxv_io 2 maxv_ufm 1 
//synopsys translate_off
`timescale 1 ps / 1 ps
//synopsys translate_on
(* ALTERA_ATTRIBUTE = {"X_ON_VIOLATION_OPTION=OFF;AUTO_CLOCK_ENABLE_RECOGNITION=OFF;suppress_da_rule_internal=c101;suppress_da_rule_internal=c103;suppress_da_rule_internal=c104;suppress_da_rule_internal=c106;suppress_da_rule_internal=r101;suppress_da_rule_internal=s102;suppress_da_rule_internal=s104"} *)
module  i2c_CORE_ufm_i2c_0
	( 
	a0,
	a1,
	a2,
	global_reset,
	osc,
	scl,
	sda) /* synthesis synthesis_clearbox=1 */;
	input   a0;
	input   a1;
	input   a2;
	input   global_reset;
	output   osc;
	inout   scl;
	inout   sda;
`ifndef ALTERA_RESERVED_QIS
// synopsys translate_off
`endif
	tri0   a0;
	tri0   a1;
	tri0   a2;
	tri0   global_reset;
`ifndef ALTERA_RESERVED_QIS
// synopsys translate_on
`endif

	wire  [3:0]   wire_data_pad_cntr_q;
	wire  [1:0]   wire_er_wr_cntr_q;
	wire  [3:0]   wire_general_cntr_q;
	wire  [1:0]   wire_stage_cntr_q;
	reg	a0_dly_reg;
	reg	ack_data_reg;
	wire	wire_ack_data_reg_clrn;
	wire	wire_ack_data_reg_ena;
	reg	ack_ma_reg;
	wire	wire_ack_ma_reg_clrn;
	reg	ack_sa_reg;
	wire	wire_ack_sa_reg_clrn;
	reg	add_en_reg;
	wire	wire_add_en_reg_clrn;
	reg	bgpbsy_rdreg;
	wire	wire_bgpbsy_rdreg_ena;
	reg	bgpend_det_reg;
	reg	busy_dea_reg;
	wire	wire_busy_dea_reg_ena;
	reg	busy_det_reg;
	reg	busy_det_reg2;
	reg	clr_drclk_reg;
	reg	data_suc_reg;
	wire	wire_data_suc_reg_ena;
	reg	[6:0]	dev_add_reg;
	reg	din_en_reg;
	wire	wire_din_en_reg_clrn;
	wire	wire_din_en_reg_ena;
	reg	do_memadd_reg;
	reg	do_memadd_reg2;
	reg	drdout_reg;
	reg	drshft_reg;
	reg	ena_drclk_reg;
	reg	ena_write_reg;
	reg	end_datpd_reg;
	reg	end_din_reg;
	wire	wire_end_din_reg_clrn;
	reg	end_memadd_reg;
	wire	wire_end_memadd_reg_clrn;
	reg	end_write_reg;
	reg	end_write_reg2;
	reg	eradd_match_reg;
	reg	eradd_match_reg2;
	reg	fin_devadd_reg;
	wire	wire_fin_devadd_reg_clrn;
	reg	gcntr_aclr_int_reg;
	reg	gcntr_aclr_reg;
	reg	gcntr_aclr_reg2;
	reg	gen_cntr2_reg;
	wire	wire_gen_cntr2_reg_clrn;
	reg	memadd_shft_reg;
	wire	wire_memadd_shft_reg_clrn;
	wire	[7:0]	wire_rd_addr_reg_d;
	reg	[7:0]	rd_addr_reg;
	wire	[7:0]	wire_rd_addr_reg_ena;
	reg	rd_wr_reg;
	wire	wire_rd_wr_reg_clrn;
	wire	wire_rd_wr_reg_ena;
	reg	reach_cnt9_reg;
	reg	read_nack_reg;
	wire	wire_read_nack_reg_clrn;
	wire	wire_read_nack_reg_ena;
	reg	read_oe_reg;
	wire	wire_read_oe_reg_prn;
	reg	rstart_clr_reg;
	reg	rstart_clr_reg2;
	reg	rstart_det_da_reg;
	reg	rstart_det_da_reg2;
	reg	rstart_det_reg;
	wire	wire_rstart_det_reg_clrn;
	reg	sda_indly_reg;
	reg	sda_indly_reg2;
	reg	start_datpd_reg;
	reg	start_detect_reg;
	wire	wire_start_detect_reg_ena;
	reg	start_din_reg;
	wire	wire_start_din_reg_clrn;
	reg	start_er_reg;
	reg	start_memadd_reg;
	wire	wire_start_memadd_reg_clrn;
	wire	wire_start_memadd_reg_ena;
	reg	start_prog_reg;
	wire	wire_start_prog_reg_clrn;
	wire	wire_start_prog_reg_ena;
	reg	start_rd_reg;
	reg	start_wr_reg;
	wire	wire_start_wr_reg_ena;
	reg	stop_det_da_reg;
	reg	stop_det_da_reg2;
	reg	stop_detect_reg;
	wire	wire_stop_detect_reg_ena;
	reg	stop_rst_reg;
	reg	stop_rst_reg2;
	reg	strd_drclk_reg;
	wire  wire_cmpr4_aeb;
	wire  wire_cmpr6_aeb;
	wire  wire_cmpr7_aeb;
	wire  wire_maxii_io2_combout;
	wire  wire_maxii_io3_combout;
	wire  wire_maxii_ufm_block1_bgpbusy;
	wire  wire_maxii_ufm_block1_busy;
	wire  wire_maxii_ufm_block1_drdout;
	wire  wire_maxii_ufm_block1_osc;
	wire  a0_wire;
	wire  ack_pulse_data;
	wire  ack_pulse_ma;
	wire  ack_pulse_sa;
	wire  ardin_en;
	wire  bgpbusy_detect;
	wire  bgplow;
	wire  busy_deassert;
	wire  busy_det;
	wire  clock_oe;
	wire  clr_rstart;
	wire  count9;
	wire  count_end;
	wire  data_pad_complete;
	wire  data_suc;
	wire  do_add_shft;
	wire  do_mem_add;
	wire  do_read;
	wire  do_write;
	wire  drdin_en;
	wire  end_din_reg_ena;
	wire  end_er_write;
	wire  end_memadd_reg_ena;
	wire  end_write;
	wire  erase_add_match;
	wire  fin_devadd_reg_ena;
	wire  finish_dev_add;
	wire  gen_cntr2;
	wire  memadd_shft_reg_ena;
	wire  ncount8;
	wire oscena;
	wire  reach_count_9;
	wire  read_nack;
	wire  read_oe;
	wire  rnw;
	wire  rstart_detect;
	wire  scl_wire;
	wire  sda_in_delay;
	wire  sda_in_wire;
	wire  sda_oe;
	wire  sda_out_wire;
	wire  slave_add_match;
	wire  start_data_pad;
	wire  start_detect;
	wire  start_prog;
	wire  start_write;
	wire  stop_det_rst;
	wire  stop_detect;
	wire  ufm_arclk;
	wire  ufm_ardin;
	wire  ufm_arshft;
	wire  ufm_bgpbusy;
	wire  ufm_busy;
	wire  ufm_drclk;
	wire  ufm_drdin;
	wire  ufm_drdout;
	wire  ufm_drshft;
	wire  ufm_erase;
	wire  ufm_osc;
	wire  ufm_oscena;
	wire  ufm_program;
	wire  write_prot;
	wire  write_prot_true;

	a_graycounter   data_pad_cntr
	( 
	.aclr(end_write),
	.clk_en((start_write & (~ data_pad_complete))),
	.clock(ufm_osc),
	.q(wire_data_pad_cntr_q),
	.qbin()
	`ifndef FORMAL_VERIFICATION
	// synopsys translate_off
	`endif
	,
	.cnt_en(1'b1),
	.sclr(1'b0),
	.updown(1'b1)
	`ifndef FORMAL_VERIFICATION
	// synopsys translate_on
	`endif
	);
	defparam
		data_pad_cntr.width = 4,
		data_pad_cntr.lpm_type = "a_graycounter";
	a_graycounter   er_wr_cntr
	( 
	.aclr(stop_detect),
	.clk_en((start_prog & (~ ufm_bgpbusy))),
	.clock(end_write),
	.q(wire_er_wr_cntr_q),
	.qbin()
	`ifndef FORMAL_VERIFICATION
	// synopsys translate_off
	`endif
	,
	.cnt_en(1'b1),
	.sclr(1'b0),
	.updown(1'b1)
	`ifndef FORMAL_VERIFICATION
	// synopsys translate_on
	`endif
	);
	defparam
		er_wr_cntr.width = 2,
		er_wr_cntr.lpm_type = "a_graycounter";
	a_graycounter   general_cntr
	( 
	.aclr(((count_end | stop_detect) | rstart_detect)),
	.clk_en((start_detect & (~ bgpbusy_detect))),
	.clock(scl_wire),
	.q(wire_general_cntr_q),
	.qbin()
	`ifndef FORMAL_VERIFICATION
	// synopsys translate_off
	`endif
	,
	.cnt_en(1'b1),
	.sclr(1'b0),
	.updown(1'b1)
	`ifndef FORMAL_VERIFICATION
	// synopsys translate_on
	`endif
	);
	defparam
		general_cntr.width = 4,
		general_cntr.lpm_type = "a_graycounter";
	a_graycounter   stage_cntr
	( 
	.aclr((stop_detect | rstart_detect)),
	.clk_en((((start_detect & count9) & (~ ((rnw & (~ wire_stage_cntr_q[1])) & wire_stage_cntr_q[0]))) & (~ (((~ rnw) & wire_stage_cntr_q[1]) & wire_stage_cntr_q[0])))),
	.clock((~ scl_wire)),
	.q(wire_stage_cntr_q),
	.qbin()
	`ifndef FORMAL_VERIFICATION
	// synopsys translate_off
	`endif
	,
	.cnt_en(1'b1),
	.sclr(1'b0),
	.updown(1'b1)
	`ifndef FORMAL_VERIFICATION
	// synopsys translate_on
	`endif
	);
	defparam
		stage_cntr.width = 2,
		stage_cntr.lpm_type = "a_graycounter";
	// synopsys translate_off
	initial
		a0_dly_reg = 0;
	// synopsys translate_on
	always @ ( negedge scl_wire)
		  a0_dly_reg <= a0_wire;
	// synopsys translate_off
	initial
		ack_data_reg = 0;
	// synopsys translate_on
	always @ ( negedge scl_wire or  negedge wire_ack_data_reg_clrn)
		if (wire_ack_data_reg_clrn == 1'b0) ack_data_reg <= 1'b0;
		else if  (wire_ack_data_reg_ena == 1'b1)   ack_data_reg <= ((((((wire_stage_cntr_q[1] & wire_stage_cntr_q[0]) & (~ ufm_bgpbusy)) & wire_general_cntr_q[3]) & wire_general_cntr_q[2]) & (~ wire_general_cntr_q[1])) & (~ wire_general_cntr_q[0]));
	assign
		wire_ack_data_reg_ena = (((~ write_prot) & slave_add_match) & (~ rnw)),
		wire_ack_data_reg_clrn = (~ (stop_detect | rstart_detect));
	// synopsys translate_off
	initial
		ack_ma_reg = 0;
	// synopsys translate_on
	always @ ( negedge scl_wire or  negedge wire_ack_ma_reg_clrn)
		if (wire_ack_ma_reg_clrn == 1'b0) ack_ma_reg <= 1'b0;
		else  ack_ma_reg <= (((((((slave_add_match & (~ rnw)) & (~ wire_stage_cntr_q[1])) & wire_stage_cntr_q[0]) & wire_general_cntr_q[3]) & wire_general_cntr_q[2]) & (~ wire_general_cntr_q[1])) & (~ wire_general_cntr_q[0]));
	assign
		wire_ack_ma_reg_clrn = (~ (stop_detect | rstart_detect));
	// synopsys translate_off
	initial
		ack_sa_reg = 0;
	// synopsys translate_on
	always @ ( negedge scl_wire or  negedge wire_ack_sa_reg_clrn)
		if (wire_ack_sa_reg_clrn == 1'b0) ack_sa_reg <= 1'b0;
		else  ack_sa_reg <= ((((((((~ ufm_bgpbusy) & slave_add_match) & (~ wire_stage_cntr_q[1])) & (~ wire_stage_cntr_q[0])) & wire_general_cntr_q[3]) & wire_general_cntr_q[2]) & (~ wire_general_cntr_q[1])) & (~ wire_general_cntr_q[0]));
	assign
		wire_ack_sa_reg_clrn = (~ (stop_detect | rstart_detect));
	// synopsys translate_off
	initial
		add_en_reg = 0;
	// synopsys translate_on
	always @ ( negedge scl_wire or  negedge wire_add_en_reg_clrn)
		if (wire_add_en_reg_clrn == 1'b0) add_en_reg <= 1'b0;
		else  add_en_reg <= ((slave_add_match & (~ rnw)) & memadd_shft_reg);
	assign
		wire_add_en_reg_clrn = (~ (stop_detect | rstart_detect));
	// synopsys translate_off
	initial
		bgpbsy_rdreg = 0;
	// synopsys translate_on
	always @ ( negedge ufm_osc or  posedge stop_detect)
		if (stop_detect == 1'b1) bgpbsy_rdreg <= 1'b0;
		else if  (wire_bgpbsy_rdreg_ena == 1'b1)   bgpbsy_rdreg <= ufm_bgpbusy;
	assign
		wire_bgpbsy_rdreg_ena = (((rnw & (~ wire_stage_cntr_q[1])) & wire_stage_cntr_q[0]) & count_end);
	// synopsys translate_off
	initial
		bgpend_det_reg = 0;
	// synopsys translate_on
	always @ ( negedge ufm_bgpbusy or  posedge stop_detect)
		if (stop_detect == 1'b1) bgpend_det_reg <= 1'b0;
		else  bgpend_det_reg <= bgpbusy_detect;
	// synopsys translate_off
	initial
		busy_dea_reg = 0;
	// synopsys translate_on
	always @ ( negedge busy_det or  posedge end_write)
		if (end_write == 1'b1) busy_dea_reg <= 1'b0;
		else if  (wire_busy_dea_reg_ena == 1'b1)   busy_dea_reg <= 1'b1;
	assign
		wire_busy_dea_reg_ena = (ufm_program | ufm_erase);
	// synopsys translate_off
	initial
		busy_det_reg = 0;
	// synopsys translate_on
	always @ ( posedge ufm_osc or  posedge end_write)
		if (end_write == 1'b1) busy_det_reg <= 1'b0;
		else  busy_det_reg <= (((ufm_program | ufm_erase) & ufm_busy) | ((~ (ufm_program | ufm_erase)) & busy_det_reg));
	// synopsys translate_off
	initial
		busy_det_reg2 = 0;
	// synopsys translate_on
	always @ ( posedge ufm_osc or  posedge end_write)
		if (end_write == 1'b1) busy_det_reg2 <= 1'b0;
		else  busy_det_reg2 <= (((ufm_program | ufm_erase) & busy_det_reg) | ((~ (ufm_program | ufm_erase)) & busy_det_reg2));
	// synopsys translate_off
	initial
		clr_drclk_reg = 0;
	// synopsys translate_on
	always @ ( negedge scl_wire)
		  clr_drclk_reg <= ((((~ wire_general_cntr_q[3]) & wire_general_cntr_q[2]) & (~ wire_general_cntr_q[1])) & (~ wire_general_cntr_q[0]));
	// synopsys translate_off
	initial
		data_suc_reg = 0;
	// synopsys translate_on
	always @ ( posedge scl_wire or  posedge end_write)
		if (end_write == 1'b1) data_suc_reg <= 1'b0;
		else if  (wire_data_suc_reg_ena == 1'b1)   data_suc_reg <= 1'b1;
	assign
		wire_data_suc_reg_ena = ((wire_stage_cntr_q[1] & wire_stage_cntr_q[0]) & ack_pulse_data);
	// synopsys translate_off
	initial
		dev_add_reg = 0;
	// synopsys translate_on
	always @ ( posedge scl_wire)
		  dev_add_reg <= {(((start_detect & (~ finish_dev_add)) & dev_add_reg[5]) | ((~ (start_detect & (~ finish_dev_add))) & dev_add_reg[6])), (((start_detect & (~ finish_dev_add)) & dev_add_reg[4]) | ((~ (start_detect & (~ finish_dev_add))) & dev_add_reg[5])), (((start_detect & (~ finish_dev_add)) & dev_add_reg[3]) | ((~ (start_detect & (~ finish_dev_add))) & dev_add_reg[4])), (((start_detect & (~ finish_dev_add)) & dev_add_reg[2]) | ((~ (start_detect & (~ finish_dev_add))) & dev_add_reg[3])), (((start_detect & (~ finish_dev_add)) & dev_add_reg[1]) | ((~ (start_detect & (~ finish_dev_add))) & dev_add_reg[2])), (((start_detect & (~ finish_dev_add)) & dev_add_reg[0]) | ((~ (start_detect & (~ finish_dev_add))) & dev_add_reg[1])), (((start_detect & (~ finish_dev_add)) & sda_in_wire) | ((~ (start_detect & (~ finish_dev_add))) & dev_add_reg[0]))};
	// synopsys translate_off
	initial
		din_en_reg = 0;
	// synopsys translate_on
	always @ ( negedge scl_wire or  negedge wire_din_en_reg_clrn)
		if (wire_din_en_reg_clrn == 1'b0) din_en_reg <= 1'b0;
		else if  (wire_din_en_reg_ena == 1'b1)   din_en_reg <= 1'b1;
	assign
		wire_din_en_reg_ena = ((((slave_add_match & (~ rnw)) & (~ wire_stage_cntr_q[1])) & wire_stage_cntr_q[0]) & count9),
		wire_din_en_reg_clrn = (~ ((end_din_reg | stop_detect) | rstart_detect));
	// synopsys translate_off
	initial
		do_memadd_reg = 0;
	// synopsys translate_on
	always @ ( posedge ufm_osc)
		  do_memadd_reg <= ((slave_add_match & start_memadd_reg) & (~ end_memadd_reg));
	// synopsys translate_off
	initial
		do_memadd_reg2 = 0;
	// synopsys translate_on
	always @ ( posedge ufm_osc)
		  do_memadd_reg2 <= do_memadd_reg;
	// synopsys translate_off
	initial
		drdout_reg = 0;
	// synopsys translate_on
	always @ ( negedge scl_wire)
		  drdout_reg <= ufm_drdout;
	// synopsys translate_off
	initial
		drshft_reg = 0;
	// synopsys translate_on
	always @ ( negedge scl_wire or  posedge stop_detect)
		if (stop_detect == 1'b1) drshft_reg <= {1{1'b1}};
		else  drshft_reg <= (~ (rnw & (~ ncount8)));
	// synopsys translate_off
	initial
		ena_drclk_reg = 0;
	// synopsys translate_on
	always @ ( negedge scl_wire)
		  ena_drclk_reg <= (((wire_general_cntr_q[3] & wire_general_cntr_q[2]) & (~ wire_general_cntr_q[1])) & (~ wire_general_cntr_q[0]));
	// synopsys translate_off
	initial
		ena_write_reg = 0;
	// synopsys translate_on
	always @ ( negedge ufm_osc or  posedge end_write)
		if (end_write == 1'b1) ena_write_reg <= 1'b0;
		else  ena_write_reg <= (((((stop_det_rst & data_suc) | ((~ stop_det_rst) & ena_write_reg)) & (~ write_prot_true)) & (~ ufm_bgpbusy)) & (~ ufm_busy));
	// synopsys translate_off
	initial
		end_datpd_reg = 0;
	// synopsys translate_on
	always @ ( negedge ufm_osc or  posedge end_write)
		if (end_write == 1'b1) end_datpd_reg <= 1'b0;
		else  end_datpd_reg <= data_pad_complete;
	// synopsys translate_off
	initial
		end_din_reg = 0;
	// synopsys translate_on
	always @ ( negedge scl_wire or  negedge wire_end_din_reg_clrn)
		if (wire_end_din_reg_clrn == 1'b0) end_din_reg <= 1'b0;
		else  end_din_reg <= (end_din_reg_ena | ((~ end_din_reg_ena) & end_din_reg));
	assign
		wire_end_din_reg_clrn = (~ (stop_detect | rstart_detect));
	// synopsys translate_off
	initial
		end_memadd_reg = 0;
	// synopsys translate_on
	always @ ( negedge scl_wire or  negedge wire_end_memadd_reg_clrn)
		if (wire_end_memadd_reg_clrn == 1'b0) end_memadd_reg <= 1'b0;
		else  end_memadd_reg <= (end_memadd_reg_ena | ((~ end_memadd_reg_ena) & end_memadd_reg));
	assign
		wire_end_memadd_reg_clrn = (~ (stop_detect | rstart_detect));
	// synopsys translate_off
	initial
		end_write_reg = 0;
	// synopsys translate_on
	always @ ( posedge ufm_osc)
		  end_write_reg <= busy_deassert;
	// synopsys translate_off
	initial
		end_write_reg2 = 0;
	// synopsys translate_on
	always @ ( posedge ufm_osc)
		  end_write_reg2 <= end_write_reg;
	// synopsys translate_off
	initial
		eradd_match_reg = 0;
	// synopsys translate_on
	always @ ( negedge ufm_osc)
		  eradd_match_reg <= erase_add_match;
	// synopsys translate_off
	initial
		eradd_match_reg2 = 0;
	// synopsys translate_on
	always @ ( negedge ufm_osc)
		  eradd_match_reg2 <= eradd_match_reg;
	// synopsys translate_off
	initial
		fin_devadd_reg = 0;
	// synopsys translate_on
	always @ ( negedge scl_wire or  negedge wire_fin_devadd_reg_clrn)
		if (wire_fin_devadd_reg_clrn == 1'b0) fin_devadd_reg <= 1'b0;
		else  fin_devadd_reg <= (fin_devadd_reg_ena | ((~ fin_devadd_reg_ena) & fin_devadd_reg));
	assign
		wire_fin_devadd_reg_clrn = (~ (stop_detect | rstart_detect));
	// synopsys translate_off
	initial
		gcntr_aclr_int_reg = 0;
	// synopsys translate_on
	always @ ( posedge ufm_osc)
		  gcntr_aclr_int_reg <= gcntr_aclr_reg;
	// synopsys translate_off
	initial
		gcntr_aclr_reg = 0;
	// synopsys translate_on
	always @ ( posedge ufm_osc)
		  gcntr_aclr_reg <= reach_count_9;
	// synopsys translate_off
	initial
		gcntr_aclr_reg2 = 0;
	// synopsys translate_on
	always @ ( posedge ufm_osc)
		  gcntr_aclr_reg2 <= gcntr_aclr_int_reg;
	// synopsys translate_off
	initial
		gen_cntr2_reg = 0;
	// synopsys translate_on
	always @ ( negedge scl_wire or  negedge wire_gen_cntr2_reg_clrn)
		if (wire_gen_cntr2_reg_clrn == 1'b0) gen_cntr2_reg <= 1'b0;
		else  gen_cntr2_reg <= (wire_general_cntr_q[2] & (~ ((~ wire_stage_cntr_q[1]) & (~ wire_stage_cntr_q[0]))));
	assign
		wire_gen_cntr2_reg_clrn = (~ (stop_detect | rstart_detect));
	// synopsys translate_off
	initial
		memadd_shft_reg = 0;
	// synopsys translate_on
	always @ ( negedge scl_wire or  negedge wire_memadd_shft_reg_clrn)
		if (wire_memadd_shft_reg_clrn == 1'b0) memadd_shft_reg <= 1'b0;
		else  memadd_shft_reg <= (memadd_shft_reg_ena | ((~ memadd_shft_reg_ena) & memadd_shft_reg));
	assign
		wire_memadd_shft_reg_clrn = (~ (stop_detect | rstart_detect));
	// synopsys translate_off
	initial
		rd_addr_reg[0:0] = 0;
	// synopsys translate_on
	always @ ( posedge scl_wire)
		if (wire_rd_addr_reg_ena[0:0] == 1'b1)   rd_addr_reg[0:0] <= wire_rd_addr_reg_d[0:0];
	// synopsys translate_off
	initial
		rd_addr_reg[1:1] = 0;
	// synopsys translate_on
	always @ ( posedge scl_wire)
		if (wire_rd_addr_reg_ena[1:1] == 1'b1)   rd_addr_reg[1:1] <= wire_rd_addr_reg_d[1:1];
	// synopsys translate_off
	initial
		rd_addr_reg[2:2] = 0;
	// synopsys translate_on
	always @ ( posedge scl_wire)
		if (wire_rd_addr_reg_ena[2:2] == 1'b1)   rd_addr_reg[2:2] <= wire_rd_addr_reg_d[2:2];
	// synopsys translate_off
	initial
		rd_addr_reg[3:3] = 0;
	// synopsys translate_on
	always @ ( posedge scl_wire)
		if (wire_rd_addr_reg_ena[3:3] == 1'b1)   rd_addr_reg[3:3] <= wire_rd_addr_reg_d[3:3];
	// synopsys translate_off
	initial
		rd_addr_reg[4:4] = 0;
	// synopsys translate_on
	always @ ( posedge scl_wire)
		if (wire_rd_addr_reg_ena[4:4] == 1'b1)   rd_addr_reg[4:4] <= wire_rd_addr_reg_d[4:4];
	// synopsys translate_off
	initial
		rd_addr_reg[5:5] = 0;
	// synopsys translate_on
	always @ ( posedge scl_wire)
		if (wire_rd_addr_reg_ena[5:5] == 1'b1)   rd_addr_reg[5:5] <= wire_rd_addr_reg_d[5:5];
	// synopsys translate_off
	initial
		rd_addr_reg[6:6] = 0;
	// synopsys translate_on
	always @ ( posedge scl_wire)
		if (wire_rd_addr_reg_ena[6:6] == 1'b1)   rd_addr_reg[6:6] <= wire_rd_addr_reg_d[6:6];
	// synopsys translate_off
	initial
		rd_addr_reg[7:7] = 0;
	// synopsys translate_on
	always @ ( posedge scl_wire)
		if (wire_rd_addr_reg_ena[7:7] == 1'b1)   rd_addr_reg[7:7] <= wire_rd_addr_reg_d[7:7];
	assign
		wire_rd_addr_reg_d = {rd_addr_reg[6:0], sda_in_wire};
	assign
		wire_rd_addr_reg_ena = {8{((((~ rnw) & (~ wire_stage_cntr_q[1])) & wire_stage_cntr_q[0]) & (~ (((wire_general_cntr_q[3] & wire_general_cntr_q[2]) & (~ wire_general_cntr_q[1])) & (~ wire_general_cntr_q[0]))))}};
	// synopsys translate_off
	initial
		rd_wr_reg = 0;
	// synopsys translate_on
	always @ ( posedge scl_wire or  negedge wire_rd_wr_reg_clrn)
		if (wire_rd_wr_reg_clrn == 1'b0) rd_wr_reg <= 1'b0;
		else if  (wire_rd_wr_reg_ena == 1'b1)   rd_wr_reg <= sda_in_wire;
	assign
		wire_rd_wr_reg_ena = (((((((~ wire_stage_cntr_q[1]) & (~ wire_stage_cntr_q[0])) & slave_add_match) & (~ wire_general_cntr_q[3])) & wire_general_cntr_q[2]) & (~ wire_general_cntr_q[1])) & (~ wire_general_cntr_q[0])),
		wire_rd_wr_reg_clrn = (~ (stop_detect | rstart_detect));
	// synopsys translate_off
	initial
		reach_cnt9_reg = 0;
	// synopsys translate_on
	always @ ( negedge scl_wire)
		  reach_cnt9_reg <= count9;
	// synopsys translate_off
	initial
		read_nack_reg = 0;
	// synopsys translate_on
	always @ ( posedge scl_wire or  negedge wire_read_nack_reg_clrn)
		if (wire_read_nack_reg_clrn == 1'b0) read_nack_reg <= 1'b0;
		else if  (wire_read_nack_reg_ena == 1'b1)   read_nack_reg <= sda_in_wire;
	assign
		wire_read_nack_reg_ena = ((((((~ wire_stage_cntr_q[1]) & wire_stage_cntr_q[0]) & wire_general_cntr_q[3]) & wire_general_cntr_q[2]) & (~ wire_general_cntr_q[1])) & (~ wire_general_cntr_q[0])),
		wire_read_nack_reg_clrn = (~ (stop_detect | rstart_detect));
	// synopsys translate_off
	initial
		read_oe_reg = 0;
	// synopsys translate_on
	always @ ( negedge scl_wire or  negedge wire_read_oe_reg_prn)
		if (wire_read_oe_reg_prn == 1'b0) read_oe_reg <= {1{1'b1}};
		else  read_oe_reg <= (~ (((wire_general_cntr_q[3] & wire_general_cntr_q[2]) & (~ wire_general_cntr_q[1])) & (~ wire_general_cntr_q[0])));
	assign
		wire_read_oe_reg_prn = (~ (stop_detect | rstart_detect));
	// synopsys translate_off
	initial
		rstart_clr_reg = 0;
	// synopsys translate_on
	always @ ( posedge ufm_osc)
		  rstart_clr_reg <= rstart_detect;
	// synopsys translate_off
	initial
		rstart_clr_reg2 = 0;
	// synopsys translate_on
	always @ ( posedge ufm_osc)
		  rstart_clr_reg2 <= rstart_clr_reg;
	// synopsys translate_off
	initial
		rstart_det_da_reg = 0;
	// synopsys translate_on
	always @ ( posedge ufm_osc)
		  rstart_det_da_reg <= rstart_det_reg;
	// synopsys translate_off
	initial
		rstart_det_da_reg2 = 0;
	// synopsys translate_on
	always @ ( posedge ufm_osc)
		  rstart_det_da_reg2 <= rstart_det_da_reg;
	// synopsys translate_off
	initial
		rstart_det_reg = 0;
	// synopsys translate_on
	always @ ( negedge sda_in_delay or  negedge wire_rstart_det_reg_clrn)
		if (wire_rstart_det_reg_clrn == 1'b0) rstart_det_reg <= 1'b0;
		else  rstart_det_reg <= ((scl_wire & start_detect) | ((~ (scl_wire & start_detect)) & rstart_det_reg));
	assign
		wire_rstart_det_reg_clrn = (~ (stop_detect | clr_rstart));
	// synopsys translate_off
	initial
		sda_indly_reg = 0;
	// synopsys translate_on
	always @ ( posedge ufm_osc)
		  sda_indly_reg <= sda_in_wire;
	// synopsys translate_off
	initial
		sda_indly_reg2 = 0;
	// synopsys translate_on
	always @ ( posedge ufm_osc)
		  sda_indly_reg2 <= sda_indly_reg;
	// synopsys translate_off
	initial
		start_datpd_reg = 0;
	// synopsys translate_on
	always @ ( posedge ufm_osc or  posedge end_write)
		if (end_write == 1'b1) start_datpd_reg <= 1'b0;
		else  start_datpd_reg <= start_write;
	// synopsys translate_off
	initial
		start_detect_reg = 0;
	// synopsys translate_on
	always @ ( negedge sda_in_delay or  posedge stop_detect)
		if (stop_detect == 1'b1) start_detect_reg <= 1'b0;
		else if  (wire_start_detect_reg_ena == 1'b1)   start_detect_reg <= 1'b1;
	assign
		wire_start_detect_reg_ena = (((scl_wire & (~ (start_write & (~ erase_add_match)))) & (~ (start_prog & erase_add_match))) & (~ ufm_bgpbusy));
	// synopsys translate_off
	initial
		start_din_reg = 0;
	// synopsys translate_on
	always @ ( posedge scl_wire or  negedge wire_start_din_reg_clrn)
		if (wire_start_din_reg_clrn == 1'b0) start_din_reg <= 1'b0;
		else  start_din_reg <= (((slave_add_match & (~ rnw)) & wire_stage_cntr_q[1]) & wire_stage_cntr_q[0]);
	assign
		wire_start_din_reg_clrn = (~ ((end_din_reg | stop_detect) | rstart_detect));
	// synopsys translate_off
	initial
		start_er_reg = 0;
	// synopsys translate_on
	always @ ( negedge ufm_osc or  posedge end_write)
		if (end_write == 1'b1) start_er_reg <= 1'b0;
		else  start_er_reg <= (((start_prog & eradd_match_reg2) & (~ wire_er_wr_cntr_q[0])) & (~ ufm_bgpbusy));
	// synopsys translate_off
	initial
		start_memadd_reg = 0;
	// synopsys translate_on
	always @ ( posedge scl_wire or  negedge wire_start_memadd_reg_clrn)
		if (wire_start_memadd_reg_clrn == 1'b0) start_memadd_reg <= 1'b0;
		else if  (wire_start_memadd_reg_ena == 1'b1)   start_memadd_reg <= 1'b1;
	assign
		wire_start_memadd_reg_ena = ((~ rnw) & ack_pulse_sa),
		wire_start_memadd_reg_clrn = (~ (stop_detect | rstart_detect));
	// synopsys translate_off
	initial
		start_prog_reg = 0;
	// synopsys translate_on
	always @ ( posedge ufm_osc or  negedge wire_start_prog_reg_clrn)
		if (wire_start_prog_reg_clrn == 1'b0) start_prog_reg <= 1'b0;
		else if  (wire_start_prog_reg_ena == 1'b1)   start_prog_reg <= data_pad_complete;
	assign
		wire_start_prog_reg_ena = (((start_write & (~ ufm_bgpbusy)) & (~ ufm_busy)) & (~ write_prot_true)),
		wire_start_prog_reg_clrn = (~ ((((~ erase_add_match) & busy_deassert) | (erase_add_match & end_er_write)) | ((erase_add_match & ufm_bgpbusy) & end_write)));
	// synopsys translate_off
	initial
		start_rd_reg = 0;
	// synopsys translate_on
	always @ ( posedge scl_wire or  posedge stop_detect)
		if (stop_detect == 1'b1) start_rd_reg <= 1'b0;
		else  start_rd_reg <= (((rnw & ack_pulse_sa) & slave_add_match) | ((~ ((rnw & ack_pulse_sa) & slave_add_match)) & start_rd_reg));
	// synopsys translate_off
	initial
		start_wr_reg = 0;
	// synopsys translate_on
	always @ ( negedge ufm_osc or  posedge end_write)
		if (end_write == 1'b1) start_wr_reg <= 1'b0;
		else if  (wire_start_wr_reg_ena == 1'b1)   start_wr_reg <= wire_er_wr_cntr_q[0];
	assign
		wire_start_wr_reg_ena = (((erase_add_match & (~ wire_er_wr_cntr_q[1])) & wire_er_wr_cntr_q[0]) & (~ ufm_bgpbusy));
	// synopsys translate_off
	initial
		stop_det_da_reg = 0;
	// synopsys translate_on
	always @ ( posedge ufm_osc)
		  stop_det_da_reg <= stop_detect_reg;
	// synopsys translate_off
	initial
		stop_det_da_reg2 = 0;
	// synopsys translate_on
	always @ ( posedge ufm_osc)
		  stop_det_da_reg2 <= stop_det_da_reg;
	// synopsys translate_off
	initial
		stop_detect_reg = 0;
	// synopsys translate_on
	always @ ( posedge sda_in_delay or  posedge stop_det_rst)
		if (stop_det_rst == 1'b1) stop_detect_reg <= 1'b0;
		else if  (wire_stop_detect_reg_ena == 1'b1)   stop_detect_reg <= 1'b1;
	assign
		wire_stop_detect_reg_ena = ((scl_wire & (~ start_write)) & (~ ufm_erase));
	// synopsys translate_off
	initial
		stop_rst_reg = 0;
	// synopsys translate_on
	always @ ( posedge ufm_osc)
		  stop_rst_reg <= stop_detect;
	// synopsys translate_off
	initial
		stop_rst_reg2 = 0;
	// synopsys translate_on
	always @ ( posedge ufm_osc)
		  stop_rst_reg2 <= stop_rst_reg;
	// synopsys translate_off
	initial
		strd_drclk_reg = 0;
	// synopsys translate_on
	always @ ( posedge scl_wire or  posedge clr_drclk_reg)
		if (clr_drclk_reg == 1'b1) strd_drclk_reg <= 1'b0;
		else  strd_drclk_reg <= (((rnw & slave_add_match) & ena_drclk_reg) | ((~ ((rnw & slave_add_match) & ena_drclk_reg)) & strd_drclk_reg));
	lpm_compare   cmpr4
	( 
	.aeb(wire_cmpr4_aeb),
	.agb(),
	.ageb(),
	.alb(),
	.aleb(),
	.aneb(),
	.dataa({1'b1, 1'b0, 1'b1, 1'b0, a2, a1}),
	.datab({dev_add_reg[6:1]})
	`ifndef FORMAL_VERIFICATION
	// synopsys translate_off
	`endif
	,
	.aclr(1'b0),
	.clken(1'b1),
	.clock(1'b0)
	`ifndef FORMAL_VERIFICATION
	// synopsys translate_on
	`endif
	);
	defparam
		cmpr4.lpm_width = 6,
		cmpr4.lpm_type = "lpm_compare";
	lpm_compare   cmpr6
	( 
	.aeb(wire_cmpr6_aeb),
	.agb(),
	.ageb(),
	.alb(),
	.aleb(),
	.aneb(),
	.dataa({9{1'b0}}),
	.datab({a0_wire, rd_addr_reg[7:0]})
	`ifndef FORMAL_VERIFICATION
	// synopsys translate_off
	`endif
	,
	.aclr(1'b0),
	.clken(1'b1),
	.clock(1'b0)
	`ifndef FORMAL_VERIFICATION
	// synopsys translate_on
	`endif
	);
	defparam
		cmpr6.lpm_width = 9,
		cmpr6.lpm_type = "lpm_compare",
		cmpr6.lpm_hint = "ONE_INPUT_IS_CONSTANT=YES";
	lpm_compare   cmpr7
	( 
	.aeb(wire_cmpr7_aeb),
	.agb(),
	.ageb(),
	.alb(),
	.aleb(),
	.aneb(),
	.dataa({1'b0, 1'b1, {7{1'b0}}}),
	.datab({a0_wire, rd_addr_reg[7:0]})
	`ifndef FORMAL_VERIFICATION
	// synopsys translate_off
	`endif
	,
	.aclr(1'b0),
	.clken(1'b1),
	.clock(1'b0)
	`ifndef FORMAL_VERIFICATION
	// synopsys translate_on
	`endif
	);
	defparam
		cmpr7.lpm_width = 9,
		cmpr7.lpm_type = "lpm_compare",
		cmpr7.lpm_hint = "ONE_INPUT_IS_CONSTANT=YES";
	maxv_io   maxii_io2
	( 
	.combout(wire_maxii_io2_combout),
	.datain(1'b0),
	.oe(clock_oe),
	.padio(scl));
	defparam
		maxii_io2.open_drain_output = "true",
		maxii_io2.operation_mode = "bidir",
		maxii_io2.lpm_type = "maxv_io";
	maxv_io   maxii_io3
	( 
	.combout(wire_maxii_io3_combout),
	.datain(sda_out_wire),
	.oe(sda_oe),
	.padio(sda));
	defparam
		maxii_io3.open_drain_output = "true",
		maxii_io3.operation_mode = "bidir",
		maxii_io3.lpm_type = "maxv_io";
	maxv_ufm   maxii_ufm_block1
	( 
	.arclk(ufm_arclk),
	.ardin(ufm_ardin),
	.arshft(ufm_arshft),
	.bgpbusy(wire_maxii_ufm_block1_bgpbusy),
	.busy(wire_maxii_ufm_block1_busy),
	.drclk(ufm_drclk),
	.drdin(ufm_drdin),
	.drdout(wire_maxii_ufm_block1_drdout),
	.drshft(ufm_drshft),
	.erase(ufm_erase),
	.osc(wire_maxii_ufm_block1_osc),
	.oscena(ufm_oscena),
	.program(ufm_program)
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
		maxii_ufm_block1.erase_time = 500000000,
		maxii_ufm_block1.init_file = "none",
		maxii_ufm_block1.mem1 = 512'hFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF,
		maxii_ufm_block1.mem10 = 512'hFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF,
		maxii_ufm_block1.mem11 = 512'hFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF,
		maxii_ufm_block1.mem12 = 512'hFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF,
		maxii_ufm_block1.mem13 = 512'hFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF,
		maxii_ufm_block1.mem14 = 512'hFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF,
		maxii_ufm_block1.mem15 = 512'hFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF,
		maxii_ufm_block1.mem16 = 512'hFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF,
		maxii_ufm_block1.mem2 = 512'hFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF,
		maxii_ufm_block1.mem3 = 512'hFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF,
		maxii_ufm_block1.mem4 = 512'hFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF,
		maxii_ufm_block1.mem5 = 512'hFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF,
		maxii_ufm_block1.mem6 = 512'hFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF,
		maxii_ufm_block1.mem7 = 512'hFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF,
		maxii_ufm_block1.mem8 = 512'hFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF,
		maxii_ufm_block1.mem9 = 512'hFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF,
		maxii_ufm_block1.osc_sim_setting = 180000,
		maxii_ufm_block1.program_time = 1600000,
		maxii_ufm_block1.lpm_type = "maxv_ufm";
	assign
		a0_wire = dev_add_reg[0],
		ack_pulse_data = ack_data_reg,
		ack_pulse_ma = ack_ma_reg,
		ack_pulse_sa = ack_sa_reg,
		ardin_en = (add_en_reg & (~ end_memadd_reg)),
		bgpbusy_detect = bgpbsy_rdreg,
		bgplow = bgpend_det_reg,
		busy_deassert = busy_dea_reg,
		busy_det = busy_det_reg2,
		clock_oe = (bgpbusy_detect & (~ bgplow)),
		clr_rstart = (rstart_clr_reg & (~ rstart_clr_reg2)),
		count9 = (((wire_general_cntr_q[3] & wire_general_cntr_q[2]) & (~ wire_general_cntr_q[1])) & wire_general_cntr_q[0]),
		count_end = (gcntr_aclr_int_reg & (~ gcntr_aclr_reg2)),
		data_pad_complete = (((wire_data_pad_cntr_q[3] & wire_data_pad_cntr_q[2]) & (~ wire_data_pad_cntr_q[1])) & (~ wire_data_pad_cntr_q[0])),
		data_suc = data_suc_reg,
		do_add_shft = (memadd_shft_reg & (~ end_memadd_reg)),
		do_mem_add = do_memadd_reg2,
		do_read = (((~ bgpbusy_detect) & start_rd_reg) & strd_drclk_reg),
		do_write = start_din_reg,
		drdin_en = din_en_reg,
		end_din_reg_ena = ((((~ rnw) & wire_stage_cntr_q[1]) & wire_stage_cntr_q[0]) & (~ ncount8)),
		end_er_write = (wire_er_wr_cntr_q[1] & wire_er_wr_cntr_q[0]),
		end_memadd_reg_ena = ((((~ rnw) & (~ wire_stage_cntr_q[1])) & wire_stage_cntr_q[0]) & (~ ncount8)),
		end_write = end_write_reg2,
		erase_add_match = (wire_cmpr6_aeb | wire_cmpr7_aeb),
		fin_devadd_reg_ena = ((((((~ wire_stage_cntr_q[1]) & (~ wire_stage_cntr_q[0])) & (~ wire_general_cntr_q[3])) & wire_general_cntr_q[2]) & (~ wire_general_cntr_q[1])) & (~ wire_general_cntr_q[0])),
		finish_dev_add = fin_devadd_reg,
		gen_cntr2 = gen_cntr2_reg,
		memadd_shft_reg_ena = ((((~ rnw) & (~ ncount8)) & (~ wire_stage_cntr_q[1])) & (~ wire_stage_cntr_q[0])),
		ncount8 = (~ (((wire_general_cntr_q[3] & wire_general_cntr_q[2]) & (~ wire_general_cntr_q[1])) & (~ wire_general_cntr_q[0]))),
		osc = ufm_osc,
		oscena = 1'b1,
		reach_count_9 = reach_cnt9_reg,
		read_nack = read_nack_reg,
		read_oe = read_oe_reg,
		rnw = rd_wr_reg,
		rstart_detect = rstart_det_da_reg2,
		scl_wire = wire_maxii_io2_combout,
		sda_in_delay = sda_indly_reg2,
		sda_in_wire = wire_maxii_io3_combout,
		sda_oe = (((ack_pulse_sa | ack_pulse_ma) | ack_pulse_data) | ((((rnw & (~ bgpbusy_detect)) & read_oe) & (~ read_nack)) & (~ ((~ wire_stage_cntr_q[1]) & (~ wire_stage_cntr_q[0]))))),
		sda_out_wire = ((~ slave_add_match) | ((drdout_reg & rnw) & (~ ((~ wire_stage_cntr_q[1]) & (~ wire_stage_cntr_q[0]))))),
		slave_add_match = wire_cmpr4_aeb,
		start_data_pad = (start_datpd_reg & (~ end_datpd_reg)),
		start_detect = start_detect_reg,
		start_prog = start_prog_reg,
		start_write = ena_write_reg,
		stop_det_rst = (stop_rst_reg & (~ stop_rst_reg2)),
		stop_detect = stop_det_da_reg2,
		ufm_arclk = (((gen_cntr2 & rnw) & (~ ((~ wire_stage_cntr_q[1]) & (~ wire_stage_cntr_q[0])))) | ((do_mem_add & (~ rnw)) & scl_wire)),
		ufm_ardin = ((ack_pulse_sa & a0_dly_reg) | (ardin_en & sda_in_wire)),
		ufm_arshft = do_add_shft,
		ufm_bgpbusy = wire_maxii_ufm_block1_bgpbusy,
		ufm_busy = wire_maxii_ufm_block1_busy,
		ufm_drclk = ((((rnw & scl_wire) & do_read) | (((~ rnw) & scl_wire) & do_write)) | (ufm_osc & start_data_pad)),
		ufm_drdin = ((drdin_en & sda_in_wire) | (start_write & (~ end_datpd_reg))),
		ufm_drdout = wire_maxii_ufm_block1_drdout,
		ufm_drshft = drshft_reg,
		ufm_erase = start_er_reg,
		ufm_osc = wire_maxii_ufm_block1_osc,
		ufm_oscena = oscena,
		ufm_program = ((start_prog & (~ erase_add_match)) | (start_wr_reg & erase_add_match)),
		write_prot = 1'b0,
		write_prot_true = write_prot;
	initial/*synthesis enable_verilog_initial_construct*/
 	begin
		$display("Warning: MGL_INTERNAL_WARNING: ( The parameter value is not one of the pre-specified values in the value list.) altufm_i2c|PORT_GLOBAL_RESET The value assigned is USED and the valid value list is PORT_UNUSED|PORT_USED");
	end
endmodule //i2c_CORE_ufm_i2c_0
//VALID FILE
