`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:52:33 04/15/2015 
// Design Name: 
// Module Name:    Inverter 
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
module Inverter(
    input [11:0] D,
    output Sign,
    output [11:0] Abs
    );

reg [11:0] temp;

always @ (*) begin
    if (Sign == 1) begin
        if (D == 12'b1000_0000_0000) begin temp = ~D; end
        else begin temp = ~D + 1; end
    end
    else begin
        temp = D;
    end
end
assign Sign = D[11];
assign Abs[11:0] = temp[11:0];

endmodule
