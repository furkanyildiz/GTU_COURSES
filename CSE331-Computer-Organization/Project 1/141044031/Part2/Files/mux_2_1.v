module mux_2_1(outp,d0,d1,select);


input select;
input[4:0] d0;
input[4:0] d1;

output[4:0] outp;
wire[4:0] outp;

wire select;
wire[4:0] d0;
wire[4:0] d1;

wire notselect;
not notop(notselect, select);

wire[4:0] temp;
wire[4:0] temp2;

and A(temp[0],d0[0], notselect);
and A1(temp[1],d0[1], notselect);
and A2(temp[2],d0[2], notselect);
and A3(temp[3],d0[3], notselect);
and A4(temp[4],d0[4], notselect);


and B(temp2[0],d1[0], select);
and B1(temp2[1],d1[1], select);
and B2(temp2[2],d1[2], select);
and B3(temp2[3],d1[3], select);
and B4(temp2[4],d1[4], select);



or result(outp[0],temp[0],temp2[0]);
or result1(outp[1],temp[1],temp2[1]);
or result2(outp[2],temp[2],temp2[2]);
or result3(outp[3],temp[3],temp2[3]);
or result4(outp[4],temp[4],temp2[4]);

endmodule