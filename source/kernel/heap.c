#include "heap.h"

HeapHeader* HeapBase = (HeapHeader*)0xa00000;

void* HeapAllocate(uint64_t requestedSize)
{
    if (requestedSize == 0)
        return NULL;
    
    // Always return a size that is aligned on an 8 byte boundary. This will
    // prevent unaligned memory access exceptions from occuring.
    requestedSize = align(requestedSize, 8);

    HeapHeader* header = HeapBase;
    while (header != NULL)
    {
        if (header->IsFree && header->Length >= requestedSize)
        {
            uintptr_t startOfData = (uintptr_t)header + sizeof(HeapHeader);
            uintptr_t endOfBlock = startOfData + header->Length;

            uintptr_t startOfNextHeader = startOfData + requestedSize;
            uintptr_t startOfNextData = startOfNextHeader + sizeof(HeapHeader);
            int64_t nextLength = endOfBlock - startOfNextData; // Fix logic so a signed integer doesn't have to be used here?

            header->IsFree = false;
            header->Length = requestedSize;
            
            // We can only split the block if a theoretical block can store at least 8 bytes.
            if (nextLength >= 8)
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
            else
            {
                // Request more heap space.
            }

            return (void*)startOfData;
        }

        header = header->Next;
    }
    
    return NULL;
}

void HeapFree(void* memory)
{
    // The parameter specifies the start of the data which is right after the header. Subtract
    // the size of the header from the pointer to get a pointer to the start of the header.
    memory = (void*)((uintptr_t)memory - sizeof(HeapHeader));
    HeapHeader* header = (HeapHeader*)memory;
    
    if (header->Previous != NULL && header->Previous->IsFree
        && header->Next != NULL && header->Next->IsFree)
    {
        // x < previous <> header <> next > y
        // 
        // Previous and next are guaranteed to exist due to the if statement above.
        HeapHeader* previous = header->Previous;
        HeapHeader* next = header->Next;
        HeapHeader* y = next->Next;
        
        // Merge both header and next into previous.
        previous->Length += sizeof(HeapHeader) + header->Length;
        previous->Length += sizeof(HeapHeader) + next->Length;
        
        if (y != NULL) // Connect previous to y only if y exists
        {
            previous->Next = y;
            y->Previous = previous;
        }
        else // Otherwise, y doesn't exist and both header and next are eliminated so previous points to nothing.
        {
            previous->Next = NULL;
        }
    }
    else if (header->Previous != NULL && header->Previous->IsFree)
    {
        // x < previous <> header <> next > y
        //
        // Previous is guaranteed to exist due to the if statement above.
        HeapHeader* previous = header->Previous;
        HeapHeader* next = header->Next;

        // Merge header into header's previous.
        previous->Length += sizeof(HeapHeader) + header->Length;
        
        if (next != NULL) // Connect previous to next only if next exists.
        {
            previous->Next = next;
            next->Previous = previous;
        }
        else // Otherwise, next doesn't exist and header is eliminated so previous points to nothing.
        {
            previous->Next = NULL;
        }
    }
    else if (header->Next != NULL && header->Next->IsFree)
    {
        // x < previous <> header <> next > y
        // 
        // Next is quaranteed to exist due to the if statement above.
        HeapHeader* y = header->Next->Next;
        
        // Merge next into header.
        header->Length += sizeof(HeapHeader) + header->Next->Length;
        
        if (y != NULL) // Connect header to y only if y exists.
        {
            header->Next = y;
            y->Previous = header;
        }
        else // Otherwise, y doesn't exist and next is eliminated so header's next points to nothing.
        {
            header->Next = NULL;
        }
    }
    else
    {
        // No merging, just mark as free.
        header->IsFree = true;
    }
}
