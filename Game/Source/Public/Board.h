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


	/**
	 * @brief 보드의 위치를 제외한 블럭의 상태입니다.
	 */
	using BlockState = std::pair<BlockComponent::EState, BlockComponent::EColor>;


public:
	/**
	 * @brief 테트리스 게임의 보드 생성자입니다.
	 * 
	 * @param Signature 보드의 식별자입니다.
	 * @param LTPosition 보드의 왼쪽 상단 좌표입니다.
	 * @param RowBlockCount 보드의 세로 블럭 수입니다.
	 * @param ColBlockCount 보드의 가로 블럭 수입니다.
	 * @param Side 보드 내의 블럭 크기입니다.
	 * @param UpdateStep 보드의 업데이트 시간입니다.
	 */
	Board(
		const std::string& Signature,
		const Vec2f& LTPosition,
		const int32_t& RowBlockCount,
		const int32_t& ColBlockCount,
		const float& Side,
		const float& UpdateStep
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
	 * @brief 보드의 업데이트 시간을 얻습니다.
	 * 
	 * @return 보드의 업데이트 시간을 반환합니다.
	 */
	float GetUpdateStep() const { return UpdateStep_; }


	/**
	 * @brief 보드의 업데이트 시간을 설정합니다.
	 * 
	 * @param UpdateStep 설정할 보드의 업데이트 시간입니다.
	 */
	void SetUpdateStep(const float& UpdateStep) { UpdateStep_ = UpdateStep; }


	/**
	 * @brief 보드의 블럭들을 얻습니다.
	 * 
	 * @note 이 메서드를 사용할 경우, 블럭을 변경할 수 없습니다.
	 * 
	 * @return 보드의 블럭들을 반환합니다.
	 */
	const std::vector<BlockComponent*>& GetBlocks() const { return Blocks_; }


	/**
	 * @brief 보드의 블럭들을 얻습니다.
	 * 
	 * @note 이 메서드를 사용할 경우, 블럭을 변경할 수 있습니다.
	 * 
	 * @return 변경 가능한 보드의 블럭들을 반환합니다.
	 */
	std::vector<BlockComponent*>& GetBlocks() { return Blocks_; }


	/**
	 * @brief 보드의 삭제된 라인 수를 얻습니다.
	 * 
	 * @return  보드의 삭제된 라인 수를 반환합니다.
	 */
	int32_t GetRemoveLine() const { return CountOfRemoveLine_; }


	/**
	 * @brief 보드의 블럭들을 추가합니다.
	 * 
	 * @param Blocks 추가할 블럭들입니다.
	 */
	void AddBlocks(const std::array<BlockComponent*, 4>& Blocks);


private:
	/**
	 * @brief 보드의 블럭들을 생성합니다. 생성합니다.
	 */
	void CreateBoardBlocks();


	/**
	 * @brief 보드의 라인이 채워져 있는지 검사합니다.
	 *
	 * @param RowLine 검사를 수행할 행입니다.
	 *
	 * @return 보드의 라인이 채워져있다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsFullRowLine(const int32_t& RowLine);


	/**
	 * @brief 보드의 라인이 비워져있는지 검사합니다.
	 *
	 * @param RowLine 검사를 수행할 행입니다.
	 *
	 * @return 보드의 라인이 비워져있다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsEmptyRowLine(const int32_t& RowLine);


	/**
	 * @brief 보드의 라인을 지웁니다.
	 *
	 * @param RowLine 삭제할 라인입니다.
	 */
	void RemoveRowLine(const int32_t& RowLine);


	/**
	 * @brief 보드에 삭제할 라인이 있는지 찾습니다.
	 * 
	 * @return 보드의 가장 아래 라인에서 가까운 라인을 찾아서 반환합니다. 삭제할 라인이 없다면 -1을 반환합니다.
	 */
	int32_t FindRemoveRowLine();


	/**
	 * @brief 보드의 비어있는 라인을 채워 정리합니다.
	 */
	void CleanupEmptyRowLine();


	/**
	 * @brief 보드의 모든 라인을 삭제합니다.
	 */
	void CleanupAllRowLine();


	/**
	 * @brief 보드 내 블럭들의 복사본을 얻습니다.
	 * 
	 * @return 보드 내 블럭들의 복사본을 반환합니다.
	 */
	std::vector<BlockState> GetCopyBoardBlocks();


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
	 * @brief 보드의 삭제한 라인 수입니다.
	 */
	int32_t CountOfRemoveLine_ = 0;


	/**
	 * @brief 레벨업에 필요한 라인 수입니다.
	 */
	int32_t LevelRemoveLine_ = 0;


	/**
	 * @brief 프레임 누적 시간입니다.
	 */
	float AccrueFrameTime_ = 0.0f;


	/**
	 * @brief 보드의 업데이트 시간입니다.
	 */
	float UpdateStep_ = 0.0f;


	/**
	 * 보드의 블럭 컴포넌트입니다.
	 */
	std::vector<BlockComponent*> Blocks_;
};