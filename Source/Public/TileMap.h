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
	 * @brief 타일 맵의 상태를 업데이트합니다.
	 * 
	 * @param DeltaSeconds 초단위 델타 시간값입니다.
	 */
	virtual void Update(float DeltaSeconds) override;


	/**
	 * @brief 타일 맵을 화면에 그립니다.
	 * 
	 * @param Camera 게임의 시야 처리를 위한 카메라입니다.
	 */
	virtual void Render(Camera2D& Camera) override;


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
	 * @brief 타일 맵의 타일을 씁니다.
	 * 
	 * @param 타일 맵을 쓸 타일입니다.
	 * 
	 * @throws 타일 맵의 범위를 벗어날 경우, C++ 표준 예외를 던집니다.
	 */
	void WriteTileInMap(const Tile& WriteTile);


	/**
	 * @brief 특정 위치의 타일 맵을 읽습니다.
	 * 
	 * @param Position 타일 맵을 읽을 위치입니다.
	 * 
	 * @throws 타일 맵의 범위를 벗어날 경우, C++ 표준 예외를 던집니다.
	 * 
	 * @return 원하는 위치의 타일의 참조자를 반환합니다.
	 */
	Tile& ReadTileInMap(const Vec2i& Position);


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