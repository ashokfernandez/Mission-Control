/* Include the hardware abstraction layer headers */
#include "DataTypes.h"
#include "MidiDefinitions.h"
#include "USB.h"
#include "USBMIDI.h"
#include "Digital.h"
#include "Analogue.h"

/* User includes for recipies */
#include "SinglePot.h"
#include "SingleButton.h"


/* Pins used by recipies */
static Pin_Analogue_t analogue_0 = {PORT_F, 7, 7};
static Pin_Digital_t digital_0 = {PORT_D, 2};


/* Template engine replace */
void System_Init(void){
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);
}

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	/* Initialise System */
	System_Init();
	USBMIDI_Init();

	while(1)
	{
		/* Run User Tasks */
		SinglePot(analogue_0);
SingleButton(digital_0);

		
		/* Update the USB MIDI port */
		USBMIDI_Update();
	}
}