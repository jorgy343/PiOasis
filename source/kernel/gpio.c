#include "gpio.h"

struct GpioRegisterView* GpioRegisters = (struct GpioRegisterView*)GpioRegisterViewBase;

enum GpioFunction SafeGetFunction(enum GpioPin pin, uint32_t* registerBase)
{
    if (pin < 0 || pin > 53)
        return -1;
    
    registerBase += pin / 10;
    pin = pin % 10;

    return *registerBase & (0x7 << (pin * 3));
}

void SafeSetFunction(enum GpioPin pin, enum GpioFunction function, uint32_t* registerBase)
{
    if (pin < 0 || pin > 53)
        return;
    
    registerBase += pin / 10;
    pin = pin % 10;
        
    uint32_t value = *registerBase;    
    
    // Clear out the bits we are going to set.
    value &= ~(0x7 << (pin * 3));
    
    // Set the bits while preserving the existing bits.
    *registerBase |= (function << (pin * 3));
}

enum GpioPinLevel SafeGetPin(enum GpioPin pin, uint32_t* register0, uint32_t* register1)
{
    if (pin < 0 || pin > 53)
        return -1;

    if (pin <= 31)
        return *register0 & bit(pin);

    return *register1 & bit(pin - 32);
}

void SafeSetPin(enum GpioPin pin, uint32_t* register0, uint32_t* register1)
{
    if (pin < 0 || pin > 53)
        return;

    if (pin <= 31)
        *register0 = bit(pin);
    else
        *register1 = bit(pin - 32);
}

enum GpioFunction GpioGetPinFunction(enum GpioPin pin)
{
    return SafeGetFunction(pin, &GpioRegisters->FunctionSelect0);
}

void GpioSetPinFunction(enum GpioPin pin, enum GpioFunction function)
{
    SafeSetFunction(pin, function, &GpioRegisters->FunctionSelect0);
}

void GpioSetPinOutput(enum GpioPin pin)
{
    SafeSetPin(pin, &GpioRegisters->PinOutputSet0, &GpioRegisters->PinOutputSet1);
}

void GpioClearPinOutput(enum GpioPin pin)
{
    SafeSetPin(pin, &GpioRegisters->PinOutputClear0, &GpioRegisters->PinOutputClear1);
}

enum GpioPinLevel GpioGetPinLevel(enum GpioPin pin)
{
    return SafeGetPin(pin, &GpioRegisters->PinLevel0, &GpioRegisters->PinLevel1);
}
