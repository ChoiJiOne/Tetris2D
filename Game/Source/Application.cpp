#include "Type.h"

#include <string>
#include <windows.h>

#pragma warning(disable: 28251)


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
LRESULT CALLBACK WindowProc(HWND WindowHandle, uint32_t Message, WPARAM WParam, LPARAM LParam)
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


/**
 * @brief Windows ���ø����̼� �������Դϴ�.
 *
 * @see https://learn.microsoft.com/ko-kr/windows/win32/learnwin32/winmain--the-application-entry-point
 *
 * @param hInstance �ν��Ͻ��� ���� �ڵ��Դϴ�.
 * @param hPrevInstance �ƹ� �ǹ� ���� �Ķ�����Դϴ�.
 * @param CmdLine ������ �μ��Դϴ�.
 * @param CmdShow �⺻ ���ø����̼� â�� �ּ�ȭ����, �ִ�ȭ���� �Ǵ� ���������� ǥ�������� ��Ÿ���� �÷����Դϴ�.
 *
 * @return �ٸ� ���α׷��� ������ �� �ִ� ���� �ڵ带 ��ȯ�մϴ�.
 */
int32 WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR CmdLine, int32 CmdShow)
{
	WNDCLASSEXW WC = {};

	WC.cbSize         = sizeof(WNDCLASSEXW);
	WC.style          = CS_HREDRAW | CS_VREDRAW;
	WC.lpfnWndProc    = WindowProc;
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

	MSG Message;

	while (TRUE)
	{
		while (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		if (Message.message == WM_QUIT)
			break;
	}

	return static_cast<int32>(Message.wParam);
}