#include "Window.h"
#include "InputManager.h"

/**
 * @brief 윈도우 메시지 핸들러입니다.
 *
 * @note 내부의 윈도우 메시지 핸들러를 호출합니다.
 *
 * @see https://learn.microsoft.com/ko-kr/windows/win32/learnwin32/writing-the-window-procedure
 *
 * @param WindowHandle 윈도우 창에 대한 핸들입니다.
 * @param Message 윈도우 메시지 코드입니다.
 * @param WParam 윈도우 메시지의 추가 데이터입니다.
 * @param LParam 윈도우 메시지의 추가 데이터입니다.
 *
 * @return 윈도우에 반환할 값입니다.
 */
LRESULT CALLBACK WindowProc(HWND WindowHandle, uint32_t Message, WPARAM WParam, LPARAM LParam)
{
	return InputManager::Get().ProcessWindowMessage(WindowHandle, Message, WParam, LParam);
}

Window::Window(const WindowConstructorParam& ConstructorParam)
	: Window(ConstructorParam.Title, ConstructorParam.PositionX, ConstructorParam.PositionY, ConstructorParam.Width, ConstructorParam.Height, ConstructorParam.bIsFullScreen)
{
}

Window::Window(const std::wstring& Title, int32_t PositionX, int32_t PositionY, int32_t Width, int32_t Height, bool bIsFullScreen)
	: bIsFullScreen_(bIsFullScreen)
{
	RegisterWindowClass(Title);

	DWORD WindowStyle = WS_VISIBLE;
	int32_t WindowPositionX = 0;
	int32_t WindowPositionY = 0;
	int32_t WindowWidth = 0;
	int32_t WindowHeight = 0;

	if (bIsFullScreen_)
	{
		WindowWidth = GetSystemMetrics(SM_CXSCREEN);
		WindowHeight = GetSystemMetrics(SM_CYSCREEN);
		WindowStyle |= WS_POPUP;

		DEVMODE ScreenSettings = {};

		ScreenSettings.dmSize = sizeof(DEVMODE);
		ScreenSettings.dmPelsWidth = static_cast<DWORD>(WindowWidth);
		ScreenSettings.dmPelsHeight = static_cast<DWORD>(WindowHeight);
		ScreenSettings.dmBitsPerPel = 32;
		ScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&ScreenSettings, CDS_FULLSCREEN);
	}
	else
	{
		RECT Rect = { 0, 0, Width, Height };
		CHECK(AdjustWindowRect(&Rect, WS_OVERLAPPEDWINDOW | WS_VISIBLE, false), "failed to adjust window size");

		WindowStyle |= WS_OVERLAPPEDWINDOW;
		WindowPositionX = PositionX;
		WindowPositionY = PositionY;
		WindowWidth = Rect.right - Rect.left;
		WindowHeight = Rect.bottom - Rect.top;
	}

	WindowHandle_ = CreateWindowW(
		Title.c_str(),
		Title.c_str(),
		WindowStyle,
		WindowPositionX, WindowPositionY, WindowWidth, WindowHeight,
		nullptr,
		nullptr,
		GetModuleHandle(nullptr),
		nullptr
	);

	CHECK((WindowHandle_ != nullptr), "failed to create window");
}

Window::~Window()
{
	if (WindowHandle_)
	{
		DestroyWindow(WindowHandle_);
	}
}

void Window::RegisterWindowClass(const std::wstring& ClassTitle)
{
	WNDCLASSEXW WindowClass = {};

	WindowClass.cbSize = sizeof(WNDCLASSEXW);
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpfnWndProc = WindowProc;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hInstance = GetModuleHandle(nullptr);
	WindowClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	WindowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	WindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WindowClass.lpszMenuName = nullptr;
	WindowClass.lpszClassName = ClassTitle.c_str();
	WindowClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	CHECK((RegisterClassExW(&WindowClass) != 0), "failed to register window class");
}