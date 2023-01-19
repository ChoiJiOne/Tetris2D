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
	return InputManager::Get().WindowMessageHandler(WindowHandle, Message, WParam, LParam);
}

Window::Window(const WindowConstructorParam& ConstructorParam)
	: Window(ConstructorParam.Title, ConstructorParam.PositionX, ConstructorParam.PositionY, ConstructorParam.Width, ConstructorParam.Height)
{
}

Window::Window(const std::wstring& Title, int32_t PositionX, int32_t PositionY, int32_t Width, int32_t Height)
{
	WNDCLASSEX WC;
	WC.cbSize = sizeof(WNDCLASSEX);
	WC.style = CS_HREDRAW | CS_VREDRAW;
	WC.lpfnWndProc = WindowProc;
	WC.cbClsExtra = 0;
	WC.cbWndExtra = 0;
	WC.hInstance = GetModuleHandle(nullptr);
	WC.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	WC.hCursor = LoadCursor(nullptr, IDC_ARROW);
	WC.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WC.lpszMenuName = nullptr;
	WC.lpszClassName = Title.c_str();
	WC.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	CHECK((RegisterClassEx(&WC) != 0), "failed to register window class");

	RECT Rect = { 0, 0, Width, Height };
	CHECK(AdjustWindowRect(&Rect, WS_OVERLAPPEDWINDOW, false), "failed to adjust window size");

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
	CHECK((WindowHandle_ != nullptr), "failed to create window");

	CHECK(ShowWindow(WindowHandle_, SW_SHOW) == 0, "failed to show window");
}

Window::~Window()
{
}