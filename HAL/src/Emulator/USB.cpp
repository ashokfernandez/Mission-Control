#include "USB.h"
#include "RtMidi.h"
#include <stdio.h>
#include <iostream>

// RtMidi parameters
#define VIRTUAL_MIDI_PORT_NAME "Mission Control Hardware Emulator"
#define MACOSX_CORE

// Virtual midi port
static RtMidiOut::RtMidiOut *virtualMidiOutput;

// Init the virtual midi port
void USB_init(void){
	// Open a midi port   
    try 
    {
        virtualMidiOutput = new RtMidiOut::RtMidiOut();
        virtualMidiOutput->RtMidiOut::openVirtualPort(VIRTUAL_MIDI_PORT_NAME);
    }
    catch ( RtError &error ) 
    {
        error.printMessage();
        exit( EXIT_FAILURE );
    }

    printf("Initilaised MIDI out\n");
}


/// Used to send a midi message down a virtual midi port with a given note and velocity.
/// Waits 500ms after sending the on signal to send the off signal.
void USB_sendMidiMessage(int command, int channel, int value)
{
    
    /// Send message down channel 10, the convention for percussion
    /// For more on how this message is constructed see table 2
    /// at http://www.midi.org/techspecs/midimessages.php
    std::vector<unsigned char> midiMessage(3);

    midiMessage[0] = command;
    midiMessage[1] = channel;
    midiMessage[2] = value;
    virtualMidiOutput->sendMessage( &midiMessage );

    printf("MIDI message sent\n");
    
}