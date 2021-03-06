# File:   Makefile
# Author: M. P. Hayes, UCECE
# Date:   12 Sep 2010
# Descr:  Makefile for ex4

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: ex4.out


# Compile: create object files from C source files.
ex4.o: ex4.c ../../drivers/avr/system.h button.h led.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

button.o: button.c ../../drivers/avr/pio.h ../../drivers/avr/system.h button.h
	$(CC) -c $(CFLAGS) $< -o $@

led.o: led.c ../../drivers/avr/pio.h ../../drivers/avr/system.h led.h
	$(CC) -c $(CFLAGS) $< -o $@



# Link: create ELF output file from object files.
ex4.out: ex4.o pio.o system.o button.o led.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean: 
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: ex4.out
	$(OBJCOPY) -O ihex ex4.out ex4.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash ex4.hex; dfu-programmer atmega32u2 start


