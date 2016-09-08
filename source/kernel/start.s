_start:
    movz x6, 0x0
    movk x6, 0x1000, LSL 16
    mov sp, x6
    b main

hang:
    wfe
    b hang
