
#include "stm32f10x.h"  // Thu vien thanh ghi STM32F1
#include "timer.h"      // File khai bao ham Timer

void TIM2_Config(void)
{
    // 1. Bat clock cho Timer 2
    RCC->APB1ENR |= (1 << 0);

    // 2. Chia clock Timer: 72 MHz / (7199 + 1) = 10 kHz
    TIM2->PSC = 7199;

    // 3. Dem tu 0 den 4999, sau do tao su kien cap nhat
    TIM2->ARR = 4999;

    // 4. Dua bo dem CNT ve 0
    TIM2->CNT = 0;

    // 5. Tao su kien cap nhat de nap gia tri PSC
    TIM2->EGR = 1;

    // 6. Xoa co ngat cap nhat cu
    TIM2->SR &= ~(1 << 0);

    // 7. Cho phep ngat khi Timer dem het mot chu ky
    TIM2->DIER |= (1 << 0);

    // 8. Cho phep ngat TIM2 trong bo NVIC
    NVIC_EnableIRQ(TIM2_IRQn);

    // 9. Bat Timer 2
    TIM2->CR1 |= (1 << 0);
}
