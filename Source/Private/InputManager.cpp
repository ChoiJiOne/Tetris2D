#include "InputManager.h"

LRESULT CALLBACK InputManager::WindowMessageHandler(HWND WindowHandle, uint32_t Message, WPARAM WParam, LPARAM LParam)
{
	switch (Message)
	{
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

void InputManager::Tick()
{
	bool bHaveMessage = true;
	MSG EventMessage = {};

	while (bHaveMessage)
	{
		if (EventMessage.message == WM_QUIT)
		{
			bIsDetectQuitMessage = true;
			bHaveMessage = false;
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
