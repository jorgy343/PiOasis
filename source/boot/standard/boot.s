.globl _start
_start:
    
    mov x0, 0x40000000
    str wzr, [x0]
    mov w1, 0x80000000
    str w1, [x0, 0x8]
    
    ldr x0, =19200000
    msr cntfrq_el0, x0
    
    msr cntvoff_el2, xzr
    
    //mov x0, 0x33ff
    //msr cptr_el3, x0
    
    b 0x80000
    
    mov x0, 0x5b1
    msr scr_el3, x0
    
    mov x0, 0x40
    msr s3_1_c15_c2_1, x0
    
    ldr x0, =0x30c50830
    msr sctlr_el2, x0
    
    mov x0, 0x3c9
    msr spsr_el3, x0
    adr x0, el2
    msr elr_el3, x0
    eret
    
el2:
    mrs x6, mpidr_el1
    and x6, x6, 0x3
    cbz x6, primary_cpu
    
secondary_cpus:
    wfe
    b secondary_cpus
    
primary_cpu:
    b 0x80000
    
    /*
    // Setup the timer here.
    
    // Enable the FPU and SIMD.
    mov x0, 0x33ff
    msr cptr_el3, x0
    
    // Setup the SCR register.
    mov x0, 0x4b1
    msr SCR_EL3, x0
    
    // Setup the SCTLR_EL2 register.
    movz x0, 0x183f
    movk x0, 0x30cd, LSL 16
    msr SCTLR_EL2, x0
    
    // Change exception level to EL2.
    mov x0, 0x3c9
    msr SPSR_EL3, x0
    
    adr x0, el2
    msr ELR_EL3, x0
    
el2:
    mrs x0, mpidr_el1
    and x0, x0, 0x3
    cbz x0, primary_cpu
    
secondary_cpus:
    wfe // Sleep the secondary CPUs forever.
    b secondary_cpus
    
primary_cpu:
    b 0x80000
    */
hang:
    b hang
