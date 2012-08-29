#ifndef IR_H
#define IR_H

// Calculate the number of timer ticks for a given number of seconds.
#define IR_TIME(t) ((uint16_t)(t*(F_CPU/256)))

// Represents the direction of the edge of a received signal.
enum ir_edge_direction_t {
	// The edge is falling (going from IR carrier to no IR carrier).
	IR_EDGE_FALLING,
	// The edge is rising (going from no IR carrier to IR carrier).
	IR_EDGE_RISING,
};

// Initialise the IR decoding code.
void ir_init(void);

#endif