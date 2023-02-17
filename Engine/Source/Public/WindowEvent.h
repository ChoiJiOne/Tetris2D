#pragma once

#include "Type.h"

#include <functional>
#include <windows.h>


/**
 * @brief 윈도우 이벤트 키 값입니다.
 */
enum class EWindowEvent
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
