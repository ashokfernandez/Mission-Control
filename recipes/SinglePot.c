#include "SinglePot.h"


void SinglePot(Pin_Analogue_t potentiometer)
{
	static uint8_t PrevDialValue;
	static bool init = false;

	if(!init){
		Analogue_Init(potentiometer);
		init = true;
	}

	uint8_t MIDICommand = 0;
	uint8_t MIDIPitch;

	/* Get current joystick mask, XOR with previous to detect joystick changes */
	uint8_t DialValue  = Analogue_Read(potentiometer);
	DialValue = DialValue >> 1; // Convert to 7 bit

	/* Get board button status - if pressed use channel 10 (percussion), otherwise use channel 1 */
	uint8_t Channel = 1;

	if (DialValue != PrevDialValue)
	{
		USBMIDIEvent_t MIDIEvent = 
			{
				.Type 		 = MIDI_EVENT_CC_CHANGE,
				.Channel     = Channel,
				.Key         = MIDI_KEY_GENERAL_PURPOSE_CC,
				.Value       = DialValue,
			};

		USBMIDI_SendMessage(MIDIEvent);
	}

	PrevDialValue = DialValue;
}