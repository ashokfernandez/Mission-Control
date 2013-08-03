#include "pio.h"
#include "button.h"
#define PUSH_BUTTON PIO_DEFINE (PORT_D, 7)

/** Return non-zero if button pressed.  */
int button_pressed_p (void)
{
    return pio_input_get(PUSH_BUTTON);
}


/** Initialise button1.  */
void button_init (void)
{
    pio_config_set(PUSH_BUTTON, PIO_INPUT);
}

