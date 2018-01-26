// Copyright (C) 1991-2013 Altera Corporation
// Your use of Altera Corporation's design tools, logic functions 
// and other software and tools, and its AMPP partner logic 
// functions, and any output files from any of the foregoing 
// (including device programming or simulation files), and any 
// associated documentation or information are expressly subject 
// to the terms and conditions of the Altera Program License 
// Subscription Agreement, Altera MegaCore Function License 
// Agreement, or other applicable license agreement, including, 
// without limitation, that your use is for the sole purpose of 
// programming logic devices manufactured by Altera and sold by 
// Altera or its authorized distributors.  Please refer to the 
// applicable agreement for further details.

module likeALU_demo
(
// {ALTERA_ARGS_BEGIN} DO NOT REMOVE THIS LINE!

	inp_A,
	inp_B,
	out,
	select
// {ALTERA_ARGS_END} DO NOT REMOVE THIS LINE!

);

// {ALTERA_IO_BEGIN} DO NOT REMOVE THIS LINE!
input	[4:0]	inp_A;
input	[4:0]	inp_B;
output	[4:0]	out;
input	[1:0]	select;

// {ALTERA_IO_END} DO NOT REMOVE THIS LINE!
// {ALTERA_MODULE_BEGIN} DO NOT REMOVE THIS LINE!
// {ALTERA_MODULE_END} DO NOT REMOVE THIS LINE!
endmodule

