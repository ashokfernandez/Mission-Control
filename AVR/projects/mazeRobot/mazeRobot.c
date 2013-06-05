/** @file   mazeRobot.c
    @author A. Z. Fernandez
    @date   22 June 2012
    @brief  Main file for the maze solving robot for the ENEL300 robot  
*/

/**********************************************************************
 * -------------------------DEPENDENCIES------------------------------
 * *******************************************************************/

/** Include modules */
#include "system.h" // System definitions and bit macros
#include "debugLed.h" // Debug LED macros
#include "lineSensors.h" // Line Sensors module
#include "motors.h" // Motor Control module

#include "lcd.h"
#include "lcdText.h"

/** Include builtin AVR libraries */
#include <avr/io.h> // Pin and register definitions
#include <util/delay.h>

/**********************************************************************
 * ---------------------------DEFINITIONS------------------------------
 * *******************************************************************/

#define BLACK_CUTOFF 200
#define GREY_CUTOFF 300

/**********************************************************************
 * -----------------------------MACROS---------------------------------
 * *******************************************************************/

/* Determins if a sensor is reading black or white */
#define IS_BLACK(x) ((x) < BLACK_CUTOFF)
#define IS_WHITE(x) ((x) > BLACK_CUTOFF)

/**********************************************************************
 * -------------------------FILE VARIABLES-----------------------------
 * *******************************************************************/
 
static sensors_t sensors = {0, 0, 0};

/**********************************************************************
 * -----------------------PRIVATE FUNCTIONS----------------------------
 * *******************************************************************/

/** Flashes a debug LED to let the user know the micro has been reset */
void resetBlink(void)
{
    int i = 0;
    
    for(i = 0; i < 5; i++)
    {
        DEBUG_LED_1_ON;
        _delay_ms(75);
        DEBUG_LED_1_OFF;
        _delay_ms(75);
    }
}

void updateDisplay(void)
{
    lcd_clrscr();
    lcdText_printf(1, "%i, %i, %i", sensors.middle, sensors.right, sensors.front);
    lcdText_printf(2, "%i, %i", OCR1A, OCR1B);
    //lcd_gotoxy(0, 2);
    //if(IR_sensors.middle < BLACK_CUTOFF)
    //    lcd_puts("Black");
    //else if(IR_sensors.middle < GREY_CUTOFF)
    //    lcd_puts("Grey");
    //else
    //    lcd_puts("White");
    
    //lcd_gotoxy(6,2);
    
    //if(IR_sensors.left < BLACK_CUTOFF)
    //    lcd_puts("Black");
    //else if(IR_sensors.left < GREY_CUTOFF)
    //    lcd_puts("Grey");
    //else
    //    lcd_puts("White");
}
/**********************************************************************
 * -------------------*****   MAIN   *****---------------------------
 * *******************************************************************/

int main(void)
{
    /* Flash the debug light upon reset */
    DEBUG_LED_INIT;
    resetBlink();
    
    /* Initialise components */    
    lcd_init(LCD_DISP_ON);
    lineSensors_init();
    motors_init();
    
    _delay_ms(3000);
    
    while(1) // Loop forever
    {
        
    lineSensors_read(&sensors);
    //updateDisplay();
    
    
    if (IS_BLACK(sensors.right) && IS_WHITE(sensors.middle))
        motors_go(FORWARD);
        
    else if (IS_WHITE(sensors.right) && IS_WHITE(sensors.middle))
        motors_go(LEFT);
        
    else if (IS_BLACK(sensors.right) && IS_BLACK(sensors.middle))
        motors_go(RIGHT);
        
    else if (IS_WHITE(sensors.right) && IS_BLACK(sensors.middle))
        motors_go(RIGHT);
    
    //motors_stop()
    
    //_delay_ms(50);
    }

}
