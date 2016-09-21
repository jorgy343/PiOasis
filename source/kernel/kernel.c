#include <stdio.h>

#include "standard.h"
#include "mini-uart.h"
#include "gpio.h"

void main();

void main()
{
    GpioSetPinFunction(GpioPin2, GpioFunctionOutput);
    GpioSetPinOutput(GpioPin2);
    
    MiniUartWriteChar('d');
    puts("sdf");

    while (true);
}
