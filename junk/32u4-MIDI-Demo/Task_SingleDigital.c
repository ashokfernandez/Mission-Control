#include "main.h"
#include "MidiDefinitions.h"
#include "USBMIDI.h"

void Task_SingleDigital_Init(void){
	LEDs_Init();
	Buttons_Init();
}

void Task_SingleDigital_Run(void)
{
	static uint8_t PrevButtonPress;

	uint8_t MIDICommand = 0;
	uint8_t MIDIPitch;

	/* Get current joystick mask, XOR with previous to detect joystick changes */
	uint8_t ButtonPress  = Buttons_GetStatus();
	uint8_t ButtonChanged = (ButtonPress ^ PrevButtonPress);

	/* Get board button status - if pressed use channel 10 (percussion), otherwise use channel 1 */
	uint8_t Channel = 1;

	if (ButtonChanged)
	{
		MIDICommand = (ButtonPress ? MIDI_EVENT_NOTE_ON : MIDI_EVENT_NOTE_OFF);
		MIDIPitch   = 0x3C;
	
		USBMIDIEvent_t MIDIEvent = 
			{
				.Type    	 = MIDICommand,
				.Channel     = Channel,
				.Key       	 = MIDIPitch,
				.Value       = MIDI_STANDARD_VELOCITY,
			};

		USBMIDI_SendMessage(MIDIEvent);
	}

	PrevButtonPress = ButtonPress;
}