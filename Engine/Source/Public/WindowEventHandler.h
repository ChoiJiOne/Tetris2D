#pragma once

#include <cstdint>
#include <unordered_map>
#include <functional>
#include <windows.h>


/**
 * @brief ������ �̺�Ʈ�� ó���ϴ� �ڵ鷯�Դϴ�.
 * 
 * @note �� Ŭ������ ��� �޼���� ��� ������ ���� Ÿ���Դϴ�.
 */
class WindowEventHandler
{
public:
	/**
	 * @biref ������ �̺�Ʈ�� �޽��� Ÿ���Դϴ�.
	 */
	enum class EEventType : int32_t
	{
		NONE,
		CREATE,
		ACTIVE,
		INACTIVE,
		MINIMZED,
		MAXIMIZED,
		RESIZE,
		ENTERSIZEMOVE,
		EXITSIZEMOVE,
		LBUTTONDOWN,
		LBUTTONUP,
		RBUTTONDOWN,
		RBUTTONUP,
		MOUSEMOVE,
		CLOSE,
		MAXHIDE, /* https://learn.microsoft.com/ko-kr/windows/win32/winmsg/wm-size */
		MAXSHOW, /* https://learn.microsoft.com/ko-kr/windows/win32/winmsg/wm-size */
	};


public:
	/**
	 * @brief ������ �޽����� �����ϴ� �ݹ� �̺�Ʈ�� ���ε��մϴ�.
	 *
	 * @param WindowEvent ������ �޽����Դϴ�.
	 * @param CallbackEvent ������ �޽����� �����ϴ� �ݹ� �̺�Ʈ�Դϴ�.
	 */
	static void BindCallbackEvent(const EEventType& WindowEvent, const std::function<void()>& CallbackEvent);


	/**
	 * @brief ������ �޽����� ó���մϴ�.
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
	static LRESULT ProcessWindowMessage(HWND WindowHandle, uint32_t Message, WPARAM WParam, LPARAM LParam);


	/**
	 * @brief �޽��� ť�� ���� Ǯ���� �մϴ�.
	 */
	static void PollEventQueue();


	/**
	 * @brief ������ �̺�Ʈ �ڵ鷯�� ������ ������ �ڵ��� ����ϴ�.
	 * 
	 * @return ������ �̺�Ʈ �ڵ鷯�� ������ ������ �ڵ��� ��ȯ�մϴ�.
	 */
	static HWND GetWindowHandle() { return CurrentWindowHandle_; }


private:
	/**
	 * @brief ������ �̺�Ʈ�� �����ϴ� �ݹ� �̺�Ʈ�� �����մϴ�.
	 *
	 * @param WindowEvent �ݹ� �̺�Ʈ�� ������ ������ �̺�Ʈ�Դϴ�.
	 */
	static void ExecuteWindowCallbackEvent(const EEventType& WindowEvent);


private:
	/**
	 * @brief ������ �̺�Ʈ�� �����ϴ� �ݹ� �̺�Ʈ�Դϴ�.
	 */
	static std::unordered_map<EEventType, std::function<void()>> WindowCallbackEvents_;


	/**
	 * @brief �̺�Ʈ ó���� ���� ������ �ڵ� ���Դϴ�.
	 */
	static HWND CurrentWindowHandle_;
};