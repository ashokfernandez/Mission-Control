# File:   Makefile
# Author: M. P. Hayes, UCECE
# Date:   12 Sep 2010
# Descr:  Makefile for ex3

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: ex3.out


# Compile: create object files from C source files.
ex3.o: ex3.c ../../drivers/avr/system.h button.h led.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

button.o: button.c button.h
	$(CC) -c $(CFLAGS) $< -o $@

led.o: led.c led.h
	$(CC) -c $(CFLAGS) $< -o $@



# Link: create ELF output file from object files.
ex3.out: ex3.o system.o button.o led.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean: 
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: ex3.out
	$(OBJCOPY) -O ihex ex3.out ex3.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash ex3.hex; dfu-programmer atmega32u2 start


