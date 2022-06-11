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

		if (GameEngine::GetGameInput().GetKeyboardState().IsCurrKeyPress(SDL_SCANCODE_UP) &&
			!GameEngine::GetGameInput().GetKeyboardState().IsPrevKeyPress(SDL_SCANCODE_UP))
		{
			CurrTetromino->Spin(Tetromino::ESpin::CW);
		}


		// 프레임 렌더링을 시작합니다.
		GameEngine::GetGameRenderer().BeginFrame(ColorUtil::Black);

		if (!bIsPaused)
		{
			GameEngine::GetGameRenderer().DrawText2D(Font, Vec2i(0, 35), StringUtil::StringFormat(L"FPS : %.f", 1.0f / Timer.DeltaTime()), ColorUtil::White);
		}

		int32_t x = 250, y = 250;
		TetrisBoard.DrawBoard(Vec2i(x, y), 0.3f);

		NextTetromino->DrawTetromino(Vec2i(700, 400), 0.4f);

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
		"Tetris1.0",
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
