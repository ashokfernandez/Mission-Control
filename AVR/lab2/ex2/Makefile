# File:   Makefile
# Author: M. P. Hayes, UCECE
# Date:   12 Sep 2010
# Descr:  Makefile for ex2

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../drivers/avr -I../../drivers
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: ex2.out


# Compile: create object files from C source files.
ex2.o: ex2.c ../../drivers/avr/system.h ../../drivers/led.h timer.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

led.o: ../../drivers/led.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/led.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: timer.c ../../drivers/avr/system.h timer.h
	$(CC) -c $(CFLAGS) $< -o $@



# Link: create ELF output file from object files.
ex2.out: ex2.o pio.o system.o led.o timer.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean: 
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: ex2.out
	$(OBJCOPY) -O ihex ex2.out ex2.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash ex2.hex; dfu-programmer atmega32u2 start


