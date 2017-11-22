`timescale 1ns / 1ps

module stopwatch(
    input [2:0] sw,   // sw[0] for "DIR": 0 = up, 1 = down
                      // sw[1] for "SEL": 0 = min, 1 = sec
                      // sw[2] for "ADJ": 0 = normal, 1 = 2x

    input btnS,       // PAUSE
    input btnR,       // RESET
    input clk,        // 100 MHz   0b101111101011110000100000000
    
    output [7:0] seg,
    output [3:0] an
    );

// CLOCK VARIABLES
wire clk_1;      // 1      Hz     Normal Counting
wire clk_2;      // 2      Hz     Adjust
wire clk_blink;  // 1.5    Hz     Blink
wire clk_666;    // 666.66 Hz     Display

// OUTPUT FOR EACH DIGIT
wire [7:0] digit0_display;
wire [7:0] digit1_display;
wire [7:0] digit2_display;
wire [7:0] digit3_display;

reg PAUSE;
reg RESET;

// Debouncing
always @ (posedge clk_666) begin
    PAUSE <= btnS;
    RESET <= btnR;
end

// MAKE THE CLOCKS
make_clocks clocks( // INPUTS
                   .clk      (clk),
                   .PAUSE    (PAUSE),
                    // OUTPUTS
                   .clk_1    (clk_1),
                   .clk_2    (clk_2),
                   .clk_blink(clk_blink),
                   .clk_666  (clk_666)
                   );

time_counter count( //INPUTS
                   .counting_clk  (clk_1),
                   .adjusting_clk (clk_2),
                   .refresh_clk   (clk_666),

                   .RESET         (RESET),

                   .dir           (sw[0]),
                   .sel           (sw[1]),
                   .adj           (sw[2]),

                   .digit0_display(digit0_display),
                   .digit1_display(digit1_display),
                   .digit2_display(digit2_display),
                   .digit3_display(digit3_display)
                   );

blink_display blink( // INPUTS
                    .display_clk   (clk_666),
                    .blink_clk     (clk_blink),

                    .sel           (sw[1]),
                    .adj           (sw[2]),
                    
                    .digit0_display(digit0_display),
                    .digit1_display(digit1_display),
                    .digit2_display(digit2_display),
                    .digit3_display(digit3_display),

                     // OUTPUTS
                    .seg           (seg),
                    .an            (an));

endmodule
