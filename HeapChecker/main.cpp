
#include <cstring>
#include "HeapChecker.h"

int main() {
	HEAPCHECK
	char *p = new char[5] ;
	strcpy(p, "Hello") ;

	 
}
