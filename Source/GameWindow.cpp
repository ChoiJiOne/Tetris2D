#include "../Public/Macro.h"
#include "../Public/GameWindow.h"

GameWindow::~GameWindow()
{
	DestroyWindow();
}

void GameWindow::CreateWindow(const std::string InTitle, int32_t InX, int32_t InY, int32_t InWidth, int32_t InHeight, uint32_t InFlags)
{
	if (!Window)
	{
		Window = SDL_CreateWindow(
			InTitle.c_str(),
			static_cast<int>(InX),
			static_cast<int>(InY),
			static_cast<int>(InWidth),
			static_cast<int>(InHeight),
			static_cast<Uint32>(InFlags)
		);

		CHECK_SDL_FAILED((Window != nullptr));
	}
}

void GameWindow::DestroyWindow()
{
	if (Window)
	{
		SDL_DestroyWindow(Window);
		Window = nullptr;
	}
}

SDL_Window* GameWindow::GetWindow() noexcept
{
	return Window;
}

void GameWindow::SetWindowTitle(const std::string& InTitle) noexcept
{
	SDL_SetWindowTitle(Window, InTitle.c_str());
}

void GameWindow::SetVisibleConsoleWindow(bool bIsShow) noexcept
{
	HWND ConsoleWindowHandle = GetConsoleWindow();
	ShowWindow(ConsoleWindowHandle, bIsShow ? SW_SHOW : SW_HIDE);
}