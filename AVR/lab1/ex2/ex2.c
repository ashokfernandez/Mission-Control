#include <avr/io.h>
#include "system.h"


static void led_init (void)
{
    /* Initialise port to drive LED 1.  */

    PORTC = 0;
}


static void led_on (void)
{
    /* Set port to turn LED 1 on.  */

    PORTC |= (1<<2);
}


static void led_off (void)
{
    /* Set port to turn LED 1 off.  */

    PORTC = 0;
}



static void button_init (void)
{
    /* Initialise port to read button 1.  */

    DDRD = 0;
}


static int button_pressed_p (void)
{
    /* Return non-zero if button pressed_p.  */
	int on = 0;
    if((PIND&(1 << 7 )) > 0) {
			on = 1;
		}
	return on;
}


int main (void)
{
    system_init ();

    led_init ();
    button_init ();

    while (1)
    {
        if (button_pressed_p ())
        {
            led_on ();
        }
        else
        {
            led_off ();
        }
    }
}
