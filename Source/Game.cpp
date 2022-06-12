#include "Block.h"
#include "Game.h"

Game::~Game()
{
	CurrTetromino.reset();
	NextTetromino.reset();

	GameEngine::Release();
}

void Game::Setup()
{
	// 게임 엔진을 초기화합니다.
	GameEngine::Init();


	// 전체 게임 관련 리소스를 초기화합니다.
	SetupCommonProperties();


	// 테트리스 관련 리소스를 초기화합니다.
	SetupTetrisProperties();
}

void Game::Run()
{
	// 게임 타이머를 초기화합니다.
	Timer.Reset();


	// 루프를 수행합니다.
	while (!bIsDone)
	{
		// 게임 타이머를 업데이트 합니다.
		Timer.Tick();


		// 입력 처리를 업데이트합니다.
		GameEngine::GetGameInput().Tick();


		// 프레임 렌더링을 시작합니다.
		GameEngine::GetGameRenderer().BeginFrame(ColorUtil::Black);

		
		// Grid 평면을 그립니다.
		for (int32_t x = 10; x < 1000; x += 10)
		{
			GameEngine::GetGameRenderer().DrawLine2D(Vec2i(x, 0), Vec2i(x, 800), ColorUtil::White);
		}

		for (int32_t y = 10; y < 800; y += 10)
		{
			GameEngine::GetGameRenderer().DrawLine2D(Vec2i(0, y), Vec2i(1000, y), ColorUtil::White);
		}

		GameEngine::GetGameRenderer().DrawText2D(
			Font, Vec2i(200, 200), L"Hello World한글?", ColorUtil::Green
		);

		GameEngine::GetGameRenderer().DrawWireframeRectangle2D(
			Vec2i(200, 200), Vec2i(500, 500), ColorUtil::Red
		);


		// 프레임 렌더링을 종료하고, 벡 버퍼를 화면에 표시합니다.
		GameEngine::GetGameRenderer().EndFrame();
	}
}

void Game::SetupCommonProperties()
{
	// 게임 윈도우를 생성합니다.
	int32_t WindowWidth = 1000;
	int32_t WindowHeight = 800;

	GameEngine::GetGameWindow().CreateWindow(
		"Tetris2D",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WindowWidth,
		WindowHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
	);


	// GameInput을 초기화합니다.
	GameEngine::GetGameInput().Init();


	// Callback 함수를 등록합니다.
	GameEngine::GetGameInput().SetQuitEventCallback([&]() { bIsDone = true; });
	GameEngine::GetGameInput().SetResizeEventCallback([&](int32_t InWidth, int32_t InHeight) {});
	GameEngine::GetGameInput().SetMinimizeEventCallback([&]() { bIsPaused = true;  Timer.Stop(); });
	GameEngine::GetGameInput().SetMaximizeEventCallback([&]() { bIsPaused = false; Timer.Start(); });
	GameEngine::GetGameInput().SetActiveWindowCallback([&]() { bIsPaused = false; Timer.Start(); });
	GameEngine::GetGameInput().SetInactiveWindowCallback([&]() { bIsPaused = true; Timer.Stop(); });
	GameEngine::GetGameInput().SetExposeWindowCallback([&]() {});


	// 렌더러를 초기화합니다.
	GameEngine::GetGameRenderer().Init(GameEngine::GetGameWindow().GetWindow());
}

void Game::SetupTetrisProperties()
{
	// 게임 리소스 경로입니다.
	std::string ResourceDirectory = GameEngine::GetResourceDirectory();


	// 게임 폰트를 생성합니다.
	std::string FontPath = ResourceDirectory + "font/Nanum.ttf";
	Font.CreateGameFont(FontPath, 32.0f);


	// 테트리스 보드를 초기화합니다.
	TetrisBoard.Init();


	// 테트로미노를 생성합니다.
	CurrTetromino = Tetromino::GenerateRandomTetromino(Vec2i(TetrisBoard.GetBoardWidth() / 3, 0));
	NextTetromino = Tetromino::GenerateRandomTetromino(Vec2i(TetrisBoard.GetBoardWidth() / 3, 0));
}
