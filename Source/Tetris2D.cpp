#include "Game/SDLHelper.h"
#include "Game/Renderer.h"

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

	// 이 부분 수정 필요!
	std::string FontPath = Game::SDLHelper::GetExecuteDirectory() + "../../../../Font/Nanum.ttf";
	Font = std::make_unique<Game::Font>(Renderer, FontPath, 32.0f);
}

void Tetris2D::Run()
{
	SDL_Event Event;
	GameTImer.Reset();

	while (!bIsDoneLoop)
	{
		GameTImer.Tick();

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
	Game::Renderer::BeginFrame(Renderer, ColorHelper::Black);

	Game::Renderer::DrawText2D(Renderer, *Font, Vec2i(40, 40), L"한글 출력 확인", ColorHelper::White);

	Game::Renderer::EndFrame(Renderer);
}