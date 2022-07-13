#include "SDLHelper.h"
#include "ResourceHelper.h"
#include "StringHelper.h"
#include "Texture2D.h"
#include "Font.h"

#include "Tetris2D.h"

Tetris2D::~Tetris2D()
{
	Game::ResourceHelper::Cleanup();
	Game::SDLHelper::Release();
}

void Tetris2D::Setup()
{
	// 프레임워크를 초기화합니다.
	Game::SDLHelper::Init();


	// SDL 윈도우를 생성합니다.
	int32_t WindowWidth  = 600;
	int32_t WindowHeight = 720;

	Game::WindowConstructParams WindowParams;
	WindowParams.Title = "Tetris2D";
	WindowParams.w = WindowWidth;
	WindowParams.h = WindowHeight;
	WindowParams.Flags |= SDL_WINDOW_ALLOW_HIGHDPI;

	Window.Initialize(WindowParams);


	// SDL 렌더러를 생성합니다.
	Graphics2D.Initialize(Window.GetSDLWindow());


	// 폰트를 생성합니다. (TODO : 폰트 리소스 경로 수정 필요)
	std::string FontPath = Game::SDLHelper::GetExecuteDirectory() + "../../../../Resource/Font/kenvector_future.ttf";
	FontKey = Game::StringHelper::GetHash("Font");
	Game::ResourceHelper::CreateFont(Graphics2D.GetRenderer(), FontKey, FontPath, 40.0f);

	
	// 텍스처를 생성합니다. (TODO : 텍스처 리소스 경로 수정 필요)
	std::string TexturePath = Game::SDLHelper::GetExecuteDirectory() + "../../../../Resource/Texture/Block/BlueBlockFX.png";
	TextureKey = Game::StringHelper::GetHash("Texture");
	Game::ResourceHelper::CreateTexture2D(Graphics2D.GetRenderer(), TextureKey, TexturePath);
}

void Tetris2D::Run()
{
	GameTimer.Reset();

	while (!bIsDoneLoop)
	{
		GameTimer.Tick();

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
	Graphics2D.BeginFrame(Game::ColorHelper::Black);

	Graphics2D.DrawRect2D(Game::Vec2i(100, 100), Game::Vec2i(400, 200), Game::ColorHelper::Blue);

	Game::LinearColor Color = Game::ColorHelper::White;
	if (Keyboard.GetKeyState(SDL_Scancode::SDL_SCANCODE_A) == Game::EButtonState::Held)
	{
		Color = Game::ColorHelper::Red;
	}
	Graphics2D.DrawText2D(FontKey, Game::Vec2i(100, 100), L"ABCDEFGHIJK", Color);
	Graphics2D.DrawTexture2D(TextureKey, Game::Vec2i(200, 400));

	Graphics2D.EndFrame();
}