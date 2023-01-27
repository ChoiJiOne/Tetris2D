#pragma once

#include "GameObject.h"
#include "Tile.h"


/**
 * @brief 테트리스의 보드입니다.
 */
class Board : public GameObject
{
public:
	/**
	 * 테트리스 보드의 상태입니다.
	 */
	enum class EState : int32_t
	{
		NONE   = 0,
		WAIT   = 1,
		ACTIVE = 2
	};


public:
	/**
	 * @brief 테트리스 보드의 생성자입니다.
	 * 
	 * @param Signature 테트리스 보드의 시그니처 값입니다.
	 * @param TilePosition 타일 맵 상의 테트리스 보드 왼쪽 상단의 좌표입니다.
	 * @param Width 테트리스 보드의 가로 크기입니다.
	 * @param Height 테트리스 보드의 세로 크기입니다.
	 * 
	 * @throws 테트리스 보드 생성에 실패하면 C++ 표준 예외를 던집니다.
	 */
	Board(const std::string& Signature, const Vec2i& TilePosition, const int32_t& Width, const int32_t& Height);


	/**
	 * @brief 테트리스 보드의 가상 소멸자입니다.
	 */
	virtual ~Board() {}


	/**
	 * @brief 명시적으로 대입 연산자와 복사 생성자를 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Board);


	/**
	 * @brief 테트리스의 보드를 업데이트합니다.
	 *
	 * @param DeltaSeconds 초단위 델타 시간값입니다.
	 */
	virtual void Tick(float DeltaSeconds) override;


	/**
	 * @brief 타일들이 보드를 벗어나는지 확인합니다.
	 *
	 * @param Tiles 검사를 수행할 타일들입니다.
	 *
	 * @return 범위를 벗어나면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsOutOfRangeTiles(const std::vector<Tile>& Tiles);


	/**
	 * @brief 보드에 타일들을 추가합니다.
	 *
	 * @note 추가할 타일들이 보드 범위를 벗어나면 아무 동작도 수행하지 않습니다.
	 *
	 * @param Tiles 보드에 추가할 타일들입니다.
	 */
	void AddTiles(const std::vector<Tile>& Tiles);


	/**
	 * @brief 보드 상의 타일들을 삭제합니다.
	 *
	 * @note 삭제할 타일이 보드 범위를 벗어나면 아무 동작도 수행하지 않습니다.
	 *
	 * @param Tiles 보드에서 삭제할 타일들입니다.
	 */
	void RemoveTiles(const std::vector<Tile>& Tiles);


	/**
	 * @brief 보드 상의 타일들과 충돌을 검사합니다.
	 *
	 * @note 범위를 벗어나는 행위도 충돌 처리됩니다.
	 *
	 * @param Tiles 충돌하는지 검사할 타일입니다.
	 *
	 * @return 보드 상의 타일과 충돌한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsCollisionTiles(const std::vector<Tile>& Tiles);


private:
	/**
	 * @brief 비어있는 테트리스 보드의 타일을 생성합니다.
	 * 
	 * @param TilePosition 타일 맵 상의 테트리스 보드 왼쪽 상단의 좌표입니다.
	 * @param Width 테트리스 보드의 가로 크기입니다.
	 * @param Height 테트리스 보드의 세로 크기입니다.
	 * 
	 * @return 생성된 테트리스 보드 타일의 벡터를 반환합니다.
	 */
	std::vector<Tile> CreateBoardTile(const Vec2i& TilePosition, const int32_t& Width, const int32_t& Height);


	/**
	 * @brief 좌표가 테트리스 보드 내에 있는지 검사합니다.
	 * 
	 * @param Position 검사를 수행할 좌표입니다.
	 * 
	 * @return 좌표가 테트리스 보드 내에 있지 않다면 true, 보드 내에 있다면 false를 반환합니다.
	 */
	bool IsOutOfRangePosition(const Vec2i& Position);


private:
	/**
	 * @brief 타일 상의 테트리스 보드의 왼쪽 상단 좌표입니다.
	 */
	Vec2i TilePosition_;


	/**
	 * @brief 테트리스 보드의 가로 크기입니다.
	 */
	int32_t Width_ = 0;


	/**
	 * @brief 테트리스 보드의 세로 크기입니다.
	 */
	int32_t Height_ = 0;


	/**
	 * @brief 타일 맵 상의 테트리스 보드 타일입니다.
	 */
	std::vector<Tile> Tiles_;


	/**
	 * @brief 보드의 현재 상태입니다.
	 */
	EState State_ = EState::ACTIVE;


	/**
	 * @brief 보드의 업데이트 필요 여부입니다.
	 */
	bool bIsNeedUpdate_ = false;
};