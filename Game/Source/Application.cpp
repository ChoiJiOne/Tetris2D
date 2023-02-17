#include "Type.h"
#include "WindowEvent.h"

#include <string>
#include <windows.h>

#pragma warning(disable: 28251)


/**
 * @brief Windows 애플리케이션 진입점입니다.
 *
 * @see https://learn.microsoft.com/ko-kr/windows/win32/learnwin32/winmain--the-application-entry-point
 *
 * @param hInstance 인스턴스에 대한 핸들입니다.
 * @param hPrevInstance 아무 의미 없는 파라미터입니다.
 * @param CmdLine 명령줄 인수입니다.
 * @param CmdShow 기본 애플리케이션 창을 최소화할지, 최대화할지 또는 정상적으로 표시할지를 나타내는 플래그입니다.
 *
 * @return 다른 프로그램에 전달할 수 있는 상태 코드를 반환합니다.
 */
int32 WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR CmdLine, int32 CmdShow)
{
	WNDCLASSEXW WC = {};

	WC.cbSize         = sizeof(WNDCLASSEXW);
	WC.style          = CS_HREDRAW | CS_VREDRAW;
	WC.lpfnWndProc    = GetWindowMessageHandlerPtr();
	WC.cbClsExtra     = 0;
	WC.cbWndExtra     = 0;
	WC.hInstance      = GetModuleHandle(nullptr);
	WC.hIcon          = LoadIcon(nullptr, IDI_APPLICATION);
	WC.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	WC.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
	WC.lpszMenuName   =  nullptr;
	WC.lpszClassName  = L"Tetris2D";
	WC.hIconSm        = LoadIcon(nullptr, IDI_APPLICATION);

	RegisterClassExW(&WC);

	HWND WindowHandle = CreateWindowW(
		L"Tetris2D",
		L"Tetris2D",
		WS_OVERLAPPEDWINDOW,
		200, 200, 1000, 800,
		nullptr,
		nullptr,
		GetModuleHandle(nullptr),
		nullptr
	);

	ShowWindow(WindowHandle, SW_SHOW);

	bool bIsDone = false;
	BindWindowCallbackEvent(EWindowEvent::CLOSE, [&]() {
		bIsDone = true;
	});

	while (!bIsDone)
	{
		PollWindowEvent();
	}

	return 0;
}