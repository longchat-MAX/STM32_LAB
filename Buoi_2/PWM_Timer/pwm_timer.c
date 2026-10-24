
#include "stm32f10x.h"
#include "pwm_timer.h"

void PWM_TIM2_Init(void)
{
    // 1. Bat clock GPIOA
    RCC->APB2ENR |= (1 << 2);

    // 2. Bat clock Timer 2
    RCC->APB1ENR |= (1 << 0);

    // 3. Cau hinh PA0 la ngo ra PWM (Alternate Function Push-Pull)
    GPIOA->CRL &= ~(0xF << 0);
    GPIOA->CRL |=  (0xB << 0);

    // 4. Cau hinh bo chia tan PSC
    // 72 MHz / (71 + 1) = 1 MHz
    TIM2->PSC = 71;

    // 5. Cau hinh ARR
    // Dem 1000 xung: tan so PWM = 1 MHz / 1000 = 1 kHz
    TIM2->ARR = 999;

    // 6. Dat duty cycle ban dau la 0%
    TIM2->CCR1 = 0;

    // 7. Chon PWM Mode 1 cho kenh CH1
    TIM2->CCMR1 &= ~(7 << 4);
    TIM2->CCMR1 |=  (6 << 4);

    // 8. Cho phep nap lai gia tri CCR1
    TIM2->CCMR1 |= (1 << 3);

    // 9. Cho phep dau ra PWM kenh CH1
    TIM2->CCER |= (1 << 0);

    // 10. Cho phep nap lai gia tri ARR
    TIM2->CR1 |= (1 << 7);

    // 11. Cap nhat cac thanh ghi Timer
    TIM2->EGR = 1;

    // 12. Bat Timer 2
    TIM2->CR1 |= (1 << 0);
}

void PWM_SetDuty(uint8_t duty)
{
    if (duty > 100)
    {
        duty = 100;
    }
    TIM2->CCR1 = (duty * 1000) / 100;
}
