#include "Game/GameString.h"
#include "Game/GameSDLUtility.h"

#include "SDL2/SDL.h"

int main(int argc, char* argv[])
{
#if defined(DEBUG) || defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	try
	{
		Game::SDLUtility::Init();

		SDL_Window* Window = Game::SDLUtility::CreateSDLWindow(
			"Tetris2D",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			700,
			800,
			SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI
		);
		Sleep(3000);

		Game::SDLUtility::DestroySDLWindow(Window);
	}
	catch (const std::exception& Exception)
	{
		std::cout << Exception.what() << std::endl;
	}

	Game::SDLUtility::Release();
	return 0;
}