#include <stdint.h>

void main()
{
    uint32_t* gpioSelect0 = 0x3f200000;
    uint32_t* gpioSet0 = 0x3f20001c;
    uint32_t* gpioClear0 = 0x3f200028;

    *gpioSelect0 = 0x40;
    *gpioSet0 = 0x4;

    for (;;);
}
