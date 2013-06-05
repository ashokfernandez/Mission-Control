#include <avr/io.h>
#include "button.h"


/** Return non-zero if button pressed.  */
int button_pressed_p (void)
{
    int on = 0;
    if((PIND&(1 << 7 )) > 0) {
			on = 1;
		}
	return on;
}


/** Initialise button1.  */
void button_init (void)
{
    DDRD = 0;
    
}

