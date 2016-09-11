#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include "standard.h"

#define GpioRegisterViewBase 0x3f200000

struct GpioRegisterView
{
    uint32_t FunctionSelect0;
    uint32_t FunctionSelect1;
    uint32_t FunctionSelect2;
    uint32_t FunctionSelect3;
    uint32_t FunctionSelect4;
    uint32_t FunctionSelect5;
    uint32_t Reserved0;

    uint32_t PinOutputSet0;
    uint32_t PinOutputSet1;
    uint32_t Reserved1;

    uint32_t PinOutputClear0;
    uint32_t PinOutputClear1;
    uint32_t Reserved2;

    uint32_t PinLevel0;
    uint32_t PinLevel1;
    uint32_t Reserved3;

    uint32_t PinEventDetectStatus0;
    uint32_t PinEventDetectStatus1;
    uint32_t Reserved4;

    uint32_t PinRisingEdgeDetectEnable0;
    uint32_t PinRisingEdgeDetectEnable1;
    uint32_t Reserved5;

    uint32_t PinFallingEdgeDetectEnable0;
    uint32_t PinFallingEdgeDetectEnable1;
    uint32_t Reserved6;

    uint32_t PinHighDetectEnable0;
    uint32_t PinHighDetectEnable1;
    uint32_t Reserved7;

    uint32_t PinLowDetectEnable0;
    uint32_t PinLowDetectEnable1;
    uint32_t Reserved8;

    uint32_t PinAsyncRisingEdgeDetect0;
    uint32_t PinAsyncRisingEdgeDetect1;
    uint32_t Reserved9;

    uint32_t PinAsyncFallingEdgeDetect0;
    uint32_t PinAsyncFallingEdgeDetect1;
    uint32_t Reserved10;

    uint32_t PinPullUpDownEnable;
    uint32_t PinPullUpDownEnableClock0;
    uint32_t PinPullUpDownEnableClock1;
    uint32_t reserved11;

    uint32_t Test;
};

enum GpioFunction
{
    GpioFunctionInput,
    GpioFunctionOutput,
    GpioFunctionAlternate5,
    GpioFunctionAlternate4,
    GpioFunctionAlternate0,
    GpioFunctionAlternate1,
    GpioFunctionAlternate2,
    GpioFunctionAlternate3
};

extern struct GpioRegisterView* GpioRegisters;

void GpioSetPinFunction(uint32_t pin, enum GpioFunction function);

void GpioSetPinOutput(uint32_t pin);
void GpioClearPinOutput(uint32_t pin);

#endif
