#include "WindowEvent.h"

#include <unordered_map>


/**
 * @brief 윈도우 이벤트에 대응하는 콜백 이벤트입니다.
 */
static std::unordered_map<EWindowEvent, std::function<void()>> WindowCallbackEvents;


/**
 * @brief 이벤트 처리를 위한 윈도우 핸들 값입니다.
 */
static HWND CurrentWindowHandle = nullptr;


/**
 * @brief 윈도우 이벤트에 대응하는 콜백 이벤트를 실행합니다.
 * 
 * @param WindowEvent 콜백 이벤트를 실행할 윈도우 이벤트입니다.
 */
void ExecuteWindowCallbackEvent(const EWindowEvent& WindowEvent);


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
LRESULT CALLBACK WindowMessageHandler(HWND WindowHandle, uint32 Message, WPARAM WParam, LPARAM LParam);


WindowMessageHandlerPtr GetWindowMessageHandlerPtr()
{
	return WindowMessageHandler;
}

HWND GetEventTargetWindowHandle()
{
	return CurrentWindowHandle;
}

void BindWindowCallbackEvent(const EWindowEvent& WindowEvent, const std::function<void()>& CallbackEvent)
{
	WindowCallbackEvents.insert({ WindowEvent , CallbackEvent });
}

void PollWindowEvent()
{
	MSG Message = {};

	while (PeekMessage(&Message, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
}

void ExecuteWindowCallbackEvent(const EWindowEvent& WindowEvent)
{
	if (WindowCallbackEvents.find(WindowEvent) != WindowCallbackEvents.end())
	{
		WindowCallbackEvents.at(WindowEvent)();
	}
}

LRESULT CALLBACK WindowMessageHandler(HWND WindowHandle, uint32 Message, WPARAM WParam, LPARAM LParam)
{
	EWindowEvent WindowEvent = EWindowEvent::NONE;

	switch (Message)
	{
	case WM_CREATE:
		CurrentWindowHandle = WindowHandle;
		break;

	case WM_ACTIVATE:
		WindowEvent = (LOWORD(WParam) == WA_INACTIVE) ? EWindowEvent::INACTIVE : EWindowEvent::ACTIVE;
		break;

	case WM_SIZE:
		switch (WParam)
		{
		case SIZE_MINIMIZED:
			WindowEvent = EWindowEvent::MINIMZED;
			break;

		case SIZE_MAXIMIZED:
			WindowEvent = EWindowEvent::MAXIMIZED;
			break;

		case SIZE_RESTORED:
			WindowEvent = EWindowEvent::RESIZE;
			break;

		case SIZE_MAXHIDE:
			WindowEvent = EWindowEvent::MAXHIDE;
			break;

		case SIZE_MAXSHOW:
			WindowEvent = EWindowEvent::MAXSHOW;
			break;
		}
		break;

	case WM_ENTERSIZEMOVE:
		WindowEvent = EWindowEvent::ENTERSIZEMOVE;
		break;

	case WM_EXITSIZEMOVE:
		WindowEvent = EWindowEvent::EXITSIZEMOVE;
		break;

	case WM_LBUTTONDOWN:
		WindowEvent = EWindowEvent::LBUTTONDOWN;
		break;

	case WM_LBUTTONUP:
		WindowEvent = EWindowEvent::LBUTTONUP;
		break;

	case WM_RBUTTONDOWN:
		WindowEvent = EWindowEvent::RBUTTONDOWN;
		break;

	case WM_RBUTTONUP:
		WindowEvent = EWindowEvent::RBUTTONUP;
		break;

	case WM_MOUSEMOVE:
		WindowEvent = EWindowEvent::MOUSEMOVE;
		break;

	case WM_CLOSE:
		DestroyWindow(WindowHandle);
		WindowEvent = EWindowEvent::CLOSE;
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(WindowHandle, Message, WParam, LParam);
	}

	ExecuteWindowCallbackEvent(WindowEvent);
	return 0;
}