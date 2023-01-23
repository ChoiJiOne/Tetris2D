#include "GameFramework.h"
#include "Macro.h"

#include <windows.h>

GameFramework::GameFramework()
{
	CHECK_HR(CoInitializeEx(nullptr, COINIT_MULTITHREADED), "failed to com initialize");
}

GameFramework::~GameFramework()
{
	CoUninitialize();
}
