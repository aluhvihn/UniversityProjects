module blink_display(
    input        display_clk,           // Refresh rate
    input        blink_clk,             // Blink rate
    
    input  [1:0] mode,                  // Blink or not

    input  [7:0] digit0_display,    // What to display on each digit
    input  [7:0] digit1_display,
    input  [7:0] digit2_display,
    input  [7:0] digit3_display,

    input  [1:0] digit,

    output [7:0] seg,          // Which segments to display
    output [3:0] an           // Which digit to light up
    );

reg [1:0] counter;

reg [3:0] an_t;
reg [7:0] seg_t;

initial begin
    counter = 2'b0;
end

always @ (posedge display_clk) begin
    
    counter <= counter+1;
    
    if (mode == 1) begin    // MEMORY MODE/EDIT MODE

        if (!counter[1] && !counter[0]) begin
            // Alternate between Blank Display and Normal Display, according to blink_clk
            if (blink_clk && digit == 0) begin
                an_t <= 4'b1111;
                seg_t <= 8'b1111_1111;
            end
            else begin
                an_t <= 4'b1110;
                seg_t <= digit0_display;
            end
        end
        
        else if (!counter[1] && counter[0]) begin
            // Alternate between Blank Display and Normal Display, according to blink_clk
            if (blink_clk && digit == 1) begin
                an_t <= 4'b1111;
                seg_t <= 8'b1111_1111;
            end
            else begin
                an_t <= 4'b1101;
                seg_t <= digit1_display;
            end
        end
        
        else if (counter[1] && !counter[0]) begin
            // Alternate between Blank Display and Normal Display, according to blink_clk
            if (blink_clk && digit == 2) begin
                an_t <= 4'b1111;
                seg_t <= 8'b1111_1111;
            end
            else begin
                an_t <= 4'b1011;
                seg_t <= digit2_display;
            end
        end

        else if (counter[1] && counter[0]) begin
            // Alternate between Blank Display and Normal Display, according to blink_clk
            if (blink_clk && digit == 3) begin
                an_t <= 4'b1111;
                seg_t <= 8'b1111_1111;
            end
            else begin
                an_t <= 4'b0111;
                seg_t <= digit3_display;
            end
        end
        
    end

    else if (mode == 0 || mode == 2) begin  // NORMAL DISPLAY
        
        if (!counter[1] && !counter[0]) begin
            an_t <= 4'b1110;
            seg_t <= digit0_display;
        end
        
        else if (!counter[1] && counter[0]) begin
            an_t <= 4'b1101;
            seg_t <= digit1_display;
        end
        
        else if (counter[1] && !counter[0]) begin
            an_t <= 4'b1011;
            seg_t <= digit2_display;
        end

        else if (counter[1] && counter[0]) begin
            an_t <= 4'b0111;
            seg_t <= digit3_display;
        end

    end
    
end

assign an = an_t;
assign seg = seg_t;

endmodule
