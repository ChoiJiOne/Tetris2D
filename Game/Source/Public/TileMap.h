#pragma once

#include <vector>

#include "GameObject.h"
#include "Tile.h"


/**
 * @brief 2D Ÿ�� ���Դϴ�.
 */
class TileMap : public GameObject
{
public:
	/**
	 * @brief 2D Ÿ�ϸ��� �������Դϴ�.
	 * 
	 * @param Signature Ÿ�� ���� �ĺ����Դϴ�.
	 * @param CenterPosition 2D ���� ���� Ÿ�ϸ��� �߽� ��ǥ�Դϴ�.
	 * @param RowSize Ÿ�ϸ��� ���� ũ���Դϴ�.
	 * @param ColSize Ÿ�ϸ��� ���� ũ���Դϴ�.
	 * @param TileSize Ÿ���� ũ���Դϴ�.
	 */
	TileMap(
		const std::string& Signature,
		const Vec2f& CenterPosition,
		const int32_t& RowSize,
		const int32_t& ColSize,
		const int32_t& TileSize
	);


	/**
	 * @brief 2D Ÿ�ϸ��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~TileMap() {}


	/**
	 * @brief ���������� ���� �����ڿ� ���� �����ڸ� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(TileMap);


	/**
	 * @brief Ÿ�� ���� ������Ʈ�մϴ�.
	 * 
	 * @param DeltaSeconds �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float DeltaSeconds) override;


	/**
	 * @brief Ÿ���� ���� ũ�⸦ ����ϴ�.
	 * 
	 * @return Ÿ���� ���� ũ�⸦ ��ȯ�մϴ�.
	 */
	int32_t GetColSize() const { return ColSize_; }


	/**
	 * @brief Ÿ���� ���� ũ�⸦ ����ϴ�.
	 * 
	 * @return Ÿ���� ���� ũ�⸦ ����ϴ�.
	 */
	int32_t GetRowSize() const { return RowSize_; }


	/**
	 * @brief Ÿ���� Ÿ�� �� ������ ������� Ȯ���մϴ�.
	 * 
	 * @param TargetTile �˻縦 ������ Ÿ���Դϴ�.
	 * 
	 * @return ������ ����� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsOutOfRangeTileInMap(const Tile& TargetTile);


	/**
	 * @brief Ÿ�� �ʿ� Ÿ���� �߰��մϴ�.
	 * 
	 * @note �߰��� Ÿ���� Ÿ�� �� ������ ����� �ƹ� ���۵� �������� �ʽ��ϴ�.
	 * 
	 * @param AddTile Ÿ�� �ʿ� �߰��� Ÿ���Դϴ�.
	 */
	void AddTileInMap(const Tile& AddTile);


	/**
	 * @brief Ÿ�� �� ���� Ÿ���� �����մϴ�.
	 * 
	 * @note ������ Ÿ���� Ÿ�� �� ������ ����� �ƹ� ���۵� �������� �ʽ��ϴ�.
	 * 
	 * @param RemoveTile Ÿ�� �ʿ� ������ Ÿ���Դϴ�.
	 */
	void RemoveTileInMap(const Tile& RemoveTile);


	/**
	 * @brief Ÿ�� �� ���� Ÿ���� ����ϴ�.
	 * 
	 * @param Position Ÿ�� �� ���� ��ġ�Դϴ�.
	 * 
	 * @throws ��ǥ�� Ÿ�� ���� ����� C++ ǥ�ؿ��ܸ� �����ϴ�.
	 * 
	 * @return Ÿ�� �� ���� ��ġ�� �����ϴ� Ÿ���� ��ȯ�մϴ�.
	 */
	Tile& GetTileInMap(const Vec2i& Position);


