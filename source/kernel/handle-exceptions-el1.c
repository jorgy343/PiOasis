#include "handle-exceptions-el1.h"

// Current EL with SP0
void HandleException_CurrentElWithSp0_Synchronous()
{
    uint64_t spsr;
    uint64_t elr;
    uint64_t esr;

    asm("mrs %[_spsr], spsr_el1" : [_spsr] "=r" (spsr));
    asm("mrs %[_elr], elr_el1" : [_elr] "=r" (elr));
    asm("mrs %[_esr], esr_el1" : [_esr] "=r" (esr));

    MiniUartWriteString("Current EL with SP0 - Synchronous\r\n");
    MiniUartWriteString("spsr = 0x");
    MiniUartWriteHex64(spsr);
    MiniUartWriteString("\r\nelr = 0x");
    MiniUartWriteHex64(elr);
    MiniUartWriteString("\r\nesr = 0x");
    MiniUartWriteHex64(esr);
    MiniUartWriteString("\r\n");

    while (true);
}

void HandleException_CurrentElWithSp0_Irq()
{
    MiniUartWriteString("Current EL with SP0 - IRQ\r\n");
}

void HandleException_CurrentElWithSp0_Fiq()
{
    MiniUartWriteString("Current EL with SP0 - FIQ\r\n");
}

void HandleException_CurrentElWithSp0_Error()
{
    MiniUartWriteString("Current EL with SP0 - Error\r\n");
}

// Current EL with SPx
void HandleException_CurrentElWithSpx_Synchronous()
{
    MiniUartWriteString("Current EL with SPx - Synchronous\r\n");
}

void HandleException_CurrentElWithSpx_Irq()
{
    MiniUartWriteString("Current EL with SPx - IRQ\r\n");
}

void HandleException_CurrentElWithSpx_Fiq()
{
    MiniUartWriteString("Current EL with SPx - FIQ\r\n");
}

void HandleException_CurrentElWithSpx_Error()
{
    MiniUartWriteString("Current EL with SPx - Error\r\n");
}

// Lower EL using AAarch64
void HandleException_LowerElUsingAarch64_Synchronous()
{
    MiniUartWriteString("Lower EL using AArch64 - Synchronous\r\n");
}

void HandleException_LowerElUsingAarch64_Irq()
{
    MiniUartWriteString("Lower EL using AArch64 - IRQ\r\n");
}

void HandleException_LowerElUsingAarch64_Fiq()
{
    MiniUartWriteString("Lower EL using AArch64 - FIQ\r\n");
}

void HandleException_LowerElUsingAarch64_Error()
{
    MiniUartWriteString("Lower EL using AArch64 - Error\r\n");
}

// Lower EL using AArch32
void HandleException_LowerElUsingAarch32_Synchronous()
{
    MiniUartWriteString("Lower EL using AArch32 - Synchronous\r\n");
}

void HandleException_LowerElUsingAarch32_Irq()
{
    MiniUartWriteString("Lower EL using AArch32 - IRQ\r\n");
}

void HandleException_LowerElUsingAarch32_Fiq()
{
    MiniUartWriteString("Lower EL using AArch32 - FIQ\r\n");
}

void HandleException_LowerElUsingAarch32_Error()
{
    MiniUartWriteString("Lower EL using AArch32 - Error\r\n");
}
