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


	// 디버그 모드일 경우, 콘솔 창을 표시합니다.
#if defined(DEBUG) || defined(_DEBUG)
	GetGameWindow().SetVisibleConsoleWindow(true);
#else
	GetGameWindow().SetVisibleConsoleWindow(false);
#endif


	// 입력 처리 인스턴스에 Callback 함수를 등록합니다.
	GetGameInput().SetExitEventCallback(
		[&]() {
			bIsExit = true;
		}
	);

	GetGameInput().SetResizeEventCallback(
		[&](int32_t InWidth, int32_t InHeight) {
			// TODO : 윈도우 크기 변경 이벤트를 구현합니다.
		}
	);


	// 렌더러를 초기화합니다.
	GetGameRenderer().Init(GetGameWindow().GetWindow());


	// 게임 폰트를 생성합니다.
	Font.CreateGameFont(GetGameRenderer().GetRenderer(), "D:\\Repository\\Tetris1.0\\Resource\\font\\Nanum.ttf", 32.0f);
}

void Game::Run()
{
	// 게임 타이머를 초기화합니다.
	GlobalTimer.Reset();
	

	// 루프를 수행합니다.
	while (!bIsExit)
	{
		// 게임 타이머를 업데이트 합니다.
		GlobalTimer.Tick();


		// 입력 처리를 업데이트합니다.
		GetGameInput().Tick();


		// 프레임 렌더링을 시작합니다.
		GetGameRenderer().BeginFrame(ColorUtil::Black);


		// 화면에 FPS를 표시합니다.
		GetGameRenderer().DrawText2D(Font, Vec2i(0, 35), StringUtil::StringFormat(L"FPS : %.f", 1.0f / GlobalTimer.DeltaTime()), ColorUtil::White);


		// 프레임 렌더링을 종료하고, 벡 버퍼를 화면에 표시합니다.
		GetGameRenderer().EndFrame();
	}
}