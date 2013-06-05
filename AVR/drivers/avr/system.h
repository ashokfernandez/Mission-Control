/** @file   system.h
    @author M. P. Hayes, UCECE
    @date   15 May 2007
    @brief  System specific definitions
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


/* LED matrix columns.  
#define LCD_PIO PIO_DEFINE(PORT_A, 1)
#define LEDMAT_COL2_PIO PIO_DEFINE(PORT_B, 7)
#define LEDMAT_COL3_PIO PIO_DEFINE(PORT_C, 4)
#define LEDMAT_COL4_PIO PIO_DEFINE(PORT_C, 7)
#define LEDMAT_COL5_PIO PIO_DEFINE(PORT_C, 5)
#define LEDMAT_COLS_NUM 5
*/

void system_init (void);

#endif
