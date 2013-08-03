/** @file   lcdText.h
    @author Ashok Fernandez
    @date   8 Jan 2012
    @brief  Set of functions to generate and display strings on an LCD
            display. Dependant on lcd driver functions.
*/

#include <stdint.h>

#ifndef LCDTEXT_H
#define LCDTEXT_H

#define LINE_1 1
#define LINE_2 2

/** Same as lcd_puts but with option to choose which line the string will
    print on. If line specified is invalid the cursor is set to the first 
    line by default
 */
void lcdText_puts(uint8_t line, const char *text);

/** Same functionality as printf but string will be printed to the lcd.
    also accepts argument of line to print on. If line specified is 
    invalid the cursor is set to the first line by default
 */
void lcdText_printf(uint8_t line, const char *format, ...);


#endif /* LCDTEXT_H */
