button.h: 

led.h: 

ex4.c: button.h led.h

ex4.o: ex4.c

../../drivers/avr/pio.h: 

button.c: ../../drivers/avr/pio.h button.h

button.o: button.c

../../drivers/avr/system.c: 

../../drivers/avr/system.o: ../../drivers/avr/system.c

led.c: ../../drivers/avr/pio.h led.h

led.o: led.c

../../drivers/avr/pio.c: ../../drivers/avr/pio.h

../../drivers/avr/pio.o: ../../drivers/avr/pio.c

ex4.out: ex4.o button.o ../../drivers/avr/system.o led.o ../../drivers/avr/pio.o

