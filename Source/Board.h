#pragma once

// Block을 사용하기 위한 헤더 선언을 추가합니다.
#include "Block.h"


// 테트리스 보드를 관리하는 클래스입니다.
class Board
{
public:
	// 생성자입니다.
	Board() = default;


	// 가상 소멸자입니다.
	virtual ~Board();


	// 복사 생성자입니다.
	//
	// @param InInstance - 복사를 수행할 Board 인스턴스입니다.
	Board(Board&& InInstance) noexcept;


	// 복사 생성자입니다.
	//
	// @param InInstance - 복사를 수행할 Board 인스턴스입니다.
	Board(const Board& InInstance) noexcept;


	// 대입 연산자입니다.
	//
	// @param InInstance - 복사를 수행할 Board 인스턴스입니다.
	Board& operator=(Board&& InInstance) noexcept;


	// 대입 연산자입니다.
	//
	// @param InInstance - 복사를 수행할 Board 인스턴스입니다.
	Board& operator=(const Board& InInstance) noexcept;


	// Board를 초기화합니다.
	// 
	// @param InBoardWidth - 테트리스 보드의 가로 크기입니다.
	// @param InBoardHeight - 테트리스 보드의 세로 크기입니다.
	void Init(int32_t InBoardWidth = 10, int32_t InBoardHeight = 16);


	// Board의 상태를 최초의 상태로 설정합니다.
	void Reset();


	// Board의 가로 크기를 반환합니다.
	//
	// @return - Board의 가로 크기를 반환합니다.
	int32_t GetBoardWidth() const { return BoardWidth; }


	// Board의 세로 크기를 반환합니다.
	//
	// @return - Board의 세로 크기를 반환합니다.
	int32_t GetBoardHeight() const { return BoardHeight; }


	// Board 특정 좌표의 블럭을 반환합니다.
	//
	// @param InRow - Board의 세로 좌표입니다.
	// @param InCol - Board의 가로 좌표입니다.
	// @throws - (Col, Row)이 Board의 범위를 벗어나는 경우, C++ 표준 예외를 반환합니다.
	// @return - (Col, Row)에 대응하는 Board의 블럭을 반환합니다.
	Block GetBlockInBoard(int32_t InRow, int32_t InCol) const;


	// Board 특정 좌표의 상태를 반환합니다.
	//
	// @param InRow - Board의 세로 좌표입니다.
	// @param InCol - Board의 가로 좌표입니다.
	// @throws - (Col, Row)이 Board의 범위를 벗어나는 경우, C++ 표준 예외를 반환합니다.
	// @return - (Col, Row)에 대응하는 Board의 상태를 반환합니다.
	EBlockState GetBlockStateInBoard(int32_t InRow, int32_t InCol) const;


	// Board 특정 좌표의 색상을 반환합니다.
	//
	// @param InRow - Board의 세로 좌표입니다.
	// @param InCol - Board의 가로 좌표입니다.
	// @throws - (Col, Row)이 Board의 범위를 벗어나는 경우, C++ 표준 예외를 반환합니다.
	// @return - (Col, Row)에 대응하는 Board의 색상을 반환합니다.
	EBlockColor GetBlockColorInBoard(int32_t InRow, int32_t InCol) const;


	// Board 특정 좌표 블럭의 설정을 변경합니다.
	//
	// @param InRow - Board의 세로 좌표입니다.
	// @param InCol - Board의 가로 좌표입니다.
	// @param InBlock - 설정할 Board의 블럭입니다.
	void SetBlockInBoard(int32_t InRow, int32_t InCol, const Block& InBlock);


	// Board 특정 좌표 상태의 설정을 변경합니다.
	//
	// @param InRow - Board의 세로 좌표입니다.
	// @param InCol - Board의 가로 좌표입니다.
	// @param InBlockState - 설정할 Board의 상태입니다.
	void SetBlockStateInBoard(int32_t InRow, int32_t InCol, const EBlockState& InBlockState);


	// Board 특정 좌표 색상의 설정을 변경합니다.
	//
	// @param InRow - Board의 세로 좌표입니다.
	// @param InCol - Board의 가로 좌표입니다.
	// @param InBlockColor - 설정할 Board의 색상입니다.
	void SetBlockColorInBoard(int32_t InRow, int32_t InCol, const EBlockColor& InBlockColor);


	// 테트리스 보드를 화면에 그립니다.
	//
	// @param InPosition - 윈도우 좌표계를 기준으로 테트리스 보드의 왼쪽 상단점입니다.
	// @param InScale - 렌더링 할 텍스처의 Scale 값입니다.
	void DrawBoard(const Vec2i& InPosition, float InScale);


private:
	// Board 좌표의 영역을 검사합니다.
	//
	// @param InRow - Board의 세로 좌표입니다.
	// @param InCol - Board의 가로 좌표입니다.
	// @return - (Col, Row) 이 Board 내의 점이면 true, 그렇지 않으면 false를 반환합니다.
	bool IsInsidePosition(int32_t InRow, int32_t InCol) const;


	// Board의 Offset를 반환합니다.
	//
	// @param InRow - Board의 세로 좌표입니다.
	// @param InCol - Board의 가로 좌표입니다.
	// @return - Board의 Offset를 반환합니다.
	int32_t GetBoardOffset(int32_t InRow, int32_t InCol) const;


	// 테트리스 블럭의 텍스처를 생성합니다.
	void CreateBlockTexture();


private:
	// 테트리스 보드의 가로 크기입니다.
	int32_t BoardWidth = 0;


	// 테트리스 보드의 세로 크기입니다.
	int32_t BoardHeight = 0;


	// 테트리스 보드의 상태입니다.
	std::vector<Block> BoardState;


	// 테트리스 블럭 텍스처입니다.
	std::unordered_map<EBlockColor, std::unique_ptr<GameTexture2D>> BlockTextureCache;
};