/*
  MocoMico for LUFA
*/

#include "MIDI.h"

/** LUFA MIDI Class driver interface configuration and state information. This structure is
 *  passed to all MIDI Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_MIDI_Device_t Keyboard_MIDI_Interface = {
  .Config = {
    .StreamingInterfaceNumber = 1,
    
    .DataINEndpointNumber      = MIDI_STREAM_IN_EPNUM,
    .DataINEndpointSize        = MIDI_STREAM_EPSIZE,
    .DataINEndpointDoubleBank  = false,

    .DataOUTEndpointNumber     = MIDI_STREAM_OUT_EPNUM,
    .DataOUTEndpointSize       = MIDI_STREAM_EPSIZE,
    .DataOUTEndpointDoubleBank = false,
  },
};

#define setPortBit0(port, bit) *(port) &= ~_BV(bit);
#define setPortBit1(port, bit) *(port) |= _BV(bit);
#define flipPortBit(port, bit) (*(port) ^= _BV(bit))
#define setPortBit(port, bit, val) { \
    if ((val) == 0) { setPortBit0((port), (bit)); } else	\
      { setPortBit1((port), (bit)); }				\
}

/* debugging LED  at PE6 */
#define LED_OFF  { PORTE &= ~0x40; }
#define LED_ON   { PORTE |=  0x40; }
#define FLIP_LED { PORTE ^=  0x40; }

#define    RX_SIZE        (HW_CDC_BULK_IN_SIZE)
static uchar utxrdy = FALSE;	/* USB Packet ready in utx_buf */
static uchar rx_buf[RX_SIZE];	/* tempory buffer */
static uchar utx_buf[RX_SIZE];	/* BULK_IN buffer */

#define    TX_SIZE        (HW_CDC_BULK_OUT_SIZE<<2)
#define    TX_MASK        (TX_SIZE-1)
static uchar uwptr = 0, irptr = 0;
static uchar tx_buf[TX_SIZE];


void parseUSBMidiMessage(uchar *data, uchar len) {
  uchar cin = (*data) & 0x0f;	/* CABLE NOを無視する */
  uchar i;

  LED_ON

  if (cin > 1) {		/* ignore cin == 0 and cin == 1 */
    for (i = 1 ; i < 4 ; i++) {
      tx_buf[uwptr++] = *(data + i);
      uwptr &= TX_MASK;
      if (i == 1) {
	if ((cin == 5) || /* single byte system common */
	    (cin == 15))  /* single byte */
	  break;
      }
      if (i == 2) {
	if ((cin == 2) ||  /* two-byte system common */
	    (cin == 6) ||  /* system ex end with 2 bytes */
	    (cin == 12) || /* program change */
	    (cin == 13))   /* channel pressure */
	  break;
      }
    }
  }

  LED_OFF

  if (len > 4) {
    parseUSBMidiMessage(data+4, len-4);
  }
}

uchar parseSerialMidiMessage(uchar RxByte) {
  static uchar PC = 0;
  static uchar SysEx = FALSE;
  static uchar stateTransTable[] = {
    0, 				/* 0 dummy */
    0,				/* 1 dummy */
    3,				/* 2->3 NOTE OFF (3) */
    2 | 0x80,			/* 3->2 */
    5,				/* 4->5 NOTE ON (3) */
    4 | 0x80,			/* 5->4 */
    7,				/* 6->7 Polyphonic key pressure (3) */
    6 | 0x80,			/* 7->6 */
    9,				/* 8->9 Control Change (3) */
    8 | 0x80,			/* 8->9 */
    10 | 0x80,			/* 10->10 program change (2) */
    0,				/* dummy */
    12 | 0x80,			/* 12->12 Channel Pressure (2) */
    0,				/* 13 dummy */
    15,				/* 14->15 Pitch Bend (3) */
    14 | 0x80			/* 15->14 */
  };

  if(SysEx){  /* MIDI System Message */
    if(RxByte == 0xf7){		/* MIDI_EndSysEx */
      SysEx = FALSE;
    }
    return FALSE;
  }
  if (RxByte >= 0xF8){		/* Single Byte Message */
    utx_buf[0] = 0x0f;
    utx_buf[1] = RxByte;
    utx_buf[2] = 0;
    utx_buf[3] = 0;
    return TRUE;
  }

  if(RxByte > 0x7F){		/* Channel message */
    if(RxByte == 0xf0){		/* MIDI_StartSysEx */
      SysEx = TRUE;
      return FALSE;
    }
    PC = 0;
  }

  if (PC == 0) {
    PC = (((RxByte >> 4) & 0x07) + 1) * 2;
    // conversion
    // 0x80 -> 2, 0x90 -> 4, 0xa0 -> 6, 0xb0 -> 8, 0xc0 -> 10, 0xd0 -> 12, 0xe0 -> 14
    rx_buf[0] = RxByte >> 4;
    rx_buf[1] = RxByte;
    rx_buf[3] = 0;
  } else {
    uchar tt = stateTransTable[PC];
    rx_buf[(PC & 1) + 2] = RxByte;
    PC = tt & 0x0f;
    if ((tt & 0x80) != 0) {
      memcpy(utx_buf, rx_buf, 4);
      return TRUE;
    }
  }
  return FALSE;
}

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void) {

  SetupHardware();
  sei();

  for (;;){ 
    /* receive from Serial MIDI line */
    if( UCSR1A & (1<<RXC1)) {
      utxrdy |= parseSerialMidiMessage(UDR1);
    }

    /* send packets to USB MIDI */
    if( utxrdy ) {
      MIDI_Device_SendEventPacket(&Keyboard_MIDI_Interface, (MIDI_EventPacket_t *)&utx_buf);
      MIDI_Device_Flush(&Keyboard_MIDI_Interface);
      utxrdy = FALSE;
    }

    /* receive from USB MIDI */
    MIDI_EventPacket_t ReceivedMIDIEvent;
    while (MIDI_Device_ReceiveEventPacket(&Keyboard_MIDI_Interface, &ReceivedMIDIEvent)) {
      /* for each MIDI packet w/ 4 bytes */
      parseUSBMidiMessage((uchar *)&ReceivedMIDIEvent, 4);
    }
      
    /* send to Serial MIDI line  */
    if( (UCSR1A & (1<<UDRE1)) && uwptr!=irptr ) {
      UDR1 = tx_buf[irptr++];
      irptr &= TX_MASK;
    }

    MIDI_Device_USBTask(&Keyboard_MIDI_Interface);
    USB_USBTask();
  }
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void) {
  /* Disable watchdog if enabled by bootloader/fuses */
  MCUSR &= ~(1 << WDRF);
  wdt_disable();
  
  /* Disable clock division */
  clock_prescale_set(clock_div_1);

  /* Hardware Initialization */

  DDRE |= 0b01000000; /* PE6 = OUTPUT */

  /* set baud rate */
  UBRR1L = 31;			/* 312500Hz at 16MHz clock */
  /*  */
  UCSR1B = (1<<RXEN1) | (1<<TXEN1);

  USB_Init();
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void) {
#if 0
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
#endif
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void) {
#if 0
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
#endif
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void) {
  bool ConfigSuccess = true;

  ConfigSuccess &= MIDI_Device_ConfigureEndpoints(&Keyboard_MIDI_Interface);

#if 0
  LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
#endif
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void) {
  MIDI_Device_ProcessControlRequest(&Keyboard_MIDI_Interface);
}

/* EOF */
