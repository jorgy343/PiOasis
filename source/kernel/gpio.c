#include "gpio.h"

struct GpioRegisterView* GpioRegisters = (struct GpioRegisterView*)GpioRegisterViewBase;

void GpioSetRegisterToSinglePin(uint32_t pin, uint32_t* register0, uint32_t* register1)
{
    if (pin < 0 || pin > 53)
        return;

    if (pin <= 31)
        *register0 = bit(pin);
    else
        *register1 = bit(pin - 32);
}

void GpioSetPinFunctionOnRegister(uint32_t pin, enum GpioFunction function, uint32_t* register0)
{
    pin = pin % 10;
    uint32_t value = *register0;

    // TODO: Preserve value.
    value = function << (pin * 3);
    *register0 = value;
}

void GpioSetPinFunction(uint32_t pin, enum GpioFunction function)
{
    if (pin < 0 || pin > 53)
        return;

    if (pin <= 9)
        GpioSetPinFunctionOnRegister(pin, function, &GpioRegisters->FunctionSelect0);
}

void GpioSetPinOutput(uint32_t pin)
{
    GpioSetRegisterToSinglePin(pin, &GpioRegisters->PinOutputSet0, &GpioRegisters->PinOutputSet1);
}

void GpioClearPinOutput(uint32_t pin)
{
    
    GpioSetRegisterToSinglePin(pin, &GpioRegisters->PinOutputClear0, &GpioRegisters->PinOutputClear1);
}
