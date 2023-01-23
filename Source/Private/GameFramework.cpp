#include "GameFramework.h"
#include "Macro.h"

#include <windows.h>

GameFramework::GameFramework()
{
	CHECK_HR(CoInitializeEx(nullptr, COINIT_MULTITHREADED), "failed to initialize for component object model resource");
}

GameFramework::~GameFramework()
{
	CoUninitialize();
}
