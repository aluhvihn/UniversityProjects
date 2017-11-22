`timescale 1ns / 1ps

module clock_1_5hz(
    input     clk,
    output    clk_blink
    );

reg [24:0] clk_counter;
reg clk_blink_TEMP;

initial begin
    clk_counter = 25'b0;
    clk_blink_TEMP = 0;
end

always @ (posedge clk) begin
    if (clk_counter == 25'b1_1111_1100_1010_0000_0101_0101) begin
        clk_counter <= 0;
        clk_blink_TEMP <= ~clk_blink_TEMP;
    end
    else begin
        clk_counter <= clk_counter+1;
    end
end
    
assign clk_blink = clk_blink_TEMP;

endmodule
