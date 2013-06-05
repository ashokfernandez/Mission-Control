/** @file   lineSensors.c
    @author A. Z. Fernandez
    @date   12 July 2012
    @brief  Module to read and return the values of the line sensors for
            the ENEL300 line following robot
*/

/**********************************************************************
 * -------------------------DEPENDENCIES------------------------------
 * *******************************************************************/

/** Include modules */
#include "system.h" // System definitions and bit macros
#include "adc.h" // ADC module
#include "lineSensors.h" // Function definitions
#include "debugLed.h" // Debug LEDs

#include "lcdText.h" 

/** Include built-in AVR libraries */
#include <avr/io.h> // Pin and register definitions // Pin Definitions
#include <avr/delay.h> // _delay_ms()

/**********************************************************************
 * -------------------------FILE VARIABLES-----------------------------
 * *******************************************************************/

static sensors_t ambientLight = {0, 0, 0};

/**********************************************************************
 * -----------------------PRIVATE FUNCTIONS----------------------------
 * *******************************************************************/

/** Turns the IR LEDs inside the sensor unit on or off depending on the
 *  given state
 *      @param ON or OFF
*/
void lineSensors_IR(IRLedState_t state)
{
    switch(state)
    {
        case ON:
            IR_LEDS_PORT |= BIT(IR_LEDS_PIN);
            break;
        case OFF:
            IR_LEDS_PORT &= ~BIT(IR_LEDS_PIN);
            break;
    }
}

/** Turns off the IR LEDs and reads the ambient light value of the sensors
 *  and stores the results to the ambientLight file variable */
void lineSensors_calibrate(void)
{
    lineSensors_IR(OFF);
    _delay_ms(2);    
    
    adc_startConversion(RIGHT_SENSOR_CHANNEL);
    ambientLight.right = adc_read();
    
    adc_startConversion(MIDDLE_SENSOR_CHANNEL);
    ambientLight.middle = adc_read();    
    
    adc_startConversion(FRONT_SENSOR_CHANNEL);
    ambientLight.front = adc_read(); 
    
    lineSensors_IR(ON);
    _delay_ms(2);   
}

/**********************************************************************
 * ------------------------PUBLIC FUNCTIONS----------------------------
 * *******************************************************************/

/** Initialise the ADC module and calibrates the line sensors */
void lineSensors_init(void)
{
    /* Initialise ADC */
    adc_init(ADC_SINGLE_ENDED | ADC_10_BIT | ADC_REF_AVCC | ADC_PRESCALE_32);
    
    /* Initialise the sensors LED lights */
    IR_LEDS_DDR |= BIT(IR_LEDS_PIN);
    
    /* Turn the IR lights on */
    lineSensors_IR(ON);
}


/** Given a pointer to a sensor variable this will read the current value
 *  of the line sensors, calculate the compensated output from the 
 *  calibrations and assign the new values to the sensor variable
 *      @param pointer to the sensor variable to be updated */
void lineSensors_read(sensors_t *sensors)
{
    uint16_t right = 0;
    uint16_t middle = 0;
    uint16_t front = 0;
    uint8_t i = 0;
    
    /* Calibrate the current ambient light noise */
    //lineSensors_calibrate();

    /* Read the current forced IR values with the IR LEDs on
     * 8x oversample to reduce noise */
    for(i = 0; i < 8; i++)
    {
    adc_startConversion(RIGHT_SENSOR_CHANNEL);
    right += adc_read();

    adc_startConversion(MIDDLE_SENSOR_CHANNEL);
    middle += adc_read();
    
    adc_startConversion(FRONT_SENSOR_CHANNEL);
    front += adc_read();
    }
    
    /* Compensate for ambient light conditions */    
    //left -= ambientLight.right;
    //middle -= ambientLight.middle;
 
    /* Shifiting by 3 is the same as dividing by 8 so this averages out
     * the 8x oversample (as 2^3 = 8) */
    sensors->right = (right >> 3);
    sensors->middle = (middle >> 3);
    sensors->front = (front >> 3);
}


