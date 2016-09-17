#include "mini-uart.h"

MiniUartRegisterView* MiniUartRegisters = (MiniUartRegisterView*)MiniUartRegisterViewBase;

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

void MiniUartWriteBool(bool value)
{
    if (value == true)
        MiniUartWriteString("true");
    else MiniUartWriteString("false");
}

void MiniUartWriteHex4(uint32_t value)
{
    if (value < 10)
        MiniUartWriteChar('0' + value);
    else
        MiniUartWriteChar('a' + value - 10);
}

void MiniUartWriteHex32(uint32_t value)
{
    for (int i = 28; i >= 0; i -= 4)
        MiniUartWriteHex4((value >> i) & 0xf);
}

void MiniUartWriteHex64(uint64_t value)
{
    MiniUartWriteHex32(value >> 32);
    MiniUartWriteHex32(value & 0xffffffffU);
}
