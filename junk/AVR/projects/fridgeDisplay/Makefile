# File:   Makefile
# Author: Ashok Fernandez
# Date:   29/01/2012
# Descr:  Makefile for keg fridge display (fridgeDisplay.c)

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=attiny861a -Os -Wall -Wstrict-prototypes -Wextra -g -I ./source -I ../../drivers/ -I ../../drivers/avr/ -I ../../extra/
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: fridgeDisplay.out


# Compile: create object files from C source files.
fridgeDisplay.o: ./source/fridgeDisplay.c ./source/lcd.h ./source/adc.h ../../extra/lcdText.h ./source/system.h 
	$(CC) -c $(CFLAGS) $< -o $@

adc.o: ../../drivers/avr/adc.c ./source/adc.h ./source/system.h ../../drivers/avr/bits.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ./source/system.c ./source/system.h
	$(CC) -c $(CFLAGS) $< -o $@

lcd.o: ../../drivers/lcd.c ./source/lcd.h ./source/system.h
	$(CC) -c $(CFLAGS) $< -o $@

lcdText.o: ../../extra/lcdText.c ../../extra/lcdText.h ./source/lcd.h
	$(CC) -c $(CFLAGS) $< -o $@


# Link: create ELF output file from object files.
fridgeDisplay.out: fridgeDisplay.o adc.o system.o lcd.o lcdText.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean: 
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: fridgeDisplay.out
	$(OBJCOPY) -O ihex fridgeDisplay.o fridgeDisplay.hex
	avrdude -c avrispmkII -P usb -p attiny861 -u -U flash:w:fridgeDisplay.hex


