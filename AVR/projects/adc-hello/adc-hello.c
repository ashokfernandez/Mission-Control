#include "system.h"
#include "lcd.h"
#include "lcdText.h"
#include "adc.h"
#include <avr/io.h>
#include <util/delay.h>



int main (void)
{
    system_init ();
    lcd_init(LCD_DISP_ON);
    lcd_backlight(1);
    adc_init();
    adc_reference_select(ADC_REF_2V56);
    uint8_t sample;
    lcd_puts("blah");
    
    while(1){
        /*
        adc_start(ADC5);
        sample = adc_read();
        lcdText_printf(1, "ADC = %i", sample);
        _delay_ms(200);
    */
    }
    return 0;
}
