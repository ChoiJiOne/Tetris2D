#include "WindowEventHandler.h"

std::unordered_map<WindowEventHandler::EEventType, std::function<void()>> WindowEventHandler::WindowCallbackEvents_;
HWND WindowEventHandler::CurrentWindowHandle_ = nullptr;

void WindowEventHandler::BindCallbackEvent(const WindowEventHandler::EEventType& WindowEvent, const std::function<void()>& CallbackEvent)
{
	WindowCallbackEvents_.insert({ WindowEvent , CallbackEvent });
}

LRESULT WindowEventHandler::ProcessWindowMessage(HWND WindowHandle, uint32_t Message, WPARAM WParam, LPARAM LParam)
{
	EEventType WindowEvent = EEventType::NONE;

	switch (Message)
	{
	case WM_CREATE:
		CurrentWindowHandle_ = WindowHandle;
		break;

	case WM_ACTIVATE:
		WindowEvent = (LOWORD(WParam) == WA_INACTIVE) ? EEventType::INACTIVE : EEventType::ACTIVE;
		break;

	case WM_SIZE:
		switch (WParam)
		{
		case SIZE_MINIMIZED:
			WindowEvent = EEventType::MINIMZED;
			break;

		case SIZE_MAXIMIZED:
			WindowEvent = EEventType::MAXIMIZED;
			break;

		case SIZE_RESTORED:
			WindowEvent = EEventType::RESIZE;
			break;

		case SIZE_MAXHIDE:
			WindowEvent = EEventType::MAXHIDE;
			break;

		case SIZE_MAXSHOW:
			WindowEvent = EEventType::MAXSHOW;
			break;
		}
		break;

	case WM_ENTERSIZEMOVE:
		WindowEvent = EEventType::ENTERSIZEMOVE;
		break;

	case WM_EXITSIZEMOVE:
		WindowEvent = EEventType::EXITSIZEMOVE;
		break;

	case WM_LBUTTONDOWN:
		WindowEvent = EEventType::LBUTTONDOWN;
		break;

	case WM_LBUTTONUP:
		WindowEvent = EEventType::LBUTTONUP;
		break;

	case WM_RBUTTONDOWN:
		WindowEvent = EEventType::RBUTTONDOWN;
		break;

	case WM_RBUTTONUP:
		WindowEvent = EEventType::RBUTTONUP;
		break;

	case WM_MOUSEMOVE:
		WindowEvent = EEventType::MOUSEMOVE;
		break;

	case WM_CLOSE:
		DestroyWindow(WindowHandle);
		WindowEvent = EEventType::CLOSE;
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

void WindowEventHandler::PollEventQueue()
{
	MSG Message = {};

	while (PeekMessage(&Message, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
}

void WindowEventHandler::ExecuteWindowCallbackEvent(const EEventType& WindowEvent)
{
	if (WindowCallbackEvents_.find(WindowEvent) != WindowCallbackEvents_.end())
	{
		WindowCallbackEvents_.at(WindowEvent)();
	}
}