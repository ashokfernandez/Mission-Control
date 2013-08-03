/*
             LUFA Library
     Copyright (C) Dean Camera, 2012.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2012  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/* Olimexino 32U4 Board drivers for use with the LUFA library 
 * Written by Ashok Fernandez using the LUFA board drivers as a base
 * 2nd July 2012 
 * */

/** \file
 *  \brief Board specific LED driver header for the Olimexino-32U4.
 *  \copydetails Group_LEDs_OLIMEXINO32U4
 *
 *  \note This file should not be included directly. It is automatically included as needed by the LEDs driver
 *        dispatch header located in LUFA/Drivers/Board/LEDs.h.
 */

/** \ingroup Group_LEDs
 *  \defgroup Group_LEDs_OLIMEXINO32U4 OLIMEXINO32U4
 *  \brief Board specific LED driver header for the Olimexino-32U4.
 *
 *  Board specific LED driver header for the Olimexino-32U4 (http://www.olimex.com/dev/olimexino-32u4.html).
 *
 *  @{
 */

#ifndef __LEDS_OLIMEXINO32U4_H__
#define __LEDS_OLIMEXINO32U4_H__
    
    // LED1 is on PE6 and LED 2 is on PB5, both are active high

    /* Public Interface - May be used in end-application: */
        /* Macros: */
            /** LED mask for the first LED on the board. */
            #define LEDS_LED1   (1 << 6)
            #define LEDS_LED2   (1 << 5)

            /** LED mask for all the LEDs on the board. */
            #define LEDS_ALL_LEDS    (LEDS_LED1 | LEDS_LED2)

            /** LED mask for none of the board LEDs. */
            #define LEDS_NO_LEDS     0

        /* Inline Functions: */
        #if !defined(__DOXYGEN__)
            static inline void LEDs_Init(void)
            {
                // LED 1 Init
                DDRE  |= LEDS_ALL_LEDS;
                PORTE |= LEDS_ALL_LEDS;
            
                // LED 2 Init
                DDRB  |= LEDS_LED2;
                PORTB |= LEDS_LED2;
            }

            static inline void LEDs_Disable(void)
            {
                // Release LED 1
                DDRE  &= ~LEDS_ALL_LEDS;
                PORTE &= ~LEDS_ALL_LEDS;
            
                // Release LED 2
                DDRB  &= ~LEDS_LED2;
                PORTB &= ~LEDS_LED2;
            }

            static inline void LEDs_TurnOnLEDs(const uint8_t LEDMask)
            {
                PORTE |= (LEDS_LED1 & LEDMask);
                PORTB |= (LEDS_LED2 & LEDMask);
            }

            static inline void LEDs_TurnOffLEDs(const uint8_t LEDMask)
            {
                PORTE &= ~(LEDS_LED1 & LEDMask);
                PORTB &= ~(LEDS_LED2 & LEDMask);
            }

            static inline void LEDs_SetAllLEDs(const uint8_t LEDMask)
            {
                // Turns the LED on if it is in the bitmask and off if it is not
                PORTE = ((PORTE | LEDS_LED1) & ~(LEDMask & LEDS_LED1));
                PORTB = ((PORTB | LEDS_LED2) & ~(LEDMask & LEDS_LED2));
            }

            static inline void LEDs_ChangeLEDs(const uint8_t LEDMask,
                                               const uint8_t ActiveMask)
            {
                // Update the LEDs to the active mask
                PORTE = ((PORTE | (LEDMask & LEDS_LED1)) & ~(ActiveMask & LEDS_LED1));
                PORTB = ((PORTB | (LEDMask & LEDS_LED2)) & ~(ActiveMask & LEDS_LED2));
            }

            static inline void LEDs_ToggleLEDs(const uint8_t LEDMask)
            {
                PORTE ^= (LEDMask & LEDS_LED1);
                PORTB ^= (LEDMask & LEDS_LED2);
            }

            static inline uint8_t LEDs_GetLEDs(void) ATTR_WARN_UNUSED_RESULT;
            static inline uint8_t LEDs_GetLEDs(void)
            {
                return ((~PORTE & LEDS_LED1) | (~PORTB & LEDS_LED2));
            }
        #endif

    /* Disable C linkage for C++ Compilers: */
        #if defined(__cplusplus)
            }
        #endif

#endif

/** @} */

