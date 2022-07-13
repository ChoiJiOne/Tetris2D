#include "Tetris2D.h"

Tetris2D::~Tetris2D()
{
}

void Tetris2D::Initialize()
{
	Engine::Initialize();

	Game::WindowConstructParams WindowParams;
	WindowParams.Title = "Tetris2D";
	WindowParams.w = 1000;
	WindowParams.h = 800;
	WindowParams.Flags |= SDL_WINDOW_ALLOW_HIGHDPI;

	Window.Create(WindowParams);
}

void Tetris2D::Input()
{
}

void Tetris2D::Update()
{
}

void Tetris2D::Render()
{
}

void Tetris2D::Run()
{
	bool bIsDoneLoop = false;

	while (!bIsDoneLoop)
	{
		SDL_Event Event;

		while (SDL_PollEvent(&Event))
		{
			if (Event.type == SDL_QUIT)
			{
				bIsDoneLoop = true;
			}
		}

		Input();
		Update();
		Render();
	}
}
