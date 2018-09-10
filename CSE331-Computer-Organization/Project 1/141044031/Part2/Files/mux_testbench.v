`define DELAY 20
module mux_testbench(); 
reg[4:0] s1;
reg[4:0] s2;
reg[4:0] s3;
reg[4:0] s4;

reg[1:0] select;
wire[4:0] result;

mux1 MUX(result,select, s1,s2,s3,s4);
initial begin
s1 = 5'b00001; s2 = 5'b00011;s3 = 5'b00111; s4 = 5'b01111; select = 2'b00;
#`DELAY;
s1 = 5'b00001; s2 = 5'b00011;s3 = 5'b00111; s4 = 5'b01111; select = 2'b01;
#`DELAY;
s1 = 5'b00001; s2 = 5'b00011;s3 = 5'b00111; s4 = 5'b01111; select = 2'b10;
#`DELAY;
s1 = 5'b00001; s2 = 5'b00011;s3 = 5'b00111; s4 = 5'b01111; select = 2'b11;
end
 
 
initial
begin
$monitor("time = %2d, s1 =%5.1b, s2=%5.1b, s3=%5.1b, s4=%5.1b, select=%2.1b, result=%5.1b", $time, s1, s2,s3,s4, select, result);
end
 
endmodule