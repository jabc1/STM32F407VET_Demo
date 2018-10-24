#ifndef _delay_h
#define _delay_h
#include "stm32f4xx_hal.h"

void SysTick_delay_ms(u16 ms);
void SysTick_delay_us(u32 us);
void SysTick_delay_xms(u32 xms);

#endif





