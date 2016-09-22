#include "newlib-system-calls.h"

void* NewlibSystemCallsHeapPointer = (void*)0x500000; // 5MiB mark.

int _fstat(int file, struct stat* st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

int _open(const char* name, int flags, int mode)
{
    return -1;
}

int _close(int file)
{
    return -1;
}

int _lseek(int file, int ptr, int dir)
{
    return 0;
}

int _isatty(int file, int ptr, int dir)
{
    return 1;
}

int _read(int file, char* ptr, int len)
{
    return len;
}

int _write(int file, char* ptr, int len)
{
    for (int i = 0; i < len; ++i)
        MiniUartWriteChar(ptr[i]);

    return len;
}

void* _sbrk(int incr)
{
    void* heapPointer = NewlibSystemCallsHeapPointer;
    NewlibSystemCallsHeapPointer = (void*)((uintptr_t)heapPointer + incr);
    
    return heapPointer;
}
