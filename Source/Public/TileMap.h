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
	 * @brief Ÿ�� ���� ���¸� ������Ʈ�մϴ�.
	 * 
	 * @param DeltaSeconds �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Update(float DeltaSeconds) override;


	/**
	 * @brief Ÿ�� ���� ȭ�鿡 �׸��ϴ�.
	 * 
	 * @param Camera ������ �þ� ó���� ���� ī�޶��Դϴ�.
	 */
	virtual void Render(Camera2D& Camera) override;


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
	 * @brief Ÿ�� ���� Ÿ���� ���ϴ�.
	 * 
	 * @param Ÿ�� ���� �� Ÿ���Դϴ�.
	 * 
	 * @throws Ÿ�� ���� ������ ��� ���, C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	void WriteTileInMap(const Tile& WriteTile);


	/**
	 * @brief Ư�� ��ġ�� Ÿ�� ���� �н��ϴ�.
	 * 
	 * @param Position Ÿ�� ���� ���� ��ġ�Դϴ�.
	 * 
	 * @throws Ÿ�� ���� ������ ��� ���, C++ ǥ�� ���ܸ� �����ϴ�.
	 * 
	 * @return ���ϴ� ��ġ�� Ÿ���� �����ڸ� ��ȯ�մϴ�.
	 */
	Tile& ReadTileInMap(const Vec2i& Position);


	/**
	 * @brief Ÿ�ϸ��� �ʱ�ȭ�մϴ�.
	 */
	void ClearMap();


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