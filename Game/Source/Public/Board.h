#pragma once

#include "GameObject.h"
#include "Tile.h"


/**
 * @brief ��Ʈ������ �����Դϴ�.
 */
class Board : public GameObject
{
public:
	/**
	 * ��Ʈ���� ������ �����Դϴ�.
	 */
	enum class EState : int32_t
	{
		NONE   = 0,
		WAIT   = 1,
		ACTIVE = 2
	};


public:
	/**
	 * @brief ��Ʈ���� ������ �������Դϴ�.
	 * 
	 * @param Signature ��Ʈ���� ������ �ñ״�ó ���Դϴ�.
	 * @param TilePosition Ÿ�� �� ���� ��Ʈ���� ���� ���� ����� ��ǥ�Դϴ�.
	 * @param Width ��Ʈ���� ������ ���� ũ���Դϴ�.
	 * @param Height ��Ʈ���� ������ ���� ũ���Դϴ�.
	 * 
	 * @throws ��Ʈ���� ���� ������ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	Board(const std::string& Signature, const Vec2i& TilePosition, const int32_t& Width, const int32_t& Height);


	/**
	 * @brief ��Ʈ���� ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Board() {}


	/**
	 * @brief ���������� ���� �����ڿ� ���� �����ڸ� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Board);


	/**
	 * @brief ��Ʈ������ ���带 ������Ʈ�մϴ�.
	 *
	 * @param DeltaSeconds �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float DeltaSeconds) override;


	/**
	 * @brief ������ ���¸� ����ϴ�.
	 *
	 * @return ������ ���¸� ��ȯ�մϴ�.
	 */
	EState GetState() const { return State_; }


	/**
	 * @brief ������ ���¸� �����մϴ�.
	 *
	 * @param State ������ ������ �����Դϴ�.
	 */
	void SetState(const EState& State) { State_ = State; }


	/**
	 * @brief ���忡 ������ ���� ���� ����ϴ�.
	 * 
	 * @return ���忡 ������ ���� ���� ��ȯ�մϴ�.
	 */
	int32_t GetRemoveLine() const { return RemoveLine_; }


	/**
	 * @brief ������ �ִ� ���� �ð��� ����ϴ�.
	 *
	 * @return ������ �ִ� ���� �ð��� ��ȯ�մϴ�.
	 */
	static float GetMaxAccrueTickTime() { return MaxAccrueTickTime_; }


	/**
	 * @brief ������ �ִ� ���� �ð��� �����մϴ�.
	 *
	 * @note �ð��� �ʴ��� �Դϴ�.
	 *
	 * @param MaxAccrueTickTime ������ �ִ� ���� �ð��Դϴ�.
	 */
	static void SetMaxAccrueTickTime(const float& MaxAccrueTickTime);


private:
	/**
	 * @brief ����ִ� ��Ʈ���� ������ Ÿ���� �����մϴ�.
	 * 
	 * @param TilePosition Ÿ�� �� ���� ��Ʈ���� ���� ���� ����� ��ǥ�Դϴ�.
	 * @param Width ��Ʈ���� ������ ���� ũ���Դϴ�.
	 * @param Height ��Ʈ���� ������ ���� ũ���Դϴ�.
	 * 
	 * @return ������ ��Ʈ���� ���� Ÿ���� ���͸� ��ȯ�մϴ�.
	 */
	std::vector<Tile> CreateBoardTile(const Vec2i& TilePosition, const int32_t& Width, const int32_t& Height);


	/**
	 * @brief Ÿ�� �����κ��� ���� Ÿ���� �����մϴ�.
	 */
	void DumpBoardFromTileMap();


	/**
	 * @brief ���� Ÿ���� Ÿ�� �ʿ� �����մϴ�.
	 */
	void DumpTileMapFromBoard();

	
	/**
	 * @brief ������ ���� ���� ��� ���� �������� Ȯ���մϴ�.
	 * 
	 * @param BoardYPosition �˻��� ���� ���� Y��ǥ�Դϴ�.
	 * @param TileState Ȯ���� Ÿ�� �����Դϴ�.
	 * 
	 * @return ������ ���� ���� ��� ���� ���¶�� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsAllSameRowLine(const int32_t& BoardYPosition, const Tile::EState& TileState);


	/**
	 * @brief ������ ���� ���� ������ �� �ִ��� Ȯ���մϴ�.
	 * 
	 * @param BoardYPosition ������ �� �ִ��� Ȯ���� ���� ���� Y��ǥ�Դϴ�.
	 * 
	 * @return ������ �� �ִٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool CanRemoveRowLine(const int32_t& BoardYPosition);


	/**
	 * @brief ������ ���� ���� ����ִ��� Ȯ���մϴ�.
	 * 
	 * @param BoardYPosition ����ִ��� Ȯ���� ���� ���� Y��ǥ�Դϴ�.
	 * 
	 * @return ����ִٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool IsEmptyRowLine(const int32_t& BoardYPosition);


	/**
	 * @brief ������ ���� ���� �����մϴ�.
	 * 
	 * @param BoardYPosition ������ ���� ���Դϴ�.
	 */
	void ClearRowLine(const int32_t& BoardYPosition);


	/**
	 * @brief ������ ����ִ� ���� �������մϴ�.
	 */
	void ArrangeEmptyRowLine();


private:
	/**
	 * @brief Ÿ�� ���� ��Ʈ���� ������ ���� ��� ��ǥ�Դϴ�.
	 */
	Vec2i TilePosition_;


	/**
	 * @brief ��Ʈ���� ������ ���� ũ���Դϴ�.
	 */
	int32_t Width_ = 0;


	/**
	 * @brief ��Ʈ���� ������ ���� ũ���Դϴ�.
	 */
	int32_t Height_ = 0;


	/**
	 * @brief Ÿ�� �� ���� ��Ʈ���� ���� Ÿ���Դϴ�.
	 */
	std::vector<Tile> Tiles_;


	/**
	 * @brief ������ ���� �����Դϴ�.
	 */
	EState State_ = EState::ACTIVE;


	/**
	 * @brief ���尡 ������ ���� ���Դϴ�.
	 */
	int32_t RemoveLine_ = 0;


	/**
	 * @brief ������ ������Ʈ ���� �ð��Դϴ�.
	 */
	float AccrueTickTime_ = 0.0f;


	/**
	 * @brief ������ �ִ� ������Ʈ ���� �ð��Դϴ�.
	 */
	static float MaxAccrueTickTime_;
};