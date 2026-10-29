
#include "uart.h"

void UART1_Init(void)
{
    // 1. Bat clock GPIOA va USART1
    RCC->APB2ENR |= (1 << 2);   // GPIOA
    RCC->APB2ENR |= (1 << 14);  // USART1

    // 2. Cau hinh PA9: USART1_TX
    // MODE9 = 11: output 50 MHz
    // CNF9  = 10: alternate-function push-pull
    GPIOA->CRH &= ~(0xF << 4);
    GPIOA->CRH |=  (0xB << 4);

    // 3. Cau hinh PA10: USART1_RX
    // MODE10 = 00, CNF10 = 01: input floating
    GPIOA->CRH &= ~(0xF << 8);
    GPIOA->CRH |=  (0x4 << 8);

    // 4. Cau hinh baud rate 9600
    // Gia dinh PCLK2 = 72 MHz
    USART1->BRR = 0x1D4C;

    // 5. Cho phep UART, truyen va nhan
    USART1->CR1 = 0;
    USART1->CR1 |= (1 << 13);   // UE: Enable USART
    USART1->CR1 |= (1 << 3);    // TE: Enable transmitter
    USART1->CR1 |= (1 << 2);    // RE: Enable receiver
}

char UART1_ReadChar(void)
{
    // Cho den khi nhan duoc du lieu
    while ((USART1->SR & (1 << 5)) == 0);

    return (char)USART1->DR;
}

void UART1_SendChar(char c)
{
    // Cho den khi thanh ghi truyen trong
    while ((USART1->SR & (1 << 7)) == 0);

    USART1->DR = (uint16_t)c;
}
