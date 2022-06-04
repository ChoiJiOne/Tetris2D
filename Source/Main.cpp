#include "GameWindow.h"
#include "GlobalProperty.h"
#include "Logger.h"

int main(int argc, char* argv[])
{
#if defined(DEBUG) || defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	GlobalProperty::Initialize();

	GameWindow Window;
	Window.CreateWindow(
		"Tetris1.0",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1000,
		800,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
	);

	Sleep(3000);
	Window.~GameWindow();


	GlobalProperty::Release();

	return 0;
}