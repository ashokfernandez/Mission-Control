/* Name: main.c
 * Author: <JLECTRONIQUE.ORG>
 * Copyright: <(c) www.jlectronique.org>
 */


#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    
    DDRA = 1 << 4;           /* make the LED pin PD2 an output */
    for(;;){
        char i;
        for(i = 0; i < 10; i++){
            _delay_ms(30);      /* depend on F_CPU in MHz */
        }
        PORTA ^= 1 << 4;        /* toggle the LED */
    }
    return 0;
}
