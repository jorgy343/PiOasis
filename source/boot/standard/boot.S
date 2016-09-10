#define bit(x) (1 << x)

#define localControl		0x40000000
#define localPrescaler		0x40000008
#define oscFreq			19200000

.globl _start
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
    
    mov x0, 0x3c9 // spsr
    msr spsr_el3, x0
    adr x0, el2
    msr elr_el3, x0
    eret
    
el2:
    mrs x0, mpidr_el1
    and x0, x0, 0x3
    cbz x0, primaryCpu
    
secondaryCpus:
    wfe
    b secondaryCpus
    
primaryCpu:
    ldr w0, kernelEntry32
    br x0
    
hang: 
    wfe
    b hang

.ltorg

.org 0xf0
.globl magicValue
magicValue:
    .word 0x5afe570b

.org 0xf4
.globl stubVersion
stubVersion:
    .word 0

.org 0xf8
.globl dtbPointer32
dtbPointer32:
    .word 0x0

.org 0xfc
.globl kernelEntry32
kernelEntry32:
    .word 0x0

.org 0x100
.globl dtbSpace
dtbSpace:
