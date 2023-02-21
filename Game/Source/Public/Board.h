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
	 * @param LevelUpCondition 레벨업 조건입니다.
	 */
	Board(
		const std::string& Signature,
		const Vec2f& LTPosition,
		const int32_t& RowBlockCount,
		const int32_t& ColBlockCount,
		const float& Side,
		const float& UpdateStep,
		const int32_t& LevelUpCondition
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


	/**
	 * @brief 보드의 블럭들을 얻습니다.
	 * 
	 * @note 이 메서드를 사용할 경우, 블럭을 변경할 수 있습니다.
	 * 
	 * @return 변경 가능한 보드의 블럭들을 반환합니다.
	 */
	std::vector<BlockComponent*>& GetBlocks() { return Blocks_; }


	/**
	 * @brief 보드의 블럭들에 새로운 블럭들을 추가합니다.
	 * 
	 * @param NewBlocks 추가할 새로운 블럭들입니다.
	 */
	void AddBlocks(const std::array<BlockComponent*, 4>& NewBlocks);


	/**
	 * @brief 보드의 삭제된 라인 수를 얻습니다.
	 * 
	 * @return 보드의 삭제된 라인 수를 반환합니다.
	 */
	int32_t GetRemoveLine();


	/**
	 * @brief 레벨업에 필요한 라인 수를 얻습니다.
	 *
	 * @return 레벨업에 필요한 라인 수를 반환합니다.
	 */
	int32_t GetLevelRemoveLine();


	/**
	 * @brief 레벨업에 필요한 라인 수를 초기화합니다.
	 */
	void ResetLevelRemoveLine();


	/**
	 * @brief 보드의 업데이트 시간을 설정합니다.
	 * 
	 * @param UpdateStep 설정할 보드의 업데이트 시간입니다.
	 */
	void SetUpdateStep(const float& UpdateStep);


private:
	/**
	 * @brief 보드의 상태입니다..
	 */
	EState State_ = EState::WAIT;


	/**
	 * 보드의 블럭 컴포넌트입니다.
	 */
	std::vector<BlockComponent*> Blocks_;
};