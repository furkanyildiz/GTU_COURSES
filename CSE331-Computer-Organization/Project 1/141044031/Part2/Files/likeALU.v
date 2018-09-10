module likeALU(out,inp_A,inp_B,select);
input[4:0] inp_A;
input[4:0] inp_B;
input[1:0] select;
wire[1:0] select;
output[4:0] out;
wire carry_out;

wire[4:0] and_5bit;
wire[4:0] sum_5bit;
wire[4:0] or_5bit;
wire[4:0] xor_5bit;

and anded_1 (and_5bit[0],inp_A[0],inp_B[0]);
and anded_2 (and_5bit[1],inp_A[1],inp_B[1]);
and anded_3 (and_5bit[2],inp_A[2],inp_B[2]);
and anded_4 (and_5bit[3],inp_A[3],inp_B[3]);
and anded_5(and_5bit[4],inp_A[4],inp_B[4]);


five_bit_adder fba (inp_A,inp_B,carry_out,sum_5bit); //A+B cout S:Sum


or ored_1 (or_5bit[0],inp_A[0],inp_B[0]);
or ored_2 (or_5bit[1],inp_A[1],inp_B[1]);
or ored_3 (or_5bit[2],inp_A[2],inp_B[2]);
or ored_4 (or_5bit[3],inp_A[3],inp_B[3]);
or ored_5 (or_5bit[4],inp_A[4],inp_B[4]);


xor xored_1(xor_5bit[0],inp_A[0],inp_B[0]);
xor xored_2(xor_5bit[1],inp_A[1],inp_B[1]);
xor xored_3(xor_5bit[2],inp_A[2],inp_B[2]);
xor xored_4(xor_5bit[3],inp_A[3],inp_B[3]);
xor xored_5(xor_5bit[4],inp_A[4],inp_B[4]);

mux_4_1 m(out,and_5bit,sum_5bit,or_5bit,xor_5bit,select);
endmodule