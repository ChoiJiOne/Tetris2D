#pragma once

#include "Type.h"

#include <functional>
#include <windows.h>


/**
 * @brief ������ �̺�Ʈ Ű ���Դϴ�.
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


/**
 * @brief ������ �޽��� �ڵ鷯�� �Լ� �������Դϴ�.
 */
using WindowMessageHandlerPtr = LRESULT(*)(HWND, uint32, WPARAM, LPARAM);


/**
 * @brief ������ �޽��� �ڵ鷯�� �����͸� ����ϴ�.
 * 
 * @return ������ �޽��� �ڵ鷯�� �����͸� ��ȯ�մϴ�.
 */
WindowMessageHandlerPtr GetWindowMessageHandlerPtr();


/**
 * @brief ���� ������ �̺�Ʈ ó�� ����� ������ �ڵ��� ����ϴ�.
 * 
 * @return �̺�Ʈ ó�� ����� ������ �ڵ� ���� ��ȯ�մϴ�.
 */
HWND GetEventTargetWindowHandle();


/**
 * @brief ������ �޽����� �����ϴ� �ݹ� �̺�Ʈ�� ���ε��մϴ�.
 * 
 * @param WindowEvent ������ �޽����Դϴ�.
 * @param CallbackEvent ������ �޽����� �����ϴ� �ݹ� �̺�Ʈ�Դϴ�.
 */
void BindWindowCallbackEvent(const EWindowEvent& WindowEvent, const std::function<void()>& CallbackEvent);


/**
 * @brief �޽��� ť�� ���� Ǯ���� �մϴ�.
 */
void PollWindowEvent();