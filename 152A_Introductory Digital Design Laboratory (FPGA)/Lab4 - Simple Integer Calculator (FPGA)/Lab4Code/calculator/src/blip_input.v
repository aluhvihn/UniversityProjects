module blip_input(
    input INPUT,
    input clk,
    
    // For updating register
    output blip_INPUT
    );
    
reg flip_flopped_input;

initial begin
    flip_flopped_input = 0;
end

always @ (posedge clk) begin
    flip_flopped_input <= INPUT;
end

assign blip_INPUT = (INPUT && !flip_flopped_input);

endmodule
