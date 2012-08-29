#ifndef USB_KEYBOARD_H
#define USB_KEYBOARD_H

#include <avr/io.h>

enum usb_keyboard_key_t {
	USB_KEYBOARD_KEY_NONE = 0x00,
	USB_KEYBOARD_KEY_A = 0x04,
	USB_KEYBOARD_KEY_B = 0x05,
	USB_KEYBOARD_KEY_C = 0x06,
	USB_KEYBOARD_KEY_D = 0x07,
	USB_KEYBOARD_KEY_E = 0x08,
	USB_KEYBOARD_KEY_F = 0x09,
	USB_KEYBOARD_KEY_G = 0x0A,
	USB_KEYBOARD_KEY_H = 0x0B,
	USB_KEYBOARD_KEY_I = 0x0C,
	USB_KEYBOARD_KEY_J = 0x0D,
	USB_KEYBOARD_KEY_K = 0x0E,
	USB_KEYBOARD_KEY_L = 0x0F,
	USB_KEYBOARD_KEY_M = 0x10,
	USB_KEYBOARD_KEY_N = 0x11,
	USB_KEYBOARD_KEY_O = 0x12,
	USB_KEYBOARD_KEY_P = 0x13,
	USB_KEYBOARD_KEY_Q = 0x14,
	USB_KEYBOARD_KEY_R = 0x15,
	USB_KEYBOARD_KEY_S = 0x16,
	USB_KEYBOARD_KEY_T = 0x17,
	USB_KEYBOARD_KEY_U = 0x18,
	USB_KEYBOARD_KEY_V = 0x19,
	USB_KEYBOARD_KEY_W = 0x1A,
	USB_KEYBOARD_KEY_X = 0x1B,
	USB_KEYBOARD_KEY_Y = 0x1C,
	USB_KEYBOARD_KEY_Z = 0x1D,
	USB_KEYBOARD_KEY_1 = 0x1E,
	USB_KEYBOARD_KEY_2 = 0x1F,
	USB_KEYBOARD_KEY_3 = 0x20,
	USB_KEYBOARD_KEY_4 = 0x21,
	USB_KEYBOARD_KEY_5 = 0x22,
	USB_KEYBOARD_KEY_6 = 0x23,
	USB_KEYBOARD_KEY_7 = 0x24,
	USB_KEYBOARD_KEY_8 = 0x25,
	USB_KEYBOARD_KEY_9 = 0x26,
	USB_KEYBOARD_KEY_0 = 0x27,
	USB_KEYBOARD_KEY_ENTER = 0x28,
	USB_KEYBOARD_KEY_ESCAPE = 0x29,
	USB_KEYBOARD_KEY_BACKSPACE = 0x2A,
	USB_KEYBOARD_KEY_TAB = 0x2B,
	USB_KEYBOARD_KEY_SPACE = 0x2C,
	USB_KEYBOARD_KEY_MINUS = 0x2D,
	USB_KEYBOARD_KEY_EQUALS = 0x2E,
	USB_KEYBOARD_KEY_LEFT_BRACKET = 0x2F,
	USB_KEYBOARD_KEY_RIGHT_BRACKET = 0x30,
	USB_KEYBOARD_KEY_BACKSLASH = 0x31,
	USB_KEYBOARD_KEY_HASH = 0x32,
	USB_KEYBOARD_KEY_SEMICOLON = 0x33,
	USB_KEYBOARD_KEY_QUOTE = 0x34,
	USB_KEYBOARD_KEY_GRAVE_ACCENT = 0x35,
	USB_KEYBOARD_KEY_COMMA = 0x36,
	USB_KEYBOARD_KEY_FULL_STOP = 0x37,
	USB_KEYBOARD_KEY_SLASH = 0x38,
	USB_KEYBOARD_KEY_CAPS_LOCK = 0x39,
	USB_KEYBOARD_KEY_F1 = 0x3A,
	USB_KEYBOARD_KEY_F2 = 0x3B,
	USB_KEYBOARD_KEY_F3 = 0x3C,
	USB_KEYBOARD_KEY_F4 = 0x3D,
	USB_KEYBOARD_KEY_F5 = 0x3E,
	USB_KEYBOARD_KEY_F6 = 0x3F,
	USB_KEYBOARD_KEY_F7 = 0x40,
	USB_KEYBOARD_KEY_F8 = 0x41,
	USB_KEYBOARD_KEY_F9 = 0x42,
	USB_KEYBOARD_KEY_F10 = 0x43,
	USB_KEYBOARD_KEY_F11 = 0x44,
	USB_KEYBOARD_KEY_F12 = 0x45,
	USB_KEYBOARD_KEY_PRINT_SCREEN = 0x46,
	USB_KEYBOARD_KEY_SCROLL_LOCK = 0x47,
	USB_KEYBOARD_KEY_PAUSE = 0x48,
	USB_KEYBOARD_KEY_INSERT = 0x49,
	USB_KEYBOARD_KEY_HOME = 0x4A,
	USB_KEYBOARD_KEY_PAGE_UP = 0x4B,
	USB_KEYBOARD_KEY_DELETE = 0x4C,
	USB_KEYBOARD_KEY_END = 0x4D,
	USB_KEYBOARD_KEY_PAGE_DOWN = 0x4E,
	USB_KEYBOARD_KEY_CURSOR_RIGHT = 0x4F,
	USB_KEYBOARD_KEY_CURSOR_LEFT = 0x50,
	USB_KEYBOARD_KEY_CURSOR_DOWN = 0x51,
	USB_KEYBOARD_KEY_CURSOR_UP = 0x52,
	USB_KEYBOARD_KEY_NUM_LOCK = 0x53,
	USB_KEYBOARD_KEY_NUMPAD_SLASH = 0x54,
	USB_KEYBOARD_KEY_NUMPAD_ASTERISK = 0x55,
	USB_KEYBOARD_KEY_NUMPAD_MINUS = 0x56,
	USB_KEYBOARD_KEY_NUMPAD_PLUS = 0x57,
	USB_KEYBOARD_KEY_NUMPAD_ENTER = 0x58,
	USB_KEYBOARD_KEY_NUMPAD_1 = 0x59,
	USB_KEYBOARD_KEY_NUMPAD_2 = 0x5A,
	USB_KEYBOARD_KEY_NUMPAD_3 = 0x5B,
	USB_KEYBOARD_KEY_NUMPAD_4 = 0x5C,
	USB_KEYBOARD_KEY_NUMPAD_5 = 0x5D,
	USB_KEYBOARD_KEY_NUMPAD_6 = 0x5E,
	USB_KEYBOARD_KEY_NUMPAD_7 = 0x5F,
	USB_KEYBOARD_KEY_NUMPAD_8 = 0x60,
	USB_KEYBOARD_KEY_NUMPAD_9 = 0x61,
	USB_KEYBOARD_KEY_NUMPAD_0 = 0x62,
	USB_KEYBOARD_KEY_NUMPAD_POINT = 0x63,
	USB_KEYBOARD_KEY_NUMPAD_BACKSLASH = 0x64,
	USB_KEYBOARD_KEY_APPLICATION = 0x65,
	USB_KEYBOARD_KEY_POWER = 0x66,
	USB_KEYBOARD_KEY_NUMPAD_EQUALS = 0x67,
	USB_KEYBOARD_KEY_F13 = 0x68,
	USB_KEYBOARD_KEY_F14 = 0x69,
	USB_KEYBOARD_KEY_F15 = 0x6A,
	USB_KEYBOARD_KEY_F16 = 0x6B,
	USB_KEYBOARD_KEY_F17 = 0x6C,
	USB_KEYBOARD_KEY_F18 = 0x6D,
	USB_KEYBOARD_KEY_F19 = 0x6E,
	USB_KEYBOARD_KEY_F20 = 0x6F,
	USB_KEYBOARD_KEY_F21 = 0x70,
	USB_KEYBOARD_KEY_F22 = 0x71,
	USB_KEYBOARD_KEY_F23 = 0x72,
	USB_KEYBOARD_KEY_F24 = 0x73,
	USB_KEYBOARD_KEY_EXECUTE = 0x74,
	USB_KEYBOARD_KEY_HELP = 0x75,
	USB_KEYBOARD_KEY_MENU = 0x76,
	USB_KEYBOARD_KEY_SELECT = 0x77,
	USB_KEYBOARD_KEY_STOP = 0x78,
	USB_KEYBOARD_KEY_AGAIN = 0x79,
	USB_KEYBOARD_KEY_UNDO = 0x7A,
	USB_KEYBOARD_KEY_CUT = 0x7B,
	USB_KEYBOARD_KEY_COPY = 0x7C,
	USB_KEYBOARD_KEY_PASTE = 0x7D,
	USB_KEYBOARD_KEY_FIND = 0x7E,
	USB_KEYBOARD_KEY_MUTE = 0x7F,
	USB_KEYBOARD_KEY_VOLUME_UP = 0x80,
	USB_KEYBOARD_KEY_VOLUME_DOWN = 0x81,
	USB_KEYBOARD_KEY_LOCKING_CAPS_LOCK = 0x82,
	USB_KEYBOARD_KEY_LOCKING_NUM_LOCK = 0x83,
	USB_KEYBOARD_KEY_LOCKING_SCROLL_LOCK = 0x84,
	USB_KEYBOARD_KEY_NUMPAD_COMMA = 0x85,
	USB_KEYBOARD_KEY_NUMPAD_EQUAL = 0x86,
	USB_KEYBOARD_KEY_INTERNATIONAL_1 = 0x87,
	USB_KEYBOARD_KEY_INTERNATIONAL_2 = 0x88,
	USB_KEYBOARD_KEY_INTERNATIONAL_3 = 0x89,
	USB_KEYBOARD_KEY_INTERNATIONAL_4 = 0x8A,
	USB_KEYBOARD_KEY_INTERNATIONAL_5 = 0x8B,
	USB_KEYBOARD_KEY_INTERNATIONAL_6 = 0x8C,
	USB_KEYBOARD_KEY_INTERNATIONAL_7 = 0x8D,
	USB_KEYBOARD_KEY_INTERNATIONAL_8 = 0x8E,
	USB_KEYBOARD_KEY_INTERNATIONAL_9 = 0x8F,
	USB_KEYBOARD_KEY_LANG_1 = 0x90,
	USB_KEYBOARD_KEY_LANG_2 = 0x91,
	USB_KEYBOARD_KEY_LANG_3 = 0x92,
	USB_KEYBOARD_KEY_LANG_4 = 0x93,
	USB_KEYBOARD_KEY_LANG_5 = 0x94,
	USB_KEYBOARD_KEY_LANG_6 = 0x95,
	USB_KEYBOARD_KEY_LANG_7 = 0x96,
	USB_KEYBOARD_KEY_LANG_8 = 0x97,
	USB_KEYBOARD_KEY_LANG_9 = 0x98,
	USB_KEYBOARD_KEY_ALTERNATE_ERASE = 0x99,
	USB_KEYBOARD_KEY_SYS_REQ = 0x9A,
	USB_KEYBOARD_KEY_CANCEL = 0x9B,
	USB_KEYBOARD_KEY_CLEAR = 0x9C,
	USB_KEYBOARD_KEY_PRIOR = 0x9D,
	USB_KEYBOARD_KEY_RETURN = 0x9E,
	USB_KEYBOARD_KEY_SEPARATOR = 0x9F,
	USB_KEYBOARD_KEY_OUT = 0xA0,
	USB_KEYBOARD_KEY_OPER = 0xA1,
	USB_KEYBOARD_KEY_CLEAR_AGAIN = 0xA2,
	USB_KEYBOARD_KEY_CR_SEL = 0xA3,
	USB_KEYBOARD_KEY_EX_SEL = 0xA4,
	USB_KEYBOARD_KEY_LEFT_CONTROL = 0xE0,
	USB_KEYBOARD_KEY_LEFT_SHIFT = 0xE1,
	USB_KEYBOARD_KEY_LEFT_ALT = 0xE2,
	USB_KEYBOARD_KEY_LEFT_GUI = 0xE3,
	USB_KEYBOARD_KEY_RIGHT_CONTROL = 0xE4,
	USB_KEYBOARD_KEY_RIGHT_SHIFT = 0xE5,
	USB_KEYBOARD_KEY_RIGHT_ALT = 0xE6,
	USB_KEYBOARD_KEY_RIGHT_GUI = 0xE7,
};

