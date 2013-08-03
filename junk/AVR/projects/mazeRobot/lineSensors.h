/** @file   lineSensors.h
    @author A. Z. Fernandez
    @date   12 July 2012
    @brief  Module to read and return the values of the line sensors for
            the ENEL300 line following robot
*/

#ifndef LINE_SENSORS_H
#define LINE_SENSORS_H

/**********************************************************************
 * ---------------------------DEFINITIONS------------------------------
 * *******************************************************************/

/* Pin to turn on the IR LEDs */
#define IR_LEDS_PORT PORTB
#define IR_LEDS_DDR DDRB
#define IR_LEDS_PIN PB5

/* ADC channels for the sensors */
#define RIGHT_SENSOR_CHANNEL 2
#define MIDDLE_SENSOR_CHANNEL 0
#define FRONT_SENSOR_CHANNEL 3

/* LED states */
typedef enum {ON, OFF} IRLedState_t;

/**********************************************************************
 * -------------------------DATA STRUCTURES----------------------------
 * *******************************************************************/
 
typedef struct sensors 
    {
        uint16_t right;
        uint16_t middle;
        uint16_t front;
    } sensors_t;


/**********************************************************************
 * ------------------------PUBLIC FUNCTIONS----------------------------
 * *******************************************************************/
 
/** Initialise the ADC module and calibrates the line sensors */
void lineSensors_init(void);

/** Given a pointer to a sensor variable this will read the current value
 *  of the line sensors, calculate the compensated output from the 
 *  calibrations and assign the new values to the sensor variable
 *      @param sensor variable location to update */
void lineSensors_read(sensors_t *sensors);

#endif /* LINE_SENSORS_H */

