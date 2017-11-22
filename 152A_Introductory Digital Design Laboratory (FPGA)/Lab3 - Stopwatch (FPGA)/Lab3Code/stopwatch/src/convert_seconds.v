`timescale 1ns / 1ps

module convert_seconds(
    input [5:0]     seconds_output,

    output [7:0]    digit0_display,     // What to display on each digit
    output [7:0]    digit1_display
    );

reg [3:0]   digit1_display_temp;
reg [3:0]   digit0_display_temp;

reg [7:0]   digit1_reg;
reg [7:0]   digit0_reg;

always @ (*) begin
    case (seconds_output)
        6'b00_0000: begin digit1_display_temp = 0; digit0_display_temp = 0; end
        6'b00_0001: begin digit1_display_temp = 0; digit0_display_temp = 1; end
        6'b00_0010: begin digit1_display_temp = 0; digit0_display_temp = 2; end
        6'b00_0011: begin digit1_display_temp = 0; digit0_display_temp = 3; end
        6'b00_0100: begin digit1_display_temp = 0; digit0_display_temp = 4; end
        6'b00_0101: begin digit1_display_temp = 0; digit0_display_temp = 5; end
        6'b00_0110: begin digit1_display_temp = 0; digit0_display_temp = 6; end
        6'b00_0111: begin digit1_display_temp = 0; digit0_display_temp = 7; end
        6'b00_1000: begin digit1_display_temp = 0; digit0_display_temp = 8; end
        6'b00_1001: begin digit1_display_temp = 0; digit0_display_temp = 9; end

        6'b00_1010: begin digit1_display_temp = 1; digit0_display_temp = 0; end
        6'b00_1011: begin digit1_display_temp = 1; digit0_display_temp = 1; end
        6'b00_1100: begin digit1_display_temp = 1; digit0_display_temp = 2; end
        6'b00_1101: begin digit1_display_temp = 1; digit0_display_temp = 3; end
        6'b00_1110: begin digit1_display_temp = 1; digit0_display_temp = 4; end
        6'b00_1111: begin digit1_display_temp = 1; digit0_display_temp = 5; end
        6'b01_0000: begin digit1_display_temp = 1; digit0_display_temp = 6; end
        6'b01_0001: begin digit1_display_temp = 1; digit0_display_temp = 7; end
        6'b01_0010: begin digit1_display_temp = 1; digit0_display_temp = 8; end
        6'b01_0011: begin digit1_display_temp = 1; digit0_display_temp = 9; end

        6'b01_0100: begin digit1_display_temp = 2; digit0_display_temp = 0; end
        6'b01_0101: begin digit1_display_temp = 2; digit0_display_temp = 1; end
        6'b01_0110: begin digit1_display_temp = 2; digit0_display_temp = 2; end
        6'b01_0111: begin digit1_display_temp = 2; digit0_display_temp = 3; end
        6'b01_1000: begin digit1_display_temp = 2; digit0_display_temp = 4; end
        6'b01_1001: begin digit1_display_temp = 2; digit0_display_temp = 5; end
        6'b01_1010: begin digit1_display_temp = 2; digit0_display_temp = 6; end
        6'b01_1011: begin digit1_display_temp = 2; digit0_display_temp = 7; end
        6'b01_1100: begin digit1_display_temp = 2; digit0_display_temp = 8; end
        6'b01_1101: begin digit1_display_temp = 2; digit0_display_temp = 9; end

        6'b01_1110: begin digit1_display_temp = 3; digit0_display_temp = 0; end
        6'b01_1111: begin digit1_display_temp = 3; digit0_display_temp = 1; end
        6'b10_0000: begin digit1_display_temp = 3; digit0_display_temp = 2; end
        6'b10_0001: begin digit1_display_temp = 3; digit0_display_temp = 3; end
        6'b10_0010: begin digit1_display_temp = 3; digit0_display_temp = 4; end
        6'b10_0011: begin digit1_display_temp = 3; digit0_display_temp = 5; end
        6'b10_0100: begin digit1_display_temp = 3; digit0_display_temp = 6; end
        6'b10_0101: begin digit1_display_temp = 3; digit0_display_temp = 7; end
        6'b10_0110: begin digit1_display_temp = 3; digit0_display_temp = 8; end
        6'b10_0111: begin digit1_display_temp = 3; digit0_display_temp = 9; end

        6'b10_1000: begin digit1_display_temp = 4; digit0_display_temp = 0; end
        6'b10_1001: begin digit1_display_temp = 4; digit0_display_temp = 1; end
        6'b10_1010: begin digit1_display_temp = 4; digit0_display_temp = 2; end
        6'b10_1011: begin digit1_display_temp = 4; digit0_display_temp = 3; end
        6'b10_1100: begin digit1_display_temp = 4; digit0_display_temp = 4; end
        6'b10_1101: begin digit1_display_temp = 4; digit0_display_temp = 5; end
        6'b10_1110: begin digit1_display_temp = 4; digit0_display_temp = 6; end
        6'b10_1111: begin digit1_display_temp = 4; digit0_display_temp = 7; end
        6'b11_0000: begin digit1_display_temp = 4; digit0_display_temp = 8; end
        6'b11_0001: begin digit1_display_temp = 4; digit0_display_temp = 9; end

        6'b11_0010: begin digit1_display_temp = 5; digit0_display_temp = 0; end
        6'b11_0011: begin digit1_display_temp = 5; digit0_display_temp = 1; end
        6'b11_0100: begin digit1_display_temp = 5; digit0_display_temp = 2; end
        6'b11_0101: begin digit1_display_temp = 5; digit0_display_temp = 3; end
        6'b11_0110: begin digit1_display_temp = 5; digit0_display_temp = 4; end
        6'b11_0111: begin digit1_display_temp = 5; digit0_display_temp = 5; end
        6'b11_1000: begin digit1_display_temp = 5; digit0_display_temp = 6; end
        6'b11_1001: begin digit1_display_temp = 5; digit0_display_temp = 7; end
        6'b11_1010: begin digit1_display_temp = 5; digit0_display_temp = 8; end
        6'b11_1011: begin digit1_display_temp = 5; digit0_display_temp = 9; end
        default: begin digit1_display_temp = 0; digit0_display_temp = 0; end
    endcase
    
    /* DISPLAY TEMP
      0
    5   1
      6
    4   2
      3    7
    */

    case (digit1_display_temp)
        4'h0: digit1_reg = 8'b1100_0000;
        4'h1: digit1_reg = 8'b1111_1001;
        4'h2: digit1_reg = 8'b1010_0100;
        4'h3: digit1_reg = 8'b1011_0000;
        4'h4: digit1_reg = 8'b1001_1001;
        4'h5: digit1_reg = 8'b1001_0010;
        4'h6: digit1_reg = 8'b1000_0010;
        4'h7: digit1_reg = 8'b1111_1000;
        4'h8: digit1_reg = 8'b1000_0000;
        4'h9: digit1_reg = 8'b1001_0000;
        default: digit1_reg = 8'b0000_0000;
    endcase

    case (digit0_display_temp)
        4'h0: digit0_reg = 8'b1100_0000;
        4'h1: digit0_reg = 8'b1111_1001;
        4'h2: digit0_reg = 8'b1010_0100;
        4'h3: digit0_reg = 8'b1011_0000;
        4'h4: digit0_reg = 8'b1001_1001;
        4'h5: digit0_reg = 8'b1001_0010;
        4'h6: digit0_reg = 8'b1000_0010;
        4'h7: digit0_reg = 8'b1111_1000;
        4'h8: digit0_reg = 8'b1000_0000;
        4'h9: digit0_reg = 8'b1001_0000;
        default: digit0_reg = 8'b0000_0000;
    endcase
end

assign digit0_display = digit0_reg;
assign digit1_display = digit1_reg;

endmodule // convert_seconds