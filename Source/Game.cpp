#include "Block.h"
#include "Game.h"

Game::~Game()
{
	for (auto& Texture : TextureCache)
	{
		Texture.second.reset();
		Texture.second = nullptr;
	}

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

		if (!bIsPaused)
		{
			GameEngine::GetGameRenderer().DrawText2D(Font, Vec2i(0, 35), StringUtil::StringFormat(L"FPS : %.f", 1.0f / Timer.DeltaTime()), ColorUtil::White);
		}


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
	Font.CreateGameFont(GameEngine::GetGameRenderer().GetRenderer(), FontPath, 32.0f);


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
		TextureCache[HashKey].get()->CreateTextureFromFile(GameEngine::GetGameRenderer().GetRenderer(), TexturePath);
	}
}

void Game::DrawBoard(const Board& InBoard, const Vec2i& InPosition, float InScale)
{
	for (int32_t Row = 0; Row < InBoard.GetBoardHeight(); ++Row)
	{
		for (int32_t Col = 0; Col < InBoard.GetBoardWidth(); ++Col)
		{
			if (InBoard.GetBlockStateInBoard(Row, Col) != EBlockState::EMPTY)
			{
				int32_t TextureWidth = 0, TextureHeight = 0;
				std::size_t HashKey = 0;

				switch (InBoard.GetBlockColorInBoard(Row, Col))
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

				TextureWidth = static_cast<int32_t>(static_cast<float>(TextureCache[HashKey]->GetWidth()) * InScale);
				TextureHeight = static_cast<int32_t>(static_cast<float>(TextureCache[HashKey]->GetWidth()) * InScale);

				Vec2i MovePosition(Col * TextureWidth, Row * TextureHeight);
				GameEngine::GetGameRenderer().DrawTexture2D(*TextureCache[HashKey].get(), InPosition + MovePosition, InScale, InScale);
			}
		}
	}
}
