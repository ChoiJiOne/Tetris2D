#pragma once

#include <cstdint>
#include <unordered_map>
#include <functional>
#include <windows.h>


/**
 * @brief 윈도우 이벤트를 처리하는 핸들러입니다.
 * 
 * @note 이 클래스의 모든 메서드와 멤버 변수는 정적 타입입니다.
 */
class WindowEventHandler
{
public:
	/**
	 * @biref 윈도우 이벤트의 메시지 타입입니다.
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
	 * @brief 윈도우 메시지에 대응하는 콜백 이벤트를 바인딩합니다.
	 *
	 * @param WindowEvent 윈도우 메시지입니다.
	 * @param CallbackEvent 윈도우 메시지에 대응하는 콜백 이벤트입니다.
	 */
	static void BindCallbackEvent(const EEventType& WindowEvent, const std::function<void()>& CallbackEvent);


	/**
	 * @brief 윈도우 메시지를 처리합니다.
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
	static LRESULT ProcessWindowMessage(HWND WindowHandle, uint32_t Message, WPARAM WParam, LPARAM LParam);


	/**
	 * @brief 메시지 큐로 부터 풀링을 합니다.
	 */
	static void PollEventQueue();


	/**
	 * @brief 윈도우 이벤트 핸들러가 소유한 윈도우 핸들을 얻습니다.
	 * 
	 * @return 윈도우 이벤트 핸들러가 소유한 윈도우 핸들을 반환합니다.
	 */
	static HWND GetWindowHandle() { return CurrentWindowHandle_; }


private:
	/**
	 * @brief 윈도우 이벤트에 대응하는 콜백 이벤트를 실행합니다.
	 *
	 * @param WindowEvent 콜백 이벤트를 실행할 윈도우 이벤트입니다.
	 */
	static void ExecuteWindowCallbackEvent(const EEventType& WindowEvent);


private:
	/**
	 * @brief 윈도우 이벤트에 대응하는 콜백 이벤트입니다.
	 */
	static std::unordered_map<EEventType, std::function<void()>> WindowCallbackEvents_;


	/**
	 * @brief 이벤트 처리를 위한 윈도우 핸들 값입니다.
	 */
	static HWND CurrentWindowHandle_;
};