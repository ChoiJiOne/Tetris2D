#include "Game/GameSDLHelper.h"

#include "Tetris2D.h"

Tetris2D::~Tetris2D()
{
	Game::SDLHelper::DestroySDLRenderer(Renderer);
	Game::SDLHelper::DestroySDLWindow(Window);
}

void Tetris2D::Setup()
{
	Game::Framework::Setup();


	int32_t WindowWidth  = 700;
	int32_t WindowHeight = 900;

	Window = Game::SDLHelper::CreateSDLWindow(
		"Tetris2D",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WindowWidth,
		WindowHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI
	);


	Renderer = Game::SDLHelper::CreateSDLRenderer(Window);
}

void Tetris2D::Run()
{
	SDL_Event Event;

	while (!bIsDoneLoop)
	{
		while (SDL_PollEvent(&Event))
		{
			if (Event.type == SDL_QUIT)
			{
				bIsDoneLoop = true;
			}
		}

		Update();
		Draw();
	}
}

void Tetris2D::Update()
{
}

void Tetris2D::Draw()
{
}