# File:   Makefile
# Author: M. P. Hayes, UCECE
# Date:   12 Sep 2010
# Descr:  Makefile for ex1

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega1284p -Os -Wall -Wstrict-prototypes -Wextra -g -I ../../drivers/ -I ../../drivers/avr/ -I ../../extra/
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: lcd-hello.out


# Compile: create object files from C source files.
lcd-hello.o: lcd-hello.c ../../drivers/lcd.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

lcd.o: ../../drivers/lcd.c ../../drivers/lcd.h
	$(CC) -c $(CFLAGS) $< -o $@

lcdText.o: ../../extra/lcdText.c ../../extra/lcdText.h ../../drivers/lcd.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

# Link: create ELF output file from object files.
lcd-hello.out: lcd-hello.o system.o pio.o lcd.o lcdText.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean: 
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: lcd-hello.out
	$(OBJCOPY) -O ihex lcd-hello.out lcd-hello.hex
	avrdude -c avrispmkII -P usb -p m1284p -u -U flash:w:lcd-hello.hex


