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
};