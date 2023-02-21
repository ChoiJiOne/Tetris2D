#pragma once

#include "Tetromino.h"
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
	 * @brief 컴포넌트의 복사 생성자 및 대입연산자를 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(TetrominoInputComponent);


	/**
	 * @brief 테트로미노의 입력 처리 컴포넌트를 업데이트합니다.
	 * 
	 * @param DeltaSecons 초단위 델타 시간값입니다.
	 */
	void Tick(float DeltaSecons);

	
	/**
	 * @brief 프레임 누적 시간을 얻습니다.
	 * 
	 * @note 시간은 초단위 입니다.
	 * 
	 * @return 프레임 누적 시간을 반환합니다.
	 */
	float GetAccrueFrameTime() const { return AccrueFrameTime_; }


	/**
	 * @brief 프레임 누적 시간을 초기화합니다.
	 * 
	 * @note 누적 시간값을 0으로 만듭니다.
	 */
	void ResetAccrueFrameTime() { AccrueFrameTime_ = 0.0f; }

	
	/**
	 * @brief 테트로미노의 이동 방향을 얻습니다.
	 * 
	 * @return 테트로미노의 이동 방향을 반환합니다.
	 */
	Tetromino::EDirection GetDirection() const { return Direction_; }


private:
	/**
	 * @brief 프레임 누적 시간입니다.
	 */
	float AccrueFrameTime_ = 0.0f;


	/**
	 * @brief 테트로미노의 이동 방향입니다.
	 */
	Tetromino::EDirection Direction_ = Tetromino::EDirection::NONE;
};