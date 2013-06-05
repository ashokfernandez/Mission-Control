#include <avr/io.h>
#include "timer.h"


/* Initialise timer.  */
void timer_init (void)
{
    /* TODO */
    TCCR1A = 0x00;
    TCCR1B = PRESCALER;
    TCCR1C = 0X00;
}


/* Wait for the specified length of time.  */
void timer_delay_ms (uint16_t milliseconds)
{
    /* Scale the clock by the prescaler and then multiple by the time in
       seconds (divide by reciprocal so floats aren't needed*/
       uint16_t prescaler[] =  {0, 1, 8, 64, 256, 1024};
       uint16_t count = (F_CPU / prescaler[PRESCALER]) / (1000/milliseconds);
    
    /* TODO: Wait for the timer/couter to reach the 
       value calculated above.  */
        TCNT1 = 0x00;
        while(TCNT1 < count) {
            continue;
        }
}
