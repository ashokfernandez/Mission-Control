#include "Task_SingleAnalogue.h"
#include "main.h"
#include "avr_adc.h"
#include "USBMIDI.h"
#include "MidiDefinitions.h"

void Task_SingleAnalogue_Init(void)
{
	adc_init(ADC_REF_AVCC | ADC_8_BIT | ADC_SINGLE_ENDED | ADC_PRESCALE_2);
}

void Task_SingleAnalogue_Run(void)
{
	static uint8_t PrevDialValue;

	uint8_t MIDICommand = 0;
	uint8_t MIDIPitch;

	/* Get current joystick mask, XOR with previous to detect joystick changes */
	adc_startConversion(7);
	uint8_t DialValue  = adc_read();
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