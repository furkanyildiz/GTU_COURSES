module mux_4_1(out,d0,d1,d2,d3,select);

input[4:0] d0;
input[4:0] d1;
input[4:0] d2;
input[4:0] d3;
input[1:0] select;

output[4:0] out;
wire[4:0] out;
wire[1:0] select;

wire[4:0] d0;
wire[4:0] d1;
wire[4:0] d2;
wire[4:0] d3;

wire[4:0] temp;
wire[4:0] temp2;


mux_2_1 O1(temp,d0,d1,select[0]);
mux_2_1 O2(temp2,d2,d3,select[0]);
mux_2_1 OResult(out,temp,temp2,select[1]);

endmodule

