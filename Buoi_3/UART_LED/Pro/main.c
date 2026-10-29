
#include "stm32f10x.h"
#include "uart.h"

void LED_Init(void)
{
    // Bat clock GPIOC
    RCC->APB2ENR |= (1 << 4);

    // Cau hinh PC13 lam output push-pull
    GPIOC->CRH &= ~(0xF << 20);
    GPIOC->CRH |=  (0x2 << 20);

    // Tat LED ban dau
    GPIOC->BSRR = (1 << 13);
}

int main(void)
{
    LED_Init();
    UART1_Init();

    while (1)
    {
        if (UART1_ReadChar() == '1')
        {
            // Bat LED
            GPIOC->BRR = (1 << 13);

            UART1_SendChar('O');
            UART1_SendChar('N');
            UART1_SendChar('\r');
            UART1_SendChar('\n');
        }
        else if (UART1_ReadChar() == '0')
        {
            // Tat LED
            GPIOC->BSRR = (1 << 13);

            UART1_SendChar('O');
            UART1_SendChar('F');
            UART1_SendChar('F');
            UART1_SendChar('\r');
            UART1_SendChar('\n');
        }
    }
}
