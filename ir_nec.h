#ifndef IR_NEC_H
#define IR_NEC_H

#include "ir.h"

// Minimum and maximum length of the start bit (nominally 9+4.5ms=13.5ms)
#define IR_NEC_START_BIT_MIN IR_TIME(13e-3)
#define IR_NEC_START_BIT_MAX IR_TIME(14e-3)

// Minimum and maximum length of data bits (nominally between 1.12ms and 2.25ms).
#define IR_NEC_DATA_BIT_MIN IR_TIME(0.62e-3)
#define IR_NEC_DATA_BIT_MAX IR_TIME(2.75e-3)

// Minimum and maximum length of the repeat bit (nominally 9+2.25ms=11.25ms).
#define IR_NEC_REPEAT_BIT_MIN IR_TIME(10.75e-3)
#define IR_NEC_REPEAT_BIT_MAX IR_TIME(11.75e-3)

// Minimum and maximum length of the delay between repeat signals.
#define IR_NEC_REPEAT_DELAY_MIN IR_TIME(0)
#define IR_NEC_REPEAT_DELAY_MAX IR_TIME(100e-3)

// Threshold between a 0 and 1 bit length.
#define IR_NEC_DATA_BIT_THRESHOLD ((IR_NEC_DATA_BIT_MIN+IR_NEC_DATA_BIT_MAX)/2)

// Defines the receiving stage.
enum ir_nec_receiving_stage_t {
	IR_NEC_RECEIVING_START,
	IR_NEC_RECEIVING_ADDRESS,
	IR_NEC_RECEIVING_COMMAND,
};

// Call to indicate a signal edge from the IR receiver has been captured.
void ir_nec_edge_captured(enum ir_edge_direction_t edge, uint16_t delta_time);

// Called when a NEC IR code is received.
extern void ir_nec_code_received(uint8_t address, uint8_t command, uint8_t repeat_count);

#endif
