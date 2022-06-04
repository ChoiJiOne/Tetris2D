#include "Game.h"

Game::~Game()
{
	// 렌더러 리소스를 할당 해제합니다.
	Renderer.reset();
	Renderer = nullptr;


	// 입력 처리 리소스를 할당 해제합니다.
	Input.reset();
	Input = nullptr;


	// 게임 윈도우 리소스를 할당 해제합니다.
	Window.reset();
	Window = nullptr;


	// 게임 타이머 리소스를 할당 해제합니다.
	GlobalTimer.reset();
	GlobalTimer = nullptr;
}

void Game::Setup()
{
	// 게임 윈도우 인스턴스를 생성합니다.
	Window = std::make_unique<GameWindow>();


	// 게임 윈도우를 생성합니다.
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


	// 디버그 모드일 경우, 콘솔 창을 표시합니다.
#if defined(DEBUG) || defined(_DEBUG)
	Window->SetVisibleConsoleWindow(true);
#else
	Window->SetVisibleConsoleWindow(false);
#endif


	// 게임 타이머 인스턴스를 생성합니다.
	GlobalTimer = std::make_unique<GameTimer>();


	// 입력 처리 인스턴스를 생성합니다.
	Input = std::make_unique<GameInput>();


	// 입력 처리 인스턴스에 Callback 함수를 등록합니다.
	Input->SetExitEventCallback(
		[&]() {
			bIsExit = true;
		}
	);

	Input->SetResizeEventCallback(
		[&](int32_t InWidth, int32_t InHeight) {
			// TODO : 윈도우 크기 변경 이벤트를 구현합니다.
		}
	);


	// 렌더러 인스터스를 생성합니다.
	Renderer = std::make_unique<GameRenderer>(Window->GetWindow());
}

void Game::Run()
{
	// 게임 타이머를 초기화합니다.
	GlobalTimer->Reset();
	

	// 루프를 수행합니다.
	while (!bIsExit)
	{
		// 게임 타이머를 업데이트 합니다.
		GlobalTimer->Tick();


		// 입력 처리를 업데이트합니다.
		Input->Tick();


		// 프레임 렌더링을 시작합니다.
		Renderer->BeginFrame(0, 0, 255, 255);


		// 프레임 렌더링을 종료하고, 벡 버퍼를 화면에 표시합니다.
		Renderer->EndFrame();
	}
}