`timescale 1ns / 1ps

module time_counter(
    input           counting_clk,       // Regular counting rate
    input           adjusting_clk,      // Double counting rate (for adjust)
    input           refresh_clk,        // Decide which clk is the magic clock

    input           RESET,              // Reset counters

    input           dir,                // 0 - adjust up, 1 - adjust down
    input           sel,                // 0 - adjust minutes, 1 - adjust seconds
    input           adj,                // 0 - regular counting, 1 - adjust time

    output [7:0]    digit0_display,     // What to display on each digit
    output [7:0]    digit1_display,
    output [7:0]    digit2_display,
    output [7:0]    digit3_display
    );

wire [5:0] seconds_output;   // allow max of 59 seconds
wire [6:0] minutes_output;   // allow max of 99 minutes

reg magic_clk;

always @ (posedge refresh_clk) begin
    if (adj) begin
        magic_clk = adjusting_clk;
    end
    else begin
        magic_clk = counting_clk;
    end
end

second_counter second(
    .magic_clk     (magic_clk),

    .reset         (RESET),

    .dir           (dir),
    .sel           (sel),
    .adj           (adj),

    .seconds_output(seconds_output)
    );

minute_counter minute(
    .magic_clk     (magic_clk),

    .reset         (RESET),

    .dir           (dir),
    .sel           (sel),
    .adj           (adj),

    .seconds_output(seconds_output),

    .minutes_output(minutes_output)
    );

display_convert convert(
    .seconds_output(seconds_output),
    .minutes_output(minutes_output),

    .digit0_display(digit0_display),
    .digit1_display(digit1_display),
    .digit2_display(digit2_display),
    .digit3_display(digit3_display)
    );

endmodule