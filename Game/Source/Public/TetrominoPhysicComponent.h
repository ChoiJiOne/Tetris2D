#pragma once

#include "Tetromino.h"
#include "PhysicComponent.h"


/**
 * @brief ��Ʈ�ι̳��� ���� ó�� ������Ʈ�Դϴ�.
 */
class TetrominoPhysicComponent : public PhysicComponent
{
public:
	/**
	 * @brief ��Ʈ�ι̳��� ���� ó�� ������Ʈ �������Դϴ�.
	 * 
	 * @param Object �� ������Ʈ�� �����ϴ� ������Ʈ�� ������ ���Դϴ�.
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
	 * @biref ��Ʈ�ι̳��� ���� ó�� ������Ʈ ���� �Ҹ����Դϴ�.
	 */
	virtual ~TetrominoPhysicComponent() {}


	/**
	 * @brief ������Ʈ�� ���� ������ �� ���Կ����ڸ� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(TetrominoPhysicComponent);


	/**
	 * @brief ��Ʈ�ι̳��� ���� ó�� ������Ʈ�� ������Ʈ�մϴ�.
	 */
	void Tick();


	/**
	 * @brief ��Ʈ�ι̳븦 Ư�� ��ġ�� �̵���ŵ�ϴ�.
	 *
	 * @param LTPosition ��Ʈ�ι̳븦 �̵� ��ų Ư�� ��ġ�Դϴ�.
	 *
	 * @return �ڷ���Ʈ��Ų ��ġ�� �浹�� �߻����� ������ true, �浹�� �߻��ϸ� false�� ��ȯ�մϴ�.
	 */
	bool Teleport(const Vec2f& LTPosition);


	/**
	 * @brief ������� �浹�� �˻��մϴ�.
	 * 
	 * @return ����� �浹�� �߻��ϸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsCollision();


private:
	/**
	 * @brief ��Ʈ�ι̳븦 Ư�� �������� �����Դϴ�.
	 * 
	 * @param Direction ��Ʈ�ι̳밡 �̵��� �����Դϴ�.
	 * @param Shape ��Ʈ�ι̳��� ����Դϴ�.
	 * @param Blocks ��Ʈ�ι̳��� �������Դϴ�.
	 */
	void Move(const Tetromino::EDirection& Direction, const Tetromino::EShape& Shape, std::array<BlockComponent*, 4>& Blocks);


	/**
	 * @brief ���� �ٸ� �������� �浹�� �˻��մϴ�.
	 * 
	 * @param LhsBlocks ���� �������Դϴ�.
	 * @param RhsBlocks ���� �� �ٸ� �������Դϴ�.
	 * 
	 * @return ���� �ٸ� �������� �浹�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsCollisionBlocks(const std::vector<BlockComponent*>& LhsBlocks, const std::array<BlockComponent*, 4>& RhsBlocks);


	/**
	 * @brief ��Ʈ�ι̳� �������� �߽� ��ġ�� ����մϴ�.
	 *
	 * @param Shape ��Ʈ�ι̳��� ����Դϴ�.
	 * @param LTPosition ��Ʈ�ι̳��� ���� ����� ��ǥ�Դϴ�.
	 * @param BlockSide ��Ʈ�ι̳� ������ ũ���Դϴ�.
	 *
	 * @return ��Ʈ�ι̳� �������� �߽� ��ġ�� ��ȯ�մϴ�.
	 */
	Vec2f CalculateBlocksCenter(const Tetromino::EShape& Shape, const Vec2f& LTPosition, const float& BlockSide);


	/**
	 * @brief ��Ʈ�ι̳밡 �����̴� ������ �ݴ� ������ ����ϴ�.
	 *
	 * @param Direction �ݴ� ������ ���� ��Ʈ�ι̳��� �̵� �����Դϴ�.
	 *
	 * @return �Ķ���ͷ� ������ ������ �ݴ� ������ ��ȯ�մϴ�.
	 */
	static Tetromino::EDirection GetCountDirection(const Tetromino::EDirection& Direction);


private:
	/**
	 * @brief ��Ʈ�ι̳��� ���� ��� ��ǥ�Դϴ�.
	 *
	 * @note LT = Left Top�� �ǹ��մϴ�.
	 */
	Vec2f LTPosition_;


	/**
	 * @brief ��Ʈ�ι̳� ������ ũ���Դϴ�.
	 */
	float BlockSide_ = 0.0f;


	/**
	 * @brief ��Ʈ�ι̳밡 �����̴� �Ÿ��Դϴ�.
	 */
	float MoveLength_ = 0.0f;
};