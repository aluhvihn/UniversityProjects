module register_t(
    input load,
    input signed [15:0] new_value,

    output signed [15:0] current_value
    );
    
reg signed [15:0] value;

initial begin
    value = 0;
end

always @ (*) begin
	if (load) begin
	    value <= new_value;
	end

	else begin
		value <= value;
	end
end

assign current_value = value;

endmodule
