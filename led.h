#ifndef LED_H
#define LED_H

// The PORT that the LED is attached to.
#define LED_PORT (PORTA)

// The DDR that the LED is attached to.
#define LED_DDR (DDRA)

// The index of the IO port that the LED is attached to.
#define LED_BIT (3)

// How many times to call led_update before it should update the LED state.
#define LED_UPDATE_PERIOD (40)

// Patterns for blinking the LED.
enum led_blink_pattern_t {
	LED_BLINK_PATTERN_SHORT = 0b00000001,
	LED_BLINK_PATTERN_LONG = 0b00001111,
	LED_BLINK_PATTERN_1_LONG_1_SHORT = 0b00100111,
	LED_BLINK_PATTERN_1_LONG_2_SHORT = 0b10100111,
	LED_BLINK_PATTERN_3_MEDIUM = 0b11011011,
};

// Initialise the LED.
void led_init(void);

// Blink the LED briefly to indicate activity.
void led_blink(enum led_blink_pattern_t pattern);

// Update the LED blink state. This should be called periodically at a constant rate.
void led_update(void);

#endif