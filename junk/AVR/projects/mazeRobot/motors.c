/** @file   motors.c
    @author A. Z. Fernandez
    @date   15 July 2012
    @brief  Routines to set PWM outputs and switching for an L293DNE H-bridge
            connected to two DC motors
*/

/**********************************************************************
 * -------------------------DEPENDENCIES------------------------------
 * *******************************************************************/

/** Include modules */
#include "system.h" // System definitions and bit macros
#include "motors.h" // Function declarations
#include "pwm.h" // PWM module

/** Include built-in AVR libraries */
#include <avr/io.h> // Pin and register definitions
#include <avr/delay.h> // _delay_ms()


/**********************************************************************
 * ---------------------------DEFINITIONS------------------------------
 * *******************************************************************/

/* PWM channels for the motors */
#define LEFT_MOTOR_PWM PWM_CHANNEL_2
#define RIGHT_MOTOR_PWM PWM_CHANNEL_1

/* Max and min duty cycles to stop the motors from stalling and drawing
 * too much current */
#define MIN_PWM_DUTY 70
#define MAX_PWM_DUTY 90

/* Base speed for the robot to drive forward */
#define BASE_MOTOR_SPEED MAX_UINT8

/**********************************************************************
 * -----------------------PRIVATE FUNCTIONS----------------------------
 * *******************************************************************/

/**------------FUNCTIONS TO CONTROL THE MOTOR CONTROL PINS------------*/

static inline void RIGHT_MOTOR_FORWARD(void)
{
    PORTB &= ~BIT(PB0); 
    PORTD |= BIT(PD7);
}

static inline void RIGHT_MOTOR_REVERSE(void)
{
    PORTB |= BIT(PB0); 
    PORTD &= ~BIT(PD7);
}

static inline void RIGHT_MOTOR_STOP(void)
{
    PORTB |= BIT(PB0); 
    PORTD |= BIT(PD7);
}


static inline void LEFT_MOTOR_FORWARD(void)
{ 
    PORTB |= BIT(PB3);
    PORTB &= ~BIT(PB4);
}


static inline void LEFT_MOTOR_REVERSE(void)
{ 
    PORTB &= ~BIT(PB3);
    PORTB |= BIT(PB4);
}


static inline void LEFT_MOTOR_STOP(void)
{ 
    PORTB |= BIT(PB4);
    PORTB |= BIT(PB3);
}

/** Ensures the pwm duty cycle does not exceed the specified limits
        @param duty cycle
        @return duty cycle clipped to saturation limits
*/
uint8_t dutyCycleSaturationFilter(uint8_t duty)
{
    uint8_t newDuty = duty;
    
    if(duty < MIN_PWM_DUTY)
        newDuty = MIN_PWM_DUTY;
    else if(duty > MAX_PWM_DUTY)
        newDuty = MAX_PWM_DUTY;

    return newDuty;    
}

/**********************************************************************
 * ------------------------PUBLIC FUNCTIONS----------------------------
 * *******************************************************************/

/** Initialises the PWM outputs and pins to send control signals
 *  to the H-bridge. */
void motors_init(void)
{
    /* Initialise PWM outputs and set control pins as outputs */
    pwm_init();
    DDRB |= BIT(PB0) | BIT (PB3) | BIT(PB4);
    DDRD |= BIT(PD7);    
    
    /* Initalise the motors to be off */
    pwm_setDuty(PWM_CHANNEL_1, 0);
    pwm_setDuty(PWM_CHANNEL_2, 0);
    
    RIGHT_MOTOR_STOP();
    LEFT_MOTOR_STOP();  
    
}

/** Sets both motors to drive forwards with a direction given as a number
 *  between -100 and 100. If direction is given as -100 the robot will go
 *  full speed to the left and vice-versa. Direction set to 0 will give
 *  equal power to both motors.
 *      @param percentage direction with -100 being 100% left and
 *             100 being 100% right (0 is straight ahead) */
void motors_go(motorDirection_t direction)
{
    /* New duty cycles for the motors */
    uint8_t leftMotorDuty = 0;
    uint8_t rightMotorDuty = 0;
    
    /* Default to both motors forward, if necessary change later */
    RIGHT_MOTOR_FORWARD();
    LEFT_MOTOR_FORWARD();    
    
    /* Adjust the duty cycles and control switches of the motors according
     * to the given direction */
    switch(direction)
    {
        case FORWARD:
            leftMotorDuty = MOTOR_FORWARD_SPEED;
            rightMotorDuty = MOTOR_FORWARD_SPEED;
            break;
        
        case LEFT:
            leftMotorDuty = MOTOR_TURNING_SPEED_LOW;
            rightMotorDuty = MOTOR_TURNING_SPEED_HIGH;
            break;
        
        case RIGHT:
            leftMotorDuty = MOTOR_TURNING_SPEED_HIGH;
            rightMotorDuty = MOTOR_TURNING_SPEED_LOW;
            break;
        
        /* For the hard turns, one motor is in reverse */
        case HARD_LEFT:
            leftMotorDuty = MOTOR_TURNING_SPEED_SHARP_BACKWARD;
            rightMotorDuty = MOTOR_TURNING_SPEED_SHARP_FORWARD;
            LEFT_MOTOR_REVERSE();
            break;
    
        case HARD_RIGHT:
            leftMotorDuty = MOTOR_TURNING_SPEED_SHARP_FORWARD;
            rightMotorDuty = MOTOR_TURNING_SPEED_SHARP_BACKWARD;
            RIGHT_MOTOR_REVERSE();
            break;
    }
    
    /* Set the motors duty cycles */
    pwm_setDuty(LEFT_MOTOR_PWM, leftMotorDuty);
    pwm_setDuty(RIGHT_MOTOR_PWM, rightMotorDuty);
    
}

/** Stops the motors */
void motors_stop(void)
{
    /* As the duty cycle as to be respecified to get the motors to start
     * again it doesnt matter at this stage and can be left as is */
    RIGHT_MOTOR_STOP();
    LEFT_MOTOR_STOP();
}
