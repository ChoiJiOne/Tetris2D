#include "InputManager.h"
#include "Utils.hpp"

LRESULT InputManager::ProcessWindowMessage(HWND WindowHandle, uint32_t Message, WPARAM WParam, LPARAM LParam)
{
	EWindowEvent WindowEvent = EWindowEvent::NONE;

	switch (Message)
	{
	case WM_CREATE:
		WindowHandle_ = WindowHandle;
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

		default:
			ENFORCE_THROW_EXCEPTION("undefined WM_SIZE event");
		}
		break;

	case WM_ENTERSIZEMOVE:
		bIsResizing_ = true;
		WindowEvent = EWindowEvent::ENTERSIZEMOVE;
		break;

	case WM_EXITSIZEMOVE:
		bIsResizing_ = false;
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
		WindowEvent = EWindowEvent::CLOSE;
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(WindowHandle, Message, WParam, LParam);
	}

	HandleWindowEvent(WindowEvent);
	return 0;
}

void InputManager::BindWindowEvent(const EWindowEvent& WindowEvent, const std::function<void()>& EventCallback)
{
	WindowEvents_.insert({ WindowEvent, EventCallback });
}

void InputManager::UnbindWindowEvent(const EWindowEvent& WindowEvent)
{
	RemoveValue<EWindowEvent, std::function<void()>>(WindowEvent, WindowEvents_);
}

void InputManager::Tick()
{
	PollEventMessage();
	UpdateKeyboardState();
	UpdateMousePosition();
}

EPressState InputManager::GetKeyPressState(const EKeyCode& KeyCode) const
{
	EPressState PressState = EPressState::NONE;

	if (IsPressKey(PrevKeyboardState_, KeyCode))
	{
		if (IsPressKey(CurrKeyboardState_, KeyCode))
		{
			PressState = EPressState::HELD;
		}
		else
		{
			PressState = EPressState::RELEASED;
		}
	}
	else
	{
		if (IsPressKey(CurrKeyboardState_, KeyCode))
		{
			PressState = EPressState::PRESSED;
		}
		else
		{
			PressState = EPressState::NONE;
		}
	}

	return PressState;
}

InputManager::InputManager()
	: PrevKeyboardState_(256, 0)
	, CurrKeyboardState_(256, 0)
{
}

void InputManager::PollEventMessage()
{
	MSG EventMessage = {};

	while (PeekMessage(&EventMessage, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&EventMessage);
		DispatchMessage(&EventMessage);
	}
}

void InputManager::UpdateKeyboardState()
{
	std::copy(CurrKeyboardState_.begin(), CurrKeyboardState_.end(), PrevKeyboardState_.begin());

	CHECK(GetKeyboardState(&CurrKeyboardState_[0]), "failed to get keyboard state");
}

bool InputManager::IsPressKey(const std::vector<uint8_t>& KeyboardState, const EKeyCode& KeyCode) const
{
	return (KeyboardState[static_cast<int32_t>(KeyCode)] & 0x80);
}

Vec2i InputManager::GetMousePositionFromScreen()
{
	POINT MousePosition;
	CHECK(GetCursorPos(&MousePosition), "failed to get current mouse position");

	return Vec2i(static_cast<int32_t>(MousePosition.x), static_cast<int32_t>(MousePosition.y));
}

Vec2i InputManager::GetMousePositionFromWindow()
{
	POINT MousePosition;
	
	CHECK(GetCursorPos(&MousePosition), "failed to get current mouse position");
	CHECK(ScreenToClient(WindowHandle_, &MousePosition), "failed to convert mouse position");

	return Vec2i(static_cast<int32_t>(MousePosition.x), static_cast<int32_t>(MousePosition.y));
}

void InputManager::UpdateMousePosition()
{
	PrevScreenMousePosition_ = CurrScreenMousePosition_;
	PrevWindowMousePosition_ = CurrWindowMousePosition_;

	CurrScreenMousePosition_ = GetMousePositionFromScreen();
	CurrWindowMousePosition_ = GetMousePositionFromWindow();
}

void InputManager::HandleWindowEvent(const EWindowEvent& WindowEvent)
{
	if (IsExistKey<EWindowEvent, std::function<void()>>(WindowEvent, WindowEvents_))
	{
		WindowEvents_.at(WindowEvent)();
	}
}
