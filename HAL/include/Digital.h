/** @file   Digital.h
    @author A. Z. Fernandez
    @date   10 April 2012
    @brief  Hardware abstraction layer for the Mission Control MIDI controller project.
    		Allows the ADC pins to be abtracted from hardware specifics and used in designs
    		with concern of the platform that the implementation will occur on
*/

#include <DataTypes.h>
#include <stdint.h>


/**
 * Initilises a pin as a digital pin
 * @param pin Pin to initialise
 */
void Digital_Init(Pin_Digital_t pin);

/**
 * Reads the value of a digital pin
 * @param pin Pin to read
 * @return true if the pin is high, false if the pin is low
 */
bool Digital_Read(Pin_Digital_t pin);

/**
 * Writes a value to the specified pin.
 * @param pin Pin to read
 * @param value true to set the pin, false to set the pin low
 */
void Digital_Write(Pin_Digital_t pin, bool value);