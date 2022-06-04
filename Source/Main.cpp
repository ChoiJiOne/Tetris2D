#include "GlobalProperty.h"
#include "Logger.h"

int main(int argc, char* argv[])
{
#if defined(DEBUG) || defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	GlobalProperty::Initialize();
	GlobalProperty::Release();

	return 0;
}