`define DELAY 20
module five_bit_adder_testbench();

reg[4:0] a;
reg[4:0] b;
wire[4:0] result;
wire cout;
five_bit_adder fba (a, b,cout, result);

initial begin
a = 5'b00000; b = 5'b00001;
#`DELAY;
a = 5'b00000; b = 5'b00001;
#`DELAY;
a = 5'b00001; b = 5'b00001;
#`DELAY;
a = 5'b00000; b = 5'b00001;
#`DELAY;
a = 5'b00010; b = 5'b00001;
#`DELAY;
a = 5'b00100; b = 5'b11011;
#`DELAY;
a = 5'b00111; b = 5'b01011;
#`DELAY;
a = 5'b00101; b = 5'b00100;
#`DELAY;
a = 5'b01100; b = 5'b00100;
end
 
 
initial
begin
$monitor("time = %2d, a =%5.1b, b=%5.1b, result=%5.1b, cout:%1b", $time, a, b, result,cout);
end
 
endmodule