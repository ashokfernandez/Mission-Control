/** @file   adc.c
    @author A. Z. Fernandez
    @date   10 April 2012
    @brief  Module to make use of the ADC on AVR microcontrollers. Provides
            a level of hardware abstraction. Designed and tested on the
            atmega1284p MCU
*/

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


/***********************************************************************
 * -------------------------PUBLIC FUNCTIONS----------------------------
***********************************************************************/

/** Initialises the ADC unit. The settings parameter is a bitmask created
 *  by using a bitwise OR on the about setting macros.
 *      @param mask of settings (i.e. ADC_10_BIT | ADC_PRESCALE_2)
 **/
void adc_init(uint16_t settings);


/** Disables the digital input buffer on ADC channels to save power.
 *      @param bitmask of ADC channels used i.e _BV(ADC0) | _BV(ADC2)
 **/
//void adc_reserveChannels(uint8_t channels);

/** Turns the ADC unit on */
void adc_on(void);

/** Turns the ADC unit off */
void adc_off(void);

/** Starts a single ended conversion or starts the free running conversion
 *  if the ADC is in free running mode 
 *      @param ADC channel to read
 **/
void adc_startConversion(uint8_t channel);

/** Waits for the current conversion to finish and reads the result. Ideally
 *  this will be written to be interrupt driven so the MCU doens't have to
 *  block other tasks while it waits for the ADC 
 *      @return ADC result
 **/
uint16_t adc_read(void);
