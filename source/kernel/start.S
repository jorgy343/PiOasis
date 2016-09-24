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
    
    // Clear all bits in cptr_el3 to disable all trapping to EL3.
    msr cptr_el3, xzr

    // cptr_el3 is used here to prevent traps to EL3.
    mov x0, \
        0x33ff   /* res1 bits. */ |\
        bit0(10) /* TFP - Clear to not trap FP and SIMD instructions to EL2. */ |\
        bit0(20) /* TTA - Clear to not trap trace registers to EL2. */ |\
        bit0(31) /* TCPAC - Clear to not trap access to CPACR_EL1 and CPTR_EL2 to EL2. */
    msr cptr_el2, x0
    
    // Allow EL0 and EL1 to use FP and SIMD instructions.
    mov x0, \
        (0x3 << 20) /* FPEN - Set both bits to not trap FP and SIMD instructions to EL1. */ |\
        bit0(28)    /* TTA - Clear to not trap trace registers to EL1. */
    msr cpacr_el1, x0    

    // Setup a lot of traps conerning EL3. Note that the kernel at EL1 and the applications
    // at EL0 will run in secure state to allow access to all of the memory.
    mov x0, \
        0x30     /* res1 bits. */ |\
        bit0(0)  /* NS - Clear to put EL0 and EL1 into secure state. */ |\
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
    
    // Set some top level controls for both EL0 and EL1.
    ldr x0, = \
        0x30d00800 /* res1 bits. */ |\
        bit0(0)    /* M - Clear to disable address translation. This isn't needed right now. */ |\
        bit0(1)    /* A - Clear to disable alignment fault checking. This should probably be set. */ |\
        bit0(2)    /* C - Something about cachebility. It's default reset value is clear so just set it to that right now. */ |\
        bit0(3)    /* SA - Clear to disable stack alignment checking at EL1. This should probably be set. */ |\
        bit0(4)    /* SA0 - Clear to disable stack alignment checking at EL0. This should probably be set. */ |\
        bit0(5)    /* CP15BEN - Just clear it for now. */ |\
        bit1(7)    /* ITD - Consider it res1. */ |\
        bit1(8)    /* SED - Consider it res1. */ |\
        bit0(9)    /* UMA - Clear to prevent EL0 from modifying the DAIF flags. */ |\
        bit0(12)   /* I - Default is clear so clear it. */ |\
        bit0(14)   /* DZE - Clear to prevent EL0 from executing DC ZVA instructions. */ |\
        bit0(15)   /* UCT - Clear to prevent EL0 from accessing ctr_el0. */ |\
        bit0(16)   /* nTWI - Clear to prevent EL0 from using the wfi instruction. */ |\
        bit0(18)   /* nTWE - Clear to prevent EL0 from using the wfe instruction. */ |\
        bit0(19)   /* WXN - Has something to do with XN (Execute Never). Clearing doesn't change anything. */ |\
        bit0(24)   /* E0E - Clear for little-endian data access. */ |\
        bit0(25)   /* EE - Clear for little-endian translation table walks. */ |\
        bit0(26)   /* UCI - Clear to prevent EL0 from executing various cache maintenance instructions. */
    msr sctlr_el1, x0

    // Setup the exception handlers for EL1. Should this be done for all processors above?
    mov x0, 0x200
    msr vbar_el1, x0

    // Move from EL3 into EL1. The kernel will run at EL1.
    mov x0, 0x3c5 // spsr
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
    
    // Jump to the kernel's main method.
    bl main
    
hang: 
    wfe
    b hang

.ltorg
