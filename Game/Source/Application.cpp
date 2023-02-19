#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <crtdbg.h>

int main(int argc, char* argv[])
{
#if defined(DEBUG) || defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif


#if defined(DEBUG) || defined(_DEBUG)
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}