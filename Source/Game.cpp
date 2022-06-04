#include "Game.h"

Game::~Game()
{
	Window.reset();
	Window = nullptr;


	GlobalTimer.reset();
	GlobalTimer = nullptr;
}

void Game::Setup()
{
	Window = std::make_unique<GameWindow>();
	

	int32_t WindowWidth = 1000;
	int32_t WindowHeight = 800;


	Window->CreateWindow(
		"Tetris1.0",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WindowWidth,
		WindowHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
	);


#if defined(DEBUG) || defined(_DEBUG)
	Window->SetVisibleConsoleWindow(true);
#else
	Window->SetVisibleConsoleWindow(false);
#endif


	GlobalTimer = std::make_unique<GameTimer>();

	Input = std::make_unique<GameInput>();

	Input->SetExitEventCallback(
		[&]() {
			bIsExit = true;
		}
	);

	Input->SetResizeEventCallback(
		[&](int32_t InWidth, int32_t InHeight) {
			Logger::Message("Resize!");
		}
	);
}

void Game::Run()
{
	while (!bIsExit)
	{
		Input->Tick();
	}
}