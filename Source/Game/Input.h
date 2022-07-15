#pragma once

#include "Math.h"

#include <vector>


namespace Game
{
	/**
	 * 버튼 입력 상태를 나타냅니다.
	 * --------------------------------------
	 * | 이전 프레임 | 현재 프레임 | 입력 상태 |
	 * --------------------------------------
	 * |     0      |     0      | None     |
	 * |     0      |     1      | Pressed  |
	 * |     1      |     0      | Released |
	 * |     1      |     1      | Held     |
	 * --------------------------------------
	 */
	enum class EButtonState
	{
		None     = 0,
		Pressed  = 1,
		Released = 2,
		Held     = 3
	};

	
	/**
	 * 키보드 상태를 나타내는 클래스입니다.
	 */
	class KeyboardState
	{
	public:
		/**
		 * 키보드 상태를 나타내는 클래스의 생성자입니다.
		 */
		KeyboardState();


		/**
		 * 키보드 상태를 나타내는 클래스의 가상 소멸자입니다.
		 */
		virtual ~KeyboardState();


		/**
		 * 키보드의 상태를 업데이트합니다.
		 */
		void Update();


		/**
		 * 키의 상태를 반환합니다.
		 * 
		 * @param InKeyCode - 키 상태를 확인할 키 코드 값입니다.
		 * 
		 * @return 키의 버튼 상태를 반환합니다.
		 */
		EButtonState GetKeyState(uint8_t InKeyCode) const;


	private:
		/**
		 * 특정 키가 눌렸는지 확인합니다.
		 * 
		 * @param InKeyboardState - 검사를 수행할 키보드의 상태입니다.
		 * @param InKeyCode - 검사를 수행할 키입니다.
		 * 
		 * @return 만약 키를 눌렀다면 true, 그렇지 않다면 false를 반환합니다.
		 */
		bool IsPressKey(const std::vector<uint8_t>& InKeyboardState, uint8_t InKeyCode) const;


	private:
		/**
		 * 업데이트 이전의 키보드 상태입니다.
		 */
		std::vector<uint8_t> PrevKeyboardState;


		/**
		 * 업데이트 후의 키보드 상태입니다.
		 */
		std::vector<uint8_t> CurrKeyboardState;
	};


	/**
	 * 마우스의 상태를 나타내는 클래스입니다.
	 */
	class MouseState
	{
	public:
		enum class EKeyType
		{
			Left  = 0,
			Right = 1,
		};


	public:
		/**
		 * 마우스 상태를 나타내는 클래스의 생성자입니다.
		 */
		MouseState();


		/**
		 * 마우스를 나타내는 클래스의 소멸자입니다.
		 */
		virtual ~MouseState();


		/**
		 * 마우스의 상태를 업데이트합니다.
		 */
		void Update();


		/**
		 * 마우스 키의 상태를 반환합니다.
		 * 
		 * @param InKeyType - 마우스 키의 타입입니다.
		 * 
		 * @return 만약 키를 눌렀다면 true, 그렇지 않다면 false를 반환합니다.
		 */
		EButtonState GetKeyState(const EKeyType& InKeyType) const;


		/**
		 * 마우스의 업데이트 이전의 위치를 반환합니다.
		 * 
		 * @return 마우스의 업데이트 이전의 위치를 반환합니다.
		 */
		Vec2i GetPrevPosition() const { return PrevCursorPosition; }


		/**
		 * 마우스의 업데이트 이후의 위치를 반환합니다.
		 * 
		 * @return 마우스의 업데이트 이후의 위치를 반환합니다.
		 */
		Vec2i GetCurrPosition() const { return CurrCursorPosition; }


	private:
		/**
		 * 현재 마우스의 상태를 얻습니다.
		 * 
		 * @param InCursorPosition - 현재 마우스의 위치입니다.
		 * @param InButtonState - 버튼 상태입니다.
		 */
		void GetCurrentMouseState(Vec2i& InCursorPosition, uint32_t& InButtonState);


		/**
		 * 마우스 버튼이 눌렸는지 확인합니다.
		 * 
		 * @param InButtonState - 마우스 버튼의 상태입니다.
		 * @param InKeyType - 마우스 키의 타입입니다.
		 * 
		 * @return 만약 키를 눌렀다면 true, 그렇지 않다면 false를 반환합니다.
		 */
		bool IsPressKey(const uint32_t& InButtonState, const EKeyType& InKeyType) const;



	private:
		/**
		 * 업데이트 이전의 마우스 위치입니다.
		 */
		Vec2i PrevCursorPosition;


		/**
		 * 업데이트 이전의 마우스 버튼 상태입니다.
		 */
		uint32_t PrevButtonState = 0;


		/**
		 * 업데이트 이후의 마우스 위치입니다.
		 */
		Vec2i CurrCursorPosition;


		/**
		 * 업데이트 이후의 마우스 버튼 상태입니다.
		 */
		uint32_t CurrButtonState = 0;
	};


	/**
	 * 입력 클래스입니다.
	 */
	class Input
	{
	public:
		/**
		 * 입력 클래스의 생성자입니다.
		 */
		Input() = default;


		/**
		 * 입력 클래스의 가상 소멸자입니다.
		 */
		virtual ~Input();


		/**
		 * 입력 상태를 업데이트합니다.
		 * @note 이때, 이 메서드는 매 프레임 호출되어야 합니다.
		 * 
		 * @return QUIT 메시지가 감지될 경우 true, 그렇지 않으면 false를 반환합니다.
		 * 
		 */
		bool Tick();

		
		/**
		 * 입력 클래스가 관리하는 키보드를 반환합니다.
		 * 
		 * @return 입력 클래스가 관리하는 키보드를 반환합니다.
		 */
		const KeyboardState& GetKeyboardState() const { return Keyboard; }


		/**
		 * 입력 클래스가 관리하는 마우스를 반환합니다.
		 * 
		 * @return 입력 클래스가 관리하는 마우스를 반환합니다.
		 */
		const MouseState& GetMouseState() const { return Mouse; }


	private:
		/**
		 * 입력 클래스가 관리하는 키보드입니다.
		 */
		KeyboardState Keyboard;


		/**
		 * 입력 클래스가 관리하는 마우스입니다.
		 */
		MouseState Mouse;
	};
}