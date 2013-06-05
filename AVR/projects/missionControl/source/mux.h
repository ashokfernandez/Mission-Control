#include <avr/io.h>

#define MUX_PORT PORTC
#define MUX_DDR DDRC
#define MUX_LOW_BIT 4
#define MUX_HIGH_BIT 7

void mux_init(void);

void mux_channelSelect(uint8_t channel);
