#pragma once

#include "Macro.h"
#include "Vector.hpp"

#include <cstdint>
#include <vector>
#include <functional>
#include <unordered_map>

#include <windows.h>


/**
 * @brief �Է� ���¸� ��Ÿ���ϴ�.
 * 
 * --------------------------------------
 * | ���� ������ | ���� ������ | �Է� ���� |
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
 * @brief Ű �ڵ� ���Դϴ�.
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
 * @brief �Է� ó�� �� Ű����, ���콺�� ���¸� �����մϴ�.
 * 
 * @note �� Ŭ������ �̱������� ����� �߰��ϸ� �ٷ� ����� �� �ֽ��ϴ�.
 */
class InputManager
{
public:
	/**
	 * @brief ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(InputManager);


	/**
	 * @brief InputManager�� �ν��Ͻ��� ����ϴ�.
	 * 
	 * @return InputManager�� �ν��Ͻ� �����ڸ� ��ȯ�մϴ�.
	 */
	static InputManager& Get()
	{
		static InputManager Instance;
		return Instance;
	}


	/**
	 * @brief ������ �޽��� �ڵ鷯�Դϴ�.
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
	LRESULT WindowMessageHandler(HWND WindowHandle, uint32_t Message, WPARAM WParam, LPARAM LParam);


	/**
	 * @brief ������ �̺�Ʈ�� ����մϴ�.
	 * 
	 * @note �̺�Ʈ�� �����ϴ� ���� ��ƾ�� �����մϴ�. ���ο� ��ƾ�� �����Ϸ��� �ٽ� ����ؾ� �մϴ�.
	 * 
	 * @param WindowEvent ����� ������ �̺�Ʈ �����Դϴ�.
	 * @param EventCallback �̺�Ʈ ���� �� ������ ��ƾ�Դϴ�.
	 */
	void RegisterWindowEvent(const EWindowEvent& WindowEvent, const std::function<void()>& EventCallback);


	/**
	 * @brief ������ �̺�Ʈ�� ��� �����մϴ�.
	 * 
	 * @param WindowEvent ��� ������ ������ �̺�Ʈ�Դϴ�.
	 */
	void UnregisterWindowEvent(const EWindowEvent& WindowEvent);


	/**
	 * @brief �Է� ���¸� ������Ʈ�մϴ�.
	 * 
	 * @note �� �޼���� �� ������ ȣ���ؾ� �մϴ�.
	 */
	void Tick();


	/**
	 * @brief Ű�� �Է� ���¸� ��ȯ�մϴ�.
	 *
	 * @param KeyCode - �˻縦 ������ Ű�Դϴ�.
	 *
	 * @return Ű�� ��ư ���¸� ��ȯ�մϴ�.
	 */
	EPressState GetKeyPressState(const EKeyCode& KeyCode) const;


	/**
	 * @brief Tick ȣ�� ������ ȭ�� ���� ���콺 ��ġ�� ����ϴ�.
	 * 
	 * @return Tick ȣ�� ������ ȭ�� ���� ���콺 ��ġ�� ��ȯ�մϴ�.
	 */
	Vec2i GetPrevMousePositionFromScreen() { return PrevScreenMousePosition_; }


	/**
	 * @brief Tick ȣ�� ������ ������ ���� ���� ���콺 ��ġ�� ����ϴ�.
	 * 
	 * @return Tick ȣ�� ������ ������ ���� ���콺 ��ġ�� ��ȯ�մϴ�.
	 */
	Vec2i GetPrevMousePositionFromWindow() { return PrevWindowMousePosition_; }


	/**
	 * @brief Tick ȣ�� ������ ȭ�� ���� ���콺 ��ġ�� ����ϴ�.
	 *
	 * @return Tick ȣ�� ������ ȭ�� ���� ���콺 ��ġ�� ��ȯ�մϴ�.
	 */
	Vec2i GetCurrMousePositionFromScreen() { return CurrScreenMousePosition_; }


