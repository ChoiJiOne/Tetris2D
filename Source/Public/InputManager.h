#pragma once

#include "Macro.h"

#include <cstdint>
#include <vector>

#include <windows.h>


/**
 * 입력 상태를 나타냅니다.
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
	 * @return InputManager의 인스턴스를 반환합니다.
	 */
	static InputManager& Get()
	{
		static InputManager Instance;
		return Instance;
	}


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
	static LRESULT CALLBACK WindowMessageHandler(HWND WindowHandle, uint32_t Message, WPARAM WParam, LPARAM LParam);


	/**
	 * @brief 입력 상태를 업데이트합니다.
	 * 
	 * @note 이 메서드는 매 프레임 호출해야 합니다.
	 */
	void Tick();


	/**
	 * @brief QUIT 메시지가 감지되었는지 확인합니다.
	 * 
	 * @return QUIT 메시지가 감지되었다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool IsDetectQuitMessage() const { return bIsDetectQuitMessage; }


	/**
	 * @brief 키의 입력 상태를 반환합니다.
	 *
	 * @param KeyCode - 검사를 수행할 키입니다.
	 *
	 * @return 키의 버튼 상태를 반환합니다.
	 */
	EPressState GetKeyPressState(int32_t KeyCode) const;
	

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
	 * @brief 특정 키가 눌렸는지 검사합니다.
	 * 
	 * @param KeyboardState 검사를 수행할 키보드 상태입니다.
	 * @param KeyCode 검사를 수행할 키 코드입니다.
	 * 
	 * @return 키가 눌렸다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool IsPressKey(const std::vector<uint8_t>& KeyboardState, int32_t KeyCode) const;


private:
	/**
	 * @brief QUIT 메시지가 감지되었는지 확인합니다.
	 */
	bool bIsDetectQuitMessage = false;


	/**
	 * @brief 업데이트 이전(Tick 호출 이전)의 키보드 상태입니다.
	 */
	std::vector<uint8_t> PrevKeyboardState_;


	/**
	 * @brief 업데이트 후(Tick 호출 후)의 키보드 상태입니다.
	 */
	std::vector<uint8_t> CurrKeyboardState_;
};