#include "Game/SDLHelper.h"
#include "Game/ResourceHelper.h"
#include "Game/DrawHelper.h"
#include "Game/StringHelper.h"
#include "Game/Texture2D.h"
#include "Game/Font.h"

#include "Tetris2D.h"

Tetris2D::~Tetris2D()
{
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
	std::string FontPath = Game::SDLHelper::GetExecuteDirectory() + "../../../../Resource/Font/kenvector_future.ttf";
	FontKey = Game::StringHelper::GetHash("Font");
	Game::ResourceHelper::CreateFont(Renderer, FontKey, FontPath, 40.0f);

	
	// 텍스처를 생성합니다. (TODO : 텍스처 리소스 경로 수정 필요)
	std::string TexturePath = Game::SDLHelper::GetExecuteDirectory() + "../../../../Resource/Texture/Block/BlueBlockFX.png";
	TextureKey = Game::StringHelper::GetHash("Texture");
	Game::ResourceHelper::CreateTexture2D(Renderer, TextureKey, TexturePath);
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

	Keyboard.Update();
}

void Tetris2D::Update()
{
}

void Tetris2D::Draw()
{
	Game::DrawHelper::BeginDraw(Renderer, ColorHelper::Black);

	Game::DrawHelper::DrawWireframeRectangle2D(Renderer, Vec2i(100, 100), Vec2i(400, 200), ColorHelper::Blue);

	LinearColor Color = ColorHelper::White;
	if (Keyboard.GetKeyState(SDL_Scancode::SDL_SCANCODE_A) == Game::EButtonState::Held)
	{
		Color = ColorHelper::Red;
	}
	Game::DrawHelper::DrawText2D(Renderer, FontKey, Vec2i(100, 100), L"ABCDEFGHIJK", Color);
	Game::DrawHelper::DrawTexture2D(Renderer, TextureKey, Vec2i(200, 400));

	Game::DrawHelper::EndDraw(Renderer);
}