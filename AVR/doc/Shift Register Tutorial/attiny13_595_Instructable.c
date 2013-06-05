/* 

Author: Roznerd   http://roznerd.blogspot.com/
AVR:  ATtiny13   with internal clock set at 1MHz  and CLKDIV8 Fuse activated so delays are timely
Compiler: AVRStudio 4.17 build 666 + WinAVR GCC 20090313
Circuit: ATtiny13 controlling a 74HC595 hooked to 8 LED's with 470ohm resistors
Size:  200-300 bytes When Compiled with -Os optimization

Purpose:  

To demonstrate how a serial to parallel shift registers work.

----------------------------------------------------------------
---------------------------HEADER FILES-------------------------
----------------------------------------------------------------*/

#include<avr/io.h>
#include<util/delay.h>  // sets up the use of _delay_ms  and _delay_us

/*-------------------------------------------------------------------
-------------CONNECTION BETWEEN 74HC595 AND ATTINY13-----------------
---------------------------------------------------------------------*/
#define CONTROL_DDR	 	 DDRB       // this is where you will change the port if you are using a different AVR
#define CONTROL_PORT 	 PORTB
#define Data_Pin		  0
#define Enable_Pin		  1
#define Latch_Clk_Pin     2     
#define Shift_Clk_Pin     3
#define Reset_Pin    	  4

/*---------------------------------------------------------------------
-------------------CONTROL BITS OF SHIFT REGISTER ---------------------
This is basically just renaming everything to make it easy to work with
-----------------------------------------------------------------------*/

#define Clear_Enable  				CONTROL_PORT|=_BV(Enable_Pin)
#define Set_Enable	 				CONTROL_PORT&=~_BV(Enable_Pin)
#define Shift_Clk_H			   		CONTROL_PORT|=_BV(Shift_Clk_Pin)
#define Shift_Clk_L			    	CONTROL_PORT&=~_BV(Shift_Clk_Pin)
#define Latch_Clk_H			    	CONTROL_PORT|=_BV(Latch_Clk_Pin)
#define Latch_Clk_L				 	CONTROL_PORT&=~_BV(Latch_Clk_Pin)
#define Reset					 	CONTROL_PORT&=~_BV(Reset_Pin)
#define Reset_Clear			        CONTROL_PORT|=_BV(Reset_Pin)
#define delay(a)					_delay_ms(a)


/*---------------------------------------------------------------------
-------------------MACRO TO MAKE SIMPLE BITWISE DEFINITIONS -----------
Creates new syntax for bitwise calls in registers. 
-----------------------------------------------------------------------*/

typedef struct
{
  unsigned int bit0:1;
  unsigned int bit1:1;
  unsigned int bit2:1;
  unsigned int bit3:1;
  unsigned int bit4:1;
  unsigned int bit5:1;
  unsigned int bit6:1;
  unsigned int bit7:1;
} _io_reg;

#define REGISTER_BIT(rg,bt) ((volatile _io_reg*)&rg)->bit##bt


/*----------------------------------------------------------------
----------------------------FUNCTIONS-----------------------------
Initialize functions that will be used later on
-----------------------------------------------------------------*/
void shift_in(void);  // function toggles the Shift Clock
void latch_in(void);  // function toggles the Latch Clock
void reset_SR(void);  // function toggles the Reset Pin


/*----------------------------------------------------------------
---------------------------MAIN FUNCTION--------------------------
------------------------------------------------------------------*/
void main(void)
{

CONTROL_DDR = 0xFF;  // Set the Control DDR (i.e. DDRB) to be all outputs

int output[8] = {1,0,0,0,0,0,0,0};   // set up array of integer data to create pattern to show on the LEDs hooked to the 595 outputs

int i;  // initialize for loop variables

//int j;  // Loop variable for OPTION 2 - If you use OPTION 1 you should comment this out or you will get a warning upon compiling

reset_SR();  // Toggle the Reset Pin on the 595 to clear out SR

Set_Enable;  // Set the Output Enable Pin on the 595 (PB1 in this case) LOW to allow data to show on the outputs upon being latched

while(1)  // infinite loop
{
// --- You have 2 options in this code by commenting in or out these sections.
// The options vary how the output array is read and how the display is latched

// ------------------------- OPTION 1 ------------------------------------------
// Read the output array from position 0 to 7 (i=0-7) and latch the display
// as each bit is shifted in so the display shows the "scrolling effect" and utilizes 
// the fact that everything in the shift register "shifts" over when a new bit is latched.
// Option 1 is simple. Comment this code out if you plan to use Option 2.

		for (i=0; i<8; i++)  
		{
		REGISTER_BIT(PORTB,0) = output[i];   // Send data from the "output" array out to the Serial Input Pin on the 595 via PB0
		// Whatever state (hi or low) the Data Pin (PB0) is in when the shift clock is hit, is the state that is stored in the Shift Register
		shift_in();  // toggle Shift Clock Pin on 595 to shift current bit into SR
		
		latch_in();  // toggle the Latch Clock Pin on 595 to update the display after each new bit is shifted in

		}  // end for


//--------------------------- OPTION 2 ----------------------------------------- 
// Read 8 bits from the output array iterating through the starting positions (i=0-7)
// and "wrapping" around the array to include all 8 bits in the output array. Once there are 8 new bits
// shifted into the shift register the Latch Pin is toggled to update the display. This option will
// yield the same results on the display, but the for loop is effectively doing the scrolling 
// (not the shifting of the register like in option 1).
// This type of setup is more useful to adapt for a situation where you want to send a byte out the 595 for
// a LCD or 7 seg display. This code doesnt exactly satisfy that application because of the iterating
// starting location and the fact that the array is small. Ideally for a 8-bit data application
// you would have an array of Char's (bytes) and you would clock them into the 595 bitwise. I will
// cover this in another Instructable.
/*
for (j=0; j<8; j++)  // this for loop allows the address of the data in the "output" array to advance after each read.
						 // Without this loop the leds wouldn't scroll, the pattern would just display statically
{
		// This FOR Loop picks the starting point for looking up the data in the "output" array
		// It starts at i=j and goes to i=8. This excludes any values for i that are less than j.

		for (i=j; i<8; i++)  
		{
		REGISTER_BIT(PORTB,0) = output[i];   // Send data from the "output" array out to the Serial Input Pin on the 595 via PB0
		// Whatever state (hi or low) the Data Pin (PB0) is in when the shift clock is hit, is the state that is stored in the Shift Register
		shift_in();  // toggle Shift Clock Pin on 595 to shift current bit into SR
		

		}  // end for

		// This FOR Loops picks up where the other FOR loop left off, but addressing the data that was less than j.
		// This loop effectively "wraps" around the array, so when i=8 and there is still room in the SR, the Loop fills in
		// the remaining spots starting back at i=0. This is useful for making a "ring counter" to 
		// "scan" the columns of a Scrolling Dot Matrix LED display.

		for (i=0; i<j; i++)  // this for loop actually picks the addresses  in the "output" array to put out.
		{
		REGISTER_BIT(PORTB,0) = output[i];   // Send data from the "output" array out to the Serial Input Pin on the 595 via PB0
		// Whatever state (hi or low) the Data Pin (PB0) is in when the shift clock is hit, is the state that is stored in the Shift Register
		shift_in();  // toggle Shift Clock Pin on 595 to shift current bit into SR

		}  // end for


	latch_in(); // After 8 new bits have been clocked into the SR, Toggle the Latch Clock Pin on the 595 to present the 8 bits in the SR to th 595 Ouput Pins

	}  // end for
*/

}  // end while

}	// end main
	


/*---------------------------------------------------------------------------
----------------FUNCTION TO SHIFT DATA INTO 74HC595 -------------------------
Toggles the Shift Clock
-----------------------------------------------------------------------------*/
void shift_in(void)
{
Shift_Clk_H;
delay(20);   // these delays are arbitrary - they are here to slow things down so you can see the pattern
// for Option 1 - the delay should be around 20 for Option 2 - the delay should be about 3.
Shift_Clk_L;
delay(20);
}

 	
/*---------------------------------------------------------------------------
-----------------FUNCTIONS TO LATCH DATA TO OUTPUTS IN 74HC595 --------------
Toggles the Latch Clock
-----------------------------------------------------------------------------*/
void latch_in(void)
{
Latch_Clk_H;
delay(3); // these delays are arbitrary - they are here to slow things down so you can see the pattern
Latch_Clk_L;
delay(3);
}

/*---------------------------------------------------------------------------
-----------------FUNCTIONS TO RESET SHIFT REGISTER in 74HC595----------------
Toggles Reset Pin to Clear Shift Register
-----------------------------------------------------------------------------*/
void reset_SR(void)
{
Reset;
delay(10);
Reset_Clear;
delay(10);
}








