#include "Game/SDLHelper.h"
#include "Game/Renderer.h"

#include "Tetris2D.h"

Tetris2D::~Tetris2D()
{
	GamePlayer.reset();

	GameBoard.reset();

	NextTetromino.reset();
	CurrentTetromino.reset();

	Font.reset();

	Game::SDLHelper::DestroySDLRenderer(Renderer);
	Game::SDLHelper::DestroySDLWindow(Window);
}

void Tetris2D::Setup()
{
	// 프레임워크를 초기화합니다.
	Game::Framework::Setup();


	// SDL 윈도우를 생성합니다.
	int32_t WindowWidth  = 600;
	int32_t WindowHeight = 720;

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
	Font = std::make_unique<Game::Font>(Renderer, FontPath, 40.0f);


	// 키보드 상태를 초기화합니다.
	PrevKeyboardState.resize(SDL_Scancode::SDL_NUM_SCANCODES);
	CurrKeyboardState.resize(SDL_Scancode::SDL_NUM_SCANCODES);


	// 테트로미노 리스폰 위치를 설정합니다.
	RespawnPosition = Vec2i(3, 0);


	// 테트로미노를 생성합니다.
	CurrentTetromino = Tetromino::GenerateRandomTetromino(RespawnPosition);
	NextTetromino = Tetromino::GenerateRandomTetromino(RespawnPosition);


	// 테트리스 보드를 생성합니다.
	GameBoard = std::make_unique<Board>();


	// 게임 플레이어를 생성합니다.
	GamePlayer = std::make_unique<Player>();
	GamePlayer->ResetAllProperties();
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
	if (IsPressKey(CurrKeyboardState, SDL_Scancode::SDL_SCANCODE_ESCAPE))
	{
		bIsDoneLoop = true;
	}

	GamePlayer->Update(GameTImer.DeltaTime());

	if (GamePlayer->GetCurrentState() == Player::EState::Wait && GamePlayer->GetBeforeState() == Player::EState::Play)
	{
		GameBoard->ResetBoardState();
	}

	if (GamePlayer->GetCurrentState() == Player::EState::Play && GamePlayer->GetBeforeState() == Player::EState::Wait)
	{
		float NewMaxStepTime = GamePlayer->GetCurrentMaxStepTime() - 0.1f;

		GamePlayer->ResetStepTime();
		GamePlayer->SetCurrentMaxStepTime(NewMaxStepTime);
		GameBoard->AddTetromino(*CurrentTetromino);
	}

	Player::EState CurrentPlayerState = GamePlayer->GetCurrentState();

	switch (CurrentPlayerState)
	{
	case Player::EState::Play:
		UpdatePlay();
		break;

	case Player::EState::Wait:
		break;

	case Player::EState::Done:
		UpdateDone();
		break;

	default:
		Game::Logger::Warning("undefined player state");
	}
}

void Tetris2D::Draw()
{
	Game::Renderer::BeginFrame(Renderer, ColorHelper::Black);

	GameBoard->Draw(Renderer, Vec2i(10, 10), 35);
	GamePlayer->Draw(Renderer, *Font, Vec2i());

	Game::Renderer::EndFrame(Renderer);
}

bool Tetris2D::IsPressKey(const std::vector<uint8_t>& InKeyboardState, uint8_t InKeyCode)
{
	return InKeyboardState[InKeyCode] == 0 ? false : true;
}

void Tetris2D::UpdatePlay()
{
	bool bIsNextTetromino = false;

	static uint8_t KeyCodes[5] = {
		SDL_Scancode::SDL_SCANCODE_LEFT,
		SDL_Scancode::SDL_SCANCODE_RIGHT,
		SDL_Scancode::SDL_SCANCODE_UP,
		SDL_Scancode::SDL_SCANCODE_DOWN,
		SDL_Scancode::SDL_SCANCODE_SPACE
	};

	for (const auto& KeyCode : KeyCodes)
	{
		if (IsPressKey(CurrKeyboardState, KeyCode) && !IsPressKey(PrevKeyboardState, KeyCode))
		{
			switch (KeyCode)
			{
			case SDL_Scancode::SDL_SCANCODE_LEFT:
				GameBoard->MoveTetromino(*CurrentTetromino, Tetromino::EMove::Left);
				break;


			case SDL_Scancode::SDL_SCANCODE_RIGHT:
				GameBoard->MoveTetromino(*CurrentTetromino, Tetromino::EMove::Right);
				break;


			case SDL_Scancode::SDL_SCANCODE_UP:
				GameBoard->SpinTetromino(*CurrentTetromino, Tetromino::ESpin::CW);
				break;


			case SDL_Scancode::SDL_SCANCODE_DOWN:
				bIsNextTetromino = !GameBoard->MoveTetromino(*CurrentTetromino, Tetromino::EMove::Down);
				break;

			case SDL_Scancode::SDL_SCANCODE_SPACE:
				while (GameBoard->MoveTetromino(*CurrentTetromino, Tetromino::EMove::Down))
					;
				bIsNextTetromino = true;
				break;

			default:
				break;
			}
		}
	}

	if (GamePlayer->GetStepTime() >= GamePlayer->GetCurrentMaxStepTime())
	{
		GamePlayer->ResetStepTime();
		bIsNextTetromino = !GameBoard->MoveTetromino(*CurrentTetromino, Tetromino::EMove::Down);
	}

	GamePlayer->AddRemoveLine(GameBoard->UpdateBoardState());

	if (bIsNextTetromino)
	{
		CurrentTetromino.reset();
		CurrentTetromino = NextTetromino;
		NextTetromino = Tetromino::GenerateRandomTetromino(RespawnPosition);

		if (!GameBoard->AddTetromino(*CurrentTetromino))
		{
			GamePlayer->SetCurrentState(Player::EState::Done);
		}
	}
}

void Tetris2D::UpdateDone()
{
	static uint8_t KeyCodes[2] = {
		SDL_Scancode::SDL_SCANCODE_ESCAPE,
		SDL_Scancode::SDL_SCANCODE_KP_ENTER
	};

	for (const auto& KeyCode : KeyCodes)
	{
		if (IsPressKey(CurrKeyboardState, KeyCode))
		{
			bIsDoneLoop = true;
		}
	}
}
