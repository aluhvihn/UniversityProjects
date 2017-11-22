`timescale 1ns / 1ps

module blink_display(
    input        display_clk,           // Refresh rate
    input        blink_clk,

    input        sel,               // Which part to blink
    input        adj,               // Only blink when adjusting

    input  [7:0] digit0_display,    // What to display on each digit
    input  [7:0] digit1_display,
    input  [7:0] digit2_display,
    input  [7:0] digit3_display,

    output [7:0] seg,          // Which segments to display
    output [3:0] an           // Which digit to light up
    );

reg [1:0] counter;

reg [3:0] digit;
reg [7:0] digit_display;

initial begin
    counter = 2'b0;
end

always @ (posedge display_clk) begin
    
    counter <= counter+1;
    
    if (adj) begin
        if (blink_clk) begin
            if (sel) begin          // BLINK SECONDS
                if (!counter[1] && !counter[0]) begin
                    digit <= 4'b1111;
                    digit_display <= digit0_display;
                end
                
                else if (!counter[1] && counter[0]) begin
                    digit <= 4'b1111;
                    digit_display <= digit1_display;
                end
                
                else if (counter[1] && !counter[0]) begin
                    digit <= 4'b1011;
                    digit_display <= digit2_display;
                end

                else if (counter[1] && counter[0]) begin
                    digit <= 4'b0111;
                    digit_display <= digit3_display;
                end
            end

            else begin              // BLINK MINUTES
                if (!counter[1] && !counter[0]) begin
                    digit <= 4'b1110;
                    digit_display <= digit0_display;
                end
                
                else if (!counter[1] && counter[0]) begin
                    digit <= 4'b1101;
                    digit_display <= digit1_display;
                end
                
                else if (counter[1] && !counter[0]) begin
                    digit <= 4'b1111;
                    digit_display <= digit2_display;
                end

                else if (counter[1] && counter[0]) begin
                    digit <= 4'b1111;
                    digit_display <= digit3_display;
                end
            end
        end
        
        else begin
            
            if (!counter[1] && !counter[0]) begin
                digit <= 4'b1110;
                digit_display <= digit0_display;
            end
            
            else if (!counter[1] && counter[0]) begin
                digit <= 4'b1101;
                digit_display <= digit1_display;
            end
            
            else if (counter[1] && !counter[0]) begin
                digit <= 4'b1011;
                digit_display <= digit2_display;
            end

            else if (counter[1] && counter[0]) begin
                digit <= 4'b0111;
                digit_display <= digit3_display;
            end
        end

    end

    else begin
        
        if (!counter[1] && !counter[0]) begin
            digit <= 4'b1110;
            digit_display <= digit0_display;
        end
        
        else if (!counter[1] && counter[0]) begin
            digit <= 4'b1101;
            digit_display <= digit1_display;
        end
        
        else if (counter[1] && !counter[0]) begin
            digit <= 4'b1011;
            digit_display <= digit2_display;
        end

        else if (counter[1] && counter[0]) begin
            digit <= 4'b0111;
            digit_display <= digit3_display;
        end

    end

end

assign an = digit;
assign seg = digit_display;

endmodule
