#include <avr/io.h>
#include <util/delay.h>
#include "system.h"

int main (void)
{
    system_init ();

    /* Initialise port A to drive LEDs  */
    
    DDRA |= 1 | (1<<1) | (1<<2);

    while (1)
    {
        int j;
        int i;
        
        /* Loop through PINs 8*/
        for(j = 0; j<4; j++){
            
        /* Toggle LEDs  */
            PORTA ^= (1<<j);
	    PORTA ^= (2<<j);
            for(i = 0; i < 200; i++){
                _delay_ms(20);
            }
        }


    }
}
