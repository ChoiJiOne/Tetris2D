#pragma once

#include "Tetromino.h"
#include "PhysicComponent.h"


/**
 * @brief 테트로미노의 물리 처리 컴포넌트입니다.
 */
class TetrominoPhysicComponent : public PhysicComponent
{
public:
	/**
	 * @brief 테트로미노의 물리 처리 컴포넌트 생성자입니다.
	 * 
	 * @param Object 이 컴포넌트를 소유하는 오브젝트의 포인터 값입니다.
	 * @param LTPosition 테트로미노의 왼쪽 상단 좌표입니다.
	 * @param BlockSide 블럭의 크기입니다.
	 * @param MoveLength 테트로미노가 한 번 움직일 떄의 거리입니다.
	 */
	TetrominoPhysicComponent(
		GameObject* Object, 
		const Vec2f& LTPosition,
		const float& BlockSide,
		const float& MoveLength
	) : PhysicComponent(Object),
		LTPosition_(LTPosition),
		BlockSide_(BlockSide),
		MoveLength_(MoveLength)
	{
	}


	/**
	 * @biref 테트로미노의 물리 처리 컴포넌트 가상 소멸자입니다.
	 */
	virtual ~TetrominoPhysicComponent() {}


	/**
	 * @brief 컴포넌트의 복사 생성자 및 대입연산자를 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(TetrominoPhysicComponent);


	/**
	 * @brief 테트로미노의 물리 처리 컴포넌트를 업데이트합니다.
	 */
	void Tick();


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
	 * @param TeleportPosition 특정 위치로 이동 시킬 테트로미노의 왼쪽 상단 좌표입니다.
	 */
	void Teleport(const Vec2f& TeleportPosition);


	/**
	 * @brief 보드와의 충돌을 검사합니다.
	 * 
	 * @return 보드와 충돌이 발생하면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsCollision();


private:
	/**
	 * @brief 테트로미노를 특정 방향으로 움직입니다.
	 * 
	 * @param Direction 테트로미노가 이동할 방향입니다.
	 * @param Shape 테트로미노의 모양입니다.
	 * @param Blocks 테트로미노의 블럭들입니다.
	 */
	void Move(const Tetromino::EDirection& Direction, const Tetromino::EShape& Shape, std::array<BlockComponent*, 4>& Blocks);


	/**
	 * @brief 서로 다른 블럭들의 충돌을 검사합니다.
	 * 
	 * @param LhsBlocks 비교할 블럭들입니다.
	 * @param RhsBlocks 비교할 또 다른 블럭들입니다.
	 * 
	 * @return 서로 다른 블럭들이 충돌한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsCollisionBlocks(const std::vector<BlockComponent*>& LhsBlocks, const std::array<BlockComponent*, 4>& RhsBlocks);


	/**
	 * @brief 테트로미노 블럭들의 중심 위치를 계산합니다.
	 *
	 * @param Shape 테트로미노의 모양입니다.
	 * @param LTPosition 테트로미노의 왼쪽 상단의 좌표입니다.
	 * @param BlockSide 테트로미노 블럭의 크기입니다.
	 *
	 * @return 테트로미노 블럭들의 중심 위치를 반환합니다.
	 */
	Vec2f CalculateBlocksCenter(const Tetromino::EShape& Shape, const Vec2f& LTPosition, const float& BlockSide);


	/**
	 * @brief 테트로미노가 움직이는 방향의 반대 방향을 얻습니다.
	 *
	 * @param Direction 반대 방향을 얻을 테트로미노의 이동 방향입니다.
	 *
	 * @return 파라미터로 전달한 방향의 반대 방향을 반환합니다.
	 */
	static Tetromino::EDirection GetCountDirection(const Tetromino::EDirection& Direction);


private:
	/**
	 * @brief 테트로미노의 왼쪽 상단 좌표입니다.
	 *
	 * @note LT = Left Top을 의미합니다.
	 */
	Vec2f LTPosition_;


	/**
	 * @brief 테트로미노 블럭의 크기입니다.
	 */
	float BlockSide_ = 0.0f;


	/**
	 * @brief 테트로미노가 움직이는 거리입니다.
	 */
	float MoveLength_ = 0.0f;
};