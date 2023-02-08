#pragma once

#include "InputComponent.h"


/**
 * @brief 테트로미노의 입력 처리 컴포넌트입니다.
 */
class TetrominoInputComponent : public InputComponent
{
public:
	/**
	 * @brief 테트로미노의 입력 처리 컴포넌트 생성자입니다.
	 * 
	 * @param Object 이 컴포넌트를 소유하는 오브젝트의 포인터 값입니다.
	 */
	TetrominoInputComponent(GameObject* Object)
		: InputComponent(Object) {}


	/**
	 * @brief 테트로미노의 입력 처리 컴포넌트 가상 소멸자입니다.
	 */
	virtual ~TetrominoInputComponent() {}


	/**
	 * @brief 테트로미노의 입력 처리 컴포넌트를 업데이트합니다.
	 * 
	 * @param DeltaSecons 초단위 델타 시간값입니다.
	 */
	void Tick(float DeltaSecons);


private:
	/**
	 * @brief 프레임 누적 시간입니다.
	 */
	float AccrueFrameTime_ = 0.0f;
};