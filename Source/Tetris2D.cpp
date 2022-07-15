// @third party code - BEGIN SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
// @third party code - END

#include "Game/ResourceManager.h"
#include "Game/Text.h"
#include "Game/Texture2D.h"
#include "Game/TTFont.h"
#include "Game/Macro.h"

#include "Tetris2D.h"

Tetris2D::~Tetris2D()
{
	Game::ResourceManager::Cleanup();

	SDL_Quit();
}

void Tetris2D::Initialize()
{
	CHECK((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_EVENTS) == 0), SDL_GetError());


	// SDL 윈도우를 생성합니다.
	Game::WindowConstructParams WindowParams;
	WindowParams.Title = "Tetris2D";
	WindowParams.w = 600;
	WindowParams.h = 720;
	WindowParams.Flags |= SDL_WINDOW_ALLOW_HIGHDPI;

	Window.Initialize(WindowParams);


	// SDL 렌더러를 생성합니다.
	Graphics2D.Initialize(Window.GetSDLWindow());
}

void Tetris2D::Run()
{
	GameTimer.Reset();

	while (!Input.Tick())
	{
		GameTimer.Tick();

		Update();
		Draw();
	}
}

void Tetris2D::Update()
{
}

void Tetris2D::Draw()
{
	Graphics2D.BeginFrame(Game::Color::Black);

	Graphics2D.EndFrame();
}