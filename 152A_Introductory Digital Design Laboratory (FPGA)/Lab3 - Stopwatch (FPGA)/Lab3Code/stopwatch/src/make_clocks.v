`timescale 1ns / 1ps

module make_clocks (
  input clk,          // Clock

  input PAUSE,
  
  output clk_1,       // 1   Hz - Normal Counting
  output clk_2,       // 2   Hz - Adjust
  output clk_blink,   // 1.5 Hz - Blinking
  output clk_666      // 666 Hz - Display
);

reg pause_status;

initial begin
    pause_status = 0;
end

always @ (posedge PAUSE) begin 
    pause_status = ~pause_status;
end

clock_1hz   c1(   .clk(clk), .pause(pause_status), .clk_1(clk_1));
clock_1_5hz c15(  .clk(clk), .clk_blink(clk_blink));
clock_2hz   c2(   .clk(clk), .pause(pause_status), .clk_2(clk_2));
clock_666hz c666( .clk(clk), .clk_666(clk_666));

endmodule