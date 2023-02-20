#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <crtdbg.h>

#include "ErrorHandler.h"
#include "WindowEventHandler.h"


int main(int argc, char* argv[])
{
#if defined(DEBUG) || defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	__try
	{

	}
	__except (ErrorHandler::GenerateCrashDump(GetExceptionInformation()))
	{
		ErrorHandler::ShowErrorMessageBox();
	}

#if defined(DEBUG) || defined(_DEBUG)
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}