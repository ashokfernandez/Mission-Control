#include "MidiDefinitions.h"
#include "USBMIDI.h"

/** LUFA MIDI Class driver interface configuration and state information. This structure is
 *  passed to all MIDI Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_MIDI_Device_t MIDI_Interface =
	{
		.Config =
			{
				.StreamingInterfaceNumber = 1,
				.DataINEndpoint           =
					{
						.Address          = MIDI_STREAM_IN_EPADDR,
						.Size             = MIDI_STREAM_EPSIZE,
						.Banks            = 1,
					},
				.DataOUTEndpoint          =
					{
						.Address          = MIDI_STREAM_OUT_EPADDR,
						.Size             = MIDI_STREAM_EPSIZE,
						.Banks            = 1,
					},
			},
	};

void USBMIDI_Init(void){
	USB_Init();
	sei();
}

void USBMIDI_SendMessage(USBMIDIEvent_t Event) {
	/* Translate the MIDI event into a LUFA Midi event */
	MIDI_EventPacket_t MIDIEvent = (MIDI_EventPacket_t)
	{
		.Event    	 = MIDI_EVENT(0, Event.Type),

		.Data1       = Event.Type | MIDI_CHANNEL(Event.Channel),
		.Data2       = Event.Key,
		.Data3       = Event.Value,
	};

	/* Queue the MIDI event in the LUFA USB Queue*/
	MIDI_Device_SendEventPacket(&MIDI_Interface, &MIDIEvent);
	MIDI_Device_Flush(&MIDI_Interface);
}

void USBMIDI_Update(void) {
	// Check the queue for MIDI events
	MIDI_EventPacket_t ReceivedMIDIEvent;
	while (MIDI_Device_ReceiveEventPacket(&MIDI_Interface, &ReceivedMIDIEvent))
		continue;

	// Sends the MIDI events down the USB connection
	MIDI_Device_USBTask(&MIDI_Interface);
	USB_USBTask();
}



/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	ConfigSuccess &= MIDI_Device_ConfigureEndpoints(&MIDI_Interface);

	LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
	MIDI_Device_ProcessControlRequest(&MIDI_Interface);
}




