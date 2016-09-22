#include <string.h>

#include "standard.h"
#include "mini-uart.h"
#include "gpio.h"

void main();

void main()
{
    GpioSetPinFunction(GpioPin2, GpioFunctionOutput);
    GpioSetPinOutput(GpioPin2);
    
    MiniUartWriteString("Mini uart initialized\r\n");

    // Unaligned memory access exception on purpose.
    int* t = (int*)0x1;
    int q = *t;

    while (true);
}
