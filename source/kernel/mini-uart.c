#include "mini-uart.h"

struct MiniUartRegisterView* MiniUartRegisters = (struct MiniUartRegisterView*)MiniUartRegisterViewBase;

bool MiniUartCanRead()
{
    return MiniUartRegisters->LineStatus & bit(0);
}

bool MiniUartCanWrite()
{
    return MiniUartRegisters->LineStatus & bit(5);
}

char MiniUartReadChar()
{
    while (!MiniUartCanRead());
    return MiniUartRegisters->IoData & 0xff; // Masking might not be necessary.
}

void MiniUartWriteChar(char data)
{
    while (!MiniUartCanWrite());
    
    uint32_t value = MiniUartRegisters->IoData;
    value = (value & 0xffffff00) | data; // Masking might not be necessary.
    
    MiniUartRegisters->IoData = value;
}

void MiniUartWriteString(const char* data)
{
    while (*data)
        MiniUartWriteChar(*data++);
}
