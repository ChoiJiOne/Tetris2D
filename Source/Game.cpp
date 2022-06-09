#include "Block.h"
#include "Game.h"

Game::~Game()
{
	for (auto& Texture : TextureCache)
	{
		Texture.second.reset();
		Texture.second = nullptr;
	}
}

void Game::Setup()
{
	// 게임 프레임워크를 초기화합니다.
	GameFramework::Setup();


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
		GetGameInput().Tick();


		// 프레임 렌더링을 시작합니다.
		GetGameRenderer().BeginFrame(ColorUtil::Black);

		if (!bIsPaused)
		{
			GetGameRenderer().DrawText2D(Font, Vec2i(0, 35), StringUtil::StringFormat(L"FPS : %.f", 1.0f / Timer.DeltaTime()), ColorUtil::White);
		}


		// 테트리스 보드를 화면에 그립니다.
		DrawBoard(Vec2i(400, 150));


		// 프레임 렌더링을 종료하고, 벡 버퍼를 화면에 표시합니다.
		GetGameRenderer().EndFrame();
	}
}

void Game::SetupCommonProperties()
{
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
	GetGameInput().SetResizeEventCallback([&](int32_t InWidth, int32_t InHeight) {});
	GetGameInput().SetMinimizeEventCallback([&]() { bIsPaused = true;  Timer.Stop(); });
	GetGameInput().SetMaximizeEventCallback([&]() { bIsPaused = false; Timer.Start(); });
	GetGameInput().SetActiveWindowCallback([&]() { bIsPaused = false; Timer.Start(); });
	GetGameInput().SetInactiveWindowCallback([&]() { bIsPaused = true; Timer.Stop(); });
	GetGameInput().SetExposeWindowCallback([&]() {});


	// 렌더러를 초기화합니다.
	GetGameRenderer().Init(GetGameWindow().GetWindow());
}

void Game::SetupTetrisProperties()
{
	// 게임 리소스 경로입니다.
	std::string ResourceDirectory = GetResourceDirectory();


	// 게임 폰트를 생성합니다.
	std::string FontPath = ResourceDirectory + "font/Nanum.ttf";
	Font.CreateGameFont(GetGameRenderer().GetRenderer(), FontPath, 32.0f);


	// 테트리스 블럭 텍스처를 생성합니다.
	std::vector<std::string> BlockTextureNames = {
		"BlueBlock",
		"CyanBlock",
		"GrayBlock",
		"GreenBlock",
		"OrangeBlock",
		"PinkBlock",
		"PurpleBlock",
		"RedBlock",
		"YellowBlock"
	};


	for (const auto& BlockTextureName : BlockTextureNames)
	{
		std::size_t HashKey = StringUtil::ConvertUTF8ToHash(BlockTextureName);
		std::string TexturePath = StringUtil::StringFormat("%stexture/%s.png", ResourceDirectory.c_str(), BlockTextureName.c_str());

		TextureCache[HashKey] = std::make_unique<GameTexture2D>();
		TextureCache[HashKey].get()->CreateTextureFromFile(GetGameRenderer().GetRenderer(), TexturePath);
	}


	Block WallState = Block(EBlockState::FIX, EBlockColor::GRAY);

	Board.resize(BoardWidth * BoardHeight, Block(EBlockState::EMPTY, EBlockColor::GRAY));

	for (int32_t Row = 0; Row < BoardHeight; ++Row)
	{
		if (Row == BoardHeight - 1)
		{
			for (int32_t Col = 0; Col < BoardWidth; ++Col)
			{
				int32_t Offset = Row * BoardWidth + Col;
				Board[Offset] = WallState;
			}
		}
		else
		{
			int32_t Offset = Row * BoardWidth;
			Board[Offset + 0]              = WallState;
			Board[Offset + BoardWidth - 1] = WallState;
		}
	}
}

void Game::DrawBoard(const Vec2i& InPosition)
{
	for (int32_t Row = 0; Row < BoardHeight; ++Row)
	{
		for (int32_t Col = 0; Col < BoardWidth; ++Col)
		{
			Block BlockState = Board[Row * BoardWidth + Col];

			if (BlockState.first != EBlockState::EMPTY)
			{
				int32_t TextureWidth = 0, TextureHeight = 0;
				std::size_t HashKey = 0;

				switch (BlockState.second)
				{
				case EBlockColor::BLUE:
					HashKey = StringUtil::ConvertUTF8ToHash("BlueBlock");
					break;


				case EBlockColor::CYAN:
					HashKey = StringUtil::ConvertUTF8ToHash("CyanBlock");
					break;


				case EBlockColor::GRAY:
					HashKey = StringUtil::ConvertUTF8ToHash("GrayBlock");
					break;


				case EBlockColor::GREEN:
					HashKey = StringUtil::ConvertUTF8ToHash("GreenBlock");
					break;


				case EBlockColor::ORANGE:
					HashKey = StringUtil::ConvertUTF8ToHash("OrangeBlock");
					break;


				case EBlockColor::PINK:
					HashKey = StringUtil::ConvertUTF8ToHash("PinkBlock");
					break;


				case EBlockColor::PURPLE:
					HashKey = StringUtil::ConvertUTF8ToHash("PurpleBlock");
					break;


				case EBlockColor::RED:
					HashKey = StringUtil::ConvertUTF8ToHash("RedBlock");
					break;


				case EBlockColor::YELLOW:
					HashKey = StringUtil::ConvertUTF8ToHash("YellowBlock");
					break;
				}

				TextureWidth = static_cast<int32_t>(static_cast<float>(TextureCache[HashKey]->GetWidth()) * 0.25f);
				TextureHeight = static_cast<int32_t>(static_cast<float>(TextureCache[HashKey]->GetWidth()) * 0.25f);

				Vec2i MovePosition(Col * TextureWidth, Row * TextureHeight);
				GetGameRenderer().DrawTexture2D(*TextureCache[HashKey].get(), InPosition + MovePosition, 0.25f, 0.25f);
			}
		}
	}
}
