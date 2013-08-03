/** @file   debegLed.h
    @author A. Z. Fernandez
    @date   8 April 2012
    @brief  Set of macros to initialize and turn an led on or off.
            Useful for debugging purposes. This assumes the LED is connected
            in an active high configuration and has a current limiting 
            resistor
*/

#ifndef DEBUG_LED
#define DEBUG_LED

/* Define Debug LED port, DDR and pin 8*/
#define DEBUG_LED_PORT PORTB
#define DEBUG_LED_DDR DDRB
#define DEBUG_LED_PIN 7

/* Debug LED Init */
#define DEBUG_LED_INIT DEBUG_LED_DDR |= _BV(DEBUG_LED_PIN)

/* Debug LED On & OFF */
#define DEBUG_LED_ON DEBUG_LED_PORT |= _BV(DEBUG_LED_PIN)
#define DEBUG_LED_OFF DEBUG_LED_PORT &= ~(_BV(DEBUG_LED_PIN))

#endif /* DEBUG_LED */
