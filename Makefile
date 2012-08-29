###############################################################################
# Makefile for the project USB_Remote
###############################################################################

## General Flags
PROJECT = USB_Remote
MCU = attiny84
TARGET = USB_Remote.elf
CC = avr-gcc
AVRDUDE = avrdude -p $(MCU) -V -P /dev/ttyUSB0 -c avrisp -b 19200

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99 -DF_CPU=12000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=USB_Remote.map

## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings

COMPILE = $(CC) $(INCLUDES) $(CFLAGS)

OBJECTS = usbdrv/usbdrv.o usbdrv/usbdrvasm.o main.o ir.o ir_nec.o usb_keyboard.o led.o

## Build
all: $(TARGET) USB_Remote.elf USB_Remote.hex size

## Compile
.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) USB_Remote.elf dep USB_Remote.hex USB_Remote.eep USB_Remote.lss USB_Remote.map

flash: all
	$(AVRDUDE) -U flash:w:USB_Remote.hex:i

fuses:
	$(AVRDUDE) -U lfuse:w:0xef:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m

## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

