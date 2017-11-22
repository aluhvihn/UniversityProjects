`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:27:51 04/15/2015 
// Design Name: 
// Module Name:    Convertor 
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
module Convertor(
    input [11:0] D,
    output Sign,
    output [11:0] Abs
    );
    
always @ (*) begin
    Sign = D[11];
    if (Sign == 1) begin
        Abs = ~D + 1;
    end
    else begin
        Abs = D;
    end
end

endmodule
