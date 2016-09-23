#include <string.h>
#include <stdio.h>

#include "standard.h"
#include "mini-uart.h"
#include "gpio.h"

void main();

void main()
{
    GpioSetPinFunction(GpioPin2, GpioFunctionOutput);
    GpioSetPinOutput(GpioPin2);
    
    MiniUartWriteString("Mini uart initialized\r\n");

    printf("test");
    MiniUartWriteString("\r\n");
    while (true);
}
