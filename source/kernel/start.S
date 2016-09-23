/* Sets PGIO 2 to high.
mov w0, 0x40
mov x1, 0x3f200000
str w0, [x1]
mov w0, 0x4
movz x1, 0x001c
movk x1, 0x3f20, lsl 16
str w0, [x1]
*/

#define bit(x) (1 << x)

#define localControl    0x40000000
#define localPrescaler  0x40000008
#define oscFreq         19200000

.global _start
_start:
    mov x0, localControl
    str wzr, [x0]
    
    mov w1, 0x80000000
    str w1, [x0, (localPrescaler - localControl)]
    
    ldr x0, =oscFreq
    msr cntfrq_el0, x0
    
    msr cntvoff_el2, xzr
    
    // 0x33ff sets all res1 bits.
    // Bit 10 => Clear to enable FPU and SIMD.
    // Bit 31 => Clear to enable access to CPACR_EL1 from EL1.
    mov x0, 0x33ff
    msr cptr_el3, x0
    
    // 0x30 sets all res1 bits.
    // Bit 0 => NS => 
    //mov x0, (0x30 | )  0x5b1 // scr
    mov x0, 0x5b1
    msr scr_el3, x0
    
    mov x0, 0x40 // smpen
    msr s3_1_c15_c2_1, x0
    
    ldr x0, =0x30c50830
    msr sctlr_el2, x0

    // Move from EL3 into EL1. The kernel will run at EL1.
    mov x0, 0x3c9 // spsr
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

    // Setup the exception handlers for EL1.
    mov x0, 0x200
    msr vbar_el1, x0

    // Jump to the kernel's main method.
    bl main
    
hang: 
    wfe
    b hang

.ltorg
