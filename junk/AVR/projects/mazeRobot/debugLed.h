/** @file   debegLed.h
    @author A. Z. Fernandez
    @date   8 April 2012
    @brief  Set of macros to initialize and turn an led on or off.
            Useful for debugging purposes. This assumes the LED is connected
            in an active high configuration and has a current limiting 
            resistor. 
            
            The entire module is written using register address and macros
            so that it is not dependant on other files (other than avr/io.h).
            This is to keep it as simple as possible so it doesnt cause errors
            when using it to try to debug things.
*/

#ifndef DEBUG_LED
#define DEBUG_LED

/** AVR io definitions */
#include <avr/io.h> // Pin and register definitions

/* Define Debug LED port, DDR and pin 8*/
#define DEBUG_LED_PORT PORTC
#define DEBUG_LED_DDR DDRC
#define DEBUG_LED_1_PIN 5
#define DEBUG_LED_2_PIN 4
#define DEBUG_LED_3_PIN 3

/* Debug LED Init */
#define DEBUG_LED_1_INIT DEBUG_LED_DDR |= _BV(DEBUG_LED_1_PIN)
#define DEBUG_LED_2_INIT DEBUG_LED_DDR |= _BV(DEBUG_LED_2_PIN)
#define DEBUG_LED_3_INIT DEBUG_LED_DDR |= _BV(DEBUG_LED_3_PIN)

#define DEBUG_LED_INIT DEBUG_LED_1_INIT; DEBUG_LED_2_INIT; DEBUG_LED_3_INIT

/* Debug LED On & OFF */
#define DEBUG_LED_1_ON DEBUG_LED_PORT |= _BV(DEBUG_LED_1_PIN)
#define DEBUG_LED_1_OFF DEBUG_LED_PORT &= ~(_BV(DEBUG_LED_1_PIN))

#define DEBUG_LED_2_ON DEBUG_LED_PORT |= _BV(DEBUG_LED_2_PIN)
#define DEBUG_LED_2_OFF DEBUG_LED_PORT &= ~(_BV(DEBUG_LED_2_PIN))

#define DEBUG_LED_3_ON DEBUG_LED_PORT |= _BV(DEBUG_LED_3_PIN)
#define DEBUG_LED_3_OFF DEBUG_LED_PORT &= ~(_BV(DEBUG_LED_3_PIN))

#endif /* DEBUG_LED */
