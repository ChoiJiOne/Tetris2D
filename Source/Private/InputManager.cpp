#include "InputManager.h"

LRESULT InputManager::WindowMessageHandler(HWND WindowHandle, uint32_t Message, WPARAM WParam, LPARAM LParam)
{
	switch (Message)
	{
	case WM_ACTIVATE:
		if (LOWORD(WParam) == WA_INACTIVE)
		{
			bIsActive_ = false;
			HandleWindowEvent(EWindowEvent::INACTIVE);
		}
		else
		{
			bIsActive_ = true;
			HandleWindowEvent(EWindowEvent::ACTIVE);
		}
		break;

	case WM_CLOSE:
		DestroyWindow(WindowHandle);
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
	bool bHaveMessage = true;
	MSG EventMessage = {};

	while (bHaveMessage)
	{
		if (EventMessage.message == WM_QUIT)
		{
			bIsQuit_ = true;
			bHaveMessage = false;
			HandleWindowEvent(EWindowEvent::QUIT);
		}

		if (PeekMessage(&EventMessage, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&EventMessage);
			DispatchMessage(&EventMessage);
		}
		else
		{
			bHaveMessage = false;
		}
	}

	std::memcpy(
		reinterpret_cast<void*>(&PrevKeyboardState_[0]),
		reinterpret_cast<const void*>(&CurrKeyboardState_[0]),
		static_cast<int32_t>(PrevKeyboardState_.size())
	);

	GetKeyboardState(&CurrKeyboardState_[0]);
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
