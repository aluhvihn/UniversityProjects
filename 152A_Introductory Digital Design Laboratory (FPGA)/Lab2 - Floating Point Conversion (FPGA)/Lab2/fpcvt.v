`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:36:51 04/15/2015 
// Design Name: 
// Module Name:    fpcvt 
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
module fpcvt(
    input [11:0] D,
    output S,
    output [2:0] E,
    output [3:0] F
    );
    
  
wire [11:0] abswire; 
wire [2:0] expwire;
wire [3:0] sigwire;
wire fifthwire;


Inverter i (D, S, abswire);
Converter c (abswire, expwire, sigwire, fifthwire);
Rounder r (expwire, sigwire, fifthwire, E, F); 




endmodule
