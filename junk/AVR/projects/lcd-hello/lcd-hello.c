#include "system.h"
#include "pio.h"
#include "lcd.h"
#include "lcdText.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define LED_PIO PIO_DEFINE (PORT_B, 7)

int main (void)
{
    int8_t i = 11;
    //pio_config_set(LED_PIO, PIO_OUTPUT_HIGH);
    system_init ();
    lcd_init(LCD_DISP_ON);
    lcd_backlight(1);
    while(1){
        lcd_clrscr();
        lcd_puts("Hello!");
        //lcdText_printf(1, "Pouring at %i%cC",i, 223);
       // lcdText_printf(2, "ABV: %i.%i%c",4,3, 37);
    }
    return 0;
}
