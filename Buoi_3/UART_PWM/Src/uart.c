#include "uart.h"
#include "stm32f10x.h"

void ConFigUart(void)
{
    RCC->APB2ENR |= (1 << 2) | (1 << 14);

    // chon che do chan PA9
    GPIOA->CRH &= ~(0xFU << 4);
    GPIOA->CRH |= (0xBU << 4); // Tx

    // chon che do chan PA10
    GPIOA->CRH &= ~(0xFU << 8);
    GPIOA->CRH |= (0x8U << 8); // Rx pull up
    GPIOA->ODR |= (1 << 10);

    // baud = 9600, PCLK2 = 72 MHz
    USART1->BRR = 0x1D4C;

    USART1->CR1 |= (1 << 2) | (1 << 3);
    USART1->CR1 |= (1 << 13);
}

void sendUart(uint8_t data)
{
    while((USART1->SR & (1 << 7)) == 0)
    {
    }

    USART1->DR = data;
}

uint8_t readUART(void)
{
    if(USART1->SR & (1 << 5))
    {
        return USART1->DR;
    }

    return 0;
}

uint16_t readfullUART(void)
{
    uint16_t number = 0;
    uint8_t data;

    while (1)
    {
        while (!(USART1->SR & (1 << 5)))
        {
        }

        data = (uint8_t)(USART1->DR & 0xFF);

        if (data == '\r' || data == '\n')
        {
            break;
        }

        if (data >= '0' && data <= '9')
        {
            number = number * 10 + (data - '0');

            if (number > 100)
            {
                number = 100;
            }
        }
        else
        {
            number = 0;
        }
    }

    return number;
}