
module i2c_CORE (
	a0,
	a1,
	a2,
	scl,
	sda,
	osc,
	global_reset);	

	input		a0;
	input		a1;
	input		a2;
	inout		scl;
	inout		sda;
	output		osc;
	input		global_reset;
endmodule
