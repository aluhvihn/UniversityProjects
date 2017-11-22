`timescale 1ns / 1ps

module clock_2hz(
    input       clk,
    input       pause,
    output      clk_2
    );

reg [24:0] clk_counter;
reg clk_2_TEMP;

initial begin
    clk_counter = 25'b0;
    clk_2_TEMP = 0;
end

always @ (posedge clk) begin
    if (!pause) begin   // ONLY COUNT WHEN NOT PAUSED
        if (clk_counter == 25'b1_0111_1101_0111_1000_0100_0000) begin
            clk_counter <= 0;
            clk_2_TEMP <= ~clk_2_TEMP;
        end
        else begin
            clk_counter <= clk_counter+1;
        end
    end
end
    
assign clk_2 = clk_2_TEMP;

endmodule
