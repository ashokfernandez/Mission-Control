/*
             LUFA Library
     Copyright (C) Dean Camera, 2012.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2012  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/* Olimexino 32U4 Board drivers for use with the LUFA library 
 * Written by Ashok Fernandez using the LUFA board drivers as a base
 * 2nd July 2012 
 * */

/** \file
 *  \brief Board specific Buttons driver header for the Olimexino-32U4 Development Board.
 *  \copydetails Group_Buttons_OLIMEXINO32U4
 *
 *  \note This file should not be included directly. It is automatically included as needed by the Buttons driver
 *        dispatch header located in LUFA/Drivers/Board/Buttons.h.
 */

/** \ingroup Group_Buttons
 *  \defgroup Group_Buttons_OLIMEXINO32U4 OLIMEXINO32U4
 *  \brief Board specific Buttons driver header for the Olimexino-32U4 Development Board.
 *
 *  Board specific Buttons driver header for the Olimexino-32U4 Development Board (http://www.olimex.com/dev/olimexino-32u4.html).
 *
 *  @{
 */

#ifndef __BUTTONS_OLIMEXINO32U4_H__
#define __BUTTONS_OLIMEXINO32U4_H__

    // Button (#HWB) is on PE2

    /* Public Interface - May be used in end-application: */
        /* Macros: */
            /** Button mask for the first button on the board. */
            #define BUTTONS_BUTTON1      (1 << 2)

        /* Inline Functions: */
        #if !defined(__DOXYGEN__)
            static inline void Buttons_Init(void)
            {
                DDRE  &= ~BUTTONS_BUTTON1;
                PORTE |=  BUTTONS_BUTTON1;
            }

            static inline void Buttons_Disable(void)
            {
                DDRE  &= ~BUTTONS_BUTTON1;
                PORTE &= ~BUTTONS_BUTTON1;
            }

            static inline uint8_t Buttons_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
            static inline uint8_t Buttons_GetStatus(void)
            {
                return ((PINE & BUTTONS_BUTTON1) ^ BUTTONS_BUTTON1);
            }
        #endif

    /* Disable C linkage for C++ Compilers: */
        #if defined(__cplusplus)
            }
        #endif

#endif

/** @} */

