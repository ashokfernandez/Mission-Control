/** @file   pwm.h
    @author A. Z. Fernandez
    @date   28 June 2012
    @brief  Module to initialise and generate pwm signals from an atmega8a
            MCU.
            A really useful summary table for bits to set to change the PWM
            settings on the atmega8 can be found at
            http://www.societyofrobots.com/member_tutorials/files/ATMega8.pdf
*/

#ifndef PWM_H
#define PWM_H

/**********************************************************************
 * ---------------------------DEFINITIONS------------------------------
 * *******************************************************************/

#define PWM_INIT_DUTY 100

/** Define the two PWM channels, channel 1 is on PB1 and channel 2 is on
    PB2 */
typedef enum {PWM_CHANNEL_1, PWM_CHANNEL_2} pwmChannel_t;

/**********************************************************************
 * ------------------------PUBLIC FUNCTIONS----------------------------
 * *******************************************************************/

/** Initialises PWM outputs on OC1A and OC1B (PB1, PB2 respectively). */
void pwm_init(void);

/** Sets the duty cycle for a given PWM output. Duty cycles are an interger
 *  (between 0 - 100) to represent a percentage duty cycle */
void pwm_setDuty(pwmChannel_t channel, uint8_t duty);

/** Enable both PWM outputs. Outputs are initialised to be on so this is
 *  to renable them if they have been switched off */
void pwm_on(void);

/** Disable both PWM outputs. It is advisable to turn off the PWM modules
 *  when not in use as this saves power */
void pwm_off(void);

#endif /* PWM_H */
