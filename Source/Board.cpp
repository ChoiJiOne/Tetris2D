#include "Macro.h"
#include "Board.h"

Board::~Board()
{
}

Board::Board(Board&& InInstance) noexcept
	: BoardWidth(InInstance.BoardWidth)
	, BoardHeight(InInstance.BoardHeight)
	, BoardState(InInstance.BoardState)
{
}

Board::Board(const Board& InInstance) noexcept
	: BoardWidth(InInstance.BoardWidth)
	, BoardHeight(InInstance.BoardHeight)
	, BoardState(InInstance.BoardState)
{
}

Board& Board::operator=(Board&& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	BoardWidth  = InInstance.BoardWidth;
	BoardHeight = InInstance.BoardHeight;
	BoardState  = InInstance.BoardState;

	return *this;
}

Board& Board::operator=(const Board& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	BoardWidth  = InInstance.BoardWidth;
	BoardHeight = InInstance.BoardHeight;
	BoardState  = InInstance.BoardState;

	return *this;
}

void Board::Init(int32_t InBoardWidth, int32_t InBoardHeight)
{
	BoardWidth  = InBoardWidth;
	BoardHeight = InBoardHeight;

	BoardState.resize(BoardWidth * BoardHeight, Block(EBlockState::EMPTY, EBlockColor::GRAY));

	for (int32_t Row = 0; Row < BoardHeight; ++Row)
	{
		if (Row == BoardHeight - 1)
		{
			for (int32_t Col = 0; Col < BoardWidth; ++Col)
			{
				BoardState[GetBoardOffset(Row, Col)] = Block(EBlockState::FIX, EBlockColor::GRAY);
			}
		}
		else
		{
			BoardState[GetBoardOffset(Row,              0)] = Block(EBlockState::FIX, EBlockColor::GRAY);
			BoardState[GetBoardOffset(Row, BoardWidth - 1)] = Block(EBlockState::FIX, EBlockColor::GRAY);
		}
	}
}

Block Board::GetBlockInBoard(int32_t InRow, int32_t InCol) const
{
	CHECK_FAILED(IsInsidePosition(InRow, InCol), "out of range in board");
	return BoardState[GetBoardOffset(InRow, InCol)];
}

EBlockState Board::GetBlockStateInBoard(int32_t InRow, int32_t InCol) const
{
	return GetBlockInBoard(InRow, InCol).first;
}

EBlockColor Board::GetBlockColorInBoard(int32_t InRow, int32_t InCol) const
{
	return GetBlockInBoard(InRow, InCol).second;
}

void Board::SetBlockInBoard(int32_t InRow, int32_t InCol, const Block& InBlock)
{
	if (IsInsidePosition(InRow, InCol))
	{
		BoardState[GetBoardOffset(InRow, InCol)] = InBlock;
	}
}

void Board::SetBlockStateInBoard(int32_t InRow, int32_t InCol, const EBlockState& InBlockState)
{
	if (IsInsidePosition(InRow, InCol))
	{
		BoardState[GetBoardOffset(InRow, InCol)].first = InBlockState;
	}
}

void Board::SetBlockColorInBoard(int32_t InRow, int32_t InCol, const EBlockColor& InBlockColor)
{
	if (IsInsidePosition(InRow, InCol))
	{
		BoardState[GetBoardOffset(InRow, InCol)].second = InBlockColor;
	}
}

bool Board::IsInsidePosition(int32_t InRow, int32_t InCol) const
{
	return (0 <= InRow && InRow < BoardHeight) 
		&& (0 <= InCol && InCol < BoardWidth);
}

int32_t Board::GetBoardOffset(int32_t InRow, int32_t InCol) const
{
	return InRow * BoardWidth + InCol;
}
