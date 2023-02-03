#pragma once

#include "Vector.hpp"
#include "InputManager.h"
#include "InputComponent.h"

#include <functional>


/**
 * @brief 버튼의 입력 처리를 수행하는 컴포넌트입니다.
 */
class ButtonInputComponent : public InputComponent
{
public:
	/**
	 * @brief 버튼의 입력 처리를 수행하는 컴포넌트의 생성자입니다.
	 * 
	 * @param Object 이 컴포넌트를 소유하는 오브젝트의 포인터 값입니다.
	 */
	ButtonInputComponent(
		GameObject* Object,
		const Vec2f& Position,
		const float& Width,
		const float& Height,
		const EKeyCode& KeyCode,
		const std::function<void()>& ClickEvent,
		const float& ReduceRate = 1.0f,
		bool bIsMouseMode = true
	);


	/**
	 * @brief 버튼의 입력 처리를 수행하는 컴포넌트의 가상 소멸자입니다.
	 */
	virtual ~ButtonInputComponent();


	/**
	 * 복사 생성자외 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(ButtonInputComponent);


	/**
	 * @brief 버튼의 입력 처리 컴포넌트를 업데이트합니다.
	 */
	void Tick();


private:
	/**
	 * @brief 마우스가 범위 내에 있는지 확인합니다.
	 *
	 * @return 마우스가 범위 내에 있다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsDetectMouse() const;


	/**
	 * @brief 버튼의 입력 처리를 수행합니다.
	 * 
	 * @param ButtonWidth[out] 입력 처리 결과로 변경된 버튼의 가로 크기입니다.
	 * @param ButtonHeight[out] 입력 처리 결과로 변경된 버튼의 세로 크기입니다. 
	 */
	void ProcessButtonInput(float& ButtonWidth, float& ButtonHeight);


private:
	/**
	 * @brief 마우스가 버튼 내에 있는지 확인합니다.
	 */
	bool bIsDetectMouse_ = false;


	/**
	 * @brief 월드 상의 사각형 버튼 중심 좌표입니다.
	 */
	Vec2f Position_;


	/**
	 * @brief 사각형 버튼의 가로 크기입니다.
	 */
	float Width_ = 0.0f;


	/**
	 * @brief 사각형 버튼의 세로 크기입니다.
	 */
	float Height_ = 0.0f;


	/**
	 * @brief 버튼에 대응하는 키 코드 값입니다.
	 */
	EKeyCode KeyCode_ = EKeyCode::CODE_NONE;


	/**
	 * @brief 버튼 클릭 시 발생할 이벤트입니다.
	 */
	std::function<void()> ClickEvent_ = nullptr;


	/**
	 * @brief 버튼 클릭 시 줄어드는 버튼의 비율입니다.
	 */
	float ReduceRate_ = 0.0f;


	/**
	 * @brief 버튼이 마우스를 감지하는 모드인지 확인합니다.
	 */
	bool bIsMouseMode_ = true;
};