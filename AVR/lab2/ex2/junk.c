#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define F_CPU 8000000
#define PRESCALER 0x05

int main(void)
{    
    uint16_t prescaler[] =  {0, 1, 8, 64, 256, 1024};
    float milliseconds = 500;
    milliseconds /= 1000;
    uint16_t count = (F_CPU / prescaler[PRESCALER]) * milliseconds;
    printf("%d", count);
    return 0;
}

