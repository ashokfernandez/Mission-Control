#include "system.h"
#include "pio.h"


/* Include the pacer module from the previous lab.
   You must have completed this before starting this exercise.  */
#include "pacer.h"

/** Define PIO pins driving LED matrix rows.  */
static const pio_t ledmat_rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, 
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};


/** Define PIO pins driving LED matrix columns.  */
static const pio_t ledmat_cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

/** Initialise LED matrix PIO pins.  */
static void ledmat_init (void)
{
    uint8_t row;
    uint8_t col;

    for (row = 0; row < 7; row++)
    {
        pio_config_set (ledmat_rows[row], PIO_OUTPUT_HIGH);
        pio_output_high (ledmat_rows[row]);
    }

    for (col = 0; col < 5; col++)
    {
        pio_config_set (ledmat_cols[col], PIO_OUTPUT_HIGH);
        pio_output_high (ledmat_cols[col]);
    }
}

int main (void)
{
    system_init ();
    
    /* TODO: Initialise the pins of the LED matrix.  */
    ledmat_init();

    /* Set up pacer with a frequency of 50 Hz.  */
    pacer_init (50);

    while (1)
    {
        /* Pace the loop.  */
       pacer_wait ();
        
         /* TODO: Drive the LED matrix using the pio functions,
         displaying only three corner LEDs.  */
        pio_output_low(ledmat_cols[0]);
        pio_output_low(ledmat_cols[4]);
        pio_output_low(ledmat_rows[0]);
        
        pio_output_high(ledmat_cols[4]);
        pio_output_high(ledmat_rows[0]);
        
        pio_output_low(ledmat_rows[6]);
        pio_output_high(ledmat_rows[6]);
        
    }
}
