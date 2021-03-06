`define DELAY 20
module like_alu_testbench(); 
reg[4:0] a;
reg[4:0] b;
reg[1:0] select;
wire[4:0] result;

likeALU ALU(result,a,b,select);

initial begin
a = 5'b00000; b = 5'b00001; select = 2'b00;
#`DELAY;
a = 5'b00000; b = 5'b10001; select = 2'b01;
#`DELAY;
a = 5'b00001; b = 5'b00001; select = 2'b00;
#`DELAY;
a = 5'b00000; b = 5'b00001; select = 2'b01;
#`DELAY;
a = 5'b00010; b = 5'b00001; select = 2'b11;
#`DELAY;
a = 5'b00100; b = 5'b11011; select = 2'b10;
#`DELAY;
a = 5'b00111; b = 5'b01011; select = 2'b10;
#`DELAY;
a = 5'b01100; b = 5'b00100; select = 2'b01;
end
 
 
initial
begin
$monitor("time = %2d, a =%5.1b, b=%5.1b, select=%2.1b, result=%5.1b", $time, a, b, select, result);
end
 
endmodule