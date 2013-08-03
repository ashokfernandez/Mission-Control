#include "mux.h"
#include "bits.h"


void mux_init(void)
{
    // Set the bits on the DDR of the mux to 1 so the pins are outputs
    BITS_SET(MUX_DDR, MUX_LOW_BIT, MUX_HIGH_BIT);
}

void mux_channelSelect(uint8_t channel)
{
    // Clear Current Setting
   BITS_CLEAR(MUX_PORT, MUX_LOW_BIT, MUX_HIGH_BIT);
   
   // Set New Channel
   BITS_INSERT(MUX_PORT, channel, MUX_LOW_BIT, MUX_HIGH_BIT);
}
