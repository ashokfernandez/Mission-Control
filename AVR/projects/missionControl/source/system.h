/** @file   system.h
    @author M. P. Hayes, UCECE
    @date   15 May 2007
    @brief  System specific definitions
    
    Edited by Ashok Fernandez on 8/4/2012 for the atmega1284p clocked at
    16Mhz
*/

#ifndef SYSTEM_H
#define SYSTEM_H

/* Data typedefs.  */
#include <stdint.h>

typedef uint8_t bool;

/* Useful macros.  */
#define BIT(X) (1 << (X))

#define ARRAY_SIZE(ARRAY) (sizeof (ARRAY) / sizeof (ARRAY[0]))

#define  __unused__ __attribute__ ((unused))

/* Clock frequency Hz.  */
#define F_CPU 8000000

void system_init (void);

#endif /* SYSTEM_H */
