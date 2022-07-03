#pragma once

// Tetromino를 사용하기 위한 헤더 선언을 추가합니다.
#include "Tetromino.h"


// 테트리스 보드입니다.
class Board
{
public:
	// 테트리스 블럭의 상태입니다.
	enum class EBlockState : int32_t
	{
		Empty = 0,
		Fill  = 1,
		Fix   = 2
	};


	// 테트리스 블럭입니다.
	using Block = std::pair<EBlockState, LinearColor>;


public:
	// 생성자입니다.
	//
	// @param InRowSize - 테트리스 보드의 세로 크기입니다.
	// @param InColSize - 테트리스 보드의 가로 크기입니다.
	// @param InWallBlockColor - 테트리스 블럭이 벽일 때의 색상입니다.
	// @param InEmptyBlockColor - 테트리스 블럭이 비어있을 때의 색상입니다.
	Board(
		int32_t InRowSize = 20, 
		int32_t InColSize = 10, 
		const LinearColor& InWallBlockColor  = ColorHelper::White, 
		const LinearColor& InEmptyBlockColor = ColorHelper::Black
	);


	// 가상 소멸자입니다.
	virtual ~Board();


	// 복사 생성자입니다.
	Board(Board&& InInstance) noexcept;
	Board(const Board& InInstance) noexcept;


	// 대입연산자입니다.
	Board& operator=(Board&& InInstance) noexcept;
	Board& operator=(const Board& InInstance) noexcept;


	// 테트리스 보드의 상태를 업데이트합니다.
	// 
	// @return - 테트리스 보드의 상태 업데이트 중 삭제한 라인의 수를 반환합니다.
	int32_t UpdateBoardState();


	// 테트리스 보드의 상태를 리셋합니다.
	void ResetBoardState();


	// 테트로미노를 테트리스 보드에 추가합니다.
	//
	// @param InTetromino - 추가할 테트로미노입니다.
	//
	// @return - 추가할 수 있다면 true, 추가할 수 없다면 false를 반환합니다.
	bool AddTetromino(const Tetromino& InTetromino);


	// 테트로미노를 테트리스 보드에 삭제합니다.
	//
	// @param InTetromino - 삭제할 테트로미노입니다.
	void RemoveTetromino(const Tetromino& InTetromino);


	// 테트리스 보드 상의 테트로미노를 움직입니다.
	//
	// @param InTetromino - 테트리스 보드 상에 움직일 테트로미노입니다.
	// @param InMove - 테트로미노가 움직일 방향입니다. 
	bool MoveTetromino(Tetromino& InTetromino, const Tetromino::EMove& InMove);


	// 테트리스 보드 상의 테트로미노를 회전시킵니다.
	//
	// @param InTetromino - 테트리스 보드 상에 회전할 테트로미노입니다.
	// @param InSpin - 테트로미노가 회전할 방향입니다. 
	bool SpinTetromino(Tetromino& InTetromino, const Tetromino::ESpin& InSpin);


	// 테트리스 보드를 화면에 그립니다.
	//
	// @param InRenderer - SDL 렌더러의 포인터입니다.
	// @param InWindowPosition - 테트리스 보드를 그릴 윈도우 상의 좌표입니다. 
	// @param InBlockSize - 화면에 그려질 테트리스 보드의 블럭 크기입니다.
	void Draw(SDL_Renderer* InRenderer, const Vec2i& InWindowPosition, int32_t InBlockSize);


private:
	// 테트리스 보드의 지울 수 있는 라인 수를 계산합니다.
	int32_t CalculateCanRemoveLine();


	// 테트로미노와 테트리스 보트가 충돌하는지 확인합니다.
	//
	// @param InTetromino - 충돌을 확인할 테트로미노입니다.
	//
	// @return - 테트로미노와 테트리스 보드가 충돌하면 true, 그렇지 않다면 false를 반환합니다
	bool IsCrashTetromino(const Tetromino& InTetromino);


private:
	// Blocks의 (InCol, InRow)가 범위 내에 있는지 검사합니다.
	//
	// @param InRow - 범위를 계산할 테트리스 보드의 세로 위치 값입니다.
	// @param InCol - 범위를 계산할 테트리스 보드의 가로 위치 값입니다.
	// @param InRowSize - 테트리스 보드의 세로 크기입니다.
	// @param InColSize - 테트리스 보드의 가로 크기입니다.
	//
	// @return - (x, y)가 Blocks 내에 있다면 true, 그렇지 않다면 false를 반환합니다.
	static bool CheckInsidePositionInBlocks(int32_t InRow, int32_t InCol, int32_t InRowSize, int32_t InColSize);


	// Blocks의 (InCol, InRow) Offset을 얻습니다.
	// 
	// @param InBlocks - Offset을 계산할 테트리스 보드입니다.
	// @param InRow - Offset을 계산할 테트리스 보드의 세로 위치 값입니다.
	// @param InCol - Offset을 계산할 테트리스 보드의 가로 위치 값입니다.
	// @param InRowSize - 테트리스 보드의 세로 크기입니다.
	// @param InColSize - 테트리스 보드의 가로 크기입니다.
	static int32_t GetBlocksOffset(int32_t InRow, int32_t InCol, int32_t InRowSize, int32_t InColSize);


	// Blocks의 가로줄이 꽉 차있는지 확인합니다. 
	// 
	// @param InBlocks - 검사를 수행할 테트리스 보드입니다.
	// @param InRowSize - 테트리스 보드의 세로 크기입니다.
	// @param InColSize - 테트리스 보드의 가로 크기입니다.
	// @param InTargetRow - 검사를 수행할 가로줄입니다.
	//
	// @return - Blocks의 가로줄이 꽉 차있다면 true, 그렇지 않다면 false를 반환합니다.
	static bool IsFullRowLine(const std::vector<Block>& InBlocks, int32_t InRowSize, int32_t InColSize, int32_t InTargetRow);


	// Blocks의 가로줄이 비어있는지 확인합니다.
	//
	// @param InBlocks - 검사를 수행할 테트리스 보드입니다.
	// @param InRowSize - 테트리스 보드의 세로 크기입니다.
	// @param InColSize - 테트리스 보드의 가로 크기입니다.
	// @param InTargetRow - 검사를 수행할 가로줄입니다.
	//
	// @return - Blocks의 가로줄이 비어있다면 true, 그렇지 않다면 false를 반환합니다.
	static bool IsEmptyRowLine(const std::vector<Block>& InBlocks, int32_t InRowSize, int32_t InColSize, int32_t InTargetRow);


	// Blocks의 가로줄을 지웁니다.
	//
	// @param InBlocks - 가로줄을 지울 테트리스 보드입니다.
	// @param InRowSize - 테트리스 보드의 세로 크기입니다.
	// @param InColSize - 테트리스 보드의 가로 크기입니다.
	// @param InTargetRow - 가로줄을 지울 열입니다.
	static void RemoveRowLine(std::vector<Block>& InBlocks, int32_t InRowSize, int32_t InColSize, int32_t InTargetRow);


	// 비어있는 테트리스 블럭을 생성합니다.
	//
	// @param InRowSize - 생성할 테트리스 보드의 세로 크기입니다.
	// @param InColSize - 생성할 테트리스 보드의 가로 크기입니다.
	// 
	// @return - 생성한 테트리스 블럭을 반환합니다.
	static std::vector<Block> GenerateEmptyBlocks(int32_t InRowSize, int32_t InColSize, const LinearColor& EmptyColor = ColorHelper::Black);


	// 블럭을 초기화합니다.
	//
	// @param InBlocks - 초기화할 테트리스 블럭입니다.
	// @param InRowSize - 테트리스 블럭의 세로 크기입니다.
	// @param InColSize - 테트리스 블럭의 가로 크기입니다.
	// @param EmptyColor - 테트리스 블럭이 비어있을 때의 색상입니다.
	// @param InWallColor - 테트리스 블럭의 벽 색상입니다.
	static void SetupBlocks(
		std::vector<Block>& InBlocks, 
		int32_t InRowSize, 
		int32_t InColSize, 
		const LinearColor& EmptyColor = ColorHelper::Black,
		const LinearColor& InWallColor = ColorHelper::White
	);


	// 테트리스 보드의 블럭을 얻습니다.
	//
	// @param InBlocks - 대상 테트리스 보드입니다.
	// @param InRow - 범위를 계산할 테트리스 보드의 세로 위치 값입니다.
	// @param InCol - 범위를 계산할 테트리스 보드의 가로 위치 값입니다.
	// @param InRowSize - 테트리스 보드의 세로 크기입니다.
	// @param InColSize - 테트리스 보드의 가로 크기입니다.
	//
	// @return - (InCol, InRow) 위치의 테트리스 블럭을 반환합니다.
	static Block GetBlock(const std::vector<Block>& InBlocks, int32_t InRow, int32_t InCol, int32_t InRowSize, int32_t InColSize);


	// 테트리스 보드의 블럭을 설정합니다.
	//
	// @param InBlocks - 대상 테트리스 보드입니다.
	// @param InBlock - 설정할 테트리스 블럭입니다.
	// @param InRow - 범위를 계산할 테트리스 보드의 세로 위치 값입니다.
	// @param InCol - 범위를 계산할 테트리스 보드의 가로 위치 값입니다.
	// @param InRowSize - 테트리스 보드의 세로 크기입니다.
	// @param InColSize - 테트리스 보드의 가로 크기입니다.
	static void SetBlock(std::vector<Block>& InBlocks, Block InBlock, int32_t InRow, int32_t InCol, int32_t InRowSize, int32_t InColSize);


private:
	// 블럭이 비어있을 때의 색상입니다.
	LinearColor EmptyBlockColor;


	// 블럭이 벽일 때의 색상입니다.
	LinearColor WallBlockColor;


	// 테트리스 보드의 세로 크기입니다.
	int32_t RowSize = 0;


	// 테트리스 보드의 가로 크기입니다.
	int32_t ColSize = 0;


	// 테트리스 보드의 블럭입니다.
	std::vector<Block> Blocks;
};