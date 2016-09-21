#ifndef MINI_UART_H
#define MINI_UART_H

#include "standard.h"
#include "gpio.h"

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

void MiniUartWriteChar(char value);
void MiniUartWriteString(const char* value);

void MiniUartWriteBool(bool value);
void MiniUartWriteHex4(uint32_t value); // Writes out the first four bits of the integer.
void MiniUartWriteHex32(uint32_t value);
void MiniUartWriteHex64(uint64_t value);

#endif
