#include "PyGuiBindings.h"
#include "DataTypes.h"
#include "MidiDefinitions.h"
#include "USB.h"
#include "Target_Emulator.h"
#include <unistd.h> 
#include <stdlib.h>
#include <stdio.h>




typedef struct _midiMap{
	int pin;
	int command;
	int channel;
	int value;
} midiMap;



void Sleep_ms(unsigned int milliSeconds)
{
    struct timespec req = {0};

    time_t seconds  = (int) (milliSeconds / 1000);
    milliSeconds    = milliSeconds - (seconds * 1000);
    req.tv_sec      = seconds;
    req.tv_nsec     = milliSeconds * 1000000L;

    while (nanosleep(&req, &req) == -1)
        continue;
}


// Initial value for the analogue pins
int analogue_pin_definitions[NUM_ANALOGUE_PINS] = {ANALOGUE_1, ANALOGUE_2, ANALOGUE_3, ANALOGUE_4,
												   ANALOGUE_5, ANALOGUE_6, ANALOGUE_7, ANALOGUE_8};
int analogue_command_definitions = CC_CHANGE; 												   

int analogue_channel_definitions[NUM_ANALOGUE_PINS] = {CC_CHANNEL_1, CC_CHANNEL_2, CC_CHANNEL_3, CC_CHANNEL_4,
												       CC_CHANNEL_5, CC_CHANNEL_6, CC_CHANNEL_7, CC_CHANNEL_8};
int analogue_value_definitions	= 0;											     

// Initial value for the digital pins
int digital_pin_definitions[NUM_DIGITAL_PINS] = {DIGITAL_1, DIGITAL_2, DIGITAL_3, DIGITAL_4,
												  DIGITAL_5, DIGITAL_6, DIGITAL_7, DIGITAL_8};

int digital_on_command_definitions = CHAN_1_NOTE_ON;

int digital_off_command_definitions = CHAN_1_NOTE_OFF;

int digital_channel_definitions[NUM_DIGITAL_PINS] = {36, 37, 38, 39, 40, 41, 42, 43};

int digital_value_definitions	= 0;											     




int main(void){
	// create some pins
	midiMap analogue_pins[NUM_ANALOGUE_PINS];
	midiMap digital_pins[NUM_DIGITAL_PINS];

	int value;
	
	// init pins
	int i;
	for(i = 0; i < NUM_DIGITAL_PINS; i++){
		digital_pins[i].pin = digital_pin_definitions[i];
		digital_pins[i].command = 0;
		digital_pins[i].channel = digital_channel_definitions[i];
		digital_pins[i].value = digital_value_definitions;
	}

	for(i = 0; i < NUM_ANALOGUE_PINS; i++){
		analogue_pins[i].pin = analogue_pin_definitions[i];
		analogue_pins[i].command = analogue_command_definitions;
		analogue_pins[i].channel = analogue_channel_definitions[i];
		analogue_pins[i].value = analogue_value_definitions;
	}

	// Init the GUI and USB
	PyGuiBindings_initConnection();
	USB_init();

	
	while(1){
		// Update the values
		PyGuiBindings_update();

		for(i = 0; i < NUM_DIGITAL_PINS; i++){
			value = PyGuiBindings_getDigital(digital_pins[i].pin);
			// If the value doesnt match the current one
			if (value != digital_pins[i].value){
				printf("Digital %i changed to %i\n",(i+1), value );
				// If the pin is not high send a midi on message
				if (value > 0){
					digital_pins[i].value = 1;
					digital_pins[i].command = digital_on_command_definitions;
				}
				// Otherwise send a midi low message
				else{
					digital_pins[i].value = 0;
					digital_pins[i].command = digital_off_command_definitions;
				}

				USB_sendMidiMessage(digital_pins[i].command, digital_pins[i].channel, digital_pins[i].value);
			}
		}

		for(i = 0; i < NUM_ANALOGUE_PINS; i++){
			value = PyGuiBindings_getAnalogue(analogue_pins[i].pin);
			// If the value doesnt match the current one
			if (value != analogue_pins[i].value){
				printf("Analogue %i changed to %i (%i)\n",(i+1), value, (value >> 2) );
				// Save the new value and send a midi message
				analogue_pins[i].value = value;
				
				USB_sendMidiMessage(analogue_pins[i].command, analogue_pins[i].channel, (analogue_pins[i].value >> 2));
			}
		}

		// Sleep for 100ms
		Sleep_ms(100);
		
	}

	return 0;
}