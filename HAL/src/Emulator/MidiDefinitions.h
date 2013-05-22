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

/// The first byte of each midi message should contain one of these codes 
/// See Table 2 here (http://www.midi.org/techspecs/midimessages.php)
#define CHAN_1_NOTE_ON 144
#define CHAN_2_NOTE_ON 145
#define CHAN_3_NOTE_ON 146
#define CHAN_4_NOTE_ON 147
#define CHAN_5_NOTE_ON 148
#define CHAN_6_NOTE_ON 149
#define CHAN_7_NOTE_ON 150
#define CHAN_8_NOTE_ON 151
#define CHAN_9_NOTE_ON 152
#define CHAN_10_NOTE_ON 153
#define CHAN_11_NOTE_ON 154
#define CHAN_12_NOTE_ON 155
#define CHAN_13_NOTE_ON 156
#define CHAN_14_NOTE_ON 157
#define CHAN_15_NOTE_ON 158
#define CHAN_16_NOTE_ON 159

#define CHAN_1_NOTE_OFF 128
#define CHAN_2_NOTE_OFF 129
#define CHAN_3_NOTE_OFF 130
#define CHAN_4_NOTE_OFF 131
#define CHAN_5_NOTE_OFF 132
#define CHAN_6_NOTE_OFF 133
#define CHAN_7_NOTE_OFF 134
#define CHAN_8_NOTE_OFF 135
#define CHAN_9_NOTE_OFF 136
#define CHAN_10_NOTE_OFF 137
#define CHAN_11_NOTE_OFF 138
#define CHAN_12_NOTE_OFF 139
#define CHAN_13_NOTE_OFF 140
#define CHAN_14_NOTE_OFF 141
#define CHAN_15_NOTE_OFF 142
#define CHAN_16_NOTE_OFF 143

/// Control Change Values (WARNING: UNTESTED!)
#define CC_CHANGE 176
#define CC_CHANNEL_1 16
#define CC_CHANNEL_2 17
#define CC_CHANNEL_3 18
#define CC_CHANNEL_4 19
#define CC_CHANNEL_5 20
#define CC_CHANNEL_6 21
#define CC_CHANNEL_7 22
#define CC_CHANNEL_8 23


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

