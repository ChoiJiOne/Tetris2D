#pragma once

#include <list>

#include "GameObject.h"
#include "Vector.hpp"

class BlockComponent;


/**
 * @brief ��Ʈ���� ������ �����Դϴ�.
 */
class Board : public GameObject
{
public:
	/**
	 * @brief ��Ʈ���� ������ ���� �������Դϴ�.
	 * 
	 * @param Signature ������ �ĺ����Դϴ�.
	 * @param LTPosition ������ ���� ��� ��ǥ�Դϴ�.
	 * @param RowBlockCount ������ ���� ���� ���Դϴ�.
	 * @param ColBlockCount ������ ���� ���� ���Դϴ�.
	 * @param Side ���� ���� ���� ũ���Դϴ�.
	 * @param ClearStep ���带 �����ϴ� �ð��Դϴ�.
	 */
	Board(
		const std::string& Signature,
		const Vec2f& LTPosition,
		const int32_t& RowBlockCount,
		const int32_t& ColBlockCount,
		const float& Side,
		const float& ClearStep
	);


	/**
	 * @brief ��Ʈ���� ������ ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Board();


	/**
	 * @brief ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Board);


	/**
	 * @brief ���带 ������Ʈ�մϴ�.
	 *
	 * @param DeltaSeconds �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float DeltaSeconds) override;


	/**
	 * @brief ������ �������� ����ϴ�.
	 * 
	 * @note �� �޼��带 ����� ���, ������ ������ �� �����ϴ�.
	 * 
	 * @return ������ �������� ��ȯ�մϴ�.
	 */
	const std::list<BlockComponent*>& GetBlocks() const { return Blocks_; }


private:
	/**
	 * @brief ������ �������� �����մϴ�.
	 * 
	 * @param LTPosition ������ ���� ��� ��ǥ�Դϴ�.
	 * @param Side ������ ���� ũ���Դϴ�.
	 * @param RowBlockCount ������ ���� ������ ���Դϴ�.
	 * @param ColBlockCount ������ ���� ������ ���Դϴ�.
	 */
	void CreateBoardBlocks(const Vec2f& LTPosition, const float& Side, const int32_t& RowBlockCount, const int32_t& ColBlockCount);


private:
	/**
	 * @brief ������ ���� ��� ��ǥ�Դϴ�.
	 */
	Vec2f LTPosition_;


	/**
	 * @brief ������ ���� ũ���Դϴ�.
	 */
	float BlockSide_ = 0.0f;


	/**
	 * @brief ������ ���� ���� ���Դϴ�.
	 */
	int32_t RowBlockCount_ = 0;


	/**
	 * @brief ������ ���� ���� ���Դϴ�.
	 */
	int32_t ColBlockCount_ = 0;


	/**
	 * @brief ������ ���� �ð��Դϴ�.
	 */
	float ClearStep_ = 0.0f;


	/**
	 * ������ ���� ������Ʈ�Դϴ�.
	 */
	std::list<BlockComponent*> Blocks_;
};