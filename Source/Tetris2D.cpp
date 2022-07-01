#include "Game/SDLHelper.h"
#include "Game/Renderer.h"

#include "Tetris2D.h"

Tetris2D::~Tetris2D()
{
	Font.reset();

	Game::SDLHelper::DestroySDLRenderer(Renderer);
	Game::SDLHelper::DestroySDLWindow(Window);
}

void Tetris2D::Setup()
{
	// 프레임워크를 초기화합니다.
	Game::Framework::Setup();


	// SDL 윈도우를 생성합니다.
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


	// SDL 렌더러를 생성합니다.
	Renderer = Game::SDLHelper::CreateSDLRenderer(Window);


	// 폰트를 생성합니다. (TODO : 폰트 리소스 경로 수정 필요)
	std::string FontPath = Game::SDLHelper::GetExecuteDirectory() + "../../../../Font/Nanum.ttf";
	Font = std::make_unique<Game::Font>(Renderer, FontPath, 32.0f);


	// 키보드 상태를 초기화합니다.
	PrevKeyboardState.resize(SDL_Scancode::SDL_NUM_SCANCODES);
	CurrKeyboardState.resize(SDL_Scancode::SDL_NUM_SCANCODES);
}

void Tetris2D::Run()
{
	GameTImer.Reset();

	while (!bIsDoneLoop)
	{
		GameTImer.Tick();

		Input();
		Update();
		Draw();
	}
}

void Tetris2D::Input()
{
	SDL_Event Event;

	while (SDL_PollEvent(&Event))
	{
		if (Event.type == SDL_QUIT)
		{
			bIsDoneLoop = true;
		}
	}

	const uint8_t* KeyState = SDL_GetKeyboardState(NULL);

	std::memcpy(
		reinterpret_cast<void*>(&PrevKeyboardState[0]),
		reinterpret_cast<const void*>(&CurrKeyboardState[0]),
		static_cast<size_t>(SDL_Scancode::SDL_NUM_SCANCODES)
	);

	std::memcpy(
		reinterpret_cast<void*>(&CurrKeyboardState[0]),
		reinterpret_cast<const void*>(&KeyState[0]),
		static_cast<size_t>(SDL_Scancode::SDL_NUM_SCANCODES)
	);
}

void Tetris2D::Update()
{
}

void Tetris2D::Draw()
{
	Game::Renderer::BeginFrame(Renderer, ColorHelper::Black);

	if (IsPressKey(CurrKeyboardState, SDL_Scancode::SDL_SCANCODE_LEFT))
	{
		Game::Renderer::DrawText2D(Renderer, *Font, Vec2i(40, 40), L"방향키 감지 : 왼쪽", ColorHelper::White);
	}
	else if (IsPressKey(CurrKeyboardState, SDL_Scancode::SDL_SCANCODE_RIGHT))
	{
		Game::Renderer::DrawText2D(Renderer, *Font, Vec2i(40, 40), L"방향키 감지 : 오른쪽", ColorHelper::White);
	}
	else if (IsPressKey(CurrKeyboardState, SDL_Scancode::SDL_SCANCODE_UP))
	{
		Game::Renderer::DrawText2D(Renderer, *Font, Vec2i(40, 40), L"방향키 감지 : 위", ColorHelper::White);
	}
	else if (IsPressKey(CurrKeyboardState, SDL_Scancode::SDL_SCANCODE_DOWN))
	{
		Game::Renderer::DrawText2D(Renderer, *Font, Vec2i(40, 40), L"방향키 감지 : 아래", ColorHelper::White);
	}
	else
	{
		Game::Renderer::DrawText2D(Renderer, *Font, Vec2i(40, 40), L"방향키가 감지되지 않습니다.", ColorHelper::White);
	}

	Game::Renderer::EndFrame(Renderer);
}

bool Tetris2D::IsPressKey(const std::vector<uint8_t>& InKeyboardState, uint8_t InKeyCode)
{
	return InKeyboardState[InKeyCode] == 0 ? false : true;
}
