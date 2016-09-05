.global _start
_start:
    mov w0, 0x40
    mov x1, 0x3f200000
    str w0, [x1]
    
    mov w0, 0x4
    
    movz x1, 0x001c
    movk x1, 0x3f20, LSL 16
    
    movz x2, 0x0028
    movk x2, 0x3f20, LSL 16
    
loop:
    str w0, [x1]
    
    mov x3, 0x200000
subloop1:
    subs x3, x3, 1
    bne subloop1
    
    str w0, [x2]
    
    mov x3, 0x200000
subloop2:
    subs x3, x3, 1
    bne subloop2
    
    b loop
    
hang:
    b hang
