#include "HeapChecker.h"
#include <crtdbg.h>
#include <iostream>


HeapChecker::HeapChecker(const char* pFun, const char* pFile):m_pFunction{pFun}, m_pFile{pFile} {
}

HeapChecker::~HeapChecker()
{
	if(_CrtCheckMemory() == 0) {
		std::cout << "### HEAP CORRUPTION DETECTED ###" << std::endl;
		std::cout << "\tFunction->" << m_pFunction << std::endl ;
		std::cout << "\tFile->" << m_pFile << std::endl; 
	}
}
