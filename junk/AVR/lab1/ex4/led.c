#include "pio.h"
#include "led.h"
#define LED_BLUE PIO_DEFINE (PORT_C, 2)

/** Turn LED1 on.  */
void led_on (void)
{
    pio_output_high(LED_BLUE);
}


/** Turn LED1 off.  */
void led_off (void)
{
    pio_output_low(LED_BLUE);
}


/** Initialise LED1.  */
void led_init (void)
{
    pio_config_set(LED_BLUE, PIO_OUTPUT_LOW);
}

/** Toggle LED1.  */
void led_toggle (void)
{
	pio_output_toggle(LED_BLUE);
}
