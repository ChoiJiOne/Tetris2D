#pragma once

#include <array>

#include "BlockComponent.h"
#include "GameObject.h"


/**
 * @brief 테트리스 게임의 테트로미노입니다.
 */
class Tetromino : public GameObject
{
public:
	/**
	 * @brief 테트로미노의 모양 타입입니다.
	 *
	 * @see https://ko.wikipedia.org/wiki/%ED%85%8C%ED%8A%B8%EB%A1%9C%EB%AF%B8%EB%85%B8
	 */
	enum class EShape : int32_t
	{
		NONE = 0,
		I = 1,
		O = 2,
		T = 3,
		J = 4,
		L = 5,
		S = 6,
		Z = 7
	};


	/**
	 * @brief 테트로미노의 움직임 방향입니다.
	 */
	enum class EDirection : int32_t
	{
		NONE  = 0,
		LEFT  = 1,
		RIGHT = 2,
		DOWN  = 3,
		UP    = 4,
		CCW   = 5,
		CW    = 6,
		JUMP  = 7,
	};


	/**
	 * @brief 테트로미노의 상태입니다.
	 */
	enum class EState : int32_t
	{
		WAIT   = 0,
		ACTIVE = 1,
		DONE   = 2,
	};


public:
	/**
	 * @brief 테트로미노의 생성자입니다.
	 *
	 * @param Signature 테트로미노의 식별자입니다.
	 * @param LTPosition 테트로미노의 왼쪽 상단의 좌표입니다.
	 * @param Side 테트로미노 블럭의 크기입니다.
	 * @param MoveStep 테트로미노가 한 번 움직일 때의 시간 입니다.
	 */
	Tetromino(
		const std::string& Signature,
		const Vec2f& LTPosition,
		const float& Side,
		const float& MoveStep
	);


	/**
	 * @brief 테트로미노의 생성자입니다.
	 * 
	 * @param Signature 테트로미노의 식별자입니다.
	 * @param LTPosition 테트로미노의 왼쪽 상단의 좌표입니다.
	 * @param Side 테트로미노 블럭의 크기입니다.
	 * @param Color 테트로미노 블럭의 색상입니다.
	 * @param MoveStep 테트로미노가 한 번 움직일 때의 시간 입니다.
	 * @param Shape 테트로미노의 모양입니다.
	 */
	Tetromino(
		const std::string& Signature,
		const Vec2f& LTPosition,
		const float& Side,
		const BlockComponent::EColor& Color,
		const float& MoveStep,
		const EShape& Shape
	);


	/**
	 * @brief 테트로미노의 가상 소멸자입니다.
	 */
	virtual ~Tetromino();


	/**
	 * @brief 명시적으로 복사 생성자와 대입 연산자를 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Tetromino);


	/**
	 * @brief 백그라운드를 업데이트합니다.
	 *
	 * @param DeltaSeconds 초단위 델타 시간값입니다.
	 */
	virtual void Tick(float DeltaSeconds) override;


	/**
	 * @brief 테트로미노를 특정 위치로 이동시킬 수 있는지 확인합니다.
	 *
	 * @param LTPosition 테트로미노를 이동 시킬 특정 위치입니다.
	 *
	 * @return 텔레포트시킨 위치에 충돌이 발생하지 않으면 true, 충돌이 발생하면 false를 반환합니다.
	 */
	bool CanTeleport(const Vec2f& LTPosition);


	/**
	 * @brief 테트로미노를 특정 위치로 이동시킵니다.
	 * 
	 * @param LPPosition 테트로미노를 이동 시킬 특정 위치입니다.
	 * 
	 * @return 텔레포트시킨 위치에 충돌이 발생하지 않으면 true, 충돌이 발생하면 false를 반환합니다. 
	 */
	void Teleport(const Vec2f& LPPosition);


	/**
	 * @brief 테트로미노가 스스로 움직이는 시간을 얻습니다.
	 *
	 * @return 테트로미노가 스스로 움직이는 시간을 반환합니다.
	 */
	float GetMoveStep() const { return MoveStep_; }


	/**
	 * @brief 테트로미노의 블럭들을 얻습니다.
	 *
	 * @note 이 메서드를 사용할 경우, 블럭을 변경할 수 없습니다.
	 *
	 * @return 테트로미노의 블럭들을 반환합니다.
	 */
	const std::array<BlockComponent*, 4>& GetBlocks() const { return Blocks_; }


	/**
	 * @brief 테트로미노의 블럭들을 얻습니다.
	 *
	 * @note 이 메서드를 사용할 경우, 블럭을 변경할 수 있습니다.
	 *
	 * @return 테트로미노의 블럭들을 반환합니다.
	 */
	std::array<BlockComponent*, 4>& GetBlocks() { return Blocks_; }


	/**
	 * @brief 테트로미노의 상태를 얻습니다.
	 * 
	 * @return 테트로미노의 상태를 반환합니다.
	 */
	EState GetState() const { return State_; }


	/**
	 * @brief 테트로미노의 상태를 설정합니다.
	 * 
	 * @param State 설정할 테트로미노의 상태입니다.
	 */
	void SetState(const EState& State) { State_ = State; }


	/**
	 * @brief 테트로미노의 모양을 얻습니다.
	 * 
	 * @return 테트로미노의 모양을 반환합니다.
	 */
	EShape GetShape() const { return Shape_; }


private:
	/**
	 * @brief 테트로미노의 블럭들을 생성합니다.
	 * 
	 * @param LTPosition 테트로미노의 왼쪽 상단의 좌표입니다.
	 * @param Side 테트로미노 블럭의 크기입니다.
	 * @param Color 테트로미노 블럭의 색상입니다.
	 * @param Shape 테트로미노의 모양입니다.
	 */
	void CreateTetrominoBlocks(
		const Vec2f& LTPosition,
		const float& Side,
		const BlockComponent::EColor& Color,
		const EShape& Shape
	);


private:
	/**
	 * @brief 테트로미노가 스스로 움직이는 시간입니다.
	 */
	float MoveStep_ = 0.0f;


	/**
	 * @brief 테트로미노의 현재 상태입니다.
	 */
	EState State_ = EState::WAIT;


	/**
	 * @brief 테트로미노의 모양입니다.
	 */
	EShape Shape_ = EShape::NONE;


	/**
	 * @brief 테트로미노의 블럭 컴포넌트입니다.
	 */
	std::array<BlockComponent*, 4> Blocks_;
};