#include "Window.h"
#include "InputManager.h"

Window::Window(const WindowConstructorParam& ConstructorParam)
	: Window(ConstructorParam.Title, ConstructorParam.PositionX, ConstructorParam.PositionY, ConstructorParam.Width, ConstructorParam.Height)
{
}

Window::Window(const std::wstring& Title, int32_t PositionX, int32_t PositionY, int32_t Width, int32_t Height)
{
	WNDCLASSEX WC;
	WC.cbSize = sizeof(WNDCLASSEX);
	WC.style = CS_HREDRAW | CS_VREDRAW;
	WC.lpfnWndProc = InputManager::WindowMessageHandler;
	WC.cbClsExtra = 0;
	WC.cbWndExtra = 0;
	WC.hInstance = GetModuleHandle(nullptr);
	WC.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WC.hCursor = LoadCursor(NULL, IDC_ARROW);
	WC.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WC.lpszMenuName = NULL;
	WC.lpszClassName = Title.c_str();
	WC.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WC);

	RECT Rect = { 0, 0, Width, Height };
	AdjustWindowRect(&Rect, WS_OVERLAPPEDWINDOW, FALSE);

	WindowHandle_ = CreateWindow(
		Title.c_str(),
		Title.c_str(),
		WS_OVERLAPPEDWINDOW,
		PositionX, PositionY,
		Rect.right - Rect.left, Rect.bottom - Rect.top,
		nullptr,
		nullptr,
		GetModuleHandle(nullptr),
		nullptr
	);

	ShowWindow(WindowHandle_, SW_SHOW);
}

Window::~Window()
{
}
