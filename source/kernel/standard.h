#ifndef STANDARD_H
#define STANDARD_H

// Standard includes used throughout the kernel code.
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <stdlib.h>

#define bit(x) (1 << (x))
#define align(x, y) ((x + y - 1) & ~(y - 1))

#endif
