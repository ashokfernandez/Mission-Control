/** @file   lcdText.h
    @author Ashok Fernandez
    @date   8 Jan 2012
    @brief  Set of functions to generate and display strings on an LCD
            display. Dependant on lcd driver functions.
*/

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "lcd.h"
#include "lcdText.h"

/** Sets the cursor to the beginning of the specified line. If line 
   specified is invalid the cursor is set to the first line by default)
 */    
void lcdText_set_line(uint8_t line) {
    /* Check if line is valid, if not set cursor to home */
    if(line > LCD_LINES) {
        lcd_home();
    }
    else {
        lcd_gotoxy(0, (line-1));
    }
}

/* *********************************************************************
 *                          PUBLIC FUNCTIONS
 * ********************************************************************/

/** Same as lcd_puts but with option to choose which line the string will
    print on
   @return none */
void lcdText_puts(uint8_t line, const char *text){
    /* set the cursor to the correct line then print the text */
    lcdText_set_line(line);
    lcd_puts(text);
}
    

/** Same functionality as printf but string will be printed to the lcd.
    also accepts argument of line to print on
 */
void lcdText_printf(uint8_t line, const char *format, ...){
    /* make buffer to hold the string */
    char buffer[LCD_DISP_LENGTH+1] = {'\0'};
    
    /* use sprintf to create formatted string */
    va_list args;
    va_start(args, format);
    vsprintf(buffer,format, args);
    va_end(args);
    
    /* display formatted string */
    lcdText_puts(line, buffer);
}
