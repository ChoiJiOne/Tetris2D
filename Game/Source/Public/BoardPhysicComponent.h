#pragma once

#include "PhysicComponent.h"
#include "BlockComponent.h"


/**
 * @brief ������ ���� ó�� ������Ʈ�Դϴ�.
 */
class BoardPhysicComponent : public PhysicComponent
{
public:
	/**
	 * @brief ������ ����/���� ��� ��ġ�� ��Ÿ���ϴ�.
	 */
	using ColRow = std::pair<int32_t, int32_t>;


	/**
	 * @brief ������ ��ġ�� ������ ������ �����Դϴ�.
	 */
	using BlockState = std::pair<BlockComponent::EState, BlockComponent::EColor>;


public:
	/**
	 * @brief ������ ���� ó�� ������Ʈ �������Դϴ�.
	 * 
	 * @param Object �� ������Ʈ�� �����ϴ� ������Ʈ�� ������ ���Դϴ�.
	 * @param LTPosition ������ ���� ��� ��ǥ�Դϴ�.
	 * @param RowBlockCount ������ ���� ���� ���Դϴ�.
	 * @param ColBlockCount ������ ���� ���� ���Դϴ�.
	 * @param Side ���� ���� ���� ũ���Դϴ�.
	 * @param UpdateStep ������ ������Ʈ �ð��Դϴ�.
	 * @param LevelUpCondition �������� ������ �����Դϴ�.
	 */
	BoardPhysicComponent(
		GameObject* Object,
		const Vec2f& LTPosition,
		const int32_t& RowBlockCount,
		const int32_t& ColBlockCount,
		const float& Side,
		const float& UpdateStep,
		const int32_t& LevelUpCondition
	);


	/**
	 * @brief ������ ���� ó�� ������Ʈ ���� �Ҹ����Դϴ�.
	 */
	virtual ~BoardPhysicComponent();


	/**
	 * @brief ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(BoardPhysicComponent);


	/**
	 * @brief ������ ���� ó�� ������Ʈ�� ������Ʈ�մϴ�.
	 * 
	 * @param �� ���� ��Ÿ �ð� ���Դϴ�.
	 */
	void Tick(float DeltaSeconds);


	/**
	 * @brief ������ ������Ʈ �ð��� ����ϴ�.
	 *
	 * @return ������ ������Ʈ �ð��� ��ȯ�մϴ�.
	 */
	float GetUpdateStep() const { return UpdateStep_; }


	/**
	 * @brief ������ ������Ʈ �ð��� �����մϴ�.
	 *
	 * @param UpdateStep ������ ������ ������Ʈ �ð��Դϴ�.
	 */
	void SetUpdateStep(const float& UpdateStep) { UpdateStep_ = UpdateStep; }


	/**
	 * @brief ������ ������ ���� ���� ����ϴ�.
	 *
	 * @return  ������ ������ ���� ���� ��ȯ�մϴ�.
	 */
	int32_t GetRemoveLine() const { return CountOfRemoveLine_; }


	/**
	 * @brief �������� �ʿ��� ���� ���� ����ϴ�.
	 * 
	 * @return �������� �ʿ��� ���� ���� ��ȯ�մϴ�.
	 */
	int32_t GetLevelRemoveLine() const { return LevelRemoveLine_; }


	/**
	 * @brief �������� �ʿ��� ���� ���� �ʱ�ȭ�մϴ�.
	 */
	void ResetLevelRemoveLine() { LevelRemoveLine_ = 0; }


	/**
	 * @brief ������ ������ �߰��մϴ�.
	 * 
	 * @param BoardBlocks ������ �������Դϴ�.
	 * @param AddBlocks �߰��� �������Դϴ�.
	 */
	void AddBlocksInBoard(std::vector<BlockComponent*>& BoardBlocks, const std::array<BlockComponent*, 4>& AddBlocks);


private:
	/**
	 * @brief ������ �������� �����մϴ�. �����մϴ�.
	 * 
	 * @param Blocks ������ ������ ������ �����Դϴ�.
	 */
	void CreateBoardBlocks(std::vector<BlockComponent*>& Blocks);


