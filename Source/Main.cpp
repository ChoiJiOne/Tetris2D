#include "Game.h"

int main(int argc, char* argv[])
{
#if defined(DEBUG) || defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	try
	{
		auto TetrisGame = std::make_shared<Game>();
		TetrisGame->Setup();
		TetrisGame->Run();
	}
	catch (const std::exception& Exception)
	{
		Logger::Error(Exception.what());
	}

	return 0;
}