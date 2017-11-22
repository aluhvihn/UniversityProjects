`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:12:35 04/15/2015 
// Design Name: 
// Module Name:    Rounder 
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
module Rounder(
    input [2:0] Exp,
    input [3:0] Significand,
    input Fifth,
    output [2:0] EOut,
    output [3:0] FOut
    );
    
reg [2:0] E;
reg [3:0] F;

reg overflow; 

always @ (*) begin
    overflow = 0;
    if (Fifth == 1) begin
        if (Significand[3] == 1 &&
            Significand[2] == 1 &&
            Significand[1] == 1 &&
            Significand[0] == 1) begin
            overflow = 1;
        end
        F = Significand + 1;
        if (overflow == 1) begin
            F[3] = 1;
            if (Exp >= 7) begin 
                F = 15; 
                E = 7;
            end 
            else begin E = Exp + 1; end
        end else begin
            E = Exp;
        end
    end else begin
        F = Significand; 
        E = Exp;
    end
end
assign EOut = E;
assign FOut = F;

endmodule
