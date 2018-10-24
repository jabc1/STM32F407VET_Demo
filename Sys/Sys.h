#ifndef _Sys_h
#define _Sys_h
#include "stm32f4xx_hal.h"
void SystemClock_Config(void);
void _Error_Handler(char *file, int line);
void assert_failed(uint8_t* file, uint32_t line);
#endif

