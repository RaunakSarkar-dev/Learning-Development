#ifndef _PTLD_C_H
#define _PTLD_C_H

#ifdef __cplusplus
// Needed for those functions that are used in both C and Cpp. Cpp name mangles all functions and hence C wont be able to understand the mangled names
// Extern "C" helps to avoid the name mangling of these functions and make it recognizable by C as well as Cpp
extern "C" 
{
#endif
   void* ptmalloc(size_t size, const char* func, const char* file, int lineNo);
   void ptfree(void* p);
#ifdef __cplusplus
}
#endif
#endif // !_PTLD_C_H