	/**
	 * @brief ������ ������ ä���� �ִ��� �˻��մϴ�.
	 *
	 * @param Blocks �˻縦 ������ ������ �����Դϴ�.
	 * @param RowLine �˻縦 ������ ���Դϴ�.
	 *
	 * @return ������ ������ ä�����ִٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsFullRowLine(const std::vector<BlockComponent*>& Blocks, const int32_t& RowLine);


	/**
	 * @brief ������ ������ ������ִ��� �˻��մϴ�.
	 * 
	 * @param Blocks �˻縦 ������ ������ �����Դϴ�.
	 * @param RowLine �˻縦 ������ ���Դϴ�.
	 *
	 * @return ������ ������ ������ִٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsEmptyRowLine(const std::vector<BlockComponent*>& Blocks, const int32_t& RowLine);


	/**
	 * @brief ������ ������ ����ϴ�.
	 *
	 * @param RowLine ������ �����Դϴ�.
	 */
	void RemoveRowLine(std::vector<BlockComponent*>& Blocks, const int32_t& RowLine);


	/**
	 * @brief ���忡 ������ ������ �ִ��� ã���ϴ�.
	 *
	 * @param Blocks ���忡 ������ ������ ã�� �������Դϴ�.
	 * 
	 * @return ������ ���� �Ʒ� ���ο��� ����� ������ ã�Ƽ� ��ȯ�մϴ�. ������ ������ ���ٸ� -1�� ��ȯ�մϴ�.
	 */
	int32_t FindRemoveRowLine(const std::vector<BlockComponent*>& Blocks);


	/**
	 * @brief ������ ����ִ� ������ ä�� �����մϴ�.
	 * 
	 * @param Blocks ������ ������ �������Դϴ�.
	 */
	void CleanupEmptyRowLine(std::vector<BlockComponent*>& Blocks);


	/**
	 * @brief ������ ��� ������ �����մϴ�.
	 * 
	 * @param Blocks ��� ������ ������ ������ �������Դϴ�.
	 */
	void CleanupAllRowLine(std::vector<BlockComponent*>& Blocks);


	/**
	 * @brief ���� �� �������� ���纻�� ����ϴ�.
	 *
	 * @param Blocks ���纻�� ������ ������ �������Դϴ�.
	 * 
	 * @return ���� �� �������� ���纻�� ��ȯ�մϴ�.
	 */
	std::vector<BlockState> GetCopyBoardBlocks(const std::vector<BlockComponent*>& Blocks);


	/**
	 * @brief ������ ��� ��ǥ�κ��� ���� ���� ���� ��ġ�� ����մϴ�.
	 *
	 * @note
	 *       �� Col ��
	 *     ����������������������
	 *  ��  ��         ��
	 * Row ��         ��
	 *  ��  ��         ��
	 *     ����������������������
	 *
	 * @param LTPosition ������ ���� ��� ��ǥ�Դϴ�.
	 * @param BlockColRow ������ ��� ��ǥ�Դϴ�.
	 * @param Side ������ ũ���Դϴ�.
	 *
	 * @return ���� ������ ��� ��ǥ�κ��� ���� ���� ���� ��ġ�� ��ȯ�մϴ�.
	 */
	Vec2f CalculateBlockPositionFromColRow(const Vec2f& LTPosition, const ColRow& BlockColRow, const float& Side) const;


	/**
	 * @brief ���� �� ������ (Col, Row) ��ġ�� ����ϴ�.
	 *
	 * @note
	 *       �� Col ��
	 *     ����������������������
	 *  ��  ��         ��
	 * Row ��         ��
	 *  ��  ��         ��
	 *     ����������������������
	 *
	 * @param LTPosition ������ ���� ��� ��ǥ�Դϴ�.
	 * @param Block ��ġ�� ����� �����Դϴ�.
	 * @param Side ������ ũ���Դϴ�.
	 *
	 * @param ���� ���� �� ������ (Col, Row) ��ġ�� ��ȯ�մϴ�.
	 */
	ColRow CalculateColRowFromBlock(const Vec2f& LTPosition, const BlockComponent* Block, const float& Side) const;


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
	 * @brief ������ ������ ���� ���Դϴ�.
	 */
	int32_t CountOfRemoveLine_ = 0;


	/**
	 * @brief ������ �����Դϴ�.
	 */
	int32_t LevelUpCondition_ = 0;


	/**
	 * @brief �������� �ʿ��� ���� ���Դϴ�.
	 */
	int32_t LevelRemoveLine_ = 0;


	/**
	 * @brief ������ ���� �ð��Դϴ�.
	 */
	float AccrueFrameTime_ = 0.0f;


	/**
	 * @brief ������ ������Ʈ �ð��Դϴ�.
	 */
	float UpdateStep_ = 0.0f;
};