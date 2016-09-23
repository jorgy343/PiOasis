.org 0x0
.global ExceptionTableStart
ExceptionTableStart:

// Current EL with SP0
.org 0x0
Exception_CurrentElWithSp0_Synchronous:
    // Store x0, x1, and x2 on stack?

    mrs x0, spsr_el1
    mrs x1, elr_el1
    mrs x2, esr_el1

    bl HandleException_CurrentElWithSp0_Synchronous

    // Restore x0, x1, and x2 on stack?
    eret

.org 0x80
Exception_CurrentElWithSp0_Irq:
    bl HandleException_CurrentElWithSp0_Irq
    eret

.org 0x100
Exception_CurrentElWithSp0_Fiq:
    bl HandleException_CurrentElWithSp0_Fiq
    eret

.org 0x180
Exception_CurrentElWithSp0_Error:
    bl HandleException_CurrentElWithSp0_Error
    eret

// Current EL with SPx
.org 0x200
Exception_CurrentElWithSpx_Synchronous:
    bl HandleException_CurrentElWithSpx_Synchronous
    eret

.org 0x280
Exception_CurrentElWithSpx_Irq:
    bl HandleException_CurrentElWithSpx_Irq
    eret

.org 0x300
Exception_CurrentElWithSpx_Fiq:
    bl HandleException_CurrentElWithSpx_Fiq
    eret

.org 0x380
Exception_CurrentElWithSpx_Error:
    bl HandleException_CurrentElWithSpx_Error
    eret

// Lower EL using AArch64
.org 0x400
Exception_LowerElUsingAarch64_Synchronous:
    bl HandleException_LowerElUsingAarch64_Synchronous
    eret

.org 0x480
Exception_LowerElUsingAarch64_Irq:
    bl HandleException_LowerElUsingAarch64_Irq
    eret

.org 0x500
Exception_LowerElUsingAarch64_Fiq:
    bl HandleException_LowerElUsingAarch64_Fiq
    eret

.org 0x580
Exception_LowerElUsingAarch64_Error:
    bl HandleException_LowerElUsingAarch64_Error
    eret

// Lower EL using AArch32
.org 0x600
Exception_LowerElUsingAarch32_Synchronous:
    bl HandleException_LowerElUsingAarch32_Synchronous
    eret

.org 0x680
Exception_LowerElUsingAarch32_Irq:
    bl HandleException_LowerElUsingAarch32_Irq
    eret

.org 0x700
Exception_LowerElUsingAarch32_Fiq:
    bl HandleException_LowerElUsingAarch32_Fiq
    eret

.org 0x780
Exception_LowerElUsingAarch32_Error:
    bl HandleException_LowerElUsingAarch32_Error
    eret

.org 0x800
.ltorg
