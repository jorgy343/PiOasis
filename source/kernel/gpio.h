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

enum GpioPinLevel
{
    GpioPinLow,
    GpioPinHigh
};

enum GpioPin
{
    GpioPin0,
    GpioPin1,
    GpioPin2,
    GpioPin3,
    GpioPin4,
    GpioPin5,
    GpioPin6,
    GpioPin7,
    GpioPin8,
    GpioPin9,
    GpioPin10,
    GpioPin11,
    GpioPin12,
    GpioPin13,
    GpioPin14,
    GpioPin15,
    GpioPin16,
    GpioPin17,
    GpioPin18,
    GpioPin19,
    GpioPin20,
    GpioPin21,
    GpioPin22,
    GpioPin23,
    GpioPin24,
    GpioPin25,
    GpioPin26,
    GpioPin27,
    GpioPin28,
    GpioPin29,
    GpioPin30,
    GpioPin31,
    GpioPin32,
    GpioPin33,
    GpioPin34,
    GpioPin35,
    GpioPin36,
    GpioPin37,
    GpioPin38,
    GpioPin39,
    GpioPin40,
    GpioPin41,
    GpioPin42,
    GpioPin43,
    GpioPin44,
    GpioPin45,
    GpioPin46,
    GpioPin47,
    GpioPin48,
    GpioPin49,
    GpioPin50,
    GpioPin51,
    GpioPin52,
    GpioPin53
};

extern struct GpioRegisterView* GpioRegisters;

enum GpioFunction GpioGetPinFunction(enum GpioPin pin);
void GpioSetPinFunction(enum GpioPin pin, enum GpioFunction function);

void GpioSetPinOutput(enum GpioPin pin);
void GpioClearPinOutput(enum GpioPin pin);

enum GpioPinLevel GpioGetPinLevel(enum GpioPin pin);

#endif
