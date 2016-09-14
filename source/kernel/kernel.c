#include "standard.h"
#include "mini-uart.h"
#include "gpio.h"

void main()
{
    GpioSetPinFunction(GpioPin2, GpioFunctionOutput);
    GpioSetPinOutput(GpioPin2);

    MiniUartWriteString("Mini Uart initialized\r\n");
    while (true)
    {
        char value = MiniUartReadChar();

        MiniUartWriteString("Received: ");
        MiniUartWriteChar(value);
        MiniUartWriteString("\r\n");
    }
}
