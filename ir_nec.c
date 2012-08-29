#include <stdint.h>

#include <avr/io.h>

#include "ir.h"
#include "ir_nec.h"

enum ir_nec_receiving_stage_t ir_nec_receiving_stage = IR_NEC_RECEIVING_START;

uint16_t incoming_address;
uint16_t incoming_command;
uint8_t bits_received;

uint8_t repeat_count;
uint8_t repeated_address;
uint8_t repeated_command;

// Stores the time of a complete high-low signal.
uint16_t captured_time = 0;

// Stores the previous complete high-low time (used to verify repeats).
uint16_t previous_captured_time = 0;

void ir_nec_edge_captured(enum ir_edge_direction_t edge, uint16_t delta_time) {
	if (edge == IR_EDGE_FALLING) {
		captured_time = delta_time;
	} else {
		uint32_t total_captured_time = captured_time + delta_time;
		captured_time = total_captured_time > 0xFFFF ? 0xFFFF : total_captured_time;
		// Process the received data.
		if ((ir_nec_receiving_stage == IR_NEC_RECEIVING_START) && (captured_time >= IR_NEC_START_BIT_MIN) && (captured_time <= IR_NEC_START_BIT_MAX)) {
			// We've just received the start bit.
			ir_nec_receiving_stage = IR_NEC_RECEIVING_ADDRESS;
			bits_received = 0;
		} else if ((ir_nec_receiving_stage == IR_NEC_RECEIVING_START) && (captured_time >= IR_NEC_REPEAT_BIT_MIN) && (captured_time <= IR_NEC_REPEAT_BIT_MAX) && (previous_captured_time >= IR_NEC_REPEAT_DELAY_MIN) && (previous_captured_time <= IR_NEC_REPEAT_DELAY_MAX)) {
			// We're repeating.
			if (repeat_count != 0xFF) ++repeat_count;
			ir_nec_code_received(repeated_address, repeated_command, repeat_count);
		} else if ((ir_nec_receiving_stage == IR_NEC_RECEIVING_ADDRESS || ir_nec_receiving_stage == IR_NEC_RECEIVING_COMMAND) && (captured_time >= IR_NEC_DATA_BIT_MIN) && (captured_time <= IR_NEC_DATA_BIT_MAX)) {
			// Where do we store the incoming data?
			uint16_t* receiving_data = (ir_nec_receiving_stage == IR_NEC_RECEIVING_ADDRESS) ? &incoming_address : &incoming_command;
			if (captured_time >= IR_NEC_DATA_BIT_THRESHOLD) {
				// We just received a 1 bit.
				*receiving_data |= _BV(bits_received);
			} else {
				// We just received a 0 bit.
				*receiving_data &= ~_BV(bits_received);
			}
			if (++bits_received == 16) {
				// We've received all 16 bits.
				if ((*receiving_data & 0xFF) != (~*receiving_data >> 8)) {
					// Invalid data, go back to the start.
					ir_nec_receiving_stage = IR_NEC_RECEIVING_START;
				} else if (ir_nec_receiving_stage == IR_NEC_RECEIVING_ADDRESS) {
					// Move on to receiving the command data.
					ir_nec_receiving_stage = IR_NEC_RECEIVING_COMMAND;
					bits_received = 0;
				} else {
					// We've received a complete, valid code. Notify the external program.
					ir_nec_receiving_stage = IR_NEC_RECEIVING_START;
//					ir_nec_code_received(repeated_address = (uint8_t)incoming_address, repeated_command = (uint8_t)incoming_command, repeat_count = 0);
					repeated_address = (uint8_t)incoming_address;
					repeated_command = (uint8_t)incoming_command;
					repeat_count = 0;
					ir_nec_code_received(repeated_address, repeated_command, repeat_count);
				}
			}
		} else {
			// No idea what that was, so go back to waiting for the start bit.
			ir_nec_receiving_stage = IR_NEC_RECEIVING_START;
		}
		previous_captured_time = captured_time;
	}
}
