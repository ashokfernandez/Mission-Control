/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2010  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Main source file for the MIDI demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "MIDI.h"
#include "adc.h"
#include <HAL/include/USBMIDI.h>

// My CC midi definitions
 #define MIDI_CC_CHANGE 0xB0
 #define GENERAL_PURPOSE_CC_CHANGE 0x10

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
	adc_init(ADC_REF_AVCC | ADC_8_BIT | ADC_SINGLE_ENDED | ADC_PRESCALE_2);
	LEDs_Init();
	Buttons_Init();

	for (;;)
	{
		CheckButtonPress();
		CheckDialChange();
		USBMIDI_Update();
	}
}



/** Checks for changes in the position of the board joystick, sending MIDI events to the host upon each change. */
void CheckButtonPress(void)
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
		MIDICommand = (ButtonPress ? MIDI_COMMAND_NOTE_ON : MIDI_COMMAND_NOTE_OFF);
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

/** Checks for changes in the position of the board joystick, sending MIDI events to the host upon each change. */
void CheckDialChange(void)
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
				.Type 		 = MIDI_CC_CHANGE,
				.Channel     = Channel,
				.Key         = GENERAL_PURPOSE_CC_CHANGE,
				.Value       = DialValue,
			};

		USBMIDI_SendMessage(MIDIEvent);
	}

	PrevDialValue = DialValue;
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

	ConfigSuccess &= MIDI_Device_ConfigureEndpoints(&Keyboard_MIDI_Interface);

	LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
	MIDI_Device_ProcessControlRequest(&Keyboard_MIDI_Interface);
}

