`timescale 1ns / 1ps

module convert_minutes(
    input [6:0]     minutes_output,

    output [7:0]    digit2_display,     // What to display on each digit
    output [7:0]    digit3_display
    );

reg [3:0]   digit3_display_temp;
reg [3:0]   digit2_display_temp;

reg [7:0]   digit3_reg;
reg [7:0]   digit2_reg;

always @ (*) begin
    case (minutes_output)
        7'b000_0000: begin digit3_display_temp = 0; digit2_display_temp = 0; end
        7'b000_0001: begin digit3_display_temp = 0; digit2_display_temp = 1; end
        7'b000_0010: begin digit3_display_temp = 0; digit2_display_temp = 2; end
        7'b000_0011: begin digit3_display_temp = 0; digit2_display_temp = 3; end
        7'b000_0100: begin digit3_display_temp = 0; digit2_display_temp = 4; end
        7'b000_0101: begin digit3_display_temp = 0; digit2_display_temp = 5; end
        7'b000_0110: begin digit3_display_temp = 0; digit2_display_temp = 6; end
        7'b000_0111: begin digit3_display_temp = 0; digit2_display_temp = 7; end
        7'b000_1000: begin digit3_display_temp = 0; digit2_display_temp = 8; end
        7'b000_1001: begin digit3_display_temp = 0; digit2_display_temp = 9; end

        7'b000_1010: begin digit3_display_temp = 1; digit2_display_temp = 0; end
        7'b000_1011: begin digit3_display_temp = 1; digit2_display_temp = 1; end
        7'b000_1100: begin digit3_display_temp = 1; digit2_display_temp = 2; end
        7'b000_1101: begin digit3_display_temp = 1; digit2_display_temp = 3; end
        7'b000_1110: begin digit3_display_temp = 1; digit2_display_temp = 4; end
        7'b000_1111: begin digit3_display_temp = 1; digit2_display_temp = 5; end
        7'b001_0000: begin digit3_display_temp = 1; digit2_display_temp = 6; end
        7'b001_0001: begin digit3_display_temp = 1; digit2_display_temp = 7; end
        7'b001_0010: begin digit3_display_temp = 1; digit2_display_temp = 8; end
        7'b001_0011: begin digit3_display_temp = 1; digit2_display_temp = 9; end

        7'b001_0100: begin digit3_display_temp = 2; digit2_display_temp = 0; end
        7'b001_0101: begin digit3_display_temp = 2; digit2_display_temp = 1; end
        7'b001_0110: begin digit3_display_temp = 2; digit2_display_temp = 2; end
        7'b001_0111: begin digit3_display_temp = 2; digit2_display_temp = 3; end
        7'b001_1000: begin digit3_display_temp = 2; digit2_display_temp = 4; end
        7'b001_1001: begin digit3_display_temp = 2; digit2_display_temp = 5; end
        7'b001_1010: begin digit3_display_temp = 2; digit2_display_temp = 6; end
        7'b001_1011: begin digit3_display_temp = 2; digit2_display_temp = 7; end
        7'b001_1100: begin digit3_display_temp = 2; digit2_display_temp = 8; end
        7'b001_1101: begin digit3_display_temp = 2; digit2_display_temp = 9; end

        7'b001_1110: begin digit3_display_temp = 3; digit2_display_temp = 0; end
        7'b001_1111: begin digit3_display_temp = 3; digit2_display_temp = 1; end
        7'b010_0000: begin digit3_display_temp = 3; digit2_display_temp = 2; end
        7'b010_0001: begin digit3_display_temp = 3; digit2_display_temp = 3; end
        7'b010_0010: begin digit3_display_temp = 3; digit2_display_temp = 4; end
        7'b010_0011: begin digit3_display_temp = 3; digit2_display_temp = 5; end
        7'b010_0100: begin digit3_display_temp = 3; digit2_display_temp = 6; end
        7'b010_0101: begin digit3_display_temp = 3; digit2_display_temp = 7; end
        7'b010_0110: begin digit3_display_temp = 3; digit2_display_temp = 8; end
        7'b010_0111: begin digit3_display_temp = 3; digit2_display_temp = 9; end

        7'b010_1000: begin digit3_display_temp = 4; digit2_display_temp = 0; end
        7'b010_1001: begin digit3_display_temp = 4; digit2_display_temp = 1; end
        7'b010_1010: begin digit3_display_temp = 4; digit2_display_temp = 2; end
        7'b010_1011: begin digit3_display_temp = 4; digit2_display_temp = 3; end
        7'b010_1100: begin digit3_display_temp = 4; digit2_display_temp = 4; end
        7'b010_1101: begin digit3_display_temp = 4; digit2_display_temp = 5; end
        7'b010_1110: begin digit3_display_temp = 4; digit2_display_temp = 6; end
        7'b010_1111: begin digit3_display_temp = 4; digit2_display_temp = 7; end
        7'b011_0000: begin digit3_display_temp = 4; digit2_display_temp = 8; end
        7'b011_0001: begin digit3_display_temp = 4; digit2_display_temp = 9; end

        7'b011_0010: begin digit3_display_temp = 5; digit2_display_temp = 0; end
        7'b011_0011: begin digit3_display_temp = 5; digit2_display_temp = 1; end
        7'b011_0100: begin digit3_display_temp = 5; digit2_display_temp = 2; end
        7'b011_0101: begin digit3_display_temp = 5; digit2_display_temp = 3; end
        7'b011_0110: begin digit3_display_temp = 5; digit2_display_temp = 4; end
        7'b011_0111: begin digit3_display_temp = 5; digit2_display_temp = 5; end
        7'b011_1000: begin digit3_display_temp = 5; digit2_display_temp = 6; end
        7'b011_1001: begin digit3_display_temp = 5; digit2_display_temp = 7; end
        7'b011_1010: begin digit3_display_temp = 5; digit2_display_temp = 8; end
        7'b011_1011: begin digit3_display_temp = 5; digit2_display_temp = 9; end

        7'b011_1100: begin digit3_display_temp = 6; digit2_display_temp = 0; end
        7'b011_1101: begin digit3_display_temp = 6; digit2_display_temp = 1; end
        7'b011_1110: begin digit3_display_temp = 6; digit2_display_temp = 2; end
        7'b011_1111: begin digit3_display_temp = 6; digit2_display_temp = 3; end
        7'b100_0000: begin digit3_display_temp = 6; digit2_display_temp = 4; end
        7'b100_0001: begin digit3_display_temp = 6; digit2_display_temp = 5; end
        7'b100_0010: begin digit3_display_temp = 6; digit2_display_temp = 6; end
        7'b100_0011: begin digit3_display_temp = 6; digit2_display_temp = 7; end
        7'b100_0100: begin digit3_display_temp = 6; digit2_display_temp = 8; end
        7'b100_0101: begin digit3_display_temp = 6; digit2_display_temp = 9; end

        7'b100_0110: begin digit3_display_temp = 7; digit2_display_temp = 0; end
        7'b100_0111: begin digit3_display_temp = 7; digit2_display_temp = 1; end
        7'b100_1000: begin digit3_display_temp = 7; digit2_display_temp = 2; end
        7'b100_1001: begin digit3_display_temp = 7; digit2_display_temp = 3; end
        7'b100_1010: begin digit3_display_temp = 7; digit2_display_temp = 4; end
        7'b100_1011: begin digit3_display_temp = 7; digit2_display_temp = 5; end
        7'b100_1100: begin digit3_display_temp = 7; digit2_display_temp = 6; end
        7'b100_1101: begin digit3_display_temp = 7; digit2_display_temp = 7; end
        7'b100_1110: begin digit3_display_temp = 7; digit2_display_temp = 8; end
        7'b100_1111: begin digit3_display_temp = 7; digit2_display_temp = 9; end

        7'b101_0000: begin digit3_display_temp = 8; digit2_display_temp = 0; end
        7'b101_0001: begin digit3_display_temp = 8; digit2_display_temp = 1; end
        7'b101_0010: begin digit3_display_temp = 8; digit2_display_temp = 2; end
        7'b101_0011: begin digit3_display_temp = 8; digit2_display_temp = 3; end
        7'b101_0100: begin digit3_display_temp = 8; digit2_display_temp = 4; end
        7'b101_0101: begin digit3_display_temp = 8; digit2_display_temp = 5; end
        7'b101_0110: begin digit3_display_temp = 8; digit2_display_temp = 6; end
        7'b101_0111: begin digit3_display_temp = 8; digit2_display_temp = 7; end
        7'b101_1000: begin digit3_display_temp = 8; digit2_display_temp = 8; end
        7'b101_1001: begin digit3_display_temp = 8; digit2_display_temp = 9; end

        7'b101_1010: begin digit3_display_temp = 9; digit2_display_temp = 0; end
        7'b101_1011: begin digit3_display_temp = 9; digit2_display_temp = 1; end
        7'b101_1100: begin digit3_display_temp = 9; digit2_display_temp = 2; end
        7'b101_1101: begin digit3_display_temp = 9; digit2_display_temp = 3; end
        7'b101_1110: begin digit3_display_temp = 9; digit2_display_temp = 4; end
        7'b101_1111: begin digit3_display_temp = 9; digit2_display_temp = 5; end
        7'b110_0000: begin digit3_display_temp = 9; digit2_display_temp = 6; end
        7'b110_0001: begin digit3_display_temp = 9; digit2_display_temp = 7; end
        7'b110_0010: begin digit3_display_temp = 9; digit2_display_temp = 8; end
        7'b110_0011: begin digit3_display_temp = 9; digit2_display_temp = 9; end
        default: begin digit3_display_temp = 9; digit2_display_temp = 9; end
    endcase
    


    /* DISPLAY TEMP
      0
    5   1
      6
    4   2
      3    7
    */
    
    case (digit3_display_temp)
        4'h0: digit3_reg = 8'b1100_0000;
        4'h1: digit3_reg = 8'b1111_1001;
        4'h2: digit3_reg = 8'b1010_0100;
        4'h3: digit3_reg = 8'b1011_0000;
        4'h4: digit3_reg = 8'b1001_1001;
        4'h5: digit3_reg = 8'b1001_0010;
        4'h6: digit3_reg = 8'b1000_0010;
        4'h7: digit3_reg = 8'b1111_1000;
        4'h8: digit3_reg = 8'b1000_0000;
        4'h9: digit3_reg = 8'b1001_0000;
        default: digit3_reg = 8'b0000_0000;
    endcase

    case (digit2_display_temp)
        4'h0: digit2_reg = 8'b1100_0000;
        4'h1: digit2_reg = 8'b1111_1001;
        4'h2: digit2_reg = 8'b1010_0100;
        4'h3: digit2_reg = 8'b1011_0000;
        4'h4: digit2_reg = 8'b1001_1001;
        4'h5: digit2_reg = 8'b1001_0010;
        4'h6: digit2_reg = 8'b1000_0010;
        4'h7: digit2_reg = 8'b1111_1000;
        4'h8: digit2_reg = 8'b1000_0000;
        4'h9: digit2_reg = 8'b1001_0000;
        default: digit2_reg = 8'b0000_0000;
    endcase
end

assign digit2_display = digit2_reg;
assign digit3_display = digit3_reg;

endmodule // convert_minutes