module calculate(
    input sw,

    input clk,

    input UP,
    input DOWN,
    input LEFT,
    input RIGHT,
    input SELECT,
    
    input [1:0] operation,
    input [1:0] mode,

    input signed [15:0] current_value,

    output signed [15:0] num_converted,
    output signed [15:0] new_value,

    output overflow,
    output [1:0] digit
    );

reg [1:0] digit_t;
reg signed [15:0] number [3:0];
reg signed [15:0] num_converted_temp;
reg signed [15:0] new_value_temp;

reg overflow_temp;

initial begin
    digit_t = 0;
    
    number[0] = 0; // LSB
    number[1] = 0;
    number[2] = 0;
    number[3] = 0; // MSB

    new_value_temp = 0;
    
    num_converted_temp = 0;

    overflow_temp = 0;
end


always @ (*) begin
    // Convert "number[]" array into integer
    if (sw) begin   // negative
        num_converted_temp = number[3]*(-1000) + number[2]*(-100) + number[1]*(-10) - number[0];
    end
    else begin      // positive
        num_converted_temp = number[3]*(1000) + number[2]*(100) + number[1]*(10) + number[0];
    end
    
end

// "Confirm"
always @ (posedge clk) begin
    if (mode == 1 && SELECT) begin
        // Perform Operation
        if (operation == 0) begin // Add
            if (current_value + num_converted_temp > 9999 || current_value + num_converted_temp < -9999 ) begin
                overflow_temp = 1;
            end
            new_value_temp = current_value + num_converted_temp;
        end
        else if (operation == 1) begin  // Subtract
            if ( current_value-num_converted_temp < -9999 ||  current_value-num_converted_temp > 9999 ) begin
                overflow_temp = 1;
            end
            new_value_temp = current_value - num_converted_temp;
        end
        else if (operation == 2) begin  // Multiply
            if ( current_value*num_converted_temp > 9999 || current_value*num_converted_temp < -9999 ) begin
                overflow_temp = 1;
            end
            new_value_temp = current_value * num_converted_temp;
        end
        else if (operation == 3) begin  // Divide
            if (num_converted_temp == 0) begin  // Divide by 0
                overflow_temp = 1;
            end
            new_value_temp = current_value / num_converted_temp;
        end
    end

    else begin
        overflow_temp = 0;
    end
end

// "digit_t Editing" (Input)
always @ (posedge clk) begin
    if (UP) begin
        if (mode == 1) begin
            if (number[digit_t] == 9) begin
                number[digit_t] = 0;
            end
            else begin
                number[digit_t] = number[digit_t] + 1;
            end
        end
    end
    
    else if (DOWN) begin
        if (mode == 1) begin
            if (number[digit_t] == 0) begin
                number[digit_t] = 9;
            end
            else begin
                number[digit_t] = number[digit_t] - 1;
            end
        end
    end
    
    else if (LEFT) begin
        if (mode == 1) begin
            if (digit_t == 3) begin
                digit_t = 0;
            end
            else begin
                digit_t = digit_t + 1;
            end
        end
    end
    
    else if (RIGHT) begin
        if (mode == 1) begin
            if (digit_t == 0) begin
                digit_t = 3;
            end
            else begin
                digit_t = digit_t - 1;
            end
        end
    end

    else if (SELECT) begin 
        if (mode == 1) begin
            digit_t = 0;
            number[0] = 0; // LSB
            number[1] = 0;
            number[2] = 0;
            number[3] = 0; // MSB
        end
    end
end

assign new_value = new_value_temp;
assign num_converted = num_converted_temp;
assign digit = digit_t;
assign overflow = overflow_temp;

endmodule
