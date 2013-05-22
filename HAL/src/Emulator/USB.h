#ifndef __USB_H__
#define __USB_H__

#ifdef __cplusplus
extern "C" {
#endif
	void USB_init(void);
	void USB_sendMidiMessage(int command, int channel, int value);
#ifdef __cplusplus
} // extern "C"
#endif


#endif /* __USB_H__ */