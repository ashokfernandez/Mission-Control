#include "SingleButton.h"

static uint8_t ButtonPress = 0;
static uint8_t PrevButtonPress = 0;;

void SingleButton(Pin_Digital_t pushbutton)
{
	

	uint8_t MIDICommand = 0;
	uint8_t MIDIPitch;

	/* Get current joystick mask, XOR with previous to detect joystick changes */
	ButtonPress = (Digital_Read(pushbutton));// << pushbutton.PIN);
	uint8_t ButtonChanged = (ButtonPress ^ PrevButtonPress);

	/* Get board button status - if pressed use channel 10 (percussion), otherwise use channel 1 */
	uint8_t Channel = 1;

	if (ButtonChanged)
	{
		MIDICommand = (Digital_Read(pushbutton) ? MIDI_EVENT_NOTE_ON : MIDI_EVENT_NOTE_OFF);
		MIDIPitch   = 0x3C;
	
		USBMIDIEvent_t MIDIEvent = 
			{
				.Type    	 = MIDICommand,
				.Channel     = pushbutton.PIN,
				.Key       	 = MIDIPitch,
				.Value       = MIDI_STANDARD_VELOCITY,
			};

		USBMIDI_SendMessage(MIDIEvent);
	}

	PrevButtonPress = ButtonPress;
}