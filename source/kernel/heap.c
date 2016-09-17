#include "heap.h"

HeapHeader* HeapBase = (HeapHeader*)0xa00000;

void* HeapAllocate(uint64_t size)
{
    if (size == 0)
        return NULL;
    
    size = align(size, 8);

    HeapHeader* header = HeapBase;
    while (header != NULL)
    {
        if (header->IsFree && header->Length >= size)
        {
            uintptr_t startOfData = (uintptr_t)header + sizeof(HeapHeader);
            uintptr_t endOfBlock = startOfData + header->Length;

            uintptr_t startOfNextHeader = startOfData + size;
            uintptr_t startOfNextData = startOfNextHeader + sizeof(HeapHeader);
            int64_t nextLength = endOfBlock - startOfNextData; // Fix logic so a signed integer doesn't have to be used here.

            header->IsFree = false;
            header->Length = size;
            
            if (nextLength > 0)
            {
                // x < header <> nextHeader > y
                HeapHeader* newHeader = (HeapHeader*)startOfNextHeader;
                
                newHeader->Length = nextLength;
                newHeader->IsFree = true;
                newHeader->Previous = header;
                newHeader->Next = header->Next;

                // x < header >       < nextHeader > y
                //          ^\         /^
                //            newHeader
                header->Next->Previous = newHeader;

                // x < header >         nextHeader > y
                //          ^\         //
                //            newHeader
                header->Next = newHeader;

                // x < header <> newHeader <> nextHeader > y
            }

            return (void*)startOfData;
        }

        header = header->Next;
    }
    
    return NULL;
}

void HeapFree(void* memory)
{
    
}
