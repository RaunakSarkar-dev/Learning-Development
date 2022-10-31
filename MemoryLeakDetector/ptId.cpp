#include "ptmain.h"

void* operator new(size_t size, const char* func, const char* file, int lineNo)
{
   return ptmalloc(size, func, file, lineNo);
}

void* operator new[](size_t size, const char* func, const char* file, int lineNo)
{
   return ptmalloc(size, func, file, lineNo);
}

void operator delete(void* p)
{
   ptfree(p);
}

void operator delete[](void* p)
{
   ptfree(p);
}
