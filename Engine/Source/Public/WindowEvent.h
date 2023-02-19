#pragma once

#include <cstdint>
#include <functional>
#include <windows.h>


/**
 * @brief 윈도우 이벤트 키 값입니다.
 */
enum class EWindowEvent : int32_t
{
	NONE          = 0,
	ACTIVE        = 1,
	INACTIVE      = 2,
	MINIMZED      = 3,
	MAXIMIZED     = 4,
	RESIZE        = 5,
	ENTERSIZEMOVE = 6,
	EXITSIZEMOVE  = 7,
	LBUTTONDOWN   = 8,
	LBUTTONUP     = 9,
	RBUTTONDOWN   = 10,
	RBUTTONUP     = 11,
	MOUSEMOVE     = 12,
	CLOSE         = 13,
	MAXHIDE       = 14, /* https://learn.microsoft.com/ko-kr/windows/win32/winmsg/wm-size */
	MAXSHOW       = 15, /* https://learn.microsoft.com/ko-kr/windows/win32/winmsg/wm-size */
};


/**
 * @brief 윈도우 메시지 핸들러의 함수 포인터입니다.
 */
using WindowMessageHandlerPtr = LRESULT(*)(HWND, uint32_t, WPARAM, LPARAM);


/**
 * @brief 윈도우 메시지 핸들러의 포인터를 얻습니다.
 * 
 * @return 윈도우 메시지 핸들러의 포인터를 반환합니다.
 */
WindowMessageHandlerPtr GetWindowMessageHandlerPtr();


/**
 * @brief 현재 윈도우 이벤트 처리 대상인 윈도우 핸들을 얻습니다.
 * 
 * @return 이벤트 처리 대상인 윈도우 핸들 값을 반환합니다.
 */
HWND GetEventTargetWindowHandle();


/**
 * @brief 윈도우 메시지에 대응하는 콜백 이벤트를 바인딩합니다.
 * 
 * @param WindowEvent 윈도우 메시지입니다.
 * @param CallbackEvent 윈도우 메시지에 대응하는 콜백 이벤트입니다.
 */
void BindWindowCallbackEvent(const EWindowEvent& WindowEvent, const std::function<void()>& CallbackEvent);


/**
 * @brief 메시지 큐로 부터 풀링을 합니다.
 */
void PollWindowEvent();