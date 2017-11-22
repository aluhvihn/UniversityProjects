`timescale 1ns / 1ps

module tb;

    // Inputs
    reg [2:0] sw;
    reg clk;
    reg btnS;
    reg btnR;
    
    wire [7:0] seg;
    wire [3:0] an;
    initial begin
        // Initialize Inputs
        sw[0] = 1; // sw[0] for "DIR": 0 = up, 1 = down
        sw[1] = 0; // sw[1] for "SEL": 0 = min, 1 = sec
        sw[2] = 0; // sw[2] for "ADJ": 0 = normal, 1 = 2x
        clk = 0;

        btnS = 0;
        btnR = 0;

        #1000000000;

        // Reset
        sw[0] = 0;
        #1000000000;


    end

    // Instantiate the Unit Under Test (UUT)
    stopwatch uut (
        .sw(sw),

        .btnS(btnS),
        .btnR(btnR),
        .clk(clk),

        .seg (seg),
        .an  (an)
    );

    always #5 clk = ~clk;
    
    
endmodule

