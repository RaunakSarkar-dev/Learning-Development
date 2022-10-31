#pragma once
class HeapChecker
{
	const char *m_pFunction ;
	const char *m_pFile ;
public:
	HeapChecker(const char *pFun, const char *pFile);
	~HeapChecker();
};
#ifdef _DEBUG
#define HEAPCHECK HeapChecker instance{__FUNCSIG__, __FILE__} ;
#else
#define HEAPCHECK
#endif
