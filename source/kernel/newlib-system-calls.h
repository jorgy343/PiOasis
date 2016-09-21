#ifndef NEWLIB_SYSTEM_CALLS_H
#define NEWLIB_SYSTEM_CALLS_H

#include <sys/stat.h>

#include "standard.h"
#include "mini-uart.h"

extern void* NewlibSystemCallsHeapPointer;

int _fstat(int file, struct stat* st);

int _open(const char* name, int flags, int mode);
int _close(int file);

int _lseek(int file, int ptr, int dir);
int _isatty(int file, int ptr, int dir);

int _read(int file, char* ptr, int len);
int _write(int file, char* ptr, int len);

void* _sbrk(int incr);

#endif
