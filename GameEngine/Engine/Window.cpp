#include "Macro.h"
#include "Window.h"

Game::Window::~Window()
{
	if (SDLWindow)
	{
		SDL_DestroyWindow(SDLWindow);
		SDLWindow = nullptr;
	}
}

void Game::Window::Create(const WindowConstructParams& InInWindowConstructParams)
{
	SDLWindow = SDL_CreateWindow(
		InInWindowConstructParams.Title,
		InInWindowConstructParams.x,
		InInWindowConstructParams.y,
		InInWindowConstructParams.w,
		InInWindowConstructParams.h,
		InInWindowConstructParams.Flags
	);

	CHECK((SDLWindow != nullptr), SDL_GetError());
}

float Game::Window::GetWindowAspectRatio()
{
	float WindowWidth = 0.0f, WindowHeight = 0.0f;
	GetWindowSize<float>(WindowWidth, WindowHeight);

	return WindowWidth / WindowHeight;
}

void Game::Window::SetWindowTitle(const char* InTitle)
{
	SDL_SetWindowTitle(SDLWindow, InTitle);
}