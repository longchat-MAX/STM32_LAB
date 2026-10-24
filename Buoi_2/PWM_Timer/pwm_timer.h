
#ifndef PWM_TIMER_H
#define PWM_TIMER_H

#include "stm32f10x.h"

// Ham khoi tao PWM bang Timer 2
void PWM_TIM2_Init(void);

// Ham dieu chinh do rong xung PWM (0 den 100%)
void PWM_SetDuty(uint8_t duty);

#endif