	/**
	 * @brief Ÿ�� �� ���� Ÿ�ϰ� �浹�� �˻��մϴ�.
	 * 
	 * @note ������ ����� ������ �浹 ó���˴ϴ�.
	 * 
	 * @param CollisionTile �浹�ϴ��� �˻��� Ÿ���Դϴ�.
	 * 
	 * @return Ÿ�� �� ���� Ÿ�ϰ� �浹�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsCollisionTileInMap(const Tile& CollisionTile);


	/**
	 * @brief Ÿ�ϵ��� Ÿ�� ���� ������� Ȯ���մϴ�.
	 * 
	 * @param Tiles �˻縦 ������ Ÿ���Դϴ�.
	 * 
	 * @return ������ ����� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsOutOfRangeTilesInMap(const std::vector<Tile>& Tiles);


	/**
	 * @brief Ÿ�� �ʿ� Ÿ�ϵ��� �߰��մϴ�.
	 * 
	 * @note �߰��� Ÿ���� Ÿ�� �� ������ ����� �ƹ� ���۵� �������� �ʽ��ϴ�.
	 * 
	 * @param Tiles Ÿ�� �ʿ� �߰��� Ÿ�ϵ��Դϴ�.
	 */
	void AddTilesInMap(const std::vector<Tile>& Tiles);


	/**
	 * @brief Ÿ�� �� ���� Ÿ�ϵ��� �����մϴ�.
	 * 
	 * @note ������ Ÿ���� Ÿ�� �� ������ ����� �ƹ� ���۵� �������� �ʽ��ϴ�.
	 * 
	 * @param Tiles Ÿ�� �ʿ� ������ Ÿ�ϵ��Դϴ�.
	 */
	void RemoveTilesInMap(const std::vector<Tile>& Tiles);


	/**
	 * @brief Ÿ�� �� ���� Ÿ�ϵ�� �浹�� �˻��մϴ�.
	 *
	 * @note ������ ����� ������ �浹 ó���˴ϴ�.
	 *
	 * @param Tiles �浹�ϴ��� �˻��� Ÿ���Դϴ�.
	 *
	 * @return Ÿ�� �� ���� Ÿ�ϰ� �浹�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsCollisionTilesInMap(const std::vector<Tile>& Tiles);


	/**
	 * @brief Ÿ�ϸ��� �ʱ�ȭ�մϴ�.
	 */
	void ClearMap();


private:
	/**
	 * @brief ��ǥ�� Ÿ�� ���� ������ ������� �˻��մϴ�.
	 * 
	 * @param Position �˻縦 ������ ��ǥ�Դϴ�.
	 * 
	 * @return ��ǥ�� Ÿ�� ������ ����ٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsOutOfRangePositionInMap(const Vec2i& Position);


	/**
	 * @brief Ÿ�� �ʿ� Ÿ���� �߰��մϴ�.
	 *
	 * @note �߰��� Ÿ���� Ÿ�� �� ������ ����� �ƹ� ���۵� �������� �ʽ��ϴ�.
	 *
	 * @param AddTile Ÿ�� �ʿ� �߰��� Ÿ���Դϴ�.
	 * @param bIsCheckRange ���� �˻� ���� �����Դϴ�.
	 */
	void AddTileInMap(const Tile& AddTile, bool bIsCheckRange);


	/**
	 * @brief Ÿ�� �� ���� Ÿ���� �����մϴ�.
	 *
	 * @note ������ Ÿ���� Ÿ�� �� ������ ����� �ƹ� ���۵� �������� �ʽ��ϴ�.
	 *
	 * @param RemoveTile Ÿ�� �ʿ� ������ Ÿ���Դϴ�.
	 * @param bIsCheckRange ���� �˻� ���� �����Դϴ�.
	 */
	void RemoveTileInMap(const Tile& RemoveTile, bool bIsCheckRange);


private:
	/**
	 * @brief 2D ���� ���� Ÿ�ϸ��� �߽� ��ġ�Դϴ�.
	 */
	Vec2f CenterPosition_;


	/**
	 * @brief Ÿ���� ���� ũ���Դϴ�.
	 */
	int32_t ColSize_ = 0;


	/**
	 * @brief Ÿ���� ���� ũ���Դϴ�.
	 */
	int32_t RowSize_ = 0;


	/**
	 * @brief 2D ���� Ÿ���� ũ���Դϴ�.
	 * 
	 * @note Ÿ���� ���簢���Դϴ�.
	 */
	int32_t TileSize_ = 0;


	/**
	 * @brief 2D Ÿ�ϸ��Դϴ�.
	 */
	std::vector<Tile> Tiles_;


	/**
	 * @brief Ÿ�� ���� �����ϴ� �ؽ�ó �ñ״�ó�Դϴ�.
	 */
	static std::unordered_map<Tile::EColor, std::string> TileColorSignature_;
};