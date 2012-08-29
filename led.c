#include <stdint.h>
#include <avr/io.h>

#include "led.h"

uint8_t led_blink_time = 0;
uint8_t led_blink_pattern = 0;

// Initialise the LED.
void led_init(void) {
	LED_PORT &= (uint8_t)~_BV(LED_BIT);
	LED_DDR |= _BV(LED_BIT);
}

// Blink the LED briefly to indicate activity.
void led_blink(enum led_blink_pattern_t pattern) {
	led_blink_pattern = pattern;
	led_blink_time = 0;
}

// Update the LED blink state. This should be called periodically at a constant rate.
void led_update(void) {
	if (led_blink_time) {
		--led_blink_time;
	} else {
		if (led_blink_pattern & 1) {
			LED_PORT &= (uint8_t)~_BV(LED_BIT);
		} else {
			LED_PORT |= _BV(LED_BIT);
		}
		led_blink_pattern >>= 1;
		led_blink_time = LED_UPDATE_PERIOD;
	}
}