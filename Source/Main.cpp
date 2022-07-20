#include "Tetris2D.h"

int main(void)
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
		Game::Logging::Error(Exception.what());
	}

	return 0;
}