enum usb_keyboard_key_modifier_t {
	USB_KEYBOARD_KEY_MODIFIER_NONE = 0,
	USB_KEYBOARD_KEY_MODIFIER_LEFT_CONTROL = _BV(0),
	USB_KEYBOARD_KEY_MODIFIER_LEFT_SHIFT = _BV(1),
	USB_KEYBOARD_KEY_MODIFIER_LEFT_ALT = _BV(2),
	USB_KEYBOARD_KEY_MODIFIER_LEFT_GUI = _BV(3),
	USB_KEYBOARD_KEY_MODIFIER_RIGHT_CONTROL = _BV(4),
	USB_KEYBOARD_KEY_MODIFIER_RIGHT_SHIFT = _BV(5),
	USB_KEYBOARD_KEY_MODIFIER_RIGHT_ALT = _BV(6),
	USB_KEYBOARD_KEY_MODIFIER_RIGHT_GUI = _BV(7),
};

struct usb_keyboard_modified_key_t {
	enum usb_keyboard_key_modifier_t modifier;
	enum usb_keyboard_key_t key;
};

#define USB_KEYBOARD_QUEUE_SIZE 16

// Initialise the USB keyboard.
void usb_keyboard_init(void);

// Poll the USB keyboard and handle events.
void usb_keyboard_poll(void);

// Send a key to the host.
void usb_keyboard_send_key(struct usb_keyboard_modified_key_t);

// Update the USB keyboard according to its idle counter. This should be called every 4ms.
void usb_keyboard_idle(void);

#endif