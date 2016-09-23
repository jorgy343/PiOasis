#ifndef HANDLE_EXCEPTIONS_H
#define HANDLE_EXCEPTIONS_H

#include "standard.h"
#include "gpio.h"
#include "mini-uart.h"

void HandleException_CurrentElWithSp0_Synchronous(uint64_t spsr, uint64_t elr, uint64_t esr);
void HandleException_CurrentElWithSp0_Irq();
void HandleException_CurrentElWithSp0_Fiq();
void HandleException_CurrentElWithSp0_Error();

void HandleException_CurrentElWithSpx_Synchronous();
void HandleException_CurrentElWithSpx_Irq();
void HandleException_CurrentElWithSpx_Fiq();
void HandleException_CurrentElWithSpx_Error();

void HandleException_LowerElUsingAarch64_Synchronous();
void HandleException_LowerElUsingAarch64_Irq();
void HandleException_LowerElUsingAarch64_Fiq();
void HandleException_LowerElUsingAarch64_Error();

void HandleException_LowerElUsingAarch32_Synchronous();
void HandleException_LowerElUsingAarch32_Irq();
void HandleException_LowerElUsingAarch32_Fiq();
void HandleException_LowerElUsingAarch32_Error();

#endif
