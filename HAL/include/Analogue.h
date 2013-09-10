/** @file   Analogue.h
    @author A. Z. Fernandez
    @date   10 April 2012
    @brief  Hardware abstraction layer for the Mission Control MIDI controller project.
    		Allows the ADC pins to be abtracted from hardware specifics and used in designs
    		with concern of the platform that the implementation will occur on
*/

#include <DataTypes.h>
#include <stdint.h>

/**
 * Initialises the given pin as an analogue pin (is possible)
 * @param pin Pin to initialise as an analogue input
 */
void Analogue_Init(Pin_Analogue_t pin);

/**
 * Reads the value of the given analogue pin
 * @param  pin Pin to read
 * @return     Value of the pin (between 0 - 255)
 */
uint8_t Analogue_Read(Pin_Analogue_t pin);