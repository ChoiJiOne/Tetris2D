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


	// 테트로미노를 생성합니다.
	CurrentTetromino = Tetromino::GenerateRandomTetromino(Vec2i(3, 0));
	NextTetromino = Tetromino::GenerateRandomTetromino(Vec2i(3, 0));


	// 테트리스 보드를 생성합니다.
	GameBoard = std::make_unique<Board>();
	GameBoard->AddTetromino(*CurrentTetromino);


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
	GamePlayer->UpdateRemainTime(GameTImer.DeltaTime());

	if (IsPressKey(CurrKeyboardState, SDL_Scancode::SDL_SCANCODE_ESCAPE))
	{
		bIsDoneLoop = true;
	}

	if (IsPressKey(CurrKeyboardState, SDL_Scancode::SDL_SCANCODE_LEFT) && !IsPressKey(PrevKeyboardState, SDL_Scancode::SDL_SCANCODE_LEFT))
	{
		GameBoard->MoveTetromino(*CurrentTetromino, Tetromino::EMove::Left);
	}	
	
	if (IsPressKey(CurrKeyboardState, SDL_Scancode::SDL_SCANCODE_RIGHT) && !IsPressKey(PrevKeyboardState, SDL_Scancode::SDL_SCANCODE_RIGHT))
	{
		GameBoard->MoveTetromino(*CurrentTetromino, Tetromino::EMove::Right);
	}	
	
	if (IsPressKey(CurrKeyboardState, SDL_Scancode::SDL_SCANCODE_UP) && !IsPressKey(PrevKeyboardState, SDL_Scancode::SDL_SCANCODE_UP))
	{
		GameBoard->SpinTetromino(*CurrentTetromino, Tetromino::ESpin::CW);
	}	
	
	if (IsPressKey(CurrKeyboardState, SDL_Scancode::SDL_SCANCODE_DOWN) && !IsPressKey(PrevKeyboardState, SDL_Scancode::SDL_SCANCODE_DOWN))
	{
		GameBoard->MoveTetromino(*CurrentTetromino, Tetromino::EMove::Down);
	}

	if (IsPressKey(CurrKeyboardState, SDL_Scancode::SDL_SCANCODE_SPACE) && !IsPressKey(PrevKeyboardState, SDL_Scancode::SDL_SCANCODE_SPACE))
	{
		while (GameBoard->MoveTetromino(*CurrentTetromino, Tetromino::EMove::Down))
		{

		}
	}
}

void Tetris2D::Draw()
{
	Game::Renderer::BeginFrame(Renderer, ColorHelper::Black);

	GameBoard->Draw(Renderer, Vec2i(10, 10), 35);
	NextTetromino->Draw(Renderer, Vec2i(420, 80), 35);
	GamePlayer->Draw(Renderer, *Font, Vec2i());

	Game::Renderer::EndFrame(Renderer);
}

bool Tetris2D::IsPressKey(const std::vector<uint8_t>& InKeyboardState, uint8_t InKeyCode)
{
	return InKeyboardState[InKeyCode] == 0 ? false : true;
}
