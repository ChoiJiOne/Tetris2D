#pragma once

#include <array>
#include <vector>

#include "BlockComponent.h"
#include "GameObject.h"
#include "Vector.hpp"


/**
 * @brief 테트리스 게임의 보드입니다.
 */
class Board : public GameObject
{
public:
	/**
	 * @brief 보드의 상태입니다.
	 */
	enum class EState : int32_t
	{
		WAIT   = 0,
		ACTIVE = 1
	};


	/**
	 * @brief 보드의 가로/세로 상대 위치를 나타냅니다.
	 */
	using ColRow = std::pair<int32_t, int32_t>;


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
	 * @brief 보드의 상태를 얻습니다.
	 * 
	 * @return 보드의 상태를 반환합니다.
	 */
	EState GetState() const { return State_; }


	/**
	 * @brief 보드의 상태를 설정합니다.
	 * 
	 * @param State 설정할 보드의 상태입니다.
	 */
	void SetState(const EState& State) { State_ = State; }


	/**
	 * @brief 보드의 블럭들을 얻습니다.
	 * 
	 * @note 이 메서드를 사용할 경우, 블럭을 변경할 수 없습니다.
	 * 
	 * @return 보드의 블럭들을 반환합니다.
	 */
	const std::vector<BlockComponent*>& GetBlocks() const { return Blocks_; }


private:
	/**
	 * @brief 보드의 벽을 생성합니다.
	 */
	void CreateBoardWall();


	/**
	 * @brief 보드의 블럭을 생성합니다.
	 * 
	 * @param BlockColRow 블럭의 보드 상 상대 위치입니다.
	 * @param Type 블럭의 타입입니다.
	 */
	void CreateBlock(const ColRow& BlockColRow, const BlockComponent::EType& Type);


	/**
	 * @brief 보드의 블럭을 삭제합니다.
	 * 
	 * @note 존재하지 않는 블럭을 삭제하려는 시도는 무시됩니다.
	 * 
	 * @param BlockColRow 블럭의 보드 상 상대 위치입니다.
	 */
	void DestroyBlock(const ColRow& BlockColRow);


	/**
	 * @brief 보드의 블럭이 존재하는지 확인합니다.
	 * 
	 * @param BlockColRow 블럭의 보드 상 상대 위치입니다.
	 */
	bool IsExistBlock(const ColRow& BlockColRow);


	/**
	 * @brief 보드의 상대 좌표로부터 월드 상의 블럭 위치를 계산합니다.
	 * 
	 * @note
	 *       ← Col →
	 *     ┌─────────┐
	 *  ↑  │         │
	 * Row │         │
	 *  ↓  │         │
	 *     └─────────┘
	 * 
	 * @param LTPosition 보드의 왼쪽 상단 좌표입니다.
	 * @param BlockColRow 블럭의 상대 좌표입니다.
	 * @param Side 블럭의 크기입니다.
	 * 
	 * @return 계산된 보드의 상대 좌표로부터 월드 상의 블럭 위치를 반환합니다.
	 */
	Vec2f CalculateBlockPositionFromColRow(const Vec2f& LTPosition, const ColRow& BlockColRow, const float& Side) const;


	/**
	 * @brief 보드 내 블럭의 (Col, Row) 위치를 얻습니다.
	 * 
	 * @note
	 *       ← Col →
	 *     ┌─────────┐
	 *  ↑  │         │
	 * Row │         │
	 *  ↓  │         │
	 *     └─────────┘
	 * 
	 * @param LTPosition 보드의 왼쪽 상단 좌표입니다.
	 * @param Block 위치를 계산할 블럭입니다.
	 * @param Side 블럭의 크기입니다.
	 * 
	 * @param 계산된 보드 내 블럭의 (Col, Row) 위치를 반환합니다.
	 */
	ColRow CalculateColRowFromBlock(const Vec2f& LTPosition, const BlockComponent* Block, const float& Side) const;


private:
	/**
	 * @brief 보드의 상태입니다..
	 */
	EState State_ = EState::WAIT;


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
	std::vector<BlockComponent*> Blocks_;
};