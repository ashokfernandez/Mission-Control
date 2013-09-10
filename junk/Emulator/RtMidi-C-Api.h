/* A C API for interacting with the RtMidi library */

// to compile (on OSX):
// clang++ -dynamiclib -Wall -D__MACOSX_CORE__ -o librtmidi.dylib RtMidi.cpp RtMidi-C-Api.cpp -framework CoreMIDI -framework CoreAudio -framework CoreFoundation

#if defined(__MACOSX_CORE__)
#include <sys/types.h>
#else
#include <stdint.h>
#endif

//#include <iostream>
//#include <vector>
//#include <string>
#include "RtMidi.h"

#ifdef __cplusplus
extern "C" {
#endif

// error codes

enum rtErr {
     RTMIDI_NOERROR,
     RTMIDI_ERROR
};

struct inDevice {
     RtMidiIn* ptr;
};

struct outDevice {
     RtMidiOut* ptr;
};

typedef void (*xtmCallback)( double timeStamp, int64_t messageLength, uint8_t* message );

// midi input

rtErr newMidiInDevice( inDevice* dev, RtMidi::Api api, char* clientName );
rtErr deleteMidiInDevice( inDevice* dev );

int32_t getInCurrentApi( inDevice* dev );
int64_t getInPortCount( inDevice* dev );
int8_t* getInPortName( inDevice* dev, int64_t portNumber );

rtErr openInPort( inDevice* dev, int64_t portNumber, char* portName );
rtErr openInVirtualPort( inDevice* dev, char* portName );
rtErr closeInPort( inDevice* dev );

void callbackWrapper( double timeStamp, std::vector<unsigned char> *message, void *userData );
rtErr setCallback( inDevice* dev, xtmCallback callback );
rtErr cancelCallback( inDevice* dev );

// midi output

rtErr newMidiOutDevice( outDevice* dev, RtMidi::Api api, char* clientName );
rtErr deleteMidiOutDevice( outDevice* dev );

int32_t getOutCurrentApi( outDevice* dev );
int64_t getOutPortCount( outDevice* dev );
int8_t* getOutPortName( outDevice* dev, int64_t portNumber );

rtErr openOutPort( outDevice* dev, int64_t portNumber, char* portName );
rtErr openOutVirtualPort( outDevice* dev, char* portName );
rtErr closeOutPort( outDevice* dev );
rtErr sendMessage( outDevice* dev, int64_t messageLength, uint8_t* message );

#ifdef __cplusplus
} // extern "C"
#endif
