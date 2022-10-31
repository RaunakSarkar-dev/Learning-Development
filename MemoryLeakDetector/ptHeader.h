#ifndef _PT_HEADER_H // Platform independentant
#define _PT_HEADER_H

struct MemoryBlockHeader
{
   const char* mFunction;
   const char* mFile;
   int m_LineNumber;
   size_t m_size;
   struct MemoryBlockHeader* m_Prev;
   struct MemoryBlockHeader* m_Next;
};

#endif
