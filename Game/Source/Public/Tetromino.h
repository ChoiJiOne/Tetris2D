#pragma once

#include <array>

#include "BlockComponent.h"
#include "GameObject.h"


/**
 * @brief ��Ʈ���� ������ ��Ʈ�ι̳��Դϴ�.
 */
class Tetromino : public GameObject
{
public:
	/**
	 * @brief ��Ʈ�ι̳��� ��� Ÿ���Դϴ�.
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
	 * @brief ��Ʈ�ι̳��� ������ �����Դϴ�.
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


public:
	/**
	 * @brief ��Ʈ�ι̳��� �������Դϴ�.
	 *
	 * @param Signature ��Ʈ�ι̳��� �ĺ����Դϴ�.
	 * @param LTPosition ��Ʈ�ι̳��� ���� ����� ��ǥ�Դϴ�.
	 * @param Side ��Ʈ�ι̳� ������ ũ���Դϴ�.
	 * @param MoveStep ��Ʈ�ι̳밡 �� �� ������ ���� �ð� �Դϴ�.
	 */
	Tetromino(
		const std::string& Signature,
		const Vec2f& LTPosition,
		const float& Side,
		const float& MoveStep
	);


	/**
	 * @brief ��Ʈ�ι̳��� �������Դϴ�.
	 * 
	 * @param Signature ��Ʈ�ι̳��� �ĺ����Դϴ�.
	 * @param LTPosition ��Ʈ�ι̳��� ���� ����� ��ǥ�Դϴ�.
	 * @param Side ��Ʈ�ι̳� ������ ũ���Դϴ�.
	 * @param Type ��Ʈ�ι̳� ������ Ÿ���Դϴ�.
	 * @param MoveStep ��Ʈ�ι̳밡 �� �� ������ ���� �ð� �Դϴ�.
	 * @param Shape ��Ʈ�ι̳��� ����Դϴ�.
	 */
	Tetromino(
		const std::string& Signature,
		const Vec2f& LTPosition,
		const float& Side,
		const BlockComponent::EType& Type,
		const float& MoveStep,
		const EShape& Shape
	);


	/**
	 * @brief ��Ʈ�ι̳��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Tetromino();


	/**
	 * @brief ���������� ���� �����ڿ� ���� �����ڸ� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Tetromino);


	/**
	 * @brief ��׶��带 ������Ʈ�մϴ�.
	 *
	 * @param DeltaSeconds �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float DeltaSeconds) override;


	/**
	 * @brief ��Ʈ�ι̳��� �������� ����ϴ�.
	 * 
	 * @return ��Ʈ�ι̳��� �������� ��ȯ�մϴ�.
	 */
	const std::array<BlockComponent*, 4>& GetBlocks() const { return Blocks_; }


private:
	/**
	 * @brief ��Ʈ�ι̳��� �������� �����մϴ�.
	 * 
	 * @param LTPosition ��Ʈ�ι̳��� ���� ����� ��ǥ�Դϴ�.
	 * @param Side ��Ʈ�ι̳� ������ ũ���Դϴ�.
	 * @param Type ��Ʈ�ι̳� ������ Ÿ���Դϴ�.
	 * @param Shape ��Ʈ�ι̳��� ����Դϴ�.
	 */
	void CreateTetrominoBlocks(
		const Vec2f& LTPosition,
		const float& Side,
		const BlockComponent::EType& Type,
		const EShape& Shape
	);


private:
	/**
	 * @brief ��Ʈ�ι̳��� ���� ��� ��ǥ�Դϴ�.
	 * 
	 * @note LT = Left Top�� �ǹ��մϴ�.
	 */
	Vec2f LTPosition_;


	/**
	 * @brief ��Ʈ�ι̳밡 ������ �����̴� �ð��Դϴ�.
	 */
	float MoveStep_ = 0.0f;


	/**
	 * @brief ��Ʈ�ι̳��� ����Դϴ�.
	 */
	EShape Shape_ = EShape::NONE;


	/**
	 * @brief ��Ʈ�ι̳��� ���� ������Ʈ�Դϴ�.
	 */
	std::array<BlockComponent*, 4> Blocks_;
};