#include "../Public/GameInput.h"
#include "../Public/GameRenderer.h"
#include "../Public/GameWindow.h"
#include "../Public/Macro.h"
#include "../Public/GameEngine.h"

// 게임 프레임워크 초기화 여부입니다.
bool GameEngine::bIsInitialize = false;


// 게임 프레임워크가 소유하는 윈도우입니다.
std::unique_ptr<GameWindow> GameEngine::Window = nullptr;


// 게임 프레임워크가 소유하는 입력 시스템입니다.
std::unique_ptr<GameInput> GameEngine::Input = nullptr;


// 게임 프레임워크가 소유하고 있는 렌더러 입니다.
std::unique_ptr<GameRenderer> GameEngine::Renderer = nullptr;


// 실행 파일 경로입니다.
std::string GameEngine::ExecuteDirectory;


// 게임 프로젝트의 루트 디렉토리입니다.
std::string GameEngine::ProjectRootDirectory;


// 게임 엔진 디렉토리입니다.
std::string GameEngine::EngineDirectory;


// 게임 리소스 디렉토리입니다.
std::string GameEngine::ResourceDirectory;


// SDL2의 컴파일 버전입니다.
SDL_version GameEngine::CompiledVersion;


// SDL2의 링크 버전입니다.
SDL_version GameEngine::LinkedVersion;


void GameEngine::Init()
{
	if (!bIsInitialize)
	{
		ExecuteDirectory     = SDL_GetBasePath();
		ProjectRootDirectory = ExecuteDirectory + "../../../../";
		EngineDirectory      = ExecuteDirectory + "../../../../GameEngine/";
		ResourceDirectory    = ExecuteDirectory + "../../../../Resource/";

		CHECK_SDL_FAILED((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_EVENTS) == 0));

		SDL_VERSION(&CompiledVersion);
		SDL_GetVersion(&LinkedVersion);


		// 디버그 모드일 경우, 콘솔 창을 표시합니다.
#if defined(DEBUG) || defined(_DEBUG)
		GetGameWindow().SetVisibleConsoleWindow(true);
#else
		GetGameWindow().SetVisibleConsoleWindow(false);
#endif

		bIsInitialize = true;
	}
}

void GameEngine::Release()
{
	if (bIsInitialize)
	{
		Window.reset();
		Input.reset();
		Renderer.reset();

		SDL_Quit();

		bIsInitialize = false;
	}
}

GameWindow& GameEngine::GetGameWindow()
{
	if (Window == nullptr)
	{
		Window = std::make_unique<GameWindow>();
	}

	return *Window;
}

GameInput& GameEngine::GetGameInput()
{
	if (Input == nullptr)
	{
		Input = std::make_unique<GameInput>();
	}

	return *Input;
}

GameRenderer& GameEngine::GetGameRenderer()
{
	if (Renderer == nullptr)
	{
		Renderer = std::make_unique<GameRenderer>();
	}

	return *Renderer;
}
