#include "bits.h"
#include "Digital.h"
#include <DataTypes.h>
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>

// AVR GPIO Registers
// 
// DDR set high for output, low for input
// PORT set high for output high, low for output low and high to activate pullup, low to deactivate pullup
// PIN read for pin value	
// 
// NOTE:
// As the the definitions (i.e DDRA) are actually #defined registers, it isn't possible to neatly map them in 
// a nicer way - hence the use of switch statements


/**
 * Initilises a pin as a digital pin
 * @param pin Pin to initialise
 */
void Digital_Init(Pin_Digital_t pin) {
	// Set the given pin to an output low to protect the pin from being blown
	switch(pin.PORT){
// Note: the conditional include is to prevent compile errors on boards that don't have this register
#ifdef DDRA
		case PORT_A:
			DDRA |= BIT(pin.PIN); 		// Setting the Data-Direction-Register (DDR) high makes the pin an output
			PORTA &= ~BIT(pin.PIN);    // Setting the PORT register low makes the pin an output low
			break;
#endif
#ifdef DDRB 			
		case PORT_B:
			DDRB |= BIT(pin.PIN);
			PORTB &= ~BIT(pin.PIN);
			break;
#endif
#ifdef DDRC
		case PORT_C:
			DDRC |= BIT(pin.PIN);
			PORTC &= ~BIT(pin.PIN);
			break;
#endif
#ifdef DDRD
		case PORT_D:
			DDRD |= BIT(pin.PIN);
			PORTD &= ~BIT(pin.PIN);
			break;
#endif
#ifdef DDRE
		case PORT_E:
			DDRE |= BIT(pin.PIN);
			PORTE &= ~BIT(pin.PIN);
			break;
#endif
#ifdef DDRF
		case PORT_F:
			DDRF |= BIT(pin.PIN);
			PORTF &= ~BIT(pin.PIN);
			break;
#endif
#ifdef DDRG
		case PORT_G:
			DDRG |= BIT(pin.PIN);
			PORTG &= ~BIT(pin.PIN);
			break;
#endif			
	}
}

/**
 * Reads the value of a digital pin
 * @param pin Pin to read
 * @return true if the pin is high, false if the pin is low
 */
bool Digital_Read(Pin_Digital_t pin) {
	bool pinValue;
	
	// Select the port to read from
	switch(pin.PORT){

// Note: the conditional include is to prevent compile errors on boards that don't have this register
#ifdef DDRA
		case PORT_A:
			DDRA &= ~BIT(pin.PIN); 			// Setting the Data-Direction-Register (DDR) low makes the pin an input
			pinValue = (bool)(PINA & BIT(pin.PIN)) ;    // The PIN register contains the input value
			break;
#endif
#ifdef DDRB 			
		case PORT_B:
			DDRB &= ~BIT(pin.PIN);
			pinValue = (bool)(PINB & BIT(pin.PIN)) ;
			break;
#endif
#ifdef DDRC
		case PORT_C:
			DDRC &= ~BIT(pin.PIN);
			pinValue = (bool)(PINC & BIT(pin.PIN)) ;
			break;
#endif
#ifdef DDRD
		case PORT_D:
			DDRD &= ~BIT(pin.PIN);
			pinValue = (bool)(PIND & BIT(pin.PIN)) ;
			break;
#endif
#ifdef DDRE
		case PORT_E:
			DDRE &= ~BIT(pin.PIN);
			pinValue = (bool)(PINE & BIT(pin.PIN)) ;
			break;
#endif
#ifdef DDRF
		case PORT_F:
			DDRF &= ~BIT(pin.PIN);
			pinValue = (bool)(PINF & BIT(pin.PIN)) ;
			break;
#endif
#ifdef DDRG
		case PORT_G:
			DDRG &= ~BIT(pin.PIN);
			pinValue = (bool)(PING & BIT(pin.PIN)) ;
			break;
#endif			
	}

	return pinValue;
}

/**
 * Writes a value to the specified pin.
 * @param pin Pin to read
 * @param value true to set the pin, false to set the pin low
 */
void Digital_Write(Pin_Digital_t pin, bool value) {

	// Select the port to write to
	switch(pin.PORT){
// Note: the conditional include is to prevent compile errors on boards that don't have this register
#ifdef DDRA
		case PORT_A:
			DDRA |= BIT(pin.PIN); 		// Setting the Data-Direction-Register (DDR) high makes the pin an output
			if(value) // If the bit is to be set
				PORTA |= BIT(pin.PIN);	 // Set the bit
			else
				PORTA &= ~BIT(pin.PIN);  // Clear the bit
			break;						
										
#endif
#ifdef DDRB 			
		case PORT_B:
			DDRB |= BIT(pin.PIN);
			if(value) // If the bit is to be set
				PORTB |= BIT(pin.PIN);	 // Set the bit
			else
				PORTB &= ~BIT(pin.PIN);  // Clear the bit
			break;
#endif
#ifdef DDRC
		case PORT_C:
			DDRC |= BIT(pin.PIN);
			if(value) // If the bit is to be set
				PORTC |= BIT(pin.PIN);	 // Set the bit
			else
				PORTC &= ~BIT(pin.PIN);  // Clear the bit
			break;
#endif
#ifdef DDRD
		case PORT_D:
			DDRD |= BIT(pin.PIN);
			if(value) // If the bit is to be set
				PORTD |= BIT(pin.PIN);	 // Set the bit
			else
				PORTD &= ~BIT(pin.PIN);  // Clear the bit
			break;
#endif
#ifdef DDRE
		case PORT_E:
			DDRE |= BIT(pin.PIN);
			if(value) // If the bit is to be set
				PORTE |= BIT(pin.PIN);	 // Set the bit
			else
				PORTE &= ~BIT(pin.PIN);  // Clear the bit
			break;
#endif
#ifdef DDRF
		case PORT_F:
			DDRF |= BIT(pin.PIN);
			if(value) // If the bit is to be set
				PORTF |= BIT(pin.PIN);	 // Set the bit
			else
				PORTF &= ~BIT(pin.PIN);  // Clear the bit
			break;
#endif
#ifdef DDRG
		case PORT_G:
			DDRG |= BIT(pin.PIN);
			if(value) // If the bit is to be set
				PORTG |= BIT(pin.PIN);	 // Set the bit
			else
				PORTG &= ~BIT(pin.PIN);  // Clear the bit
			break;
#endif			
	}
}