#pragma once

#include <list>

#include "GameObject.h"
#include "Vector.hpp"

class BlockComponent;


/**
 * @brief 테트리스 게임의 보드입니다.
 */
class Board : public GameObject
{
public:
	/**
	 * @brief 테트리스 게임의 보드 생성자입니다.
	 * 
	 * @param Signature 보드의 식별자입니다.
	 * @param LTPosition 보드의 왼쪽 상단 좌표입니다.
	 * @param RowBlockCount 보드의 세로 블럭 수입니다.
	 * @param ColBlockCount 보드의 가로 블럭 수입니다.
	 * @param Side 보드 내의 블럭 크기입니다.
	 * @param ClearStep 보드를 정리하는 시간입니다.
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
	 * @brief 테트리스 게임의 보드 가상 소멸자입니다.
	 */
	virtual ~Board();


	/**
	 * @brief 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Board);


	/**
	 * @brief 보드를 업데이트합니다.
	 *
	 * @param DeltaSeconds 초단위 델타 시간값입니다.
	 */
	virtual void Tick(float DeltaSeconds) override;


	/**
	 * @brief 보드의 블럭들을 얻습니다.
	 * 
	 * @note 이 메서드를 사용할 경우, 블럭을 변경할 수 없습니다.
	 * 
	 * @return 보드의 블럭들을 반환합니다.
	 */
	const std::list<BlockComponent*>& GetBlocks() const { return Blocks_; }


private:
	/**
	 * @brief 보드의 블럭들을 생성합니다.
	 * 
	 * @param LTPosition 보드의 왼쪽 상단 좌표입니다.
	 * @param Side 보드의 블럭 크기입니다.
	 * @param RowBlockCount 보드의 세로 블럭의 수입니다.
	 * @param ColBlockCount 보드의 가로 블럭의 수입니다.
	 */
	void CreateBoardBlocks(const Vec2f& LTPosition, const float& Side, const int32_t& RowBlockCount, const int32_t& ColBlockCount);


private:
	/**
	 * @brief 보드의 왼쪽 상단 좌표입니다.
	 */
	Vec2f LTPosition_;


	/**
	 * @brief 보드의 블럭 크기입니다.
	 */
	float BlockSide_ = 0.0f;


	/**
	 * @brief 보드의 세로 블럭 수입니다.
	 */
	int32_t RowBlockCount_ = 0;


	/**
	 * @brief 보드의 가로 블럭 수입니다.
	 */
	int32_t ColBlockCount_ = 0;


	/**
	 * @brief 보드의 정리 시간입니다.
	 */
	float ClearStep_ = 0.0f;


	/**
	 * 보드의 블럭 컴포넌트입니다.
	 */
	std::list<BlockComponent*> Blocks_;
};