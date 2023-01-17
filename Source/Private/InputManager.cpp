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
	MSG CurrentMessage = {};

	while (bHaveMessage && !bIsDetectQuitMessage)
	{
		if (CurrentMessage.message == WM_QUIT)
		{
			bIsDetectQuitMessage = true;
			bHaveMessage = false;

		}

		if (PeekMessage(&CurrentMessage, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&CurrentMessage);
			DispatchMessage(&CurrentMessage);
		}
		else
		{
			bHaveMessage = false;
		}
	}
}
