`timescale 1ns / 1ps

module display_convert(
    input [5:0]     seconds_output,
    input [6:0]     minutes_output,

    output [7:0]    digit0_display,     // What to display on each digit
    output [7:0]    digit1_display,
    output [7:0]    digit2_display,
    output [7:0]    digit3_display
    );

convert_seconds sec(
    .seconds_output(seconds_output),

    .digit0_display(digit0_display),
    .digit1_display(digit1_display)
    );

convert_minutes min(
    .minutes_output(minutes_output),

    .digit2_display(digit2_display),
    .digit3_display(digit3_display)
    );

endmodule // display_convert