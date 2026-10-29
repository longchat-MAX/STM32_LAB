#include "timer.h"

void TimerConFig(void)
{
    RCC->APB2ENR |= (1 << 2);
    RCC->APB2ENR |= (1 << 11);

    // Cau hinh chan PA8
    GPIOA->CRH &= ~(0xF << 0);
    GPIOA->CRH |= (0b1011 << 0);

    TIM1->ARR = 99;
    TIM1->PSC = 35;

    // CH1
    TIM1->CCMR1 &= ~(0xFF);
    TIM1->CCMR1 |= (0b110 << 4);
    TIM1->CCMR1 |= (1 << 3);

    TIM1->CCER |= (1 << 0);

    TIM1->BDTR |= (1 << 15);

    TIM1->CCR1 = 0;

    TIM1->EGR |= (1 << 0);
    TIM1->CR1 |= (1 << 7);
    TIM1->CR1 |= (1 << 0);
}

void PWM_duty(uint16_t duty)
{
    if (duty > 100)
    {
        duty = 100;
    }

    TIM1->CCR1 = duty;
}