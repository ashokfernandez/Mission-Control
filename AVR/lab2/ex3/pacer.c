#include <avr/io.h>
#include "pacer.h"

static uint16_t pacer_period;


/* Initialise the pacer module.  */
void pacer_init (uint16_t pacer_frequency)
{
    uint16_t prescaler[] =  {0, 1, 8, 64, 256, 1024};
    /* TODO: initialise timer/counter peripheral the
       same way as in lab2/ex2/timer.c but also calculate 
       the timer/counter value from the pacer frequency */
    TCCR1A = 0x00;
    TCCR1B = PRESCALER;
    TCCR1C = 0X00;
    
    pacer_period = (F_CPU / prescaler[PRESCALER]) / (pacer_frequency);
}


/* Pace a while loop.  */
void pacer_wait (void)
{

    /* TODO: Implement the same way as the timer_delay () function 
       except reset TCNT1 after the while loop. */
    while(TCNT1 < pacer_period) {
        continue;
    }
    TCNT1 = 0x00;
}
