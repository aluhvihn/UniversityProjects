`timescale 1ns / 1ps

module tb;

	// Inputs
	reg clk;
	reg btnU;
	reg btnD;
	reg btnL;
	reg btnR;
	reg btnS;
	reg sw;

	// Outputs
	wire [3:0] an;
	wire [7:0] seg;

	// Instantiate the Unit Under Test (UUT)
	calculator calculator_(
		.clk(clk), 
		.btnU(btnU), 
		.btnD(btnD), 
		.btnL(btnL), 
		.btnR(btnR), 
		.btnS(btnS), 
		.sw(sw), 
		.an(an), 
		.seg(seg)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		btnU = 0;
		btnD = 0;
		btnL = 0;
		btnR = 0;
		btnS = 0;
		sw = 0;

		// Wait 100 ns for global reset to finish
		#100000000;
        
		// Add stimulus here
        btnR = 1;
        #10000000;
        btnR = 0;
        
        
        #10000000;
        btnU = 1;
        #10000000;
        btnU = 0;

		#10000000;
        btnS = 1;
        #10000000;
        btnS = 0;        
        

	end

always #5 clk = ~clk;
      
endmodule

