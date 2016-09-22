#include <string.h>

#include "standard.h"
#include "mini-uart.h"
#include "gpio.h"

void main();

void main()
{
    GpioSetPinFunction(GpioPin2, GpioFunctionOutput);
    GpioSetPinOutput(GpioPin2);
    
    void* ptr = (void*)0xa00000;

    MiniUartWriteChar('d');
    memset(ptr, '-', 5);
    MiniUartWriteChar('e');

    while (true);
}
