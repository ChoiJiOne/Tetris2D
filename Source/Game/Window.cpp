// @third party code - BEGIN SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
// @third party code - END

#include "Macro.h"
#include "Window.h"

namespace Game
{
	Window::~Window()
	{
		if (SDLWindow)
		{
			SDL_DestroyWindow(SDLWindow);
			SDLWindow = nullptr;
		}
	}

	void Window::Initialize(const WindowConstructParams& InInWindowConstructParams)
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

	float Window::GetWindowAspectRatio()
	{
		float WindowWidth = 0.0f, WindowHeight = 0.0f;
		GetWindowSize<float>(WindowWidth, WindowHeight);

		return WindowWidth / WindowHeight;
	}

	void Window::SetWindowTitle(const char* InTitle)
	{
		SDL_SetWindowTitle(SDLWindow, InTitle);
	}
}