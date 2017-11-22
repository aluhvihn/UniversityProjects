`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   15:47:10 04/15/2015
// Design Name:   fpcvt
// Module Name:   C:/Users/152/Documents/xy_alvin/Lab2/testbench.v
// Project Name:  Lab2
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: fpcvt
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module testbench;

	// Inputs
	reg [11:0] D;

	// Outputs
	wire S;
	wire [2:0] E;
	wire [3:0] F;

	// Instantiate the Unit Under Test (UUT)
	fpcvt uut (
		.D(D), 
		.S(S), 
		.E(E), 
		.F(F)
	);

	initial begin
		// Initialize Inputs
		D = 12'b0;
		#1000
        
        D = 12'b1111_1111_1111;
        #1000
        
        D = 12'b1;
        #1000
        
        D = 12'b10;
        #1000
        
        D = 12'b11;
        #1000
        
        D = 12'b1_1000;
        #1000
        
        D = 12'b1000_0000_0000;
        #1000
        
        D = 12'b0111_1111_1111;
        #1000
              
        D = 12'b0000_0010_1100; // 0 010 1011
        #1000
        
        D = 12'b0000_0010_1101; // 0 010 1011
        #1000
        
        D = 12'b0000_0010_1110; // 0 010 1100
        #1000
        
        D = 12'b0000_0010_1111; // 0 010 1100
        #1000
        
        #1500000000  
		$display("Done");
        $finish;

	end
      
endmodule

