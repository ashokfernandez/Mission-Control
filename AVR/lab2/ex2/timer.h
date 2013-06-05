#ifndef TIMER_H
#define TIMER_H

#include "system.h"

#define PRESCALER 0x05

/* Initialise timer.  */
void timer_init (void);


/* Wait for the specified length of time.  */
void timer_delay_ms (uint16_t milliseconds);

#endif
