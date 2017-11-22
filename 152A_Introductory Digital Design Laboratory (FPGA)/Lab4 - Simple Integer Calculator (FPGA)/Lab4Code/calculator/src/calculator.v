module calculator(
    output [1:0] led,

    input clk,

    input btnU,
    input btnD,
    input btnL,
    input btnR,

    input btnS,

    input sw,

    output [3:0] an,
    output [7:0] seg
    );

// CLOCKS
wire clk_blink;     // 1.5      Hz   Blink
wire clk_666;       // 666.66   Hz  Display

assign led[1] = (mode == 1);
assign led[0] = (sw);


// CURRENT VALUE OF REGISTER
wire signed [15:0] current_value;

// NEW VALUE FOR REGISTER
wire signed [15:0] new_value;

// MODE TRACKER
reg [1:0] mode;     // 0 = Default
                    // 1 = Calculation (Digit Editing)
                    // 2 = Memory
                    // 3 = PEMDAS!!!!!
// OPERATION TRACKER
reg [1:0] operation;

// LOAD TRIGGER (LOAD TO REGISTER)
reg load;

// OUTPUT FOR EACH DIGIT
wire [7:0] digit0_display;
wire [7:0] digit1_display;
wire [7:0] digit2_display;
wire [7:0] digit3_display;

wire [1:0] current_register;
wire [15:0] num_converted;

wire [1:0] digit;

wire overflow;
wire overflow_r;

// DEBOUNCING VARIABLES
reg UP_DB;
reg DOWN_DB;
reg LEFT_DB;
reg RIGHT_DB;
reg SELECT_DB;

// BLIP VARIABLES
wire UP;
wire DOWN;
wire LEFT;
wire RIGHT;
wire SELECT;

initial begin
    mode = 0;       // MODE: DEFAULT
    load = 0;       // LOAD: NOT LOADING INTO REGISTER
    operation = 0;  // OPERATION: NO CURRENT OPERATION
end

// Debouncing
always @ (posedge clk) begin
    UP_DB <= btnU;
    DOWN_DB <= btnD;
    LEFT_DB <= btnL;
    RIGHT_DB <= btnR;
    SELECT_DB <= btnS;
end

posedge_input posedge_up(
                .INPUT   (UP_DB),
                .clk     (clk_666),

                .posedge_INPUT(UP)
                );

posedge_input posedge_down(
                .INPUT   (DOWN_DB),
                .clk     (clk_666),

                .posedge_INPUT(DOWN)
                );

posedge_input posedge_left(
                .INPUT   (LEFT_DB),
                .clk     (clk_666),

                .posedge_INPUT(LEFT)
                );

posedge_input posedge_right(
                .INPUT   (RIGHT_DB),
                .clk     (clk_666),

                .posedge_INPUT(RIGHT)
                );

posedge_input posedge_select(
                .INPUT   (SELECT_DB),
                .clk     (clk_666),

                .posedge_INPUT(SELECT)
                );

// State transition table
always @ (posedge clk_666) begin
    // if (SELECT_DB && !SELECT) begin
    if (SELECT) begin
        if (mode == 0) begin    // DEFAULT
            mode <= 2;
            load <= 0;
        end
        else if (mode == 1) begin   // CALCULATE
            mode <= 0;
            load <= 1;
        end
        else if (mode == 2) begin   // MEMORY
            mode <= 0;
            load <= 0;
        end
        else if (mode == 3) begin   //ASDPFOJKA;VBLS
            load <= 0;
        end
    end

    // else if (RIGHT_DB && !RIGHT) begin // Addition
    else if (RIGHT) begin
        if (mode == 0) begin   
            mode <= 1;
            operation <= 0;
        end
        load <= 0;
    end

    // else if (LEFT_DB && !LEFT) begin // Subtraction
    else if (LEFT) begin
        if (mode == 0) begin   
            mode <= 1;
            operation <= 1;
        end
        load <= 0;
    end

    // else if (UP_DB && !UP) begin // Multiplication
    else if (UP) begin
        if (mode == 0) begin   
            mode <= 1;
            operation <= 2;
        end
        load <= 0;
    end


    // else if (DOWN_DB && !DOWN) begin // Division
    else if (DOWN) begin
        if (mode == 0) begin   
            mode <= 1;
            operation <= 3;
        end
        load <= 0;
    end    
    
end

make_clocks make_clocks_( // INPUTS
		                 .clk(clk),
		                  // OUTPUTS
		                 .clk_blink(clk_blink),
		                 .clk_666(clk_666)
		                 );
                   
registers registers_( 	// INPUTS
                        .clk(clk_666),

						.LEFT(LEFT),	// Selecting Register
		                .RIGHT(RIGHT),
                        .DOWN            (DOWN),

		                .mode(mode),
		                
                        .overflow        (overflow),

		                .load(load),	// Updating Register
		                .new_value(new_value),
		                
		                // OUTPUTS
                        .overflow_r      (overflow_r),
                        .current_register(current_register),
		                .current_value(current_value)
		                );

calculate calculate_( 	// INPUTS
						.sw(sw),						// Slider for PEMDAS

						.clk(clk_666),

		                .UP(UP),						// Debounced button signals
		                .DOWN(DOWN),
		                .LEFT(LEFT),
		                .RIGHT(RIGHT),
		                .SELECT(SELECT),

		                .operation(operation),			// Variables for states
		                .mode(mode),

		                .current_value(current_value),	// Current value of register

		                // OUTPUTS
                        .num_converted(num_converted),
		                .new_value(new_value),			// New value for register

                        .overflow     (overflow),
                        .digit        (digit)
		                );
                    
display_convert display_convert_( 	// INPUTS
                                    .clk_blink       (clk_blink),
									.mode(mode),							// Current State
			                        
			                        .current_value(current_value),			// Display depending on mode
			                        .calculate_input(num_converted),
                                    .current_register(current_register),
			                        
                                    .overflow_r      (overflow_r),

			                        // OUTPUTS
			                        .digit0_display(digit0_display),		// Converted digits for output
			                        .digit1_display(digit1_display),
			                        .digit2_display(digit2_display),
			                        .digit3_display(digit3_display)
			                        );       

blink_display blink_display_(   // INPUTS
								.display_clk(clk_666),				// Refresh Rate
		                        .blink_clk(clk_blink),				// Blink Rate
		                    
		                        .mode(mode),						// Blink or Not
		                        
		                        .digit0_display(digit0_display),	// What to display on each digit
		                        .digit1_display(digit1_display),
		                        .digit2_display(digit2_display),
		                        .digit3_display(digit3_display),
		                        
                                .digit         (digit),

		                        // OUTPUTS
		                        .seg(seg),
		                        .an(an)
		                        );
                        
endmodule
