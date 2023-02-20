#include "ErrorHandler.h"
#include "Window.h"
#include "WindowEventHandler.h"


/**
 * @brief 애플케이션을 실행합니다.
 * 
 * @param Argc 명령행 인자의 수입니다.
 * @param Argv 명령행 인자입니다.
 * 
 * @throws 애플리케이션 실행 중 에러 발생 시 예외를 던집니다.
 */
void RunApplication(int32_t Argc, char** Argv)
{
	std::unique_ptr<Window> MainWindow = std::make_unique<Window>(L"Tetris2D", 200, 200, 1000, 800, false);

	bool bIsDone = false;
	WindowEventHandler::BindCallbackEvent(WindowEventHandler::EEventType::CLOSE, [&]() {
		bIsDone = true;
	});

	while (!bIsDone)
	{
		WindowEventHandler::PollEventQueue();
	}
}


/**
 * @brief 애플리케이션의 진입점입니다.
 * 
 * @param Argc 명령행 인자의 수입니다.
 * @param Argv 명령행 인자입니다.
 * 
 * @return 다른 프로그램에 전달할 수 있는 상태 코드를 반환합니다.
 */
int main(int32_t Argc, char** Argv)
{
#if defined(DEBUG) || defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	__try
	{
		RunApplication(Argc, Argv);
	}
	__except (ErrorHandler::GenerateCrashDump(GetExceptionInformation()))
	{
		ErrorHandler::ShowErrorMessageBox();
	}
	
	return 0;
}