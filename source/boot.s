.global _start
_start:
    mov w0, 0x40            /* GPIO2 output function. */
    mov x1, 0x3f200000      /* Address of GPIO function select register 0. */
    str w0, [x1]
    
    mov w0, 0x4             /* GPIO2 bit position (1 << 2). */
    
    movz x1, 0x001c         /* Low word of the GPIO set register 0 address. */
    movk x1, 0x3f20, LSL 16 /* High word of the GPIO set register 0 address. */
    
    movz x2, 0x0028         /* Low word of the GPIO clear register 0 address. */
    movk x2, 0x3f20, LSL 16 /* High word of the GPIO clear register 0 address. */
    
loop:
    str w0, [x1]            /* Set GPIO2 to high. */
    
    /* "Stall" for many cycles. */
    mov x3, 0x200000
subloop1:
    subs x3, x3, 1
    bne subloop1
    
    str w0, [x2]            /* Set GPIO2 to low. */
    
    /* "Stall" for many cycles again. */
    mov x3, 0x200000
subloop2:
    subs x3, x3, 1
    bne subloop2
    
    b loop                  /* Infinite loop. */
    
hang:
    b hang                  /* Not actually used, but good practice to include. */
