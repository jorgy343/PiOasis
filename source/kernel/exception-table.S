.org 0x0
.global ExceptionTableStart
ExceptionTableStart:

// Current EL with SP0
.org 0x0
Exception_CurrentElWithSp0_Synchronous:
    bl HandleException_CurrentElWithSp0_Synchronous

.org 0x80
Exception_CurrentElWithSp0_Irq:
    bl HandleException_CurrentElWithSp0_Irq

.org 0x100
Exception_CurrentElWithSp0_Fiq:
    bl HandleException_CurrentElWithSp0_Fiq

.org 0x180
Exception_CurrentElWithSp0_Error:
    bl HandleException_CurrentElWithSp0_Error

// Current EL with SPx
.org 0x200
Exception_CurrentElWithSpx_Synchronous:
    bl HandleException_CurrentElWithSpx_Synchronous

.org 0x280
Exception_CurrentElWithSpx_Irq:
    bl HandleException_CurrentElWithSpx_Irq

.org 0x300
Exception_CurrentElWithSpx_Fiq:
    bl HandleException_CurrentElWithSpx_Fiq

.org 0x380
Exception_CurrentElWithSpx_Error:
    bl HandleException_CurrentElWithSpx_Error

// Lower EL using AArch64
.org 0x400
Exception_LowerElUsingAarch64_Synchronous:
    bl HandleException_LowerElUsingAarch64_Synchronous

.org 0x480
Exception_LowerElUsingAarch64_Irq:
    bl HandleException_LowerElUsingAarch64_Irq

.org 0x500
Exception_LowerElUsingAarch64_Fiq:
    bl HandleException_LowerElUsingAarch64_Fiq

.org 0x580
Exception_LowerElUsingAarch64_Error:
    bl HandleException_LowerElUsingAarch64_Error

// Lower EL using AArch32
.org 0x600
Exception_LowerElUsingAarch32_Synchronous:
    bl HandleException_LowerElUsingAarch32_Synchronous

.org 0x680
Exception_LowerElUsingAarch32_Irq:
    bl HandleException_LowerElUsingAarch32_Irq

.org 0x700
Exception_LowerElUsingAarch32_Fiq:
    bl HandleException_LowerElUsingAarch32_Fiq

.org 0x780
Exception_LowerElUsingAarch32_Error:
    bl HandleException_LowerElUsingAarch32_Error

.org 0x800
.ltorg
