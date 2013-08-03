#include "system.h"
#include "pio.h"
#include "pacer.h"


/** Define PIO pins driving LED matrix rows.  */
static const pio_t rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, 
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};


/** Define PIO pins driving LED matrix columns.  */
static const pio_t cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

void ledmat_init(void) {
    int row, col;
    
    for(row = 0; row < LEDMAT_ROWS_NUM; row++) {
        pio_config_set(rows[row], PIO_OUTPUT_HIGH);
    }
    
    for(col = 0; col < LEDMAT_COLS_NUM; col++) {
        pio_config_set(cols[col], PIO_OUTPUT_HIGH);
    }
}

void ledmat_clear(void) {
    uint16_t row, col;
    
    for(row = 0; row < LEDMAT_ROWS_NUM; row++) {
        pio_output_high(rows[row]);
    }
    
    for(col = 0; col < LEDMAT_COLS_NUM; col++) {
        pio_output_high(cols[col]);
    }
}


static const uint8_t bitmap[] =
{
    0x63, 0x14, 0x08, 0x14, 0x63
};



static void display_column (uint8_t row_pattern, uint8_t current_column)
{
    uint16_t row = 0;
    /* TODO */
    /*clear previous info*/
    ledmat_clear();
    /* Turn on the row pattern */
    while(row < 7) {
        if(row_pattern & 1) {
            pio_output_low(rows[row]);
        }
        row++;
        row_pattern >>= 1;
    }
    /*turn on column*/
    pio_output_low(cols[current_column]);

}


int main (void)
{
    uint8_t current_column = 0;
  
    system_init ();
    pacer_init (500);
    
    /* TODO: Initialise LED matrix pins.  */
    ledmat_init();

    while (1)
    {
        pacer_wait ();
        
        display_column (bitmap[current_column], current_column);
    
        current_column++;
    
        if (current_column > (LEDMAT_COLS_NUM - 1))
        {
            current_column = 0;
        }           
    }
}
