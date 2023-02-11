#pragma once

#include "PhysicComponent.h"
#include "BlockComponent.h"


/**
 * @brief 보드의 물리 처리 컴포넌트입니다.
 */
class BoardPhysicComponent : public PhysicComponent
{
public:
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
	 * @brief 보드의 물리 처리 컴포넌트 생성자입니다.
	 * 
	 * @param Object 이 컴포넌트를 소유하는 오브젝트의 포인터 값입니다.
	 */
	BoardPhysicComponent(
		GameObject* Object,
		const Vec2f& LTPosition,
		const int32_t& RowBlockCount,
		const int32_t& ColBlockCount,
		const float& Side,
		const float& UpdateStep
	);


	/**
	 * @brief 보드의 물리 처리 컴포넌트 가상 소멸자입니다.
	 */
	virtual ~BoardPhysicComponent();


	/**
	 * @brief 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(BoardPhysicComponent);


	/**
	 * @brief 보드의 물리 처리 컴포넌트를 업데이트합니다.
	 * 
	 * @param 초 단위 델타 시간 값입니다.
	 */
	void Tick(float DeltaSeconds);


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
	 * @brief 보드의 삭제된 라인 수를 얻습니다.
	 *
	 * @return  보드의 삭제된 라인 수를 반환합니다.
	 */
	int32_t GetRemoveLine() const { return CountOfRemoveLine_; }


	/**
	 * @brief 보드의 블럭을 추가합니다.
	 * 
	 * @param BoardBlocks 보드의 블럭들입니다.
	 * @param AddBlocks 추가할 블럭들입니다.
	 */
	void AddBlocksInBoard(std::vector<BlockComponent*>& BoardBlocks, const std::array<BlockComponent*, 4>& AddBlocks);


private:
	/**
	 * @brief 보드의 블럭들을 생성합니다. 생성합니다.
	 * 
	 * @param Blocks 생성한 블럭을 저장할 벡터입니다.
	 */
	void CreateBoardBlocks(std::vector<BlockComponent*>& Blocks);


	/**
	 * @brief 보드의 라인이 채워져 있는지 검사합니다.
	 *
	 * @param Blocks 검사를 수행할 보드의 블럭입니다.
	 * @param RowLine 검사를 수행할 행입니다.
	 *
	 * @return 보드의 라인이 채워져있다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsFullRowLine(const std::vector<BlockComponent*>& Blocks, const int32_t& RowLine);


	/**
	 * @brief 보드의 라인이 비워져있는지 검사합니다.
	 * 
	 * @param Blocks 검사를 수행할 보드의 블럭입니다.
	 * @param RowLine 검사를 수행할 행입니다.
	 *
	 * @return 보드의 라인이 비워져있다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsEmptyRowLine(const std::vector<BlockComponent*>& Blocks, const int32_t& RowLine);


	/**
	 * @brief 보드의 라인을 지웁니다.
	 *
	 * @param RowLine 삭제할 라인입니다.
	 */
	void RemoveRowLine(std::vector<BlockComponent*>& Blocks, const int32_t& RowLine);


	/**
	 * @brief 보드에 삭제할 라인이 있는지 찾습니다.
	 *
	 * @param Blocks 보드에 삭제할 라인을 찾을 블럭들입니다.
	 * 
	 * @return 보드의 가장 아래 라인에서 가까운 라인을 찾아서 반환합니다. 삭제할 라인이 없다면 -1을 반환합니다.
	 */
	int32_t FindRemoveRowLine(const std::vector<BlockComponent*>& Blocks);


	/**
	 * @brief 보드의 비어있는 라인을 채워 정리합니다.
	 * 
	 * @param Blocks 정리할 보드의 블럭들입니다.
	 */
	void CleanupEmptyRowLine(std::vector<BlockComponent*>& Blocks);


	/**
	 * @brief 보드의 모든 라인을 삭제합니다.
	 * 
	 * @param Blocks 모든 라인을 삭제할 보드의 블럭들입니다.
	 */
	void CleanupAllRowLine(std::vector<BlockComponent*>& Blocks);


	/**
	 * @brief 보드 내 블럭들의 복사본을 얻습니다.
	 *
	 * @param Blocks 복사본을 생성할 보드의 블럭들입니다.
	 * 
	 * @return 보드 내 블럭들의 복사본을 반환합니다.
	 */
	std::vector<BlockState> GetCopyBoardBlocks(const std::vector<BlockComponent*>& Blocks);


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
};