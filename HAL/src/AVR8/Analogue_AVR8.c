/** @file   Analogue.h
    @author A. Z. Fernandez
    @date   10 April 2012
    @brief  Hardware abstraction layer for the Mission Control MIDI controller project.
    		Allows the ADC pins to be abtracted from hardware specifics and used in designs
    		with concern of the platform that the implementation will occur on
*/

#include <avr/io.h>
#include "bits.h"
#include <DataTypes.h>
#include <stdint.h>

/**********************************************************************
 * ------------------------ADC SETTINGS--------------------------------
 *  Bitwise or the relevant settings together to initialise the ADC.
 *  The top 8 bits are for the ADMUX register and the lower 8 bits
 *  are for the ADCSRA register 
 **********************************************************************/

/* Voltage reference select */
#define ADC_REF_AREF 0x0000
#define ADC_REF_AVCC 0x4000
#define ADC_REF_1V1 0x8000
#define ADC_REF_2V56 0xC000

/* Conversion resolution (sets the left adjust bit) */
#define ADC_10_BIT 0x0000
#define ADC_8_BIT 0x2000

/* Conversion mode */
#define ADC_FREE_RUNNING 0x0020
#define ADC_SINGLE_ENDED 0x0000

/* Interrupt Enable (global interrupts must also be enabled) */
#define ADC_INTERRUPT_ENABLE 0x0008

/* Clock Prescalers */
enum {ADC_PRESCALE_2 = 1, ADC_PRESCALE_4, ADC_PRESCALE_8, ADC_PRESCALE_16,
      ADC_PRESCALE_32, ADC_PRESCALE_64, ADC_PRESCALE_128};


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


void adc_init(uint16_t settings)
{
    /* Apply the settings to the ADC registers */
    ADCSRA = settings;
    ADMUX = (settings >> 8);
    
    /* Save whether the adc is 8 bit or not */
    adc_isEightBit |= ADMUX & _BV(ADLAR);
    
    /* Turn the ADC on */
    ADCSRA |= _BV(ADEN);
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

/**********************************************************************
 * ------------------------PUBLIC FUNCTIONS----------------------------
 * *******************************************************************/

// Initialise the ADC peripheral to do fast single ended 8-bit conversions with AVCC as a reference.
void Analogue_Init(void){
	adc_init(ADC_REF_AVCC | ADC_8_BIT | ADC_SINGLE_ENDED | ADC_PRESCALE_2);
}

// Start a pin on the specified channel and read the result
uint8_t Analogue_Read(Pin_Analogue_t pin)
{
	adc_startConversion(pin);
	uint8_t value  = adc_read();

	return value;
}