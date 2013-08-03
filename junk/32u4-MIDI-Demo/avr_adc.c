/** @file   adc.c
    @author A. Z. Fernandez
    @date   10 April 2012
    @brief  Module to make use of the ADC on AVR microcontrollers. Provides
            a level of hardware abstraction
*/

#include "avr_adc.h"
#include <avr/io.h>
#include "bits.h" // Bitwise Macros

/**********************************************************************
 * -------------------------FILE VARIABLES-----------------------------
 * *******************************************************************/

static uint8_t adc_isEightBit = 0;

/**********************************************************************
 * -----------------------PRIVATE FUNCTIONS----------------------------
 * *******************************************************************/
 
 /** Checks if the ADC is currently converting a value or not 
 *      @return TRUE if the ADC is currently not converting
 **/
uint8_t adc_ready (void)
{
    return ! (ADCSRA & BIT (ADSC));
}

/**********************************************************************
 * ------------------------PUBLIC FUNCTIONS----------------------------
 * *******************************************************************/

void adc_init(uint16_t settings)
{
    /* Apply the settings to the ADC registers */
    ADCSRA = settings;
    ADMUX = (settings >> 8);
    
    /* Save whether the adc is 8 bit or not */
    adc_isEightBit |= ADMUX & _BV(ADLAR);
    
    /* Turn the ADC on */
    adc_on();
}

/** Disables the digital input buffer on ADC channels to save power.
 *      @param bitmask of ADC channels used i.e _BV(ADC0) | _BV(ADC2)
 **/
//void adc_reserveChannels(uint8_t channels)
//{
    /* Write channel bitmask to DIDR0 register */
//    DIDR0 |= channels;                      
//}

/** Turns the ADC unit on */
void adc_on(void)
{
    ADCSRA |= _BV(ADEN);
}

/** Turns the ADC unit off */
void adc_off(void)
{
    ADCSRA &= ~_BV(ADEN);
}

/** Starts a single ended conversion or starts the free running conversion
 *  if the ADC is in free running mode 
 *      @param ADC channel to read
 **/
void adc_startConversion(uint8_t channel)
{
    /* Set the desired channel */
    BITS_INSERT (ADMUX, channel, 0, 3);
    
    /* Start the conversion if the ADC is ready */
    if(adc_ready())
        ADCSRA |= _BV(ADSC);
}

/** Waits for the current conversion to finish and reads the result. Ideally
 *  this will be written to be interrupt driven so the MCU doens't have to
 *  block other tasks while it waits for the ADC 
 *      @return ADC result
 **/
uint16_t adc_read(void)
{
    uint16_t sample = 0;
    uint16_t highBits = 0;
    
    /* Block until conversion is complete */
    while(!adc_ready())
        continue;
    
    if(adc_isEightBit)
    {
        sample = ADCH;
    }
    
    else // sample is 10-bit
    {
        sample = ADC;
    } 
    
    return sample;
} 
