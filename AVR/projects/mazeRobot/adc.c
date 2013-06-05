/** @file   adc.c
    @author A. Z. Fernandez
    @date   10 April 2012
    @brief  Module to make use of the ADC on AVR microcontrollers. Provides
            a level of hardware abstraction
            
            Modified on 12th July 2012 for an atmega8a for the ENEL300
            line following robot project
*/

#include "adc.h" // Function declarations
#include <avr/io.h> // Pin and register definitions

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
    return ! (ADCSRA & BIT(ADSC));
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
    adc_isEightBit = ADMUX & _BV(ADLAR);
    
    /* Turn the ADC on */
    adc_on();
}


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
    //ADMUX &= ~( _BV(MUX3) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0)); // Clear current multiplexer value
   //ADMUX |= (0x02); // and ensure that channel only has its
                               // lower four bits
                               
    /* Set the desired channel */
    BITSINSERT (ADMUX, channel, 0, 3);
    
    /* Start the conversion when the ADC is ready */
    while(!adc_ready())
        continue;
    
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
