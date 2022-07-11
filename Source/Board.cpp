#include "Game/Logger.h"
#include "Game/Macro.h"
#include "Game/DrawHelper.h"

#include "Board.h"

Board::Board(int32_t InRowSize, int32_t InColSize, const LinearColor& InWallBlockColor, const LinearColor& InEmptyBlockColor)
	: RowSize(InRowSize)
	, ColSize(InColSize)
	, WallBlockColor(InWallBlockColor)
	, EmptyBlockColor(InEmptyBlockColor)
{
	Blocks = GenerateEmptyBlocks(RowSize, ColSize, EmptyBlockColor);
	SetupBlocks(Blocks, RowSize, ColSize, EmptyBlockColor, WallBlockColor);
}

Board::~Board()
{
}

Board::Board(Board&& InInstance) noexcept
	: RowSize(InInstance.RowSize)
	, ColSize(InInstance.ColSize)
	, WallBlockColor(InInstance.WallBlockColor)
	, EmptyBlockColor(InInstance.EmptyBlockColor)
	, Blocks(InInstance.Blocks)
{
}

Board::Board(const Board& InInstance) noexcept
	: RowSize(InInstance.RowSize)
	, ColSize(InInstance.ColSize)
	, WallBlockColor(InInstance.WallBlockColor)
	, EmptyBlockColor(InInstance.EmptyBlockColor)
	, Blocks(InInstance.Blocks)
{
}

Board& Board::operator=(Board&& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	RowSize = InInstance.RowSize;
	ColSize = InInstance.ColSize;
	WallBlockColor = InInstance.WallBlockColor;
	EmptyBlockColor = InInstance.EmptyBlockColor;
	Blocks = InInstance.Blocks;

	return *this;
}

Board& Board::operator=(const Board& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	RowSize = InInstance.RowSize;
	ColSize = InInstance.ColSize;
	WallBlockColor = InInstance.WallBlockColor;
	EmptyBlockColor = InInstance.EmptyBlockColor;
	Blocks = InInstance.Blocks;

	return *this;
}

int32_t Board::UpdateBoardState()
{
	int32_t RemoveLine = CalculateCanRemoveLine();

	if (RemoveLine > 0)
	{
		for (int32_t Row = 0; Row < RowSize - 1; ++Row)
		{
			if (IsFullRowLine(Blocks, RowSize, ColSize, Row))
			{
				RemoveRowLine(Blocks, RowSize, ColSize, Row);
			}
		}

		std::vector<Block> NewBlocks = GenerateEmptyBlocks(RowSize, ColSize);
		SetupBlocks(NewBlocks, RowSize, ColSize, EmptyBlockColor, WallBlockColor);

		for (int32_t Row = RowSize - 2, TargetRowLine = RowSize - 2; Row >= 0; --Row)
		{
			if (!IsEmptyRowLine(Blocks, RowSize, ColSize, Row))
			{
				for (int32_t Col = 1; Col < ColSize - 1; ++Col)
				{
					NewBlocks[GetBlocksOffset(TargetRowLine, Col, RowSize, ColSize)] = Blocks[GetBlocksOffset(Row, Col, RowSize, ColSize)];
				}

				TargetRowLine--;
			}
		}

		Blocks = NewBlocks;
	}

	return RemoveLine;
}

void Board::ResetBoardState()
{
	SetupBlocks(Blocks, RowSize, ColSize, EmptyBlockColor, WallBlockColor);
}

bool Board::AddTetromino(const Tetromino& InTetromino)
{
	if (IsCrashTetromino(InTetromino))
	{
		return false;
	}

	const std::vector<Vec2i> Positions = InTetromino.GetBlockPositions();

	for (const auto& Position : Positions)
	{
		Vec2i BoardPosition = InTetromino.GetPositionInBoard() + Position;

		SetBlock(
			Blocks,
			Block(EBlockState::Fill, InTetromino.GetBlockColor()),
			BoardPosition.y,
			BoardPosition.x,
			RowSize,
			ColSize
		);
	}

	return true;
}

void Board::RemoveTetromino(const Tetromino& InTetromino)
{
	const std::vector<Vec2i> Positions = InTetromino.GetBlockPositions();

	for (const auto& Position : Positions)
	{
		Vec2i BoardPosition = InTetromino.GetPositionInBoard() + Position;

		SetBlock(
			Blocks,
			Block(EBlockState::Empty, InTetromino.GetBlockColor()),
			BoardPosition.y,
			BoardPosition.x,
			RowSize,
			ColSize
		);
	}
}

bool Board::MoveTetromino(Tetromino& InTetromino, const Tetromino::EMove& InMove)
{
	bool bCanMove = true;
	Tetromino::EMove CountMove = Tetromino::CalculateCountMove(InMove);

	RemoveTetromino(InTetromino);

	InTetromino.Move(InMove);

	if (IsCrashTetromino(InTetromino))
	{
		InTetromino.Move(CountMove);
		bCanMove = false;
	}

	AddTetromino(InTetromino);
	return bCanMove;
}

bool Board::SpinTetromino(Tetromino& InTetromino, const Tetromino::ESpin& InSpin)
{
	bool bCanSpin = true;
	Tetromino::ESpin CountSpin = Tetromino::CalculateCountSpin(InSpin);

	RemoveTetromino(InTetromino);

	InTetromino.Spin(InSpin);

	if (IsCrashTetromino(InTetromino))
	{
		InTetromino.Spin(CountSpin);
		bCanSpin = false;
	}

	AddTetromino(InTetromino);
	return bCanSpin;
}

void Board::Draw(SDL_Renderer* InRenderer, const Vec2i& InWindowPosition, int32_t InBlockSize)
{
	for (int32_t Col = 0; Col < ColSize; ++Col)
	{
		for (int32_t Row = 0; Row < RowSize; ++Row)
		{
			Block BlockState = GetBlock(Blocks, Row, Col, RowSize, ColSize);

			Vec2i LeftTopPosition(
				InWindowPosition.x + InBlockSize * Col,
				InWindowPosition.y + InBlockSize * Row
			);

			Vec2i RightBottonPosition(
				InWindowPosition.x + InBlockSize * (Col + 1),
				InWindowPosition.y + InBlockSize * (Row + 1)
			);

			if (BlockState.first == Board::EBlockState::Fix)
			{
				Game::DrawHelper::DrawRectangle2D(InRenderer, LeftTopPosition, RightBottonPosition, WallBlockColor);
			}
			else if (BlockState.first == Board::EBlockState::Fill)
			{
				Game::DrawHelper::DrawRectangle2D(InRenderer, LeftTopPosition, RightBottonPosition, BlockState.second);
				Game::DrawHelper::DrawWireframeRectangle2D(InRenderer, LeftTopPosition, RightBottonPosition, EmptyBlockColor);
			}
			else // BlockState.first == Board::EBlockState::Empty
			{
				Game::DrawHelper::DrawRectangle2D(InRenderer, LeftTopPosition, RightBottonPosition, EmptyBlockColor);
			}
		}
	}
}

int32_t Board::CalculateCanRemoveLine()
{
	int32_t CountOfRemoveLine = 0;

	for (int32_t Row = 0; Row < RowSize - 1; ++Row)
	{
		if (IsFullRowLine(Blocks, RowSize, ColSize, Row))
		{
			CountOfRemoveLine++;
		}
	}

	return CountOfRemoveLine;
}

bool Board::IsCrashTetromino(const Tetromino& InTetromino)
{
	const std::vector<Vec2i> Positions = InTetromino.GetBlockPositions();

	for (const auto& Position : Positions)
	{
		Vec2i BoardPosition = InTetromino.GetPositionInBoard() + Position;

		if (!CheckInsidePositionInBlocks(BoardPosition.y, BoardPosition.x, RowSize, ColSize))
		{
			return true;
		}

		if (GetBlock(Blocks, BoardPosition.y, BoardPosition.x, RowSize, ColSize).first != Board::EBlockState::Empty)
		{
			return true;
		}
	}

	return false;
}

bool Board::CheckInsidePositionInBlocks(int32_t InRow, int32_t InCol, int32_t InRowSize, int32_t InColSize)
{
	return ((0 <= InCol && InCol < InColSize) && (0 <= InRow && InRow < InRowSize));
}

int32_t Board::GetBlocksOffset(int32_t InRow, int32_t InCol, int32_t InRowSize, int32_t InColSize)
{
	CHECK_FAILED(CheckInsidePositionInBlocks(InRow, InCol, InRowSize, InColSize), "out of range in blocks");
	return InRow * InColSize + InCol;
}

bool Board::IsFullRowLine(const std::vector<Block>& InBlocks, int32_t InRowSize, int32_t InColSize, int32_t InTargetRow)
{
	for (int32_t Col = 1; Col < InColSize - 1; ++Col)
	{
		int32_t Offset = GetBlocksOffset(InTargetRow, Col, InRowSize, InColSize);

		if (InBlocks[Offset].first != EBlockState::Fill)
		{
			return false;
		}
	}

	return true;
}

bool Board::IsEmptyRowLine(const std::vector<Block>& InBlocks, int32_t InRowSize, int32_t InColSize, int32_t InTargetRow)
{
	for (int32_t Col = 1; Col < InColSize - 1; ++Col)
	{
		int32_t Offset = GetBlocksOffset(InTargetRow, Col, InRowSize, InColSize);

		if (InBlocks[Offset].first != EBlockState::Empty)
		{
			return false;
		}
	}

	return true;
}

void Board::RemoveRowLine(std::vector<Block>& InBlocks, int32_t InRowSize, int32_t InColSize, int32_t InTargetRow)
{
	for (int32_t Col = 1; Col < InColSize - 1; ++Col)
	{
		int32_t Offset = GetBlocksOffset(InTargetRow, Col, InRowSize, InColSize);
		InBlocks[Offset].first = EBlockState::Empty;
	}
}

std::vector<Board::Block> Board::GenerateEmptyBlocks(int32_t InRowSize, int32_t InColSize, const LinearColor& EmptyColor)
{
	return std::vector<Block>(InRowSize * InColSize, Block(EBlockState::Empty, EmptyColor));
}

void Board::SetupBlocks(
	std::vector<Block>& InBlocks,
	int32_t InRowSize,
	int32_t InColSize,
	const LinearColor& EmptyColor,
	const LinearColor& InWallColor
)
{
	std::fill(InBlocks.begin(), InBlocks.end(), Block(EBlockState::Empty, EmptyColor));

	for (int32_t Row = 0; Row < InRowSize; ++Row)
	{

		if (Row == InRowSize - 1)
		{
			for (int32_t Col = 0; Col < InColSize; ++Col)
			{
				InBlocks[GetBlocksOffset(Row, Col, InRowSize, InColSize)] = Block(EBlockState::Fix, InWallColor);
			}
		}
		else
		{
			InBlocks[GetBlocksOffset(Row,             0, InRowSize, InColSize)] = Block(EBlockState::Fix, InWallColor);
			InBlocks[GetBlocksOffset(Row, InColSize - 1, InRowSize, InColSize)] = Block(EBlockState::Fix, InWallColor);
		}
	}
}

Board::Block Board::GetBlock(const std::vector<Block>& InBlocks, int32_t InRow, int32_t InCol, int32_t InRowSize, int32_t InColSize)
{
	int32_t Offset = GetBlocksOffset(InRow, InCol, InRowSize, InColSize);
	return InBlocks[Offset];
}

void Board::SetBlock(std::vector<Block>& InBlocks, Block InBlock, int32_t InRow, int32_t InCol, int32_t InRowSize, int32_t InColSize)
{
	int32_t Offset = GetBlocksOffset(InRow, InCol, InRowSize, InColSize);
	InBlocks[Offset] = InBlock;
}
