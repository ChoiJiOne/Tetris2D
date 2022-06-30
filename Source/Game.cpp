#include "Game.h"

Game::~Game()
{
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

		if (bIsExitGame)
		{
			bIsDone = true;
		}

		Update();
		Draw();
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
		SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI
	);


	// GameInput을 초기화합니다.
	GameEngine::GetGameInput().Init();


	// Callback 함수를 등록합니다.
	GameEngine::GetGameInput().SetQuitEventCallback([&]() { bIsDone = true; });
	GameEngine::GetGameInput().SetResizeEventCallback([&](int32_t InWidth, int32_t InHeight) {});
	GameEngine::GetGameInput().SetMinimizeEventCallback([&]() { /*bIsPaused = true;  Timer.Stop();*/ });
	GameEngine::GetGameInput().SetMaximizeEventCallback([&]() { /*bIsPaused = false; Timer.Start();*/ });
	GameEngine::GetGameInput().SetActiveWindowCallback([&]() { /*bIsPaused = false; Timer.Start();*/ });
	GameEngine::GetGameInput().SetInactiveWindowCallback([&]() { /*bIsPaused = true; Timer.Stop();*/ });
	GameEngine::GetGameInput().SetExposeWindowCallback([&]() {});


	// 렌더러를 초기화합니다.
	GameEngine::GetGameRenderer().Init(GameEngine::GetGameWindow().GetWindow());

	uiPositionCache["board"] = Vec2i(333, 60);
	uiPositionCache["next"] = Vec2i(650, 130);
	uiPositionCache["nextTetromino"] = Vec2i(650, 150);
	uiPositionCache["time"] = Vec2i(650, 360);
	uiPositionCache["level"] = Vec2i(650, 400);
	uiPositionCache["remove"] = Vec2i(650, 440);
	uiPositionCache["exit"] = Vec2i(650, 480);
	uiPositionCache["countDown"] = Vec2i(650, 360);
	uiPositionCache["titleScene"] = Vec2i(450, 350);
	uiPositionCache["endingScene"] = Vec2i(400, 300);

}

void Game::SetupTetrisProperties()
{
	// 게임 리소스 경로입니다.
	std::string ResourceDirectory = GameEngine::GetResourceDirectory();


	// 게임 폰트를 생성합니다.
	std::string FontPath = ResourceDirectory + "font/Nanum.ttf";
	Font.CreateGameFont(FontPath, 20.0f);

	tetrisBoard = std::make_shared<Board>();
}

void Game::Update()
{
	if (GameEngine::GetGameInput().GetKeyboardState().IsCurrKeyPress(SDL_Scancode::SDL_SCANCODE_ESCAPE))
	{
		bIsDoneGame = true;
		bIsStartGame = false;
	}

	if (bIsStartGame)
	{
		if (bIsWaitNextLevel)
		{
			UpdateWait();
		}
		else
		{
			UpdatePlay();
		}
	}
	else
	{
		if (bIsDoneGame)
		{
			UpdateEndingScene();
		}
		else
		{
			UpdateTitleScene();
		}
	}
}

void Game::Draw()
{
	GameEngine::GetGameRenderer().BeginFrame(ColorUtil::Black);

	if (bIsStartGame)
	{
		if (bIsWaitNextLevel)
		{
			DrawWait();
		}
		else
		{
			DrawPlay();
		}
	}
	else
	{
		if (bIsDoneGame)
		{
			DrawEndingScene();
		}
		else
		{
			DrawTitleScene();
		}
	}

	GameEngine::GetGameRenderer().EndFrame();
}

