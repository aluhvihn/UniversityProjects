module make_clocks (
  input clk,          // Clock
  
  output clk_blink,   // 1.5 Hz - Blinking
  output clk_666      // 666 Hz - Display
);

clock_1_5hz c15(  .clk(clk), .clk_blink(clk_blink));
clock_666hz c666( .clk(clk), .clk_666(clk_666));

endmodule