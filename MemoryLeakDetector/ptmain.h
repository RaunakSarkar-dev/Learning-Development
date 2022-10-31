#ifndef _PTMAIN_H
#define _PTMAIN_H
#include <stddef.h>
#ifdef __cplusplus
extern "C"
{
#endif
   void ptDumpLeaks();
   #define malloc(size) ptmalloc(size, __FUNCSIG__, __FILE__, __LINE__)
   #define free ptfree;
   void* operator new(size_t size, const char* func, const char* file, int lineNo);
   void* operator new[](size_t size, const char* func, const char* file, int lineNo);
   void operator delete(void* p);
   void operator delete[](void* p);
#ifdef __cplusplus
}
#endif
#endif
