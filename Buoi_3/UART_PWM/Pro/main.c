#include "uart.h"
#include "stm32f10x.h"
#include "timer.h"

int main()
{
    ConFigUart();
    TimerConFig();

    while(1)
    {
        if (USART1->SR & (1 << 5))
        {
            uint16_t data = readfullUART(); // duty tu 0 -> 100
            PWM_duty(data);

            sendUart('0' + data / 100);
            sendUart('0' + (data / 10) % 10);
            sendUart('0' + data % 10);
            sendUart('%');
            sendUart('\r');
            sendUart('\n');
        }
    }
}