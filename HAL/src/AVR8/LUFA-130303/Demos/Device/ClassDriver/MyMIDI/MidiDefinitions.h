/** 
 * @file MidiDefinitions.h
 * @author Ashok Fernandez <azf10@uclive.ac.nz>
 * @breif Definitions of general midi messages
 * 
 * The following is a set of #define's that specify the general midi commands and notes for different percussive instruments. 
 * Sources:
 * 		http://en.wikipedia.org/wiki/General_MIDI#Percussive    
 * 		http://www.midi.org/techspecs/midimessages.php (see table 2)
 */

#define MIDI_EVENT_NOTE_ON 0x90
#define MIDI_EVENT_NOTE_OFF 0x80
#define MIDI_EVENT_CC_CHANGE 0xB0

#define MIDI_KEY_GENERAL_PURPOSE_CC 0x10



/// If channel 10 is being used with a general midi device, these definitions should be the second entry in the 
/// general midi message to get the described sound. See (http://en.wikipedia.org/wiki/General_MIDI#Percussive)
#define BASS_DRUM_1 36
#define SIDE_STICK_RIMSHOT 37
#define SNARE_DRUM_1 38
#define HAND_CLAP 39
#define SNARE_DRUM_2 40
#define LOW_TOM_2 41
#define CLOSED_HI_HAT 42
#define LOW_TOM_1 43
#define PEDAL_HI_HAT 44
#define MID_TOM_2 45
#define OPEN_HI_HAT 46
#define MID_TOM_1 47
#define HIGH_TOM_2 48
#define CRASH_CYMBAL_1 49
#define HIGH_TOM_1 50
#define RIDE_CYMBAL_1 51
#define CHINESE_CYMBAL 52
#define RIDE_BELL 53
#define TAMBOURINE 54
#define SPLASH_CYMBAL 55
#define COWBELL 56
#define CRASH_CYMBAL_2 57
#define VIBRA_SLAP 58
#define RIDE_CYMBAL_2 59
#define HIGH_BONGO 60
#define LOW_BONGO 61
#define MUTE_HIGH_CONGA 62
#define OPEN_HIGH_CONGA 63
#define LOW_CONGA 64
#define HIGH_TIMBALE 65
#define LOW_TIMBALE 66
#define HIGH_AGOGO 67
#define LOW_AGOGO 68
#define CABASA 69
#define MARACAS 70
#define SHORT_WHISTLE 71
#define LONG_WHISTLE 72
#define SHORT_GUIRO 73
#define LONG_GUIRO 74
#define CLAVES 75
#define HIGH_WOOD_BLOCK 76
#define LOW_WOOD_BLOCK 77
#define MUTE_CUICA 78
#define OPEN_CUICA 79
#define MUTE_TRIANGLE 80
#define OPEN_TRIANGLE 81

