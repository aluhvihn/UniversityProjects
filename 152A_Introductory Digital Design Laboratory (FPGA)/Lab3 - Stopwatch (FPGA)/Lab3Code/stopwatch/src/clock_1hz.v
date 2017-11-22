`timescale 1ns / 1ps

module clock_1hz(
    input       clk,
    input       pause,
    output      clk_1
    );

reg [25:0] clk_counter;
reg clk_1_TEMP;

initial begin
    clk_counter = 26'b0;
    clk_1_TEMP = 0;
end

always @ (posedge clk) begin
    if (!pause) begin   // ONLY COUNT WHEN NOT PAUSED
        if (clk_counter == 26'b10_1111_1010_1111_0000_1000_0000) begin
            clk_counter <= 0;
            clk_1_TEMP <= ~clk_1_TEMP;
        end
        else begin
            clk_counter <= clk_counter+1;
        end
    end
end
    
assign clk_1 = clk_1_TEMP;

endmodule
