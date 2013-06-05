# AVR-GCC Makefile
PROJECT=pc1202a
SOURCES=main.c lcd.c
CC=avr-gcc
OBJCOPY=avr-objcopy
MMCU=atmega8

CFLAGS=-mmcu=$(MMCU) -Wall


$(PROJECT).hex: $(PROJECT).out
	$(OBJCOPY) -j .text -O ihex $(PROJECT).out $(PROJECT).hex

# avr-gcc -mmcu=atmega8 -Wall -o pc1202a.elf main.c lcd.c
$(PROJECT).out: $(SOURCES) 
	$(CC) $(CFLAGS) -I./ -o $(PROJECT).out $(SOURCES)

# MUST BE ROOT TO PROGRAM  unless /dev/ttyS0 has rw for others
program: $(PROJECT).hex
	avrdude -p m1284p -c usbasp -e -U flash:w:$(PROJECT).hex
clean:
	rm -f $(PROJECT).o
	rm -f $(PROJECT).out
	rm -f $(PROJECT).map
	rm -f $(PROJECT).hex
