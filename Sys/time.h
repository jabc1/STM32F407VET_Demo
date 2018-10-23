#ifndef _time_h
#define _time_h
#include "stm32f4xx_hal.h"
extern TIM_HandleTypeDef htim3;
void MX_TIM3_Init(void);
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle);
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle);
#endif

