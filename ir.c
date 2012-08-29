#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "ir.h"
#include "ir_nec.h"

ISR(TIMER1_CAPT_vect) {
	// Fetch time.
	uint16_t delta_time = ICR1;
	if (TIFR1 & _BV(TOV1)) delta_time = 0xFFFF;
	// Invert the input capture edge select.
	TCCR1B ^= _BV(ICES1);
	// Reset timer.
	TCNT1 = 0;
	TIFR1 |= _BV(TOV1);
	
	// What's the direction of the edge?
	enum ir_edge_direction_t edge = (TCCR1B & _BV(ICES1)) != 0;
	
	// Pass on the information to the IR protocol handlers.
	ir_nec_edge_captured(edge, delta_time);	
}

void ir_init(void) {
	// Enable the noise canceller, capture on a negative edge and use a clkIO/256 prescaler.
	TCCR1B |= _BV(CS12);
	// Enable interrupts on input capture.
	TIMSK1 |= _BV(ICIE1);
}
