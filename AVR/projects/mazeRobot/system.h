/** @file   system.h
    @author A. Z. Fernandez
    @date   28 June 2012
    @brief  System settings and datatype definitions shared between modules
            for a maze solving robot using an atmega8 MCU
*/

#ifndef SYSTEM_H
#define SYSTEM_H

/** Clocked from internal 8MHz RC oscillator with no prescaler */
#define F_CPU 8000000

/** Datatypes */
#include <stdint.h>

typedef uint8_t bool;
#define TRUE 1
#define FALSE 0

/** Max values for different int */
#define MAX_UINT8 255
#define MAX_UINT16 65535

/** Bitwise Macros */
#define BIT(x) (1 << (x))
#define BITMASK(first, last) ((1 << ((last) + 1)) - (1 << (first)))
#define BITSINSERT(reg, val, first, last) \
    (reg) = ((reg) & ~BITMASK (first, last))  \
        | (((val) & BITMASK (0, last - first)) << (first))

#endif /* SYSTEM_H */
