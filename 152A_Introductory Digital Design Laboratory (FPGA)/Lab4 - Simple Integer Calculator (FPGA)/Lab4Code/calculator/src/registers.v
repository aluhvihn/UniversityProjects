module registers(
    // For selecting current register
    input clk,

    input LEFT,
    input RIGHT,
    input DOWN,

    input [1:0] mode,

    input overflow,
    
    // For updating register
    input load,
    input signed [15:0] new_value,
    
    output overflow_r,
    output [1:0] current_register,
    output signed [15:0] current_value
    );
    
reg [1:0] current_register_t;

reg signed [15:0] value;
reg signed [15:0] current_value_temp;

reg load0;
reg load1;
reg load2;
reg load3;

reg [3:0] register_overflow_temp;
reg overflow_r_temp;

wire signed [15:0] current_register_values [3:0];

initial begin
    current_register_t = 0;
    current_value_temp = 0;
    
    load0 = 0;
    load1 = 0;
    load2 = 0;
    load3 = 0;

    register_overflow_temp[0] = 0;
    register_overflow_temp[1] = 0;
    register_overflow_temp[2] = 0;
    register_overflow_temp[3] = 0;
    overflow_r_temp = 0;
end

// Update current register
always @ (posedge clk) begin
    if (LEFT) begin
        if (mode == 2) begin
            if (current_register_t == 0) begin
                current_register_t <= 3;
            end
            else begin
                current_register_t <= current_register_t - 1;
            end
        end
   end
   else if (RIGHT) begin
        if (mode == 2) begin
            if (current_register_t == 3) begin
                current_register_t <= 0;
            end
            else begin
                current_register_t <= current_register_t + 1;
            end
        end
   end
end

// Read and load from registers
always @ (*) begin
    // Set active output
    if (current_register_t == 0) begin
        current_value_temp = current_register_values[0];
        overflow_r_temp = register_overflow_temp[0];
    end
    else if (current_register_t == 1)  begin
        current_value_temp = current_register_values[1];
        overflow_r_temp = register_overflow_temp[1];
    end
    else if (current_register_t == 2) begin
        current_value_temp = current_register_values[2];
        overflow_r_temp = register_overflow_temp[2];
    end
    else begin
        current_value_temp = current_register_values[3];
        overflow_r_temp = register_overflow_temp[3];
    end


    if (mode == 2 && DOWN) begin // RESET
        load0 = (current_register_t == 0);
        load1 = (current_register_t == 1);
        load2 = (current_register_t == 2);
        load3 = (current_register_t == 3);
        value = 0;

        register_overflow_temp[current_register_t] = 0;
    end

    // Loading
    else if (load) begin
        load0 = (current_register_t == 0);
        load1 = (current_register_t == 1);
        load2 = (current_register_t == 2);
        load3 = (current_register_t == 3);
        value = new_value;
    end

    else begin 
        load0 = 0;
        load1 = 0;
        load2 = 0;
        load3 = 0;
    end

    if (overflow) begin
        register_overflow_temp[current_register_t] = 1;
        // register_overflow_temp[0] = (current_register_t == 0);
        // register_overflow_temp[1] = (current_register_t == 1);
        // register_overflow_temp[2] = (current_register_t == 2);
        // register_overflow_temp[3] = (current_register_t == 3);
    end
end

register_t r0(  .load(load0),
                .new_value(value),

                .current_value(current_register_values[0]));

register_t r1(  .load(load1),
                .new_value(value),

                .current_value(current_register_values[1]));

register_t r2(  .load(load2),
                .new_value(value),

                .current_value(current_register_values[2]));

register_t r3(  .load(load3),
                .new_value(value),

                .current_value(current_register_values[3]));

assign current_value = current_value_temp;
assign current_register = current_register_t;
assign overflow_r = overflow_r_temp;

endmodule
