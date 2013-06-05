/** @file   pwm.c
    @author A. Z. Fernandez
    @date   28 June 2012
    @brief  Module to initialise and generate pwm signals from an atmega8a
            MCU.
            A really useful summary table for bits to set to change the PWM
            settings on the atmega8 can be found at
            http://www.societyofrobots.com/member_tutorials/files/ATMega8.pdf
*/

/**********************************************************************
 * -------------------------DEPENDENCIES------------------------------
 * *******************************************************************/

/** Include modules */
#include "system.h" // System definitions and bit macros
#include "pwm.h" // Function declarations

/** Include built-in AVR libraries */
#include <avr/io.h> // Pin and register definitions

/**********************************************************************
 * ------------------------PUBLIC FUNCTIONS----------------------------
 * *******************************************************************/

/** Initialises PWM outputs on OC1A and OC1B (PB1, PB2 respectively). */
void pwm_init(void)
{    
    // Set wave generation mode for 8 bit phase correct with non-inverting counter
    // Note: this will enable the pwm outputs
    TCCR1A |= BIT(WGM10) | BIT(COM1A1) | BIT(COM1B1);
    
    // Set clock timer prescaler to 8 
    TCCR1B |= BIT(CS11);
    
    // Setup the PB1 and PB2 as outputs
    DDRB |= BIT(PB1) | BIT(PB2);
    
    // Set the duty cycle to the predefined init duty cycle
    OCR1A = PWM_INIT_DUTY;
    OCR1B = PWM_INIT_DUTY;
    

}

/** Sets the duty cycle for a given PWM output. Duty cycles are an interger
 *  (between 0 - 255) */
void pwm_setDuty(pwmChannel_t channel, uint8_t duty)
{
    // Set the appropriate comparator value for the given channel
    switch(channel)
    {
        case PWM_CHANNEL_1:
            OCR1A = duty;
            break;
        case PWM_CHANNEL_2:
            OCR1B = duty;
            break;
    }
}

/** Enable both PWM outputs. Outputs are initialised to be on so this is
 *  to renable them if they have been switched off */
void pwm_on(void)
{
    // Set non-inverting counter mode to turn PWM outputs on
    TCCR1A |= BIT(COM1A1) | BIT(COM1B1);    
}

/** Disable both PWM outputs. It is advisable to turn off the PWM modules
 *  when not in use as this saves power */
void pwm_off(void)
{
    // Disable non-inverting counter mode to turn PWM outputs off
    TCCR1A &= ~(BIT(COM1A1) | BIT(COM1B1)); 
}
