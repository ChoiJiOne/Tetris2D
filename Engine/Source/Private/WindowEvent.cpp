#include "WindowEvent.h"

#include <unordered_map>


/**
 * @brief ������ �̺�Ʈ�� �����ϴ� �ݹ� �̺�Ʈ�Դϴ�.
 */
static std::unordered_map<EWindowEvent, std::function<void()>> WindowCallbackEvents;


/**
 * @brief �̺�Ʈ ó���� ���� ������ �ڵ� ���Դϴ�.
 */
static HWND CurrentWindowHandle = nullptr;


/**
 * @brief ������ �̺�Ʈ�� �����ϴ� �ݹ� �̺�Ʈ�� �����մϴ�.
 * 
 * @param WindowEvent �ݹ� �̺�Ʈ�� ������ ������ �̺�Ʈ�Դϴ�.
 */
void ExecuteWindowCallbackEvent(const EWindowEvent& WindowEvent);


/**
 * @brief ������ �޽��� �ڵ鷯�Դϴ�.
 *
 * @note ������ ������ �޽��� �ڵ鷯�� ȣ���մϴ�.
 *
 * @see https://learn.microsoft.com/ko-kr/windows/win32/learnwin32/writing-the-window-procedure
 *
 * @param WindowHandle ������ â�� ���� �ڵ��Դϴ�.
 * @param Message ������ �޽��� �ڵ��Դϴ�.
 * @param WParam ������ �޽����� �߰� �������Դϴ�.
 * @param LParam ������ �޽����� �߰� �������Դϴ�.
 *
 * @return �����쿡 ��ȯ�� ���Դϴ�.
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