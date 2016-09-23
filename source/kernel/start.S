#define bit(x) (1 << x)
#define bit1(x) (1 << x)
#define bit0(x) (0 << x)

#define localControl    0x40000000
#define localPrescaler  0x40000008
#define oscFreq         19200000

.macro SetGpio2
    mov w0, 0x40
    mov x1, 0x3f200000
    str w0, [x1]
    mov w0, 0x4
    movz x1, 0x001c
    movk x1, 0x3f20, lsl 16
    str w0, [x1]
.endm

.global _start
_start:
    mov x0, localControl
    str wzr, [x0]
    
    mov w1, 0x80000000
    str w1, [x0, (localPrescaler - localControl)]
    
    ldr x0, =oscFreq
    msr cntfrq_el0, x0
    
    // Not sure why this is needed yet. It is the virtual timer offset.
    msr cntvoff_el2, xzr
    
    // cptr_el3 is used here to prevent traps to EL3.
    mov x0, \
        0x33ff   /* res1 bits. */ |\
        bit0(10) /* TFP - Clear to not trap FP and SIMD instructions. */ |\
        bit0(31) /* TCPAC - Clear to not trap access to CPACR_EL1 and CPTR_EL2. */
    msr cptr_el3, x0
    msr cptr_el2, x0

    mov x0, (3 << 20)
    msr cpacr_el1, x0
    
    // Setup a lot of traps conerning EL3.
    mov x0, \
        0x30     /* res1 bits. */ |\
        bit1(0)  /* NS - Set to put EL0 and EL1 into non-secure state. */ |\
        bit0(1)  /* IRQ - Clear to allow IRQ exceptions to be taken at exception levels other than EL3. */ |\
        bit0(2)  /* FIQ - Clear to allow FIQ exceptions to be taken at exception levels other than EL3. */ |\
        bit0(3)  /* EA - Clear to allow External Abort and SError exceptions to be taken at exception levels other than EL3. */ |\
        bit1(7)  /* SMD - Set to disable the smc instruction (allows an exception to call into EL3. This will not be needed. */ |\
        bit0(8)  /* HCE - Clear to disable the hvc instruction (allows an exception to call into EL2. This will not be needed. */ |\
        bit0(9)  /* SIF - Clear to secure state instruction fetches from non-secure memory. This doesn't really matter. */ |\
        bit1(10) /* RW - Set to force next lower exception level (EL2) to use 64-bit registers. Bassically this puts EL2 into aarch64. */ |\
        bit0(11) /* ST - Clear to only allow el3 access to the cntps_tval_el1, cnts_ctl_el1, and cntps_cval_el1 registers. Default is cleared. This doesn't matter. */ |\
        bit0(12) /* TWI - clear to not trap the wfi instruction. */ |\
        bit0(13) /* TWE - Clear to not trap the wfe instruction. */
    msr scr_el3, x0

    // The cpuectrl_el1 register aka s3_1_c15_c2_1.
    mov x0, \
        bit(6) /* SMPEN - Set to enable hardware management of data coherency between the CPU cores. This is a prerequisite for enabling the CPU cache. */
    msr s3_1_c15_c2_1, x0
    
    // This just sets all of the res1 bits. I'm not convinced this is needed
    // especially since EL2 will not be used.
    ldr x0, =0x30c50830
    msr sctlr_el2, x0

    // Move from EL3 into EL1. The kernel will run at EL1.
    mov x0, 0x3cd // spsr
    msr spsr_el3, x0
    adr x0, el1
    msr elr_el3, x0
    eret
    
el1:
    mrs x0, mpidr_el1
    and x0, x0, 0x3
    cbz x0, primaryCpu
    
secondaryCpus:
    wfe
    b secondaryCpus
    
primaryCpu:
    // Setup the stack.
    .global _stackStart
    ldr x0, =_stackStart
    mov sp, x0

    // Setup the exception handlers for EL1. Should this be done for all processors above?
    mov x0, 0x200
    msr vbar_el1, x0

    // Jump to the kernel's main method.
    bl main
    
hang: 
    wfe
    b hang

.ltorg
