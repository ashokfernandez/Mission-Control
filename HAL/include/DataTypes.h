#ifndef __DATATYPES_H__
#define __DATATYPES_H__

#include <stdbool.h>
#include <stdint.h>

/** 
 * Port definitions
 */
enum{PORT_A, PORT_B, PORT_C, PORT_D, PORT_E, PORT_F, PORT_G};

/**
 * @struct 	Pin_Analogue_t
 * @breif 	Structure to encapsulate information about ADC GPIO pins
 */
typedef struct _Pin_Analogue_t
{
	int PORT;
	int PIN;
	int CHANNEL;
} Pin_Analogue_t;


/**
 * @struct 	Pin_Digital_t
 * @breif 	Structure to encapsulate information about digital GPIO pins
 */
typedef struct _Pin_Digital_t
{
	int PORT;
	int PIN;
} Pin_Digital_t;

#endif /* __DATATYPES_H__ */