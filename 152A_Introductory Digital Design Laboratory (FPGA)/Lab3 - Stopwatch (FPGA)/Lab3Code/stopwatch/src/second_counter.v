`timescale 1ns / 1ps

module second_counter(
    input           magic_clk,

    input           reset,

    input           dir,
    input           sel,
    input           adj,

    output [5:0]    seconds_output
    );

reg [5:0] second_count;

initial begin
    second_count = 0;
end

always @ (negedge magic_clk, posedge reset) begin
    if (reset) begin
        second_count <= 0;
    end
    
    else if (!reset) begin
        // ADJ == 1, 2x speed
        if(adj) begin
            // SEL == 1, adjust seconds
            if(sel) begin
                // DIR == 1, adjust DOWN
                if (dir) begin
                    case (second_count)
                        6'b00_0000: second_count <= 6'b11_1011; // 00 - 1 = 59
                        default:    second_count <= second_count-1;
                    endcase
                end       
                // DIR == 0, adjust up     
                else begin
                    case (second_count)
                        6'b11_1011: second_count <= 6'b00_0000; // 59 + 1 = 00
                        default:    second_count <= second_count+1;
                    endcase
                end
            end
        end
        // ADJ == 0, 1x speed
        else if (!adj) begin
            // DIR == 1, adjust DOWN
            if (dir) begin
                case (second_count)
                    6'b00_0000: begin
                                    second_count <= 6'b11_1011; // 00 - 1 = 59
                                end
                    default :   begin
                                    second_count <= second_count-1;
                                end
                endcase
            end
            // !dir, up
            else begin
                case (second_count)
                    6'b11_1011: begin
                                    second_count <= 6'b00_0000; // 59 + 1 = 00
                                end
                    default : begin
                                  second_count <= second_count+1;
                              end// MINUTE > 0, REDUCE MINTUES
                endcase
            end
        end
    end
end
assign seconds_output = second_count;

endmodule // second_counter