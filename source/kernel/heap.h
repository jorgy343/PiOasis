#ifndef HEAP_H
#define HEAP_H

#include "standard.h"

typedef struct HeapHeader HeapHeader;

struct HeapHeader
{
    uint64_t Length;
    bool IsFree;
    HeapHeader* Previous;
    HeapHeader* Next;
};

extern HeapHeader* HeapBase;

void* HeapAllocate(uint64_t size);
void HeapFree(void* memory);

#endif
