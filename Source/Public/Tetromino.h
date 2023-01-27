#pragma once

#include "GameObject.h"
#include "Tile.h"


/**
 * @brief 테트리스의 테트로미노입니다.
 */
class Tetromino : public GameObject
{
public:
	/**
	 * @brief 테트로미노의 모양 타입입니다.
	 *
	 * @see https://ko.wikipedia.org/wiki/%ED%85%8C%ED%8A%B8%EB%A1%9C%EB%AF%B8%EB%85%B8
	 */
	enum class EShape : int32_t
	{
		NONE = 0,
		I    = 1,
		O    = 2,
		T    = 3,
		J    = 4,
		L    = 5,
		S    = 6,
		Z    = 7
	};


	/**
	 * @brief 테트로미노의 움직임 방향입니다.
	 */
	enum class EDirection : int32_t
	{
		NONE  = 0,
		LEFT  = 1,
		RIGHT = 2,
		DOWN  = 3,
		UP    = 4,
		CCW   = 5,
		CW    = 6,
		JUMP  = 7,
	};


	/**
	 * @brief 테트로미노의 상태입니다.
	 */
	enum class EState : int32_t
	{
		NONE   = 0,
		WAIT   = 1,
		ACTIVE = 2
	};


public:
	/**
	 * @brief 임의의 테트로미노를 생성하는 생성자입니다.
	 * 
	 * @param Signature 테트로미노의 시그니처 값입니다.
	 * @param TilePosition 테트로미노의 타일 상 왼쪽 상단의 좌표입니다.
	 * 
	 * @throws 테트로미노 생성에 실패하면 C++ 표준 예외를 던집니다.
	 */
	Tetromino(const std::string& Signature, const Vec2i& TilePosition);


	/**
	 * @brief 테트로미노 생성자입니다.
	 * 
	 * @param Signature 테트로미노의 시그니처 값입니다.
	 * @param TilePosition 테트로미노의 타일 상 왼쪽 상단의 좌표입니다.
	 * @param Shape 테트로미노의 모양입니다.
	 * @param Color 테트로미노 타일의 색상 타입입니다.
	 * 
	 * @throws 테트로미노 생성에 실패하면 C++ 표준 예외를 던집니다.
	 */
	Tetromino(const std::string& Signature, const Vec2i& TilePosition, const EShape& Shape, const Tile::EColor& Color);


	/**
	 * @brief 테트리스의 테트로미노 가상 소멸자입니다.
	 */
	virtual ~Tetromino() {}


	/**
	 * @brief 명시적으로 복사 생성자외 대입 연산자를 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Tetromino);


	/**
	 * @brief 테트리스의 테트로미노를 업데이트합니다.
	 *
	 * @param DeltaSeconds 초단위 델타 시간값입니다.
	 */
	virtual void Tick(float DeltaSeconds) override;


	/**
	 * @brief 테트로미노의 상태를 얻습니다.
	 * 
	 * @return 테트로미노의 상태를 반환합니다.
	 */
	EState GetState() const { return State_; }


	/**
	 * @brief 테트로미노의 상태를 설정합니다.
	 * 
	 * @param State 설정할 테트로미노의 상태입니다.
	 */
	void SetState(const EState& State) { State_ = State; }


private:
	/**
	 * @brief 테트로미노 타일을 생성합니다.
	 * 
	 * @param TilePosition 타일 상의 테트로미노 왼쪽 상단 위치입니다.
	 * @param Shape 테트로미노의 모양입니다.
	 * @param Color 타일의 색상입니다.
	 * 
	 * @return 생성된 테트로미노 타일의 벡터를 반환합니다.
	 */
	static std::vector<Tile> CreateTetrominoTile(const Vec2i& TilePosition, const EShape& Shape, const Tile::EColor& Color);


	/**
	 * @brief 테트로미노를 특정 방향으로 움직입니다.
	 * 
	 * @param TilePosition 타일 맵 상의 움직일 테트로미노의 왼쪽 상단 좌표입니다.
	 * @param Tiles 테트로미노의 타일입니다.
	 * @param Shape 테트로미노의 모양입니다.
	 * @param Direction 테트로미노가 움직일 방향입니다.
	 */
	static void Move(Vec2i& TilePosition, std::vector<Tile>& Tiles, const EShape& Shape, const EDirection& Direction);


	/**
	 * @brief 테트로미노를 특정 방향으로 움직일 수 있는지 확인합니다.
	 * 
	 * @param TilePosition 타일 맵 상의 움직일 테트로미노의 왼쪽 상단 좌표입니다.
	 * @param Tiles 테트로미노의 타일입니다.
	 * @param Shape 테트로미노의 모양입니다.
	 * @param Direction 테트로미노가 움직일 방향입니다.
	 * 
	 * @return 테트로미노를 움직일 수 있다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	static bool CanMove(Vec2i& TilePosition, std::vector<Tile>& Tiles, const EShape& Shape, const EDirection& Direction);


	/**
	 * @brief 테트로미노 모양에 따른 영역의 크기를 얻습니다.
	 * 
	 * @param Shape 테트로미노 모양입니다.
	 * 
	 * @return 테트로미노의 영역 크기를 반환합니다.
	 */
	static int32_t GetBoundSize(const EShape& Shape);


	/**
	 * 테트로미노 움직임의 반대 방향을 얻습니다.
	 *
	 * @param Direction 반대 방향을 알고 싶은 움직임입니다.
	 *
	 * @return 움직임의 반대 방향을 반환합니다.
	 */
	static EDirection GetCountDirection(const EDirection& Direction);


private:
	/**
	 * @brief 타일맵 상의 테트로미노 왼쪽 상단의 좌표입니다.
	 */
	Vec2i TilePosition_;


	/**
	 * @brief 테트로미노의 모양입니다.
	 */
	EShape Shape_ = EShape::NONE;


	/**
	 * @brief 테트로미노의 타일입니다.
	 */
	std::vector<Tile> Tiles_;


	/**
	 * @brief 테트로미노의 상태입니다.
	 * 
	 * @note 기본 상태는 대기중인 상태입니다.
	 */
	EState State_ = EState::WAIT;


	/**
	 * @brief 테트로미노의 업데이트 누적 시간입니다. 
	 */
	float AccrueTickTime_ = 0.0f;


	/**
	 * @brief 테트로미노의 최대 업데이트 누적 시간입니다.
	 */
	static float MaxAccrueTickTime_;
};