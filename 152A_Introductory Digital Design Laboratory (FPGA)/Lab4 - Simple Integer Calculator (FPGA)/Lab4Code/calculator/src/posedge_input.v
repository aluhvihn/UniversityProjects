module posedge_input(
    input INPUT,
    input clk,
    
    // For updating register
    output posedge_INPUT
    );
    
reg flip_flopped_input;

initial begin
    flip_flopped_input = 0;
end

always @ (posedge clk) begin
    flip_flopped_input <= INPUT;
end

assign posedge_INPUT = (INPUT && !flip_flopped_input);

endmodule
