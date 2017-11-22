`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:53:55 04/15/2015 
// Design Name: 
// Module Name:    Converter 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module Converter(
    input [11:0] Abs,
    output [2:0] ExpOut,
    output [3:0] SignificandOut,
    output FifthOut
    );
reg [3:0] leadingZeroes;
reg [11:0] temp;
reg [2:0] Exp;
reg [3:0] Significand;
reg Fifth;

always @ (*) begin
    
    leadingZeroes = 0;
    if (Abs[10] == 1) begin
        leadingZeroes = 1; 
    end else if (Abs[9] == 1) begin
        leadingZeroes = 2;
    end else if (Abs[8] == 1) begin
        leadingZeroes = 3;
    end else if (Abs[7] == 1) begin
        leadingZeroes = 4;
    end else if (Abs[6] == 1) begin
        leadingZeroes = 5;
    end else if (Abs[5] == 1) begin
        leadingZeroes = 6;
    end else if (Abs[4] == 1) begin
        leadingZeroes = 7;
    end else if (Abs[3] == 1) begin
        leadingZeroes = 8;
    end else if (Abs[2] == 1) begin
        leadingZeroes = 9;
    end else if (Abs[1] == 1) begin
        leadingZeroes = 10;
    end else if (Abs[0] == 1) begin
        leadingZeroes = 11;
    end
    
    case(leadingZeroes)
    1: Exp = 7;
    2: Exp = 6;
    3: Exp = 5;
    4: Exp = 4;
    5: Exp = 3;
    6: Exp = 2;
    7: Exp = 1;
    8: Exp = 0;
    default: Exp = 0;
    endcase
    
    if (Exp > 0) begin 
        temp = Abs >> (Exp - 1); 
        Fifth = temp[0];
        Significand[3] = temp[4];
        Significand[2] = temp[3];
        Significand[1] = temp[2];
        Significand[0] = temp[1];
    end else begin 
        temp = Abs; 
        Fifth = 0;
        Significand[3] = temp[3];
        Significand[2] = temp[2];
        Significand[1] = temp[1];
        Significand[0] = temp[0];
    end
end
assign ExpOut = Exp;
assign SignificandOut = Significand;
assign FifthOut = Fifth;

endmodule