void Game::UpdatePlay()
{
	userPlayTime += Timer.DeltaTime();
	userStepTime += Timer.DeltaTime();

	if (GameEngine::GetGameInput().GetKeyboardState().IsCurrKeyPress(SDL_Scancode::SDL_SCANCODE_UP) &&
		!GameEngine::GetGameInput().GetKeyboardState().IsPrevKeyPress(SDL_Scancode::SDL_SCANCODE_UP))
	{
		tetrisBoard->SpinClockWiseTetrominoInBoard(*currTetromino);
	}

	if (GameEngine::GetGameInput().GetKeyboardState().IsCurrKeyPress(SDL_Scancode::SDL_SCANCODE_LEFT) &&
		!GameEngine::GetGameInput().GetKeyboardState().IsPrevKeyPress(SDL_Scancode::SDL_SCANCODE_LEFT))
	{
		tetrisBoard->MoveLeftTetrominoInBoard(*currTetromino);
	}

	if (GameEngine::GetGameInput().GetKeyboardState().IsCurrKeyPress(SDL_Scancode::SDL_SCANCODE_RIGHT) &&
		!GameEngine::GetGameInput().GetKeyboardState().IsPrevKeyPress(SDL_Scancode::SDL_SCANCODE_RIGHT))
	{
		tetrisBoard->MoveRightTetrominoInBoard(*currTetromino);

	}

	if (GameEngine::GetGameInput().GetKeyboardState().IsCurrKeyPress(SDL_Scancode::SDL_SCANCODE_DOWN) &&
		!GameEngine::GetGameInput().GetKeyboardState().IsPrevKeyPress(SDL_Scancode::SDL_SCANCODE_DOWN))
	{
		if (!tetrisBoard->MoveDownTetrominoInBoard(*currTetromino))
		{
			userRemoveLine += tetrisBoard->UpdateBoardState();

			currTetromino.reset();
			currTetromino = nextTetromino;
			nextTetromino = Tetromino::GenerateRandomTetromino(
				Vec2i(tetrisBoard->GetColSize() / 3, 0)
			);

			if (tetrisBoard->IsCrashTetrominoAndBoard(*currTetromino))
			{
				bIsDoneGame = true;
				bIsStartGame = false;
			}
			else
			{
				tetrisBoard->AddTetrominoInBoard(*currTetromino);
			}

			userStepTime = 0.0f;
		}
	}

	if (GameEngine::GetGameInput().GetKeyboardState().IsCurrKeyPress(SDL_Scancode::SDL_SCANCODE_SPACE) &&
		!GameEngine::GetGameInput().GetKeyboardState().IsPrevKeyPress(SDL_Scancode::SDL_SCANCODE_SPACE))
	{
		tetrisBoard->MoveBottomTetrominoInBoard(*currTetromino);

		userRemoveLine += tetrisBoard->UpdateBoardState();

		currTetromino.reset();
		currTetromino = nextTetromino;
		nextTetromino = Tetromino::GenerateRandomTetromino(
			Vec2i(tetrisBoard->GetColSize() / 3, 0)
		);

		if (tetrisBoard->IsCrashTetrominoAndBoard(*currTetromino))
		{
			bIsDoneGame = true;
			bIsStartGame = false;
		}
		else
		{
			tetrisBoard->AddTetrominoInBoard(*currTetromino);
		}
	}

	if (userPlayTime > gamePlayTime)
	{
		userPlayTime = 0.0f;
		userStepTime = 0.0f;
		bIsWaitNextLevel = true;

		currTetromino.reset();
		nextTetromino.reset();

		tetrisBoard->ResetBoardState();
	}
	else
	{
		if (userStepTime > gameStepTime)
		{
			if (!tetrisBoard->MoveDownTetrominoInBoard(*currTetromino))
			{
				userRemoveLine += tetrisBoard->UpdateBoardState();

				currTetromino.reset();
				currTetromino = nextTetromino;
				nextTetromino = Tetromino::GenerateRandomTetromino(
					Vec2i(tetrisBoard->GetColSize() / 3, 0)
				);

				if (tetrisBoard->IsCrashTetrominoAndBoard(*currTetromino))
				{
					bIsDoneGame = true;
					bIsStartGame = false;
				}
				else
				{
					tetrisBoard->AddTetrominoInBoard(*currTetromino);
				}
			}

			userStepTime = 0.0f;
		}
	}
}

void Game::UpdateWait()
{
	waitTime += Timer.DeltaTime();

	if (waitTime > 3.0f)
	{
		userLevel++;
		waitTime = 0.0f;

		gameStepTime -= 0.1f;
		gameStepTime = std::max(0.1f, gameStepTime);

		bIsWaitNextLevel = false;

		currTetromino = Tetromino::GenerateRandomTetromino(
			Vec2i(tetrisBoard->GetColSize() / 3, 0)
		);

		nextTetromino = Tetromino::GenerateRandomTetromino(
			Vec2i(tetrisBoard->GetColSize() / 3, 0)
		);

		tetrisBoard->AddTetrominoInBoard(*currTetromino);
	}
}

