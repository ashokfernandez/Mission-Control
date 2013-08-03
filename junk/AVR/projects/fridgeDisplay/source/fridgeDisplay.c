#include "system.h"
#include "lcd.h"
#include "lcdText.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define LED_PIO PIO_DEFINE (PORT_B, 7)

int main (void)
{
    system_init ();
    lcd_init(LCD_DISP_ON);
    lcd_backlight(1);
 
    while(1){
        //lcd_clrscr();
        //_delay_ms(1000);
        lcd_puts("---- On Tap ----------------------------------------------------------------------------");
        //lcdText_puts(2, "Ragout Pilsner");
        _delay_ms(25000);
    }
    return 0;
}
