module five_bit_adder(A, B, cout,S ); //A+B cout S:Sum
input [4:0] A;
input [4:0] B;
output [4:0] S;
output cout;
wire c0, c1, c2,c3;
full_adder fa0( S[0], c0 ,A[0], B[0], 1'b0);
full_adder fa1( S[1], c1 ,A[1], B[1], c0);
full_adder fa2( S[2], c2 ,A[2], B[2], c1);
full_adder fa3( S[3], c3 ,A[3], B[3], c2 );
full_adder fa4( S[4],cout,A[4], B[4], c3 );

endmodule