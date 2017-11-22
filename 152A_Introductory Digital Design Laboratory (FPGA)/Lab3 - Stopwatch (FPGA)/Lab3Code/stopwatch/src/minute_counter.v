`timescale 1ns / 1ps

module minute_counter(
    input           magic_clk,

    input           reset,

    input           dir,
    input           sel,
    input           adj,

    input  [5:0]    seconds_output,

    output [6:0]    minutes_output
    );

reg [6:0] minute_count;

initial begin
    minute_count = 0;
end

always @ (negedge magic_clk, posedge reset) begin
    if (reset) begin
        minute_count <= 0;
    end
    
    else if (!reset) begin
        // ADJ == 1, 2x speed
        if(adj) begin
            // SEL == 0, adjust minutes
            if(!sel) begin
                // DIR == 1, adjust DOWN
                if (dir) begin
                    case (minute_count)
                        7'b000_0000: minute_count <= 7'b110_0011; // 00 - 1 = 99
                        default:     minute_count <= minute_count-1;
                    endcase // minute_count
                end

                // DIR == 0, adjust up     
                else begin
                    case (minute_count)
                        7'b110_0011: minute_count <= 7'b000_0000; // 99 + 1 = 00
                        default:     minute_count <= minute_count+1;
                    endcase // minute_count
                end
            end
        end
        else begin
            // If counting down
            if (dir && seconds_output == 6'b0) begin
                case (minute_count)
                        7'b000_0000: minute_count <= 7'b110_0011; // 00 - 1 = 99
                        default:     minute_count <= minute_count-1;
                endcase // minute_count
            end
            // If counting up
            else if (!dir && seconds_output == 6'b11_1011) begin
                case (minute_count)
                        7'b110_0011: minute_count <= 7'b000_0000; // 99 + 1 = 00
                        default:     minute_count <= minute_count+1;
                endcase // minute_count
            end
        end
    end
end

assign minutes_output = minute_count;

endmodule // minute_counter