#include <stdint.h>

#include "standard.h"
#include "mini-uart.h"
#include "gpio.h"

void main()
{
    GpioSetPinFunction(2, GpioFunctionOutput);
    GpioSetPinOutput(2);

    while (true)
    {
        char value = ReadMiniUartChar();
        
        MiniUartWriteString("Received: ");
        MiniUartWriteChar(value);
        MiniUartWriteString("\r\n");
    }
    
    uint32_t* gpioSelect0 = (uint32_t*)0x3f200000;
    uint32_t* gpioSet0 = (uint32_t*)0x3f20001c;
    uint32_t* gpioClear0 = (uint32_t*)0x3f200028;
    
    *gpioSelect0 = 0x40;
    
    bool shouldSet = true;
    while (true)
    {
        if (shouldSet)
            *gpioSet0 = 0x4;
        else
            *gpioClear0 = 0x4;
        
        shouldSet = !shouldSet;
        for (int i = 0; i < 200000; i++);
    }
}
