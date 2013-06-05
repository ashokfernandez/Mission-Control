/** @file   missionControl.c
    @author A. Z. Fernandez
    @date   8 April 2012
    @brief  Main file for the "Mission Control" USB Midi Mixer project. 
*/

/** Include builtin AVR libraries */
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

/** Include modules */
#include "system.h" // System definitions
#include "debugLed.h" // Debug LED macros
#include "lcd.h" // LCD driver
#include "lcdText.h" //LCD printing functions
#include "adc.h" // ADC driver
#include "mux.h" // Analouge multiplexer driver

/** Include look tables for pot mappings */
#include "pot_linear.h" // Linear pot lookup table
#include "pot_steps.h" // Stepping pot lookup table

static volatile uint16_t pot_1 = 0;
static volatile uint16_t pot_2 = 0;

void scan_pots(void)
{
    uint8_t i, j;

    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 16; j++)
        {
            mux_channelSelect(j);
            adc_startConversion(i);
            if(!i)
            {
                if(j==0)
                    pot_1 = adc_read();
                else if (j == 1)
                    pot_2 = adc_read();
                else
                    adc_read();
            }
            else
                adc_read();
        }
    }
}

int main(void)
{
    // Init debugging tools
    DEBUG_LED_INIT;
    DEBUG_LED_OFF;
    lcd_init(LCD_DISP_ON);
    lcd_clrscr();
    
    // Init mux and ADC
    adc_init(ADC_REF_AVCC | ADC_10_BIT | ADC_SINGLE_ENDED | ADC_PRESCALE_64);
    //adc_reserveChannels(BIT(ADC0D) | BIT(ADC1D) | BIT(ADC2D));
    mux_init();
    
    

    while(1) // Loop forever
    {
        DEBUG_LED_ON;
        //Read all the pots
        scan_pots();
        DEBUG_LED_OFF;
        
        // Update the display
        lcd_clrscr();
        lcdText_printf(1, "ADC = %i", pot_linear[pot_1]);
        lcdText_printf(2, "ADC = %i", pot_steps[pot_2]);

        // Simulate polling of switches
        _delay_ms(10000);
        
    }
}
