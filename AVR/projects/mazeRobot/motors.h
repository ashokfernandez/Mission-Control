/** @file   motors.c
    @author A. Z. Fernandez
    @date   15 July 2012
    @brief  Routines to set PWM outputs and switching for an L293DNE H-bridge
            connected to two DC motors
*/

#ifndef MOTORS_H
#define MOTORS_H

/**********************************************************************
 * ---------------------------DEFINITIONS------------------------------
 * *******************************************************************/
 
/* Directions the motor can undertake */
typedef enum {FORWARD, LEFT, RIGHT, HARD_LEFT, HARD_RIGHT} motorDirection_t;

/* PWM duty cycle for the motors going forward (valid values between 0 - 255) */
#define MOTOR_FORWARD_SPEED 90

/* PWM duty cycles for the two wheels when turning, HIGH being the speed
 * of the faster turning wheel; hence the difference between the values
 * is the sharpness of the turn (valid values between 0 - 255) */
#define MOTOR_TURNING_SPEED_HIGH 90
#define MOTOR_TURNING_SPEED_LOW 60

/* PWM duty cycles for the two wheels when making a sharp turn. A sharp
 * turn will spin the wheels in opposite directions, FORWARD will give the
 * speed of the foward wheel; again the difference between the values is
 * the sharpness of the turn. If the values are equal the robot should 
 * turn on the spot (valid values between 0 - 255) */
#define MOTOR_TURNING_SPEED_SHARP_FORWARD 90
#define MOTOR_TURNING_SPEED_SHARP_BACKWARD 60

/**********************************************************************
 * ------------------------PUBLIC FUNCTIONS----------------------------
 * *******************************************************************/

/** Initialises the PWM outputs and pins to send control signals
 *  to the H-bridge. */
void motors_init(void);

/** Sets the appropriate duty cycle and control pins for the motors. The
 *  motors have been designated finite directions which they can be in:
 *  LEFT, RIGHT, HARD_LEFT, HARD_RIGHT and FORWARD. Passing one of these
 *  as a parameter will put the motor into the described directon until 
 *  until the direction is changed again or motors_stop() is called.
 *      @param motor state to change the motor to */
void motors_go(motorDirection_t direction);

/** Stops the motors given a parameter of how to stop. Valid arguments are
 *  FREE_RUNNING or BRAKE */
void motors_stop(void);

#endif /* MOTORS_H */
