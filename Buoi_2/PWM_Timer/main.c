
#include "stm32f10x.h"
#include "pwm_timer.h"

void Delay(volatile uint32_t time);

int main(void)
{
    // Khoi tao PWM
    PWM_TIM2_Init();

    while (1)
    {
        // Tang do sang tu 0% den 100%
        for (uint8_t duty = 0; duty <= 100; duty++)
        {
            PWM_SetDuty(duty);
            Delay(10000);
        }

        // Giam do sang tu 100% ve 0%
        for (int duty = 100; duty >= 0; duty--)
        {
            PWM_SetDuty((uint8_t)duty);
            Delay(10000);
        }
    }
}


void Delay(volatile uint32_t time)
{
    while (time > 0)
    {
        time--;
    }
}

