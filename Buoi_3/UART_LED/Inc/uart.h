
#ifndef UART_H
#define UART_H

#include "stm32f10x.h"
#include <stdint.h>

void UART1_Init(void);
char UART1_ReadChar(void);
void UART1_SendChar(char c);

#endif
