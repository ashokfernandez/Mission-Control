/** @file   Analogue.c
    @author A. Z. Fernandez
    @date   10 April 2012
    @brief  Hardware abstraction layer for the Mission Control MIDI controller project.
    		Allows the ADC pins to be abtracted from hardware specifics and used in designs
    		with concern of the platform that the implementation will occur on
*/

#include "Analogue.h"
#include "adc_avr.h"

