module ff_input(
    input INPUT,
    input clk,
    
    // For updating register
    output ff_INPUT
    );
    
reg flip_flopped_input;

initial begin
    flip_flopped_input = 0;
end

always @ (posedge clk) begin
    flip_flopped_input <= INPUT;
end

assign ff_INPUT = flip_flopped_input;

endmodule
