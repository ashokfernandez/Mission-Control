#include "PyGuiBindings.h"
#include "DataTypes.h"
#include "MidiDefinitions.h"
#include "USB.h"
#include "Target_Emulator.h"
#include <unistd.h> 
#include <stdlib.h>
#include <stdio.h>

int main(void){
	// PyGuiBindings_initConnection();
	// int digital, analogue;

	// printf("GUI connection establised");
	USB_init();
	int count = 60;
	while(1){
		// PyGuiBindings_update();
		// digital = PyGuiBindings_getDigital(DIGITAL_7);
		// analogue = PyGuiBindings_getAnalogue(ANALOGUE_1);

		// printf("Digital 7 is %i, analogue 1 is %i\n", digital, analogue);
		USB_sendMidiMessage(CC_CHANGE, CC_CHANNEL_1, count);
		count = (count + 1) % 127;
		sleep(1);
		
		
	}
	return 0;
}