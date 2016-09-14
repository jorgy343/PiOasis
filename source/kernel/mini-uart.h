#ifndef MINI_UART_H
#define MINI_UART_H

#include "standard.h"

#define MiniUartRegisterViewBase 0x3f215040

typedef struct
{
    volatile uint32_t IoData;
    volatile uint32_t InterruptEnable;
    volatile uint32_t InterruptIdentify;
    volatile uint32_t LineControl;
    volatile uint32_t ModemControl;
    volatile uint32_t LineStatus;
    volatile uint32_t ModemStatus;
    volatile uint32_t Scratch;
    volatile uint32_t ExtraControl;
    volatile uint32_t ExtraStatus;
    volatile uint32_t Baudrate;
} MiniUartRegisterView;

extern MiniUartRegisterView* MiniUartRegisters;

bool MiniUartCanRead();
bool MiniUartCanWrite();

char MiniUartReadChar();
void MiniUartWriteChar(char data);
void MiniUartWriteString(const char* string);

#endif
