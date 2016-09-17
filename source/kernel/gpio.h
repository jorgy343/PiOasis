#ifndef GPIO_H
#define GPIO_H

#include "standard.h"

#define GpioRegisterViewBase 0x3f200000

typedef struct
{
    volatile uint32_t FunctionSelect0;
    volatile uint32_t FunctionSelect1;
    volatile uint32_t FunctionSelect2;
    volatile uint32_t FunctionSelect3;
    volatile uint32_t FunctionSelect4;
    volatile uint32_t FunctionSelect5;
    volatile uint32_t Reserved0;

    volatile uint32_t PinOutputSet0;
    volatile uint32_t PinOutputSet1;
    volatile uint32_t Reserved1;

    volatile uint32_t PinOutputClear0;
    volatile uint32_t PinOutputClear1;
    volatile uint32_t Reserved2;

    volatile uint32_t PinLevel0;
    volatile uint32_t PinLevel1;
    volatile uint32_t Reserved3;

    volatile uint32_t PinEventDetectStatus0;
    volatile uint32_t PinEventDetectStatus1;
    volatile uint32_t Reserved4;

    volatile uint32_t PinRisingEdgeDetectEnable0;
    volatile uint32_t PinRisingEdgeDetectEnable1;
    volatile uint32_t Reserved5;

    volatile uint32_t PinFallingEdgeDetectEnable0;
    volatile uint32_t PinFallingEdgeDetectEnable1;
    volatile uint32_t Reserved6;

    volatile uint32_t PinHighDetectEnable0;
    volatile uint32_t PinHighDetectEnable1;
    volatile uint32_t Reserved7;

    volatile uint32_t PinLowDetectEnable0;
    volatile uint32_t PinLowDetectEnable1;
    volatile uint32_t Reserved8;

    volatile uint32_t PinAsyncRisingEdgeDetect0;
    volatile uint32_t PinAsyncRisingEdgeDetect1;
    volatile uint32_t Reserved9;

    volatile uint32_t PinAsyncFallingEdgeDetect0;
    volatile uint32_t PinAsyncFallingEdgeDetect1;
    volatile uint32_t Reserved10;

    volatile uint32_t PinPullUpDownEnable;
    volatile uint32_t PinPullUpDownEnableClock0;
    volatile uint32_t PinPullUpDownEnableClock1;
    volatile uint32_t reserved11;

    volatile uint32_t Test;
} GpioRegisterView;

typedef enum
{
    GpioFunctionInput,
    GpioFunctionOutput,
    GpioFunctionAlternate5,
    GpioFunctionAlternate4,
    GpioFunctionAlternate0,
    GpioFunctionAlternate1,
    GpioFunctionAlternate2,
    GpioFunctionAlternate3
} GpioFunction;

typedef enum
{
    GpioPinLow,
    GpioPinHigh
} GpioPinLevel;

typedef enum
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
} GpioPin;

extern GpioRegisterView* GpioRegisters;

GpioFunction GpioGetPinFunction(GpioPin pin);
void GpioSetPinFunction(GpioPin pin, GpioFunction function);

GpioPinLevel GpioGetPinLevel(GpioPin pin);

void GpioSetPinOutput(GpioPin pin);
void GpioClearPinOutput(GpioPin pin);

#endif
