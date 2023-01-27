#pragma once

#include <vector>

#include "GameObject.h"
#include "Tile.h"


/**
 * @brief 2D 타일 맵입니다.
 */
class TileMap : public GameObject
{
public:
	/**
	 * @brief 2D 타일맵의 생성자입니다.
	 * 
	 * @param Signature 타일 맵의 식별자입니다.
	 * @param CenterPosition 2D 월드 상의 타일맵의 중싱 좌표입니다.
	 * @param RowSize 타일맵의 가로 크기입니다.
	 * @param ColSize 타일맵의 세로 크기입니다.
	 * @param TileSize 타일의 크기입니다.
	 */
	TileMap(
		const std::string& Signature,
		const Vec2f& CenterPosition,
		const int32_t& RowSize,
		const int32_t& ColSize,
		const int32_t& TileSize
	);


	/**
	 * @brief 2D 타일맵의 가상 소멸자입니다.
	 */
	virtual ~TileMap() {}


	/**
	 * @brief 명시적으로 복사 생성자외 대입 연산자를 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(TileMap);


	/**
	 * @brief 타일 맵을 업데이트합니다.
	 * 
	 * @param DeltaSeconds 초단위 델타 시간값입니다.
	 */
	virtual void Tick(float DeltaSeconds) override;


	/**
	 * @brief 타일의 가로 크기를 얻습니다.
	 * 
	 * @return 타일의 가로 크기를 반환합니다.
	 */
	int32_t GetColSize() const { return ColSize_; }


	/**
	 * @brief 타일의 세로 크기를 얻습니다.
	 * 
	 * @return 타일의 세로 크기를 얻습니다.
	 */
	int32_t GetRowSize() const { return RowSize_; }


	/**
	 * @brief 타일이 타일 맵 범위를 벗어나는지 확인합니다.
	 * 
	 * @param TargetTile 검사를 수행할 타일입니다.
	 * 
	 * @return 범위를 벗어나면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsOutOfRangeTileInMap(const Tile& TargetTile);


	/**
	 * @brief 타일 맵에 타일을 추가합니다.
	 * 
	 * @note 추가할 타일이 타일 맵 범위를 벗어나면 아무 동작도 수행하지 않습니다.
	 * 
	 * @param AddTile 타일 맵에 추가할 타일입니다.
	 */
	void AddTileInMap(const Tile& AddTile);


	/**
	 * @brief 타일 맵 상의 타일을 삭제합니다.
	 * 
	 * @note 삭제할 타일이 타일 맵 범위를 벗어나면 아무 동작도 수행하지 않습니다.
	 * 
	 * @param RemoveTile 타일 맵에 삭제할 타일입니다.
	 */
	void RemoveTileInMap(const Tile& RemoveTile);


	/**
	 * @brief 타일 맵 상의 타일과 충돌을 검사합니다.
	 * 
	 * @note 범위를 벗어나는 행위도 충돌 처리됩니다.
	 * 
	 * @param CollisionTile 충돌하는지 검사할 타일입니다.
	 * 
	 * @return 타일 맵 상의 타일과 충돌한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsCollisionTileInMap(const Tile& CollisionTile);


	/**
	 * @brief 타일들이 타일 맵을 벗어나는지 확인합니다.
	 * 
	 * @param Tiles 검사를 수행할 타일입니다.
	 * 
	 * @return 범위를 벗어나면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsOutOfRangeTilesInMap(const std::vector<Tile>& Tiles);


	/**
	 * @brief 타일 맵에 타일들을 추가합니다.
	 * 
	 * @note 추가할 타일이 타일 맵 범위를 벗어나면 아무 동작도 수행하지 않습니다.
	 * 
	 * @param Tiles 타일 맵에 추가할 타일들입니다.
	 */
	void AddTilesInMap(const std::vector<Tile>& Tiles);


	/**
	 * @brief 타일 맵 상의 타일들을 삭제합니다.
	 * 
	 * @note 삭제할 타일이 타일 맵 범위를 벗어나면 아무 동작도 수행하지 않습니다.
	 * 
	 * @param Tiles 타일 맵에 삭제할 타일들입니다.
	 */
	void RemoveTilesInMap(const std::vector<Tile>& Tiles);


	/**
	 * @brief 타일 맵 상의 타일들과 충돌을 검사합니다.
	 *
	 * @note 범위를 벗어나는 행위도 충돌 처리됩니다.
	 *
	 * @param Tiles 충돌하는지 검사할 타일입니다.
	 *
	 * @return 타일 맵 상의 타일과 충돌한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsCollisionTilesInMap(const std::vector<Tile>& Tiles);


	/**
	 * @brief 타일맵을 초기화합니다.
	 */
	void ClearMap();


private:
	/**
	 * @brief 타일 맵에 타일을 추가합니다.
	 *
	 * @note 추가할 타일이 타일 맵 범위를 벗어나면 아무 동작도 수행하지 않습니다.
	 *
	 * @param AddTile 타일 맵에 추가할 타일입니다.
	 * @param bIsCheckRange 범위 검사 수행 여부입니다.
	 */
	void AddTileInMap(const Tile& AddTile, bool bIsCheckRange);


	/**
	 * @brief 타일 맵 상의 타일을 삭제합니다.
	 *
	 * @note 삭제할 타일이 타일 맵 범위를 벗어나면 아무 동작도 수행하지 않습니다.
	 *
	 * @param RemoveTile 타일 맵에 삭제할 타일입니다.
	 * @param bIsCheckRange 범위 검사 수행 여부입니다.
	 */
	void RemoveTileInMap(const Tile& RemoveTile, bool bIsCheckRange);


private:
	/**
	 * @brief 2D 월드 상의 타일맵의 중심 위치입니다.
	 */
	Vec2f CenterPosition_;


	/**
	 * @brief 타일의 가로 크기입니다.
	 */
	int32_t ColSize_ = 0;


	/**
	 * @brief 타일의 세로 크기입니다.
	 */
	int32_t RowSize_ = 0;


	/**
	 * @brief 2D 상의 타일의 크기입니다.
	 * 
	 * @note 타일은 정사각형입니다.
	 */
	int32_t TileSize_ = 0;


	/**
	 * @brief 2D 타일맵입니다.
	 */
	std::vector<Tile> Tiles_;


	/**
	 * @brief 타일 색상에 대응하는 텍스처 시그니처입니다.
	 */
	static std::unordered_map<Tile::EColor, std::string> TileColorSignature_;
};