	/**
	 * @brief Tick ȣ�� ������ ������ ���� ���� ���콺 ��ġ�� ����ϴ�.
	 *
	 * @return Tick ȣ�� ������ ������ ���� ���콺 ��ġ�� ��ȯ�մϴ�.
	 */
	Vec2i GetCurrMousePositionFromWindow() { return CurrWindowMousePosition_; }
	

private:
	/**
	 * @brief �Է� ó���� �����ϴ� Ŭ������ �������Դϴ�.
	 */
	InputManager();


	/**
	 * @brief �Է� ó���� �����ϴ� Ŭ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~InputManager() {}


	/**
	 * @brief �̺�Ʈ ť�� ������ �̺�Ʈ�� ó���մϴ�.
	 */
	void PollEventMessage();


	/**
	 * @brief Ű������ ���¸� ������Ʈ�մϴ�.
	 */
	void UpdateKeyboardState();


	/**
	 * @brief Ư�� Ű�� ���ȴ��� �˻��մϴ�.
	 * 
	 * @param KeyboardState �˻縦 ������ Ű���� �����Դϴ�.
	 * @param KeyCode �˻縦 ������ Ű �ڵ��Դϴ�.
	 * 
	 * @return Ű�� ���ȴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool IsPressKey(const std::vector<uint8_t>& KeyboardState, const EKeyCode& KeyCode) const;


	/**
	 * @brief ����͸� �������� ���� ���콺�� ��ġ�� ����ϴ�.
	 * 
	 * @return ����͸� �������� ���� ���콺�� (X, Y) ��ġ�� ��ȯ�մϴ�.
	 */
	Vec2i GetMousePositionFromScreen();


	/**
	 * @brief �����츦 �������� ���� ���콺�� ��ġ�� ����ϴ�.
	 * 
	 * @see https://stackoverflow.com/questions/6423729/get-current-cursor-position
	 * 
	 * @return �����츦 �������� ���� ���콺�� (X, Y) ��ġ�� ��ȯ�մϴ�.
	 */
	Vec2i GetMousePositionFromWindow();


	/**
	 * @brief ���콺�� ��ġ�� ������Ʈ�մϴ�.
	 */
	void UpdateMousePosition();


	/**
	 * @brief ������ �̺�Ʈ�� �����ϴ� ��ƾ�� �����մϴ�.
	 *
	 * @param WindowEvent ������ ������ �̺�Ʈ�Դϴ�.
	 */
	void HandleWindowEvent(const EWindowEvent& WindowEvent);


private:
	/**
	 * @brief �̺�Ʈ ó�� ����� �Ǵ� ������ �ڵ��Դϴ�.
	 */
	HWND WindowHandle_ = nullptr;


	/**
	 * @brief ������ â�� ũ�Ⱑ ���� ������ Ȯ���մϴ�.
	 */
	bool bIsResizing_ = false;


	/**
	 * @brief ������Ʈ ����(Tick ȣ�� ����)�� Ű���� �����Դϴ�.
	 */
	std::vector<uint8_t> PrevKeyboardState_;


	/**
	 * @brief ������Ʈ ��(Tick ȣ�� ��)�� Ű���� �����Դϴ�.
	 */
	std::vector<uint8_t> CurrKeyboardState_;


	/**
	 * @brief ������Ʈ ����(Tick ȣ�� ����)�� ȭ�� ���� ���콺 ��ġ�Դϴ�.
	 */
	Vec2i PrevScreenMousePosition_;


	/**
	 * @brief ������Ʈ ����(Tick ȣ�� ����)�� ������ ���� ���콺 ��ġ�Դϴ�.
	 */
	Vec2i PrevWindowMousePosition_;


	/**
	 * @brief ������Ʈ ��(Tick ȣ�� ��)�� ȭ�� ���� ���콺 ��ġ�Դϴ�.
	 */
	Vec2i CurrScreenMousePosition_;
	

	/**
	 * @brief ������Ʈ ����(Tick ȣ�� ��)�� ������ ���� ���콺 ��ġ�Դϴ�.
	 */
	Vec2i CurrWindowMousePosition_;


	/**
	 * @brief ������ �̺�Ʈ Ű ���� �����ϴ� �̺�Ʈ�Դϴ�.
	 */
	std::unordered_map<EWindowEvent, std::function<void()>> WindowEvents_;
};