void Game::UpdateTitleScene()
{
	if (GameEngine::GetGameInput().GetKeyboardState().IsCurrKeyPress(SDL_Scancode::SDL_SCANCODE_RETURN))
	{
		bIsStartGame = true;
	}
}

void Game::UpdateEndingScene()
{
	if (GameEngine::GetGameInput().GetKeyboardState().IsCurrKeyPress(SDL_Scancode::SDL_SCANCODE_RETURN))
	{
		bIsExitGame = true;
	}
}

void Game::DrawPlay()
{
	tetrisBoard->Draw(uiPositionCache["board"], 30);


	GameEngine::GetGameRenderer().DrawText2D(Font, uiPositionCache["next"], L"다음 테트로미노", ColorUtil::White);
	nextTetromino->Draw(uiPositionCache["nextTetromino"], 30, ColorUtil::Black);


	int32_t remainTime = static_cast<int32_t>(gamePlayTime - userPlayTime);
	GameEngine::GetGameRenderer().DrawText2D(
		Font,
		uiPositionCache["time"],
		StringUtil::StringFormat(L"남은 시간 : %d", remainTime),
		remainTime > 10 ? ColorUtil::White : ColorUtil::Red
	);


	GameEngine::GetGameRenderer().DrawText2D(
		Font,
		uiPositionCache["level"],
		StringUtil::StringFormat(L"현재 레벨 : %d", userLevel),
		ColorUtil::White
	);


	GameEngine::GetGameRenderer().DrawText2D(
		Font,
		uiPositionCache["remove"],
		StringUtil::StringFormat(L"삭제한 라인 수 : %d", userRemoveLine),
		ColorUtil::White
	);


	GameEngine::GetGameRenderer().DrawText2D(
		Font,
		uiPositionCache["exit"],
		L"게임 종료 시 ESC 키를 입력",
		ColorUtil::White
	);
}

void Game::DrawWait()
{
	tetrisBoard->Draw(uiPositionCache["board"], 30);

	GameEngine::GetGameRenderer().DrawText2D(
		Font,
		uiPositionCache["countDown"],
		StringUtil::StringFormat(L"count down : %d", static_cast<int32_t>(gameWaitTime - waitTime)),
		ColorUtil::White
	);
}

void Game::DrawTitleScene()
{
	GameEngine::GetGameRenderer().DrawText2D(
		Font,
		uiPositionCache["titleScene"],
		L"Tetris2D",
		ColorUtil::White
	);

	GameEngine::GetGameRenderer().DrawText2D(
		Font,
		Vec2i(uiPositionCache["titleScene"].x - 80, uiPositionCache["titleScene"].y + 30),
		L"시작하려면 엔터 키를 입력하세요...",
		ColorUtil::White
	);
}

void Game::DrawEndingScene()
{
	GameEngine::GetGameRenderer().DrawText2D(
		Font,
		Vec2i(uiPositionCache["endingScene"].x, uiPositionCache["endingScene"].y),
		L"플레이 해주셔서 감사합니다.",
		ColorUtil::White
	);


	GameEngine::GetGameRenderer().DrawText2D(
		Font,
		Vec2i(uiPositionCache["endingScene"].x, uiPositionCache["endingScene"].y + 30),
		StringUtil::StringFormat(L"유저 레벨 : %d", userLevel),
		ColorUtil::White
	);


	GameEngine::GetGameRenderer().DrawText2D(
		Font,
		Vec2i(uiPositionCache["endingScene"].x, uiPositionCache["endingScene"].y + 60),
		StringUtil::StringFormat(L"플레이 시간 : %d s", static_cast<int32_t>(Timer.TotalTime())),
		ColorUtil::White
	);


	GameEngine::GetGameRenderer().DrawText2D(
		Font,
		Vec2i(uiPositionCache["endingScene"].x, uiPositionCache["endingScene"].y + 90),
		StringUtil::StringFormat(L"삭제한 라인 수 : %d", userRemoveLine),
		ColorUtil::White
	);


	GameEngine::GetGameRenderer().DrawText2D(
		Font,
		Vec2i(uiPositionCache["endingScene"].x, uiPositionCache["endingScene"].y + 120),
		L"종료하려면 엔터키를 입력하세요...",
		ColorUtil::White
	);
}
