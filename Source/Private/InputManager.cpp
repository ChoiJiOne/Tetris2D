#include "InputManager.h"

LRESULT InputManager::WindowMessageHandler(HWND WindowHandle, uint32_t Message, WPARAM WParam, LPARAM LParam)
{
	switch (Message)
	{
	case WM_ACTIVATE:
		if (LOWORD(WParam) == WA_INACTIVE)
		{
			HandleWindowEvent(EWindowEvent::INACTIVE);
		}
		else
		{
			HandleWindowEvent(EWindowEvent::ACTIVE);
		}
		break;

	case WM_SIZE:
		HandleWindowEvent(EWindowEvent::RESIZE);
		break;

	case WM_CLOSE:
		DestroyWindow(WindowHandle);

		HandleWindowEvent(EWindowEvent::CLOSE);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(WindowHandle, Message, WParam, LParam);
	}

	return 0;
}

void InputManager::RegisterWindowEvent(const EWindowEvent& WindowEvent, const std::function<void()>& EventCallback)
{
	WindowEvents_.insert({ WindowEvent, EventCallback });
}

void InputManager::UnregisterWindowEvent(const EWindowEvent& WindowEvent)
{
	if (WindowEvents_.find(WindowEvent) != WindowEvents_.end())
	{
		WindowEvents_.erase(WindowEvent);
	}
}

void InputManager::Tick()
{
	PollEventMessage();
	UpdateKeyboardState();
}

EPressState InputManager::GetKeyPressState(int32_t KeyCode) const
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
	std::copy(PrevKeyboardState_.begin(), PrevKeyboardState_.end(), CurrKeyboardState_.begin());

	CHECK(GetKeyboardState(&CurrKeyboardState_[0]), "failed to get keyboard state");
}

bool InputManager::IsPressKey(const std::vector<uint8_t>& KeyboardState, int32_t KeyCode) const
{
	return (KeyboardState[KeyCode] & 0x80);
}

void InputManager::HandleWindowEvent(const EWindowEvent& WindowEvent)
{
	if (WindowEvents_.find(WindowEvent) != WindowEvents_.end())
	{
		WindowEvents_.at(WindowEvent)();
	}
}
