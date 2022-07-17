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

	Window.Initialize(Game::WindowConstructParams{
		"Tetris2D",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		600, 700,
		SDL_WINDOW_SHOWN
	});

	Graphics2D.Initialize(Window.GetSDLWindow());

	std::string ExecuteDirectory = SDL_GetBasePath();
	std::string FontPath = ExecuteDirectory + "../../../../Resource/Font/kenvector_future.ttf";
	FontKey = Game::Text::GetHash("Font");
	Game::ResourceManager::CreateTTFont(Graphics2D.GetRenderer(), FontKey, FontPath, 40.0f);
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

	Graphics2D.DrawLine2D(Game::Vec2i(100, 100), Game::Vec2i(140, 100), Game::Color::Red);
	Graphics2D.DrawLine2D(Game::Vec2i(100, 100), Game::Vec2i(100, 140), Game::Color::Red);

	for (int32_t x = 0; x <= 600; x += 10)
	{
		Graphics2D.DrawLine2D(Game::Vec2i(x, 0), Game::Vec2i(x, 700), Game::Color::White);
	}

	for (int32_t y = 0; y <= 700; y += 10)
	{
		Graphics2D.DrawLine2D(Game::Vec2i(0, y), Game::Vec2i(600, y), Game::Color::White);
	}

	Graphics2D.DrawText2D(FontKey, Game::Vec2i(100, 100), L"ABCDEFG", Game::Color::Blue);

	Graphics2D.EndFrame();
}