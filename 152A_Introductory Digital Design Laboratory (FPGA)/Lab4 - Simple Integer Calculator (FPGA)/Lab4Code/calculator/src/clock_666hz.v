module clock_666hz(
    input     clk,
    output    clk_666
    );

reg [16:0] clk_counter;
reg clk_666_TEMP;

initial begin
    clk_counter = 17'b0;
    clk_666_TEMP = 0;
end

always @ (posedge clk) begin
    if (clk_counter == 17'b1_0010_0100_1111_1000) begin
        clk_counter <= 0;
        clk_666_TEMP <= ~clk_666_TEMP;
    end
    else begin
        clk_counter <= clk_counter+1;
    end
end
    
assign clk_666 = clk_666_TEMP;

endmodule
