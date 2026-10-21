#include "stm32f10x.h"  // Thu vien STM32F1
#include "timer.h"      // Khai bao ham cau hinh Timer

void GPIO_Config(void);

int main(void)
{
    // Cau hinh chan GPIO dieu khien LED
    GPIO_Config();

    // Cau hinh Timer 2
    TIM2_Config();

    // Chuong trinh chinh cho CPU cho Timer tao ngat
    while (1)
    {
    }
}

// Ham cau hinh chan PC13
void GPIO_Config(void)
{
    // 1. Bat clock cho GPIOC
    RCC->APB2ENR |= (1 << 4);

    // 2. Cau hinh PC13 la ngo ra push-pull
    GPIOC->CRH &= ~(0xF << 20);
    GPIOC->CRH |=  (0x2 << 20);

    // 3. Dua PC13 len muc 1
    // LED tren nhieu board STM32F103 la LED tich cuc muc thap
    // Nen muc 1 se tat LED
    GPIOC->BSRR = (1 << 13);
}

// Ham nay duoc goi moi khi TIM2 tao ngat
void TIM2_IRQHandler(void)
{
    // Kiem tra co ngat cap nhat
    if (TIM2->SR & (1 << 0))
    {
        // Xoa co ngat
        TIM2->SR &= ~(1 << 0);

        // Dao trang thai chan PC13
        GPIOC->ODR ^= (1 << 13);
    }
}
