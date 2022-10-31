#include <malloc.h>
#include <stdio.h>
#include "ptHeader.h"
#include "ptld_c.h"

#define MEMBLOCK struct MemoryBlockHeader*

MEMBLOCK pHead = NULL;

int pIsValidBlock(MEMBLOCK currBlock)
{
   for (MEMBLOCK p = pHead; p != NULL; p = p->m_Next)
   {
      if (currBlock == p)
         return 1;
   }
   return 0;
}

void ptDumpBlock(MEMBLOCK p)
{
   printf("\n Bytes Leaked <%zu>\n", p->m_size);
   printf("\n Address <0x%p>\n", p+1);
   printf("\n Line # <%d>\n", p->m_LineNumber);
   printf("\n Function <%s>\n", p->mFunction);
   printf("\n File <%s>\n", p->mFile);
}


void* ptmalloc(size_t size, const char* func, const char* file, int lineNo)
{
   void* allocated_mem = malloc(sizeof(struct MemoryBlockHeader) + size);
   if (!allocated_mem)
   {
      return NULL;
   }
   MEMBLOCK currBlock = (MEMBLOCK)allocated_mem;
   currBlock->m_size = size;
   currBlock->mFile = file;
   currBlock->mFunction = func;
   currBlock->m_LineNumber = lineNo;
   currBlock->m_Prev = NULL;
   currBlock->m_Next = NULL;
   if (pHead == NULL)
   {
      pHead = currBlock;
   }
   else // Always enter at the begining of the list
   {
      currBlock->m_Next = pHead;
      pHead->m_Prev = currBlock;
      pHead = currBlock;
   }
   return currBlock + 1; // since user_mem is just after allocated mem 
}

void ptfree(void* p)
{
   if (p == NULL)
      return;
   MEMBLOCK currBlock = (MEMBLOCK)p;
   currBlock -= 1;
   if (pIsValidBlock(currBlock))
   {
      //remove from list and remove memory
      if (pHead == currBlock) // first node 
      {
         pHead = currBlock->m_Next;
         currBlock->m_Prev = NULL;
      }
      else if (currBlock->m_Prev != NULL && currBlock->m_Next == NULL) // last node
      {
         currBlock->m_Prev = NULL;
      }
      else // in the middle
      {
         currBlock->m_Prev = currBlock->m_Next;
         currBlock->m_Next->m_Prev = currBlock->m_Prev;
      }
      free(currBlock);
   }
}

void ptDumpLeaks()
{
   if (pHead == NULL)
   {
      printf("No leaks detected!!");
   }
   else
   {
      printf("====================\n");
      printf("      LEAKS         \n");
      printf("====================\n");
      for (MEMBLOCK p = pHead; p != NULL; p = p->m_Next)
      {
         ptDumpBlock(p);
      }
   }
}
