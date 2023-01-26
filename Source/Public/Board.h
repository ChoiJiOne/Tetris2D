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
};