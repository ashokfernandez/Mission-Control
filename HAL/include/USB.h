#ifndef __USBMIDI_H__
#define __USBMIDI_H__

// Opens bracket for C++ compilers
#ifdef __cplusplus
extern "C" {
#endif

	/** @brief MIDI Event Packet.
	 *
	 *  Type define for a USBMIDI MIDI event packet, used to encapsulate sent and received MIDI messages from a USBMIDI MIDI interface.
	 *
	 *  @note Regardless of CPU architecture, these values should be stored as little endian.
	 */
	typedef struct _MIDI_Event
	{
		uint8_t  Type; 		/**< MIDI event type, Typically either MIDI_COMMAND_NOTE_ON or MIDI_CC_CHANGE */
		uint8_t  Channel; 	/**< MIDI Channel to send the command down */
		uint8_t  Key; 		/**< Key to be pressed or type of control change that has occured */
		uint8_t  Value; 	/**< Value of the event, typically either a velocity for a key press or a 7 bit value for a CC change */
	} MIDIEvent_t;

	void USBMIDI_Init(void);
	void USBMIDI_SendMidiMessage(MIDIEvent_t event);
	void USBMIDI_Update(void);

#ifdef __cplusplus
} // extern "C"
#endif


#endif /* __USBMIDI_H__ */