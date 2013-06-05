#include "pio.h"
#include "system.h"

#define BUTTON BUTTON1_PIO

void init_matrix(void) {
	pio_config_set(LEDMAT_COL1_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_COL2_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_COL3_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_COL4_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_COL5_PIO, PIO_OUTPUT_HIGH);
	
	pio_config_set(LEDMAT_ROW1_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_ROW2_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_ROW3_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_ROW4_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_ROW5_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_ROW6_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_ROW7_PIO, PIO_OUTPUT_HIGH);
	
}

int button_pushed(void) {
	int pushed = pio_input_get(BUTTON);
	return pushed;
}

void kill_matrix(void) {
	init_matrix();
}

void multiplex(pio_t ROW, pio_t COL) {
	pio_output_low(ROW);
	pio_output_low(COL);
	pio_output_high(ROW);
	pio_output_high(COL);
}

void drive_matrix(void) {
	multiplex(LEDMAT_ROW6_PIO, LEDMAT_COL2_PIO);
	multiplex(LEDMAT_ROW6_PIO, LEDMAT_COL3_PIO);
	multiplex(LEDMAT_ROW6_PIO, LEDMAT_COL4_PIO);
	multiplex(LEDMAT_ROW5_PIO, LEDMAT_COL1_PIO);
	multiplex(LEDMAT_ROW5_PIO, LEDMAT_COL5_PIO);
	multiplex(LEDMAT_ROW3_PIO, LEDMAT_COL2_PIO);
	multiplex(LEDMAT_ROW3_PIO, LEDMAT_COL4_PIO);
}

void perp_init(void) {
	pio_config_set(BUTTON, PIO_INPUT);
	init_matrix();
}

int main (void)
{
    system_init ();
	perp_init();
	
    while (1)
    {
		while(button_pushed())
        {
			drive_matrix();	
		}	
    }
}
