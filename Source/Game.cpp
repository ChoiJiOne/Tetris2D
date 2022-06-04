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
}

void Game::Run()
{
	bool bIsDone = false;
	SDL_Event EventMessage;

	while (!bIsDone)
	{
		while (SDL_PollEvent(&EventMessage))
		{
			if (EventMessage.type == SDL_QUIT)
			{
				bIsDone = true;
			}
		}
	}
}