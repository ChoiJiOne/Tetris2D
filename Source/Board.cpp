#include "Public/GameEngine.h"
#include "Public/GameRenderer.h"
#include "Board.h"

int32_t Board::GetOffset(int32_t x, int32_t y, int32_t row, int32_t col)
{
	if (!(0 <= x && x < col) &&
		!(0 <= y && y < row))
	{
		throw std::exception("out of range in board");
	}

	return y * col + x;
}

bool Board::IsFullRowLine(const std::vector<Block>& blocks, int32_t row, int32_t col, int32_t rowLine)
{
	for (int32_t x = 1; x < col - 1; ++x)
	{
		if (blocks[GetOffset(x, rowLine, row, col)].first != EBlockState::Fill)
		{
			return false;
		}
	}

	return true;
}

bool Board::IsEmptyRowLine(const std::vector<Block>& blocks, int32_t row, int32_t col, int32_t rowLine)
{
	for (int32_t x = 1; x < col - 1; ++x)
	{
		if (blocks[GetOffset(x, rowLine, row, col)].first != EBlockState::Empty)
		{
			return false;
		}
	}

	return true;
}

void Board::RemoveRowLine(std::vector<Block>& blocks, int32_t row, int32_t col, int32_t rowLine)
{
	for (int32_t x = 1; x < col - 1; ++x)
	{
		blocks[GetOffset(x, rowLine, row, col)].first = EBlockState::Empty;
	}
}

std::vector<Board::Block> Board::CreateBoardBlocks(int32_t row, int32_t col)
{
	return std::vector<Block>(row * col, Block(EBlockState::Empty, backgroundColor));
}

void Board::SetupBoardBlocks(std::vector<Block>& blocks, int32_t row, int32_t col)
{
	std::fill(blocks.begin(), blocks.end(), Block(EBlockState::Empty, backgroundColor));

	for (int32_t y = 0; y < row; ++y)
	{

		if (y == row - 1)
		{
			for (int32_t x = 0; x < col; ++x)
			{
				blocks[GetOffset(x, y, row, col)] = Block(EBlockState::Fix, wallColor);
			}
		}
		else
		{
			blocks[GetOffset(0, y, row, col)] = Block(EBlockState::Fix, wallColor);
			blocks[GetOffset(col - 1, y, row, col)] = Block(EBlockState::Fix, wallColor);
		}
	}
}

Board::Block Board::GetBlock(int32_t x, int32_t y)
{
	int32_t offset = GetOffset(x, y, rowSize, colSize);
	return boardBlocks[offset];
}

void Board::SetBlock(int32_t x, int32_t y, Block block)
{
	int32_t offset = GetOffset(x, y, rowSize, colSize);
	boardBlocks[offset] = block;
}

Board::Board(int32_t rowSize_, int32_t colSize_, LinearColor wallColor_, LinearColor backgroundColor_)
	: rowSize(rowSize_)
	, colSize(colSize_)
	, wallColor(wallColor_)
	, backgroundColor(backgroundColor_)
{
	boardBlocks = CreateBoardBlocks(rowSize, colSize);
	SetupBoardBlocks(boardBlocks, rowSize, colSize);
}

Board::~Board()
{
}

Board::Board(Board&& instance) noexcept
	: wallColor(instance.wallColor)
	, backgroundColor(instance.backgroundColor)
	, rowSize(instance.rowSize)
	, colSize(instance.colSize)
	, boardBlocks(instance.boardBlocks)
{
}

Board& Board::operator=(Board&& instance) noexcept
{
	if (this == &instance) return *this;

	wallColor = instance.wallColor;
	backgroundColor = instance.backgroundColor;
	rowSize = instance.rowSize;
	colSize = instance.colSize;
	boardBlocks = instance.boardBlocks;

	return *this;
}

Board::Board(const Board& instance) noexcept
	: wallColor(instance.wallColor)
	, backgroundColor(instance.backgroundColor)
	, rowSize(instance.rowSize)
	, colSize(instance.colSize)
	, boardBlocks(instance.boardBlocks)
{
}

Board& Board::operator=(const Board& instance) noexcept
{
	if (this == &instance) return *this;

	wallColor = instance.wallColor;
	backgroundColor = instance.backgroundColor;
	rowSize = instance.rowSize;
	colSize = instance.colSize;
	boardBlocks = instance.boardBlocks;

	return *this;
}

bool Board::CheckInsidePositionInBoard(int32_t x, int32_t y)
{
	return ((0 <= x && x < colSize) && (0 <= y && y < rowSize));
}

int32_t Board::UpdateBoardState()
{
	bool bIsUpdate = false;
	int32_t removeLine = 0;

	for (int32_t y = 0; y < rowSize - 1; ++y)
	{
		if (IsFullRowLine(boardBlocks, rowSize, colSize, y))
		{
			RemoveRowLine(boardBlocks, rowSize, colSize, y);
			removeLine++;
			bIsUpdate = true;
		}
	}

	if (bIsUpdate)
	{
		std::vector<Block> tempBlocks = CreateBoardBlocks(rowSize, colSize);
		SetupBoardBlocks(tempBlocks, rowSize, colSize);

		for (int32_t y = rowSize - 2, colLine = rowSize - 2; y >= 0; --y)
		{
			if (!IsEmptyRowLine(boardBlocks, rowSize, colSize, y))
			{
				for (int32_t x = 1; x < colSize - 1; ++x)
				{
					tempBlocks[GetOffset(x, colLine, rowSize, colSize)] = boardBlocks[GetOffset(x, y, rowSize, colSize)];
				}

				colLine--;
			}
		}

		boardBlocks = tempBlocks;
	}

	return removeLine;
}

void Board::ResetBoardState()
{
	SetupBoardBlocks(boardBlocks, rowSize, colSize);
}

void Board::Draw(const Vec2i& windowPos, int32_t blockSize)
{
	for (int32_t x = 0; x < colSize; ++x)
	{
		for (int32_t y = 0; y < rowSize; ++y)
		{
			Block state = GetBlock(x, y);

			if (state.first == Board::EBlockState::Fix)
			{
				GameEngine::GetGameRenderer().DrawRectangle2D(
					Vec2i(windowPos.x + blockSize * x, windowPos.y + blockSize * y),
					Vec2i(windowPos.x + blockSize * (x + 1), windowPos.y + blockSize * (y + 1)),
					wallColor
				);
			}
			else if (state.first == Board::EBlockState::Fill)
			{
				GameEngine::GetGameRenderer().DrawRectangle2D(
					Vec2i(windowPos.x + blockSize * x, windowPos.y + blockSize * y),
					Vec2i(windowPos.x + blockSize * (x + 1), windowPos.y + blockSize * (y + 1)),
					state.second
				);

				GameEngine::GetGameRenderer().DrawRectangle2D(
					Vec2i(windowPos.x + blockSize * x, windowPos.y + blockSize * y),
					Vec2i(windowPos.x + blockSize * (x + 1), windowPos.y + blockSize * (y + 1)),
					backgroundColor
				);
			}
			else
			{
				GameEngine::GetGameRenderer().DrawRectangle2D(
					Vec2i(windowPos.x + blockSize * x, windowPos.y + blockSize * y),
					Vec2i(windowPos.x + blockSize * (x + 1), windowPos.y + blockSize * (y + 1)),
					backgroundColor
				);
			}
		}
	}
}

void Board::AddTetrominoInBoard(Tetromino& tetromino)
{
	const std::vector<Vec2i> positions = tetromino.GetRelativePositions();

	for (const auto& position : positions)
	{
		Vec2i boardPos;
		boardPos.x = tetromino.GetAbsolutePosition().x + position.x;
		boardPos.y = tetromino.GetAbsolutePosition().y + position.y;


		SetBlock(boardPos.x, boardPos.y, Board::Block(Board::EBlockState::Fill, tetromino.GetBlockColor()));
	}
}

void Board::RemoveTetrominoInBoard(Tetromino& tetromino)
{
	const std::vector<Vec2i> positions = tetromino.GetRelativePositions();

	for (const auto& position : positions)
	{
		Vec2i boardPos;
		boardPos.x = tetromino.GetAbsolutePosition().x + position.x;
		boardPos.y = tetromino.GetAbsolutePosition().y + position.y;


		SetBlock(boardPos.x, boardPos.y, Board::Block(Board::EBlockState::Empty, tetromino.GetBlockColor()));
	}
}

bool Board::IsCrashTetrominoAndBoard(Tetromino& tetromino)
{
	const std::vector<Vec2i> positions = tetromino.GetRelativePositions();

	for (const auto& position : positions)
	{
		Vec2i boardPos;
		boardPos.x = tetromino.GetAbsolutePosition().x + position.x;
		boardPos.y = tetromino.GetAbsolutePosition().y + position.y;

		if (!CheckInsidePositionInBoard(boardPos.x, boardPos.y))
		{
			return true;
		}

		if (GetBlock(boardPos.x, boardPos.y).first != Board::EBlockState::Empty)
		{
			return true;
		}
	}

	return false;
}

bool Board::MoveDownTetrominoInBoard(Tetromino& tetromino)
{
	bool bCanMove = true;
	RemoveTetrominoInBoard(tetromino);

	tetromino.Move(Tetromino::EMove::Down);

	if (IsCrashTetrominoAndBoard(tetromino))
	{
		tetromino.Move(Tetromino::EMove::Up);
		bCanMove = false;
	}

	AddTetrominoInBoard(tetromino);
	return bCanMove;
}

void Board::MoveLeftTetrominoInBoard(Tetromino& tetromino)
{
	RemoveTetrominoInBoard(tetromino);

	tetromino.Move(Tetromino::EMove::Left);

	if (IsCrashTetrominoAndBoard(tetromino))
	{
		tetromino.Move(Tetromino::EMove::Right);
	}

	AddTetrominoInBoard(tetromino);
}

void Board::MoveRightTetrominoInBoard(Tetromino& tetromino)
{
	RemoveTetrominoInBoard(tetromino);

	tetromino.Move(Tetromino::EMove::Right);

	if (IsCrashTetrominoAndBoard(tetromino))
	{
		tetromino.Move(Tetromino::EMove::Left);
	}

	AddTetrominoInBoard(tetromino);
}

void Board::MoveBottomTetrominoInBoard(Tetromino& tetromino)
{
	RemoveTetrominoInBoard(tetromino);

	while (true)
	{
		tetromino.Move(Tetromino::EMove::Down);

		if (IsCrashTetrominoAndBoard(tetromino))
		{
			tetromino.Move(Tetromino::EMove::Up);
			break;
		}
	}

	AddTetrominoInBoard(tetromino);
}

void Board::SpinClockWiseTetrominoInBoard(Tetromino& tetromino)
{
	RemoveTetrominoInBoard(tetromino);

	tetromino.Spin(Tetromino::ESpin::CW);

	if (IsCrashTetrominoAndBoard(tetromino))
	{
		tetromino.Spin(Tetromino::ESpin::CCW);
	}

	AddTetrominoInBoard(tetromino);
}

void Board::SpinCounterClockWiseTetrominoInBoard(Tetromino& tetromino)
{
	RemoveTetrominoInBoard(tetromino);

	tetromino.Spin(Tetromino::ESpin::CCW);

	if (IsCrashTetrominoAndBoard(tetromino))
	{
		tetromino.Spin(Tetromino::ESpin::CW);
	}

	AddTetrominoInBoard(tetromino);
}