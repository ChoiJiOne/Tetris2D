#include "Macro.h"
#include "SDLHelper.h"

static bool bIsInitialize = false;
static std::string ExecuteDirectory;

void Game::SDLHelper::Init()
{
	if (!bIsInitialize)
	{
		CHECK((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_EVENTS) == 0), SDL_GetError());

		ExecuteDirectory = SDL_GetBasePath();
		bIsInitialize = true;
	}
}

void Game::SDLHelper::Release()
{
	if (bIsInitialize)
	{
		SDL_Quit();
		bIsInitialize = false;
	}
}

SDL_Window* Game::SDLHelper::CreateSDLWindow(const std::string InTitle, int32_t InX, int32_t InY, int32_t InWidth, int32_t InHeight, uint32_t InFlags)
{
	CheckInitializeSDLHelper();

	SDL_Window* Window = SDL_CreateWindow(
		InTitle.c_str(),
		static_cast<int>(InX),
		static_cast<int>(InY),
		static_cast<int>(InWidth),
		static_cast<int>(InHeight),
		static_cast<Uint32>(InFlags)
	);

	CHECK((Window != nullptr), SDL_GetError());
	return Window;
}

void Game::SDLHelper::DestroySDLWindow(SDL_Window* InWindow)
{
	if (InWindow)
	{
		SDL_DestroyWindow(InWindow);
		InWindow = nullptr;
	}
}

SDL_Renderer* Game::SDLHelper::CreateSDLRenderer(SDL_Window* InWindow)
{
	CheckInitializeSDLHelper();

	SDL_Renderer* Renderer = SDL_CreateRenderer(InWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	CHECK((Renderer != nullptr), SDL_GetError());
	return Renderer;
}

void Game::SDLHelper::DestroySDLRenderer(SDL_Renderer* InRenderer)
{
	if (InRenderer)
	{
		SDL_DestroyRenderer(InRenderer);
		InRenderer = nullptr;
	}
}

std::string Game::SDLHelper::GetExecuteDirectory()
{
	CheckInitializeSDLHelper();

	return ExecuteDirectory;
}

void Game::SDLHelper::SetWindowTitle(SDL_Window* InWindow, const std::string& InTitle)
{
	CheckInitializeSDLHelper();

	SDL_SetWindowTitle(InWindow, InTitle.c_str());
}

void Game::SDLHelper::SetVisibleConsoleWindow(bool bIsShow)
{
	CheckInitializeSDLHelper();

	HWND ConsoleWindowHandle = GetConsoleWindow();
	ShowWindow(ConsoleWindowHandle, bIsShow ? SW_SHOW : SW_HIDE);
}

float Game::SDLHelper::GetWindowAspectRatio(SDL_Window* InWindow)
{
	CheckInitializeSDLHelper();

	float WindowWidth = 0.0f, WindowHeight = 0.0f;
	GetWindowSize<float>(InWindow, WindowWidth, WindowHeight);

	return WindowWidth / WindowHeight;
}

void Game::SDLHelper::CheckInitializeSDLHelper()
{
	if (!bIsInitialize)
	{
		ENFORCE_THROW_EXCEPTION("You are not ready to use SDL. please call SDLHelper::Init()");
	}
}