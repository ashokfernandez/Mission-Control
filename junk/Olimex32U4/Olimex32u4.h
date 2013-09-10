/** 
 * @file Olimex32u4.h
 * @breif Mapping of the hardware pins on the Olimex-32u4 board to abstract data types, compatible 
 *        with the hardware abstraction layer
 *
 * Note: THIS SHOULD ONLY BE INCLUDED ONCE IN MAIN.C!
 */

#ifndef __OLIMEX_32U4__
#define __OLIMEX_32U4__

/* Analogue pins avaliable */
static Pin_Analogue_t analogue_0 = {PORT_F, 7, 7};
static Pin_Analogue_t analogue_1 = {PORT_F, 6, 6};
static Pin_Analogue_t analogue_2 = {PORT_F, 5, 5};
static Pin_Analogue_t analogue_3 = {PORT_F, 4, 4};
static Pin_Analogue_t analogue_4 = {PORT_F, 1, 1};
static Pin_Analogue_t analogue_5 = {PORT_F, 0, 1};

/* Digital pins avaliable */
static Pin_Digital_t digital_0 = {PORT_D, 2};
static Pin_Digital_t digital_1 = {PORT_D, 3};
static Pin_Digital_t digital_2 = {PORT_D, 1};
static Pin_Digital_t digital_3 = {PORT_D, 0};
static Pin_Digital_t digital_4 = {PORT_D, 4};
static Pin_Digital_t digital_5 = {PORT_C, 6};
static Pin_Digital_t digital_6 = {PORT_D, 7};
static Pin_Digital_t digital_7 = {PORT_E, 6};
static Pin_Digital_t digital_8 = {PORT_B, 4};
static Pin_Digital_t digital_9 = {PORT_B, 5};
static Pin_Digital_t digital_10 = {PORT_B, 6};
static Pin_Digital_t digital_11 = {PORT_B, 7};
static Pin_Digital_t digital_12 = {PORT_D, 6};
static Pin_Digital_t digital_13 = {PORT_C, 7};
static Pin_Digital_t digital_14 = {PORT_B, 0};
static Pin_Digital_t digital_15 = {PORT_B, 1};
static Pin_Digital_t digital_16 = {PORT_B, 2};
static Pin_Digital_t digital_17 = {PORT_B, 3};

/* The pushbutton on the acutal PCB, probably not useful in a real application but here for completness */
static Pin_Digital_t pushbutton = {PORT_E, 2};

#endif /* __OLIMEX_32U4__ */