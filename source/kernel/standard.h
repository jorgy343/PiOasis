#ifndef STANDARD_H
#define STANDARD_H

// Standard includes used throughout the kernel code.
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// Useful macros.
#define bit(x) (1 << (x))
#define align(x, y) ((x + y - 1) & ~(y - 1)) // Advances x to the next y boundary if necessary.

#define BitRangeMask64(start, end) (((uint64_t)-1 >> (63 - end)) & ~(((uint64_t)1 << start) - (uint64_t)1))
#define BitRangeMask32(start, end) (((uint32_t)-1 >> (31 - end)) & ~(((uint32_t)1 << start) - (uint32_t)1))
#define BitRangeMask16(start, end) (((uint16_t)-1 >> (15 - end)) & ~(((uint16_t)1 << start) - (uint16_t)1))
#define BitRangeMask8(start, end) (((uint8_t)-1 >> (7 - end)) & ~(((uint8_t)1 << start) - (uint8_t)1))

#define SetBits64(x, y, start, end) ((x & ~BitRangeMask64(start, end)) | ((uint64_t)y << start))

#define ReadRegister(reg, x) asm("mov %[_x], "#reg : [_x] "=r" (x))
#define ReadSystemRegister(reg, x) asm("mrs %[_x], "#reg : [_x] "=r" (x))

#define WriteRegister(reg, x) asm("mov "#reg", %[_x]" : [_x] "=r" (x))
#define WriteSystemRegister(reg, x) asm("msr "#reg", %[_x]\n\t" "isb" : [_x] "=r" (x))

#endif
