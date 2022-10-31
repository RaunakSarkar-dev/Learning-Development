#include "ptmain.h"

int main()
{
   int* p = malloc(sizeof(int));
   free(p);
   ptDumpLeaks();
}
