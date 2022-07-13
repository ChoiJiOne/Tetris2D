#pragma once

#include <vector>


namespace Game
{
	// 버튼 입력 상태를 나타냅니다.
	// --------------------------------------
	// | 이전 프레임 | 현재 프레임 | 입력 상태 |
	// --------------------------------------
	// |     0      |     0      | None     |
	// |     0      |     1      | Pressed  |
	// |     1      |     0      | Released |
	// |     1      |     1      | Held     |
	// --------------------------------------
	enum class EButtonState
	{
		None     = 0,
		Pressed  = 1,
		Released = 2,
		Held     = 3
	};


	// 키보드 상태를 나타내는 클래스입니다.
	class KeyboardState
	{
	public:
		// 생성자입니다.
		KeyboardState();


		// 가상 소멸자입니다.
		virtual ~KeyboardState();


		// 키보드의 상태를 업데이트합니다.
		void Update();


		// 키의 상태를 반환합니다.
		//
		// @param InKeyCode - 키 상태를 확인할 키 코드 값입니다.
		//
		// @return - 키의 버튼 상태를 반환합니다.
		EButtonState GetKeyState(uint8_t InKeyCode) const;


	private:
		// 특정 키가 눌렸는지 확인합니다.
		//
		// @param InKeyboardState - 검사를 수행할 키보드의 상태입니다.
		// @param InKeyCode - 검사를 수행할 키입니다.
		//
		// @return 만약 키를 눌렀다면 true, 그렇지 않다면 false를 반환합니다.
		bool IsPressKey(const std::vector<uint8_t>& InKeyboardState, uint8_t InKeyCode) const;


	private:
		// 업데이트 이전의 키보드 상태입니다.
		std::vector<uint8_t> PrevKeyboardState;


		// 업데이트 후의 키보드 상태입니다.
		std::vector<uint8_t> CurrKeyboardState;
	};
}