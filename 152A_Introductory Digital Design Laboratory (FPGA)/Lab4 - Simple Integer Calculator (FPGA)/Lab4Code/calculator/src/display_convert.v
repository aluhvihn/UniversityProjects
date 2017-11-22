module display_convert(
    input           clk_blink,          // Used to alternate between current_value and a secondary value
                                        // (calculate_input for mode == 1, current_register for mode == 2)
    input [1:0]     mode,

    input   signed [15:0]    current_value,
    input   signed [15:0]    calculate_input,
    input          [1:0]     current_register,

    input           overflow_r,

    output [7:0]    digit0_display,     // What to display on each digit
    output [7:0]    digit1_display,
    output [7:0]    digit2_display,
    output [7:0]    digit3_display
    );

// EXAMPLE: INPUT == 98312
//    98312/10000 = 9
//    (98312%10000)/1000 = 8
//    (98312%1000)/100 = 3
//    (98312%100)/10 = 1
//    (98312%10) = 2

reg [3:0] dig0;
reg [3:0] dig1;
reg [3:0] dig2;
reg [3:0] dig3;

reg [7:0] digit0_display_t;
reg [7:0] digit1_display_t;
reg [7:0] digit2_display_t;
reg [7:0] digit3_display_t;

reg sign;

reg counter;

initial begin
    dig0 = 0;
    dig1 = 0;
    dig2 = 0;
    dig3 = 0;

    sign = 0;
    counter = 0;
end

always @ (posedge clk_blink) begin
    counter <= counter + 1 ;        // Used when in modes 1, 2 to alternate displayed value
end

always @ (*) begin
    if (mode == 1) begin
        if (calculate_input[15]) begin  // Negative
            sign = 1;
            dig3 = -calculate_input/1000;
            dig2 = -(calculate_input%1000)/100;
            dig1 = -(calculate_input%100)/10;
            dig0 = -(calculate_input%10);
        end
        else begin                      // Positive
            sign = 0;
            dig3 = calculate_input/1000;
            dig2 = (calculate_input%1000)/100;
            dig1 = (calculate_input%100)/10;
            dig0 = (calculate_input%10);
        end
    end
    
    else if (mode == 2 && counter) begin    // When in memory mode (2), alternate between "current_register" and "current_value"
        sign = 0;
        dig3 = 4'b1111;
        dig2 = 4'b1111;
        dig1 = 4'b1111;
        dig0 = current_register;
    end

    else begin  // mode == 0, or mode==2&&!counter
        if (overflow_r) begin
            sign = 0;
            dig3 = 4'hA;
            dig2 = 4'hA;
            dig1 = 4'hA;
            dig0 = 4'hA;
        end
        else if (current_value[15]) begin       // Negative
            sign = 1;
            dig3 = -current_value/1000;
            dig2 = -(current_value%1000)/100;
            dig1 = -(current_value%100)/10;
            dig0 = -(current_value%10);
        end
        else begin          // Positive
            sign = 0;
            dig3 = current_value/1000;
            dig2 = (current_value%1000)/100;
            dig1 = (current_value%100)/10;
            dig0 = (current_value%10);
        end
    end

    /* DISPLAY TEMP
      0
    5   1
      6
    4   2
      3    7
    */
    
    case (dig3)
        4'h0:   begin
                    if (!sign) begin    // Positive
                        digit3_display_t = 8'b1100_0000;
                    end
                    else begin          // Negative
                        digit3_display_t = 8'b0100_0000;
                    end
                end
        4'h1:   begin
                    if (!sign) begin
                        digit3_display_t = 8'b1111_1001;
                    end
                    else begin
                        digit3_display_t = 8'b0111_1001;
                    end
                end
        4'h2:   begin
                    if (!sign) begin    // Positive
                        digit3_display_t = 8'b1010_0100;
                    end
                    else begin          // Negative
                        digit3_display_t = 8'b0010_0100;
                    end
                end
        4'h3:   begin
                    if (!sign) begin    // Positive
                        digit3_display_t = 8'b1011_0000;
                    end
                    else begin          // Negative
                        digit3_display_t = 8'b0011_0000;
                    end
                end
        4'h4:   begin
                    if (!sign) begin    // Positive
                        digit3_display_t = 8'b1001_1001;
                    end
                    else begin          // Negative
                        digit3_display_t = 8'b0001_1001;
                    end
                end
        4'h5:   begin
                    if (!sign) begin    // Positive
                        digit3_display_t = 8'b1001_0010;
                    end
                    else begin          // Negative
                        digit3_display_t = 8'b0001_0010;
                    end
                end
        4'h6:   begin
                    if (!sign) begin    // Positive
                        digit3_display_t = 8'b1000_0010;
                    end
                    else begin          // Negative
                        digit3_display_t = 8'b0000_0010;
                    end
                end
        4'h7:   begin
                    if (!sign) begin    // Positive
                        digit3_display_t = 8'b1111_1000;
                    end
                    else begin          // Negative
                        digit3_display_t = 8'b0111_1000;
                    end
                end
        4'h8:   begin
                    if (!sign) begin    // Positive
                        digit3_display_t = 8'b1000_0000;
                    end
                    else begin          // Negative
                        digit3_display_t = 8'b0000_0000;
                    end
                end
        4'h9:   begin
                    if (!sign) begin    // Positive
                        digit3_display_t = 8'b1001_0000;
                    end
                    else begin          // Negative
                        digit3_display_t = 8'b0001_0000;
                    end
                end
        default: digit3_display_t = 8'b1111_1111;
    endcase
    
    case (dig2)
        4'h0:   begin
                    if (!sign) begin    // Positive
                        digit2_display_t = 8'b1100_0000;
                    end
                    else begin          // Negative
                        digit2_display_t = 8'b0100_0000;
                    end
                end
        4'h1:   begin
                    if (!sign) begin
                        digit2_display_t = 8'b1111_1001;
                    end
                    else begin
                        digit2_display_t = 8'b0111_1001;
                    end
                end
        4'h2:   begin
                    if (!sign) begin    // Positive
                        digit2_display_t = 8'b1010_0100;
                    end
                    else begin          // Negative
                        digit2_display_t = 8'b0010_0100;
                    end
                end
        4'h3:   begin
                    if (!sign) begin    // Positive
                        digit2_display_t = 8'b1011_0000;
                    end
                    else begin          // Negative
                        digit2_display_t = 8'b0011_0000;
                    end
                end
        4'h4:   begin
                    if (!sign) begin    // Positive
                        digit2_display_t = 8'b1001_1001;
                    end
                    else begin          // Negative
                        digit2_display_t = 8'b0001_1001;
                    end
                end
        4'h5:   begin
                    if (!sign) begin    // Positive
                        digit2_display_t = 8'b1001_0010;
                    end
                    else begin          // Negative
                        digit2_display_t = 8'b0001_0010;
                    end
                end
        4'h6:   begin
                    if (!sign) begin    // Positive
                        digit2_display_t = 8'b1000_0010;
                    end
                    else begin          // Negative
                        digit2_display_t = 8'b0000_0010;
                    end
                end
        4'h7:   begin
                    if (!sign) begin    // Positive
                        digit2_display_t = 8'b1111_1000;
                    end
                    else begin          // Negative
                        digit2_display_t = 8'b0111_1000;
                    end
                end
        4'h8:   begin
                    if (!sign) begin    // Positive
                        digit2_display_t = 8'b1000_0000;
                    end
                    else begin          // Negative
                        digit2_display_t = 8'b0000_0000;
                    end
                end
        4'h9:   begin
                    if (!sign) begin    // Positive
                        digit2_display_t = 8'b1001_0000;
                    end
                    else begin          // Negative
                        digit2_display_t = 8'b0001_0000;
                    end
                end
        4'hA: digit2_display_t = 8'b1000_0110;
        default: digit2_display_t = 8'b1111_1111;
    endcase

    case (dig1)
        4'h0:   begin
                    if (!sign) begin    // Positive
                        digit1_display_t = 8'b1100_0000;
                    end
                    else begin          // Negative
                        digit1_display_t = 8'b0100_0000;
                    end
                end
        4'h1:   begin
                    if (!sign) begin
                        digit1_display_t = 8'b1111_1001;
                    end
                    else begin
                        digit1_display_t = 8'b0111_1001;
                    end
                end
        4'h2:   begin
                    if (!sign) begin    // Positive
                        digit1_display_t = 8'b1010_0100;
                    end
                    else begin          // Negative
                        digit1_display_t = 8'b0010_0100;
                    end
                end
        4'h3:   begin
                    if (!sign) begin    // Positive
                        digit1_display_t = 8'b1011_0000;
                    end
                    else begin          // Negative
                        digit1_display_t = 8'b0011_0000;
                    end
                end
        4'h4:   begin
                    if (!sign) begin    // Positive
                        digit1_display_t = 8'b1001_1001;
                    end
                    else begin          // Negative
                        digit1_display_t = 8'b0001_1001;
                    end
                end
        4'h5:   begin
                    if (!sign) begin    // Positive
                        digit1_display_t = 8'b1001_0010;
                    end
                    else begin          // Negative
                        digit1_display_t = 8'b0001_0010;
                    end
                end
        4'h6:   begin
                    if (!sign) begin    // Positive
                        digit1_display_t = 8'b1000_0010;
                    end
                    else begin          // Negative
                        digit1_display_t = 8'b0000_0010;
                    end
                end
        4'h7:   begin
                    if (!sign) begin    // Positive
                        digit1_display_t = 8'b1111_1000;
                    end
                    else begin          // Negative
                        digit1_display_t = 8'b0111_1000;
                    end
                end
        4'h8:   begin
                    if (!sign) begin    // Positive
                        digit1_display_t = 8'b1000_0000;
                    end
                    else begin          // Negative
                        digit1_display_t = 8'b0000_0000;
                    end
                end
        4'h9:   begin
                    if (!sign) begin    // Positive
                        digit1_display_t = 8'b1001_0000;
                    end
                    else begin          // Negative
                        digit1_display_t = 8'b0001_0000;
                    end
                end
        4'hA: digit1_display_t = 8'b1010_1111;
        default: digit1_display_t = 8'b1111_1111;
    endcase

    case (dig0)
        4'h0:   begin
                    if (!sign) begin    // Positive
                        digit0_display_t = 8'b1100_0000;
                    end
                    else begin          // Negative
                        digit0_display_t = 8'b0100_0000;
                    end
                end
        4'h1:   begin
                    if (!sign) begin
                        digit0_display_t = 8'b1111_1001;
                    end
                    else begin
                        digit0_display_t = 8'b0111_1001;
                    end
                end
        4'h2:   begin
                    if (!sign) begin    // Positive
                        digit0_display_t = 8'b1010_0100;
                    end
                    else begin          // Negative
                        digit0_display_t = 8'b0010_0100;
                    end
                end
        4'h3:   begin
                    if (!sign) begin    // Positive
                        digit0_display_t = 8'b1011_0000;
                    end
                    else begin          // Negative
                        digit0_display_t = 8'b0011_0000;
                    end
                end
        4'h4:   begin
                    if (!sign) begin    // Positive
                        digit0_display_t = 8'b1001_1001;
                    end
                    else begin          // Negative
                        digit0_display_t = 8'b0001_1001;
                    end
                end
        4'h5:   begin
                    if (!sign) begin    // Positive
                        digit0_display_t = 8'b1001_0010;
                    end
                    else begin          // Negative
                        digit0_display_t = 8'b0001_0010;
                    end
                end
        4'h6:   begin
                    if (!sign) begin    // Positive
                        digit0_display_t = 8'b1000_0010;
                    end
                    else begin          // Negative
                        digit0_display_t = 8'b0000_0010;
                    end
                end
        4'h7:   begin
                    if (!sign) begin    // Positive
                        digit0_display_t = 8'b1111_1000;
                    end
                    else begin          // Negative
                        digit0_display_t = 8'b0111_1000;
                    end
                end
        4'h8:   begin
                    if (!sign) begin    // Positive
                        digit0_display_t = 8'b1000_0000;
                    end
                    else begin          // Negative
                        digit0_display_t = 8'b0000_0000;
                    end
                end
        4'h9:   begin
                    if (!sign) begin    // Positive
                        digit0_display_t = 8'b1001_0000;
                    end
                    else begin          // Negative
                        digit0_display_t = 8'b0001_0000;
                    end
                end
        4'hA: digit0_display_t = 8'b1010_1111;
        default: digit0_display_t = 8'b1111_1111;
    endcase


end

assign digit0_display = digit0_display_t;
assign digit1_display = digit1_display_t;
assign digit2_display = digit2_display_t;
assign digit3_display = digit3_display_t;

endmodule // display_convert