#include "GameMacro.h"
#include "GameSDLUtility.h"

bool bIsInitialize = false;
static std::string ExecuteDirectory;

void Game::SDLUtility::Init()
{
	if (!bIsInitialize)
	{
		CHECK_SDL_FAILED((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_EVENTS) == 0));

		ExecuteDirectory = SDL_GetBasePath();
		bIsInitialize = true;
	}
}

void Game::SDLUtility::Release()
{
	if (bIsInitialize)
	{
		SDL_Quit();
		bIsInitialize = false;
	}
}

SDL_Window* Game::SDLUtility::CreateSDLWindow(const std::string InTitle, int32_t InX, int32_t InY, int32_t InWidth, int32_t InHeight, uint32_t InFlags)
{
	CheckInitializeSDLUtility();

	SDL_Window* Window = SDL_CreateWindow(
		InTitle.c_str(),
		static_cast<int>(InX),
		static_cast<int>(InY),
		static_cast<int>(InWidth),
		static_cast<int>(InHeight),
		static_cast<Uint32>(InFlags)
	);

	CHECK_SDL_FAILED((Window != nullptr));
	return Window;
}

void Game::SDLUtility::DestroySDLWindow(SDL_Window* InWindow)
{
	if (InWindow)
	{
		SDL_DestroyWindow(InWindow);
		InWindow = nullptr;
	}
}

SDL_Renderer* Game::SDLUtility::CreateSDLRenderer(SDL_Window* InWindow)
{
	CheckInitializeSDLUtility();

	SDL_Renderer* Renderer = SDL_CreateRenderer(InWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	CHECK_SDL_FAILED((Renderer != nullptr));
	return Renderer;
}

void Game::SDLUtility::DestroySDLRenderer(SDL_Renderer* InRenderer)
{
	if (InRenderer)
	{
		SDL_DestroyRenderer(InRenderer);
		InRenderer = nullptr;
	}
}

std::string Game::SDLUtility::GetExecuteDirectory()
{
	CheckInitializeSDLUtility();

	return ExecuteDirectory;
}

void Game::SDLUtility::SetWindowTitle(SDL_Window* InWindow, const std::string& InTitle)
{
	CheckInitializeSDLUtility();

	SDL_SetWindowTitle(InWindow, InTitle.c_str());
}

void Game::SDLUtility::SetVisibleConsoleWindow(bool bIsShow)
{
	CheckInitializeSDLUtility();

	HWND ConsoleWindowHandle = GetConsoleWindow();
	ShowWindow(ConsoleWindowHandle, bIsShow ? SW_SHOW : SW_HIDE);
}

float Game::SDLUtility::GetWindowAspectRatio(SDL_Window* InWindow)
{
	CheckInitializeSDLUtility();

	float WindowWidth = 0.0f, WindowHeight = 0.0f;
	GetWindowSize<float>(InWindow, WindowWidth, WindowHeight);

	return WindowWidth / WindowHeight;
}

void Game::SDLUtility::CheckInitializeSDLUtility()
{
	if (!bIsInitialize)
	{
		ENFORCE_THROW_EXCEPTION("You are not ready to use SDL. please call SDLUtility::Init()");
	}
}