#include "Game.h"

Game::~Game()
{
}

void Game::Setup()
{
	// 게임 프레임워크를 초기화합니다.
	GameFramework::Setup();


	// 게임 윈도우를 생성합니다.
	int32_t WindowWidth = 1000;
	int32_t WindowHeight = 800;

	GetGameWindow().CreateWindow(
		"Tetris1.0",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WindowWidth,
		WindowHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
	);


	// GameInput을 초기화합니다.
	GetGameInput().Init();


	// Callback 함수를 등록합니다.
	GetGameInput().SetQuitEventCallback([&]() { bIsDone = true; });
	GetGameInput().SetResizeEventCallback([&](int32_t InWidth, int32_t InHeight) { });
	GetGameInput().SetMinimizeEventCallback([&]() { bIsPaused = true;  Timer.Stop(); });
	GetGameInput().SetMaximizeEventCallback([&]() { bIsPaused = false; Timer.Start(); });
	GetGameInput().SetActiveWindowCallback([&]() { bIsPaused = false; Timer.Start(); });
	GetGameInput().SetInactiveWindowCallback([&]() { bIsPaused = true; Timer.Stop(); });
	GetGameInput().SetExposeWindowCallback([&]() {});


	// 렌더러를 초기화합니다.
	GetGameRenderer().Init(GetGameWindow().GetWindow());


	// 게임 폰트를 생성합니다.
	std::string FontPath = GetResourceDirectory() + "font/Nanum.ttf";
	Font.CreateGameFont(GetGameRenderer().GetRenderer(), FontPath, 32.0f);


	// 테트리스 블럭 텍스처를 생성합니다.

}

void Game::Run()
{
	// 게임 타이머를 초기화합니다.
	Timer.Reset();


	GameTexture2D Gray;
	Gray.CreateTextureFromFile(GetGameRenderer().GetRenderer(), GetResourceDirectory() + "texture/GrayBlock.png");

	int32_t Width = static_cast<int32_t>(static_cast<float>(Gray.GetWidth()) * 0.25f);
	int32_t Height = static_cast<int32_t>(static_cast<float>(Gray.GetHeight()) * 0.25f);
	Vec2i Position(200, 100);


	// 루프를 수행합니다.
	while (!bIsDone)
	{
		// 게임 타이머를 업데이트 합니다.
		Timer.Tick();


		// 입력 처리를 업데이트합니다.
		GetGameInput().Tick();


		// 프레임 렌더링을 시작합니다.
		GetGameRenderer().BeginFrame(ColorUtil::Black);

		if (!bIsPaused)
		{
			GetGameRenderer().DrawText2D(Font, Vec2i(0, 35), StringUtil::StringFormat(L"FPS : %.f", 1.0f / Timer.DeltaTime()), ColorUtil::White);
		}


		for (int32_t x = 0; x < 12; ++x)
		{
			for (int32_t y = 0; y < 20; ++y)
			{
				Vec2i MovePosition(x * Width, y * Height);
				GetGameRenderer().DrawTexture2D(Gray, Position + MovePosition, 0.25f, 0.25f);
			}
		}


		// 프레임 렌더링을 종료하고, 벡 버퍼를 화면에 표시합니다.
		GetGameRenderer().EndFrame();
	}
}