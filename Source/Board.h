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
		Fill = 1,
		Fix = 2
	};


	// 테트리스 블럭입니다.
	using Block = std::pair<EBlockState, LinearColor>;


public:
	Board(int32_t rowSize_ = 20, int32_t colSize_ = 10, LinearColor wallColor_ = Color::White, LinearColor backgroundColor_ = Color::Black);
	virtual ~Board();

	Board(Board&& instance) noexcept;
	Board& operator=(Board&& instance) noexcept;

	Board(const Board& instance) noexcept;
	Board& operator=(const Board& instance) noexcept;

	Block GetBlock(int32_t x, int32_t y);
	void  SetBlock(int32_t x, int32_t y, Block block);

	int32_t GetRowSize() noexcept { return rowSize; }
	int32_t GetColSize() noexcept { return colSize; }

	bool CheckInsidePositionInBoard(int32_t x, int32_t y);

	int32_t UpdateBoardState();
	void ResetBoardState();

	void AddTetrominoInBoard(Tetromino& tetromino);
	void RemoveTetrominoInBoard(Tetromino& tetromino);
	bool IsCrashTetrominoAndBoard(Tetromino& tetromino);

	bool MoveDownTetrominoInBoard(Tetromino& tetromino);
	void MoveLeftTetrominoInBoard(Tetromino& tetromino);
	void MoveRightTetrominoInBoard(Tetromino& tetromino);
	void MoveBottomTetrominoInBoard(Tetromino& tetromino);

	void SpinClockWiseTetrominoInBoard(Tetromino& tetromino);
	void SpinCounterClockWiseTetrominoInBoard(Tetromino& tetromino);

	void Draw(const Vec2i& windowPos, int32_t blockSize);

private:
	int32_t GetOffset(int32_t x, int32_t y, int32_t row, int32_t col);

	bool IsFullRowLine(const std::vector<Block>& blocks, int32_t row, int32_t col, int32_t rowLine);
	bool IsEmptyRowLine(const std::vector<Block>& blocks, int32_t row, int32_t col, int32_t rowLine);
	void RemoveRowLine(std::vector<Block>& blocks, int32_t row, int32_t col, int32_t rowLine);

	std::vector<Block> CreateBoardBlocks(int32_t row, int32_t col);
	void SetupBoardBlocks(std::vector<Block>& blocks, int32_t row, int32_t col);

private:
	LinearColor backgroundColor;
	LinearColor wallColor;

	int32_t rowSize = 0;
	int32_t colSize = 0;
	std::vector<Block> boardBlocks;
};