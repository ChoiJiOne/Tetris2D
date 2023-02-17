#include "WindowEvent.h"


/**
 * @brief 윈도우 메시지 핸들러입니다.
 *
 * @note 내부의 윈도우 메시지 핸들러를 호출합니다.
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
LRESULT CALLBACK WindowMessageHandler(HWND WindowHandle, uint32 Message, WPARAM WParam, LPARAM LParam);


WindowMessageHandlerPtr GetWindowMessageHandlerPtr()
{
	return WindowMessageHandler;
}