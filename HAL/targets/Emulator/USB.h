#ifndef __USB_H__
#define __USB_H__

// Opens bracket for C++ compilers
#ifdef __cplusplus
extern "C" {
#endif


#define MIDI_EVENT_NOTE_ON 0x90
#define MIDI_EVENT_NOTE_OFF 0x80
#define MIDI_EVENT_CC_CHANGE 0xB0

#define MIDI_KEY_GENERAL_CC_CHANGE 0x10

	/** @brief MIDI Event Packet.
	 *
	 *  Type define for a USB MIDI event packet, used to encapsulate sent and received MIDI messages from a USB MIDI interface.
	 *
	 *  @note Regardless of CPU architecture, these values should be stored as little endian.
	 */
	typedef struct _MIDI_Event
	{
		uint8_t  Type; 		/**< MIDI event type, Typically either MIDI_COMMAND_NOTE_ON or MIDI_CC_CHANGE */
		uint8_t  Channel; 	/**< MIDI Channel to send the command down */
		uint8_t  Key; 		/**< Key to be pressed or type of control change that has occured */
		uint8_t  Value; 	/**< Value of the event, typically either a velocity for a key press or a 7 bit value for a CC change */
	} MIDIEvent_t

	void USB_init(void);
	void USB_sendMidiMessage(int command, int channel, int value);

#ifdef __cplusplus
} // extern "C"
#endif


#endif /* __USB_H__ */