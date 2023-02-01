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
	 * @brief 보드의 상태를 얻습니다.
	 *
	 * @return 보드의 상태를 반환합니다.
	 */
	EState GetState() const { return State_; }


	/**
	 * @brief 보드의 상태를 설정합니다.
	 *
	 * @param State 설정할 보드의 상태입니다.
	 */
	void SetState(const EState& State) { State_ = State; }


	/**
	 * @brief 보드에 삭제된 라인 수를 얻습니다.
	 * 
	 * @return 보드에 삭제된 라인 수를 반환합니다.
	 */
	int32_t GetRemoveLine() const { return RemoveLine_; }


	/**
	 * @brief 보드의 최대 누적 시간을 얻습니다.
	 *
	 * @return 보드의 최대 누적 시간을 반환합니다.
	 */
	static float GetMaxAccrueTickTime() { return MaxAccrueTickTime_; }


	/**
	 * @brief 보드의 최대 누적 시간을 설정합니다.
	 *
	 * @note 시간은 초단위 입니다.
	 *
	 * @param MaxAccrueTickTime 설정할 최대 누적 시간입니다.
	 */
	static void SetMaxAccrueTickTime(const float& MaxAccrueTickTime);


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
	 * @brief 타일 맵으로부터 보드 타일을 적제합니다.
	 */
	void DumpBoardFromTileMap();


	/**
	 * @brief 보드 타일을 타일 맵에 적재합니다.
	 */
	void DumpTileMapFromBoard();

	
	/**
	 * @brief 보드의 세로 줄이 모두 같은 상태인지 확인합니다.
	 * 
	 * @param BoardYPosition 검사할 보드 상의 Y좌표입니다.
	 * @param TileState 확인할 타일 상태입니다.
	 * 
	 * @return 보드의 세로 줄이 모두 같은 상태라면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsAllSameRowLine(const int32_t& BoardYPosition, const Tile::EState& TileState);


	/**
	 * @brief 보드의 세로 줄을 삭제할 수 있는지 확인합니다.
	 * 
	 * @param BoardYPosition 삭제할 수 있는지 확인할 보드 상의 Y좌표입니다.
	 * 
	 * @return 삭제할 수 있다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool CanRemoveRowLine(const int32_t& BoardYPosition);


	/**
	 * @brief 보드의 세로 줄이 비어있는지 확인합니다.
	 * 
	 * @param BoardYPosition 비어있는지 확인할 보드 상의 Y좌표입니다.
	 * 
	 * @return 비어있다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool IsEmptyRowLine(const int32_t& BoardYPosition);


	/**
	 * @brief 보드의 세로 줄을 삭제합니다.
	 * 
	 * @param BoardYPosition 삭제할 세로 줄입니다.
	 */
	void ClearRowLine(const int32_t& BoardYPosition);


	/**
	 * @brief 보드의 비어있는 줄을 재정렬합니다.
	 */
	void ArrangeEmptyRowLine();


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
	 * @brief 보드가 삭제한 라인 수입니다.
	 */
	int32_t RemoveLine_ = 0;


	/**
	 * @brief 보드의 업데이트 누적 시간입니다.
	 */
	float AccrueTickTime_ = 0.0f;


	/**
	 * @brief 보드의 최대 업데이트 누적 시간입니다.
	 */
	static float MaxAccrueTickTime_;
};