#include "standard.h"
#include "mini-uart.h"
#include "gpio.h"

void main()
{
    GpioSetPinFunction(GpioPin2, GpioFunctionOutput);
    GpioSetPinOutput(GpioPin2);
    
    MiniUartWriteString("Mini uart initialized\r\n");

    uint64_t tcr;
    ReadSystemRegister(tcr_el1, tcr);

    // Pi3 supports a maximum of 1TiB of memory. The T0SZ value is
    // then 64 - 40 = 24. This means that TTBR0 will point to a
    // level two table instead of a level one.
    tcr = SetBits64(tcr, 24, 0, 5);

    // 64KiB granule size for TTBR0.
    tcr = SetBits64(tcr, 1, 14, 15);

    // IPA is 40 bits in width (1TiB).
    tcr = SetBits64(tcr, 2, 32, 34);

    // 1TiB address size limit for TTBR1 (same as TTBR0).
    tcr = SetBits64(tcr, 24, 16, 21);

    // 64KiB granule lsize for TTBR1.
    tcr = SetBits64(tcr, 1, 30, 31);

    MiniUartWriteHex64(tcr);
    MiniUartWriteString("\r\n");

    WriteSystemRegister(tcr_el1, tcr);

    // Setup the level 2 table.
    volatile uint64_t* block0 = (uint64_t*)0x500000;
    volatile uint64_t* block1 = block0 + 1;
    volatile uint64_t* block2 = block0 + 2;
    volatile uint64_t* block3 = block0 + 3;

    *block0 = 0x00000000;
    *block1 = 0x20000000;
    *block2 = 0x40000000;
    *block3 = 0x60000000;

    *block0 |= 0x1;
    *block1 |= 0x1;
    *block2 |= 0x1;
    *block3 |= 0x1;

    uint64_t ttbr0 = (uint64_t)block0;
    WriteSystemRegister(ttbr0_el1, ttbr0); // 80MiB mark.
    
    // Enable the MMU.
    uint64_t sctlr;
    ReadSystemRegister(sctlr_el1, sctlr);
    
    sctlr |= 0x1;
    WriteSystemRegister(sctlr_el1, sctlr);

    MiniUartWriteString("Virtual memory initialized\r\n");
    while (true);
}
