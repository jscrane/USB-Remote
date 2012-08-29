#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "ir.h"
#include "usb_keyboard.h"
#include "led.h"

// 4ms timer.
ISR(TIM0_COMPA_vect) {
	// USB keyboard idle timer.
	usb_keyboard_idle();
	// Update the LED output.
	led_update();
}

// Called when an NEC IR code has been received. The code is then translated into keystrokes and sent via the USB keyboard code.
void ir_nec_code_received(uint8_t address, uint8_t command, uint8_t repeat_count) {
	if (repeat_count)
		return;

        led_blink(LED_BLINK_PATTERN_SHORT);

        struct usb_keyboard_modified_key_t key;
	key.modifier = USB_KEYBOARD_KEY_MODIFIER_NONE;

	switch (command) {
	case 0x4d: 
		key.key = USB_KEYBOARD_KEY_S;
		break;
	case 0x54: 
		key.key = USB_KEYBOARD_KEY_SPACE;
		break;
	case 0x16: 
		key.key = USB_KEYBOARD_KEY_M;
		break;
	case 0x4c: 
		key.key = USB_KEYBOARD_KEY_R;
		break;
	case 0x05: 
		key.key = USB_KEYBOARD_KEY_U;
		break;
	case 0x0c: 
		key.key = USB_KEYBOARD_KEY_T;
		break;
	case 0x0a: 
		key.key = USB_KEYBOARD_KEY_MINUS;
		break;
	case 0x40: 
		key.key = USB_KEYBOARD_KEY_F;
		break;
	case 0x1e: 
		key.key = USB_KEYBOARD_KEY_EQUALS;
		break;
	case 0x12: 
		key.key = USB_KEYBOARD_KEY_0;
		break;
	case 0x02: 
		key.key = USB_KEYBOARD_KEY_D;
		break;
	case 0x1c: 
		key.key = USB_KEYBOARD_KEY_C;
		break;
	case 0x09: 
		key.key = USB_KEYBOARD_KEY_1;
		break;
	case 0x1d: 
		key.key = USB_KEYBOARD_KEY_2;
		break;
	case 0x1f: 
		key.key = USB_KEYBOARD_KEY_3;
		break;
	case 0x0d: 
		key.key = USB_KEYBOARD_KEY_4;
		break;
	case 0x19: 
		key.key = USB_KEYBOARD_KEY_5;
		break;
	case 0x1b: 
		key.key = USB_KEYBOARD_KEY_6;
		break;
	case 0x11: 
		key.key = USB_KEYBOARD_KEY_7;
		break;
	case 0x15: 
		key.key = USB_KEYBOARD_KEY_8;
		break;
	case 0x17: 
		key.key = USB_KEYBOARD_KEY_9;
		break;
	default:
		key.key = USB_KEYBOARD_KEY_SLASH;
		break;
	}
        usb_keyboard_send_key(key);
}

int main(void) {
	
	// Initialise the LED.
	led_init();
	
	// Initialise the IR decoder.
	ir_init();
	
	// Initialise the USB keyboard handler.
	usb_keyboard_init();

	// Initialise timer 0 to use it as a 4ms timer.
	TCCR0A |= _BV(WGM01); // Mode = 2, CTC.
	TCCR0B |= _BV(CS02); // clkIO/256
	OCR0A = ((256 * 4) / ((1000.0 * 256 * 256) / F_CPU)) - 1; // Desired interrupt frequency is once every 4ms.
	TIMSK0 |= _BV(OCIE0A);
	
	// Enable interrupts.
	sei();
	
	// Flash the LED to indicate we're running.
	led_blink(LED_BLINK_PATTERN_3_MEDIUM);
	
	// Infinite loop.
	for(;;) {
		// USB polling.
		usb_keyboard_poll();
	}
}
