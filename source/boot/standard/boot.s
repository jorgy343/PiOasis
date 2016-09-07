.global _start
_start:
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
    
primary_cpu:
    b 0x8000
    
hang:
    b hang
