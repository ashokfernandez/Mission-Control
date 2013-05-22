#ifndef __USB_H__
#define __USB_H__

void USB_init(void);
void USB_sendMidiMessage(int command, int channel, int value);

#endif /* __USB_H__ */