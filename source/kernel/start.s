
.globl _start
_start:
    ldr x0, =0x00100000
    mov sp, x0
    bl main

hang:
    wfe
    b hang
