#include <stdint.h>

#include <avr/io.h>

#include "usbdrv/usbdrv.h"
#include "usb_keyboard.h"

PROGMEM char usbHidReportDescriptor[35] = { /* USB report descriptor */
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,                    // USAGE (Keyboard)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x95, 0x08,                    //   REPORT_COUNT (8)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x25, 0x65,                    //   LOGICAL_MAXIMUM (101)
    0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)
    0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
    0xc0                           // END_COLLECTION
};

static uint8_t hid_report_buffer[2]; // Buffer for HID reports.
static uint8_t hid_idle_rate; // In 4ms units.
int8_t idle_timer = 5;
uint8_t pending_interrupt = 0;

// Key queue.

volatile uint8_t queue_count;
volatile uint8_t queue_read;
volatile uint8_t queue_write;

volatile struct usb_keyboard_modified_key_t queue[USB_KEYBOARD_QUEUE_SIZE];

void enqueue(struct usb_keyboard_modified_key_t value) {
	++queue_count;
	queue[queue_write] = value;
	queue_write = (queue_write + 1) % USB_KEYBOARD_QUEUE_SIZE;
}

struct usb_keyboard_modified_key_t dequeue(void) {
	struct usb_keyboard_modified_key_t value = queue[queue_read];
	queue_read = (queue_read + 1) % USB_KEYBOARD_QUEUE_SIZE;
	--queue_count;
	return value;
}

// Update the USB keyboard according to its idle counter. This should be called every 4ms.
void usb_keyboard_idle(void) {
	if (--idle_timer <= 0) {
		if (queue_count == 0) {
			struct usb_keyboard_modified_key_t no_key = { USB_KEYBOARD_KEY_MODIFIER_NONE, USB_KEYBOARD_KEY_NONE };
			enqueue(no_key);
		}
		idle_timer = hid_idle_rate;
	}
}

uint8_t usbFunctionSetup(uint8_t data[8]) {
	usbRequest_t *request = (void *)data;

	usbMsgPtr = hid_report_buffer;

	if ((request->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS) { // Class request type
		if (request->bRequest == USBRQ_HID_GET_REPORT) { 
			return sizeof(hid_report_buffer);
		} else if (request->bRequest == USBRQ_HID_GET_IDLE) {
			usbMsgPtr = &hid_idle_rate;
			return 1;
		} else if (request->bRequest == USBRQ_HID_SET_IDLE){
			hid_idle_rate = request->wValue.bytes[1];
		}
	}
	
	return 0;
}

// Initialise the USB keyboard.
void usb_keyboard_init(void) {
	// Initialise the USB library.
	usbInit();
}

// Poll the USB keyboard and handle events.
void usb_keyboard_poll(void) {
	usbPoll();
	if (queue_count > 0 && usbInterruptIsReady()) {
		struct usb_keyboard_modified_key_t key = dequeue();
		hid_report_buffer[0] = key.modifier;
		hid_report_buffer[1] = key.key;
		usbSetInterrupt(hid_report_buffer, sizeof(hid_report_buffer));
	}
}

// Send a key to the host.
void usb_keyboard_send_key(struct usb_keyboard_modified_key_t key) {
	if (queue_count < (USB_KEYBOARD_QUEUE_SIZE - 1)) {
		struct usb_keyboard_modified_key_t no_key = { USB_KEYBOARD_KEY_MODIFIER_NONE, USB_KEYBOARD_KEY_NONE };
		enqueue(key);
		enqueue(no_key);
	}
}