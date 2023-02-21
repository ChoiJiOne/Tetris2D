#pragma once

#include "Macro.h"
#include "Vector.hpp"

#include <cstdint>
#include <vector>
#include <functional>
#include <unordered_map>

#include <windows.h>


/**
 * @brief 입력 상태를 나타냅니다.
 * 
 * --------------------------------------
 * | 이전 프레임 | 현재 프레임 | 입력 상태 |
 * --------------------------------------
 * |     0      |     0      | NONE     |
 * |     0      |     1      | PRESSED  |
 * |     1      |     0      | RELEASED |
 * |     1      |     1      | HELD     |
 * --------------------------------------
 */
enum class EPressState
{
	NONE     = 0,
	PRESSED  = 1,
	RELEASED = 2,
	HELD     = 3
};


/**
 * @brief 키 코드 값입니다.
 * 
 * @see https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
 */
enum class EKeyCode
{
	CODE_NONE = 0x00,
	CODE_LBUTTON = 0x01,
	CODE_RBUTTON = 0x02,
	CODE_CANCEL = 0x03,
	CODE_MBUTTON = 0x04,
	CODE_XBUTTON1 = 0x05,
	CODE_XBUTTON2 = 0x06,
	CODE_BACK = 0x08,
	CODE_TAB = 0x09,
	CODE_CLEAR = 0x0C,
	CODE_RETURN = 0x0D,
	CODE_SHIFT = 0x10,
	CODE_CONTROL = 0x11,
	CODE_MENU = 0x12,
	CODE_PAUSE = 0x13,
	CODE_CAPITAL = 0x14,
	CODE_KANA = 0x15,
	CODE_HANGUEL = 0x15,
	CODE_HANGUL = 0x15,
	CODE_IME_ON = 0x16,
	CODE_JUNJA = 0x17,
	CODE_FINAL = 0x18,
	CODE_HANJA = 0x19,
	CODE_KANJI = 0x19,
	CODE_IME_OFF = 0x1A,
	CODE_ESCAPE = 0x1B,
	CODE_CONVERT = 0x1C,
	CODE_NONCONVERT = 0x1D,
	CODE_ACCEPT = 0x1E,
	CODE_MODECHANGE = 0x1F,
	CODE_SPACE = 0x20,
	CODE_PRIOR = 0x21,
	CODE_NEXT = 0x22,
	CODE_END = 0x23,
	CODE_HOME = 0x24,
	CODE_LEFT = 0x25,
	CODE_UP = 0x26,
	CODE_RIGHT = 0x27,
	CODE_DOWN = 0x28,
	CODE_SELECT = 0x29,
	CODE_PRINT = 0x2A,
	CODE_EXECUTE = 0x2B,
	CODE_SNAPSHOT = 0x2C,
	CODE_INSERT = 0x2D,
	CODE_DELETE = 0x2E,
	CODE_HELP = 0x2F,
	CODE_0 = 0x30,
	CODE_1 = 0x31,
	CODE_2 = 0x32,
	CODE_3 = 0x33,
	CODE_4 = 0x34,
	CODE_5 = 0x35,
	CODE_6 = 0x36,
	CODE_7 = 0x37,
	CODE_8 = 0x38,
	CODE_9 = 0x39,
	CODE_A = 0x41,
	CODE_B = 0x42,
	CODE_C = 0x43,
	CODE_D = 0x44,
	CODE_E = 0x45,
	CODE_F = 0x46,
	CODE_G = 0x47,
	CODE_H = 0x48,
	CODE_I = 0x49,
	CODE_J = 0x4A,
	CODE_K = 0x4B,
	CODE_L = 0x4C,
	CODE_M = 0x4D,
	CODE_N = 0x4E,
	CODE_O = 0x4F,
	CODE_P = 0x50,
	CODE_Q = 0x51,
	CODE_R = 0x52,
	CODE_S = 0x53,
	CODE_T = 0x54,
	CODE_U = 0x55,
	CODE_V = 0x56,
	CODE_W = 0x57,
	CODE_X = 0x58,
	CODE_Y = 0x59,
	CODE_Z = 0x5A,
	CODE_LWIN = 0x5B,
	CODE_RWIN = 0x5C,
	CODE_APPS = 0x5D,
	CODE_SLEEP = 0x5F,
	CODE_NUMPAD0 = 0x60,
	CODE_NUMPAD1 = 0x61,
	CODE_NUMPAD2 = 0x62,
	CODE_NUMPAD3 = 0x63,
	CODE_NUMPAD4 = 0x64,
	CODE_NUMPAD5 = 0x65,
	CODE_NUMPAD6 = 0x66,
	CODE_NUMPAD7 = 0x67,
	CODE_NUMPAD8 = 0x68,
	CODE_NUMPAD9 = 0x69,
	CODE_MULTIPLY = 0x6A,
	CODE_ADD = 0x6B,
	CODE_SEPARATOR = 0x6C,
	CODE_SUBTRACT = 0x6D,
	CODE_DECIMAL = 0x6E,
	CODE_DIVIDE = 0x6F,
	CODE_F1 = 0x70,
	CODE_F2 = 0x71,
	CODE_F3 = 0x72,
	CODE_F4 = 0x73,
	CODE_F5 = 0x74,
	CODE_F6 = 0x75,
	CODE_F7 = 0x76,
	CODE_F8 = 0x77,
	CODE_F9 = 0x78,
	CODE_F10 = 0x79,
	CODE_F11 = 0x7A,
	CODE_F12 = 0x7B,
	CODE_F13 = 0x7C,
	CODE_F14 = 0x7D,
	CODE_F15 = 0x7E,
	CODE_F16 = 0x7F,
	CODE_F17 = 0x80,
	CODE_F18 = 0x81,
	CODE_F19 = 0x82,
	CODE_F20 = 0x83,
	CODE_F21 = 0x84,
	CODE_F22 = 0x85,
	CODE_F23 = 0x86,
	CODE_F24 = 0x87,
	CODE_NUMLOCK = 0x90,
	CODE_SCROLL = 0x91,
	CODE_LSHIFT = 0xA0,
	CODE_RSHIFT = 0xA1,
	CODE_LCONTROL = 0xA2,
	CODE_RCONTROL = 0xA3,
	CODE_LMENU = 0xA4,
	CODE_RMENU = 0xA5,
	CODE_BROWSER_BACK = 0xA6,
	CODE_BROWSER_FORWARD = 0xA7,
	CODE_BROWSER_REFRESH = 0xA8,
	CODE_BROWSER_STOP = 0xA9,
	CODE_BROWSER_SEARCH = 0xAA,
	CODE_BROWSER_FAVORITES = 0xAB,
	CODE_BROWSER_HOME = 0xAC,
	CODE_VOLUME_MUTE = 0xAD,
	CODE_VOLUME_DOWN = 0xAE,
	CODE_VOLUME_UP = 0xAF,
	CODE_MEDIA_NEXT_TRACK = 0xB0,
	CODE_MEDIA_PREV_TRACK = 0xB1,
	CODE_MEDIA_STOP = 0xB2,
	CODE_MEDIA_PLAY_PAUSE = 0xB3,
	CODE_LAUNCH_MAIL = 0xB4,
	CODE_LAUNCH_MEDIA_SELECT = 0xB5,
	CODE_LAUNCH_APP1 = 0xB6,
	CODE_LAUNCH_APP2 = 0xB7,
	CODE_OEM_1 = 0xBA,
	CODE_OEM_PLUS = 0xBB,
	CODE_OEM_COMMA = 0xBC,
	CODE_OEM_MINUS = 0xBD,
	CODE_OEM_PERIOD = 0xBE,
	CODE_OEM_2 = 0xBF,
	CODE_OEM_3 = 0xC0,
	CODE_OEM_4 = 0xDB,
	CODE_OEM_5 = 0xDC,
	CODE_OEM_6 = 0xDD,
	CODE_OEM_7 = 0xDE,
	CODE_OEM_8 = 0xDF,
	CODE_OEM_102 = 0xE2,
	CODE_PACKET = 0xE7,
	CODE_ATTN = 0xF6,
	CODE_CRSEL = 0xF7,
	CODE_EXSEL = 0xF8,
	CODE_EREOF = 0xF9,
	CODE_PLAY = 0xFA,
	CODE_ZOOM = 0xFB,
	CODE_NONAME = 0xFC,
	CODE_PA1 = 0xFD,
	CODE_OEM_CLEAR = 0xFE,
};


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


/**
 * @brief 입력 처리 및 키보드, 마우스의 상태를 관리합니다.
 * 
 * @note 이 클래스는 싱글턴으로 헤더만 추가하면 바로 사용할 수 있습니다.
 */
class InputManager
{
public:
	/**
	 * @brief 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(InputManager);


	/**
	 * @brief InputManager의 인스턴스를 얻습니다.
	 * 
	 * @return InputManager의 인스턴스 참조자를 반환합니다.
	 */
	static InputManager& Get()
	{
		static InputManager Instance;
		return Instance;
	}


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
	LRESULT ProcessWindowMessage(HWND WindowHandle, uint32_t Message, WPARAM WParam, LPARAM LParam);


	/**
	 * @brief 윈도우 이벤트에 대응하는 콜백을 바인딩합니다.
	 * 
	 * @note 이벤트에 대응하는 실행 루틴은 유일합니다. 새로운 루틴을 실행하려면 다시 등록해야 합니다.
	 * 
	 * @param WindowEvent 등록할 윈도우 이벤트 종류입니다.
	 * @param EventCallback 이벤트 감지 시 실행할 루틴입니다.
	 */
	void BindWindowEvent(const EWindowEvent& WindowEvent, const std::function<void()>& EventCallback);


	/**
	 * @brief 윈도우 이벤트를 바인딩 해제합니다.
	 * 
	 * @param WindowEvent 바인딩 해제할 윈도우 이벤트입니다.
	 */
	void UnbindWindowEvent(const EWindowEvent& WindowEvent);


	/**
	 * @brief 입력 상태를 업데이트합니다.
	 * 
	 * @note 이 메서드는 매 프레임 호출해야 합니다.
	 */
	void Tick();


	/**
	 * @brief 키의 입력 상태를 반환합니다.
	 *
	 * @param KeyCode - 검사를 수행할 키입니다.
	 *
	 * @return 키의 버튼 상태를 반환합니다.
	 */
	EPressState GetKeyPressState(const EKeyCode& KeyCode) const;


	/**
	 * @brief Tick 호출 이전의 화면 기준 마우스 위치를 얻습니다.
	 * 
	 * @return Tick 호출 이전의 화면 기준 마우스 위치를 반환합니다.
	 */
	Vec2i GetPrevMousePositionFromScreen() { return PrevScreenMousePosition_; }


	/**
	 * @brief Tick 호출 이전의 윈도우 기준 현재 마우스 위치를 얻습니다.
	 * 
	 * @return Tick 호출 이전의 윈도우 기준 마우스 위치를 반환합니다.
	 */
	Vec2i GetPrevMousePositionFromWindow() { return PrevWindowMousePosition_; }


	/**
	 * @brief Tick 호출 이후의 화면 기준 마우스 위치를 얻습니다.
	 *
	 * @return Tick 호출 이후의 화면 기준 마우스 위치를 반환합니다.
	 */
	Vec2i GetCurrMousePositionFromScreen() { return CurrScreenMousePosition_; }


	/**
	 * @brief Tick 호출 이후의 윈도우 기준 현재 마우스 위치를 얻습니다.
	 *
	 * @return Tick 호출 이후의 윈도우 기준 마우스 위치를 반환합니다.
	 */
	Vec2i GetCurrMousePositionFromWindow() { return CurrWindowMousePosition_; }
	

private:
	/**
	 * @brief 입력 처리를 수행하는 클래스의 생성자입니다.
	 */
	InputManager();


	/**
	 * @brief 입력 처리를 수행하는 클래스의 가상 소멸자입니다.
	 */
	virtual ~InputManager() {}


	/**
	 * @brief 이벤트 큐의 윈도우 이벤트를 처리합니다.
	 */
	void PollEventMessage();


	/**
	 * @brief 키보드의 상태를 업데이트합니다.
	 */
	void UpdateKeyboardState();


	/**
	 * @brief 특정 키가 눌렸는지 검사합니다.
	 * 
	 * @param KeyboardState 검사를 수행할 키보드 상태입니다.
	 * @param KeyCode 검사를 수행할 키 코드입니다.
	 * 
	 * @return 키가 눌렸다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool IsPressKey(const std::vector<uint8_t>& KeyboardState, const EKeyCode& KeyCode) const;


	/**
	 * @brief 모니터를 기준으로 현재 마우스의 위치를 얻습니다.
	 * 
	 * @return 모니터를 기준으로 현재 마우스의 (X, Y) 위치를 반환합니다.
	 */
	Vec2i GetMousePositionFromScreen();


	/**
	 * @brief 윈도우를 기준으로 현재 마우스의 위치를 얻습니다.
	 * 
	 * @see https://stackoverflow.com/questions/6423729/get-current-cursor-position
	 * 
	 * @return 윈도우를 기준으로 현재 마우스의 (X, Y) 위치를 반환합니다.
	 */
	Vec2i GetMousePositionFromWindow();


	/**
	 * @brief 마우스의 위치를 업데이트합니다.
	 */
	void UpdateMousePosition();


	/**
	 * @brief 윈도우 이벤트에 대응하는 루틴을 실행합니다.
	 *
	 * @param WindowEvent 실행할 윈도우 이벤트입니다.
	 */
	void HandleWindowEvent(const EWindowEvent& WindowEvent);


private:
	/**
	 * @brief 이벤트 처리 대상이 되는 윈도우 핸들입니다.
	 */
	HWND WindowHandle_ = nullptr;


	/**
	 * @brief 윈도우 창의 크기가 변경 중인지 확인합니다.
	 */
	bool bIsResizing_ = false;


	/**
	 * @brief 업데이트 이전(Tick 호출 이전)의 키보드 상태입니다.
	 */
	std::vector<uint8_t> PrevKeyboardState_;


	/**
	 * @brief 업데이트 후(Tick 호출 후)의 키보드 상태입니다.
	 */
	std::vector<uint8_t> CurrKeyboardState_;


	/**
	 * @brief 업데이트 이전(Tick 호출 이전)의 화면 기준 마우스 위치입니다.
	 */
	Vec2i PrevScreenMousePosition_;


	/**
	 * @brief 업데이트 이전(Tick 호출 이전)의 윈도우 기준 마우스 위치입니다.
	 */
	Vec2i PrevWindowMousePosition_;


	/**
	 * @brief 업데이트 후(Tick 호출 후)의 화면 기준 마우스 위치입니다.
	 */
	Vec2i CurrScreenMousePosition_;
	

	/**
	 * @brief 업데이트 이전(Tick 호출 후)의 윈도우 기준 마우스 위치입니다.
	 */
	Vec2i CurrWindowMousePosition_;


	/**
	 * @brief 윈도우 이벤트 키 값에 대응하는 이벤트입니다.
	 */
	std::unordered_map<EWindowEvent, std::function<void()>> WindowEvents_;
};