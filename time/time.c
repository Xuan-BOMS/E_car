#include "time.h"
volatile unsigned int delay_times = 0;
void delay_ms(unsigned int ms)
{
    delay_times = ms;
    while( delay_times != 0 );
}


void SysTick_Handler(void)
{
    if( delay_times != 0 )
    {
        delay_times--;
    }
}
