#include "main.h"
#include "Task_SingleDigital.h"
#include "Task_SingleAnalogue.h"
#include "USBMIDI.h"
//#include "MIDIDefinitions.h"

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

	/* Initialise User Tasks */
	Task_SingleAnalogue_Init();
	Task_SingleDigital_Init();

	while(1)
	{
		/* Run User Tasks */
		Task_SingleDigital_Run();
		Task_SingleAnalogue_Run();
		
		/* Update the USB MIDI port */
		USBMIDI_Update();
	}
}


