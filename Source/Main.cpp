#include <cstdint>
#include <memory>

#include <windows.h>


/**
 * @brief 윈도우 메시지 핸들러입니다.
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
LRESULT CALLBACK WindowMessageHandler(HWND WindowHandle, uint32_t Message, WPARAM WParam, LPARAM LParam)
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
 * @brief 테트리스 게임을 초기화 및 실행합니다.
 */
class Tetris
{
public:
	/**
	 * @brief 테트리스 게임의 기본 생성자입니다.
	 */
	Tetris() = default;


	/**
	 * @brief 테트리스 게임의 가상 소멸자입니다.
	 */
	virtual ~Tetris()
	{

	}


	/**
	 * @brief 테트리스 게임을 초기화합니다.
	 */
	void Init()
	{
		WNDCLASSEX WC;
		WC.cbSize = sizeof(WNDCLASSEX);
		WC.style = CS_HREDRAW | CS_VREDRAW;
		WC.lpfnWndProc = WindowMessageHandler;
		WC.cbClsExtra = 0;
		WC.cbWndExtra = 0;
		WC.hInstance = GetModuleHandle(nullptr);
		WC.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		WC.hCursor = LoadCursor(NULL, IDC_ARROW);
		WC.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		WC.lpszMenuName = NULL;
		WC.lpszClassName = L"Tetris2D";
		WC.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		RegisterClassEx(&WC);

		RECT Rect = { 0, 0, 800, 600 };
		AdjustWindowRect(&Rect, WS_OVERLAPPEDWINDOW, FALSE);

		HWND WindowHandle = CreateWindow(
			L"Tetris2D",
			L"Tetris2D",
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
			CW_USEDEFAULT, CW_USEDEFAULT,
			Rect.right - Rect.left, Rect.bottom - Rect.top,
			nullptr,
			nullptr,
			GetModuleHandle(nullptr),
			nullptr
		);

		ShowWindow(WindowHandle, SW_SHOW);
	}


	/**
	 * @brief 테트리스 게임을 실행합니다.
	 */
	void Run()
	{
		MSG msg = { 0 };
		while (WM_QUIT != msg.message)
		{
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{

			}
		}
	}


private:
	/**
	 * @brief 윈도우 창 핸들러입니다.
	 * 
	 * @see https://learn.microsoft.com/ko-kr/windows/win32/learnwin32/creating-a-window
	 */
	HWND WindowHandle_ = nullptr;
};


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
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR CmdLine, int32_t CmdShow)
{
	auto Game = std::make_unique<Tetris>();
	Game->Init();
	Game->Run();

	return 0;
}