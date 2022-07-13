// @third party code - BEGIN crtdbg
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
// @third party code - END
// 메모리 누수를 점검하는 데 사용됩니다.

#include <iostream>
#include <stdexcept>
#include <memory>

#include "Tetris2D.h"

int main(int argc, char* argv[])
{
#if defined(DEBUG) || defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	try
	{
		auto Game = std::make_unique<Tetris2D>();
		Game->Initialize();
		Game->Run();
	}
	catch (const std::exception& Exception)
	{
		std::cout << Exception.what() << std::endl;
	}

	return 0;
}