#include "Game/Logger.h"
#include "Game/Renderer.h"

#include "Tetromino.h"

Tetromino::Tetromino(const Vec2i& InPositionInBoard, const EShape& InShape, const LinearColor& InColor)
	: PositionInBoard(InPositionInBoard)
	, BlockColor(InColor)
{
	GenerateBlockPositions(InShape);
}

Tetromino::~Tetromino()
{
}

Tetromino::Tetromino(Tetromino&& InInstance) noexcept
	: BlockColor(InInstance.BlockColor)
	, BoundSize(InInstance.BoundSize)
	, PositionInBoard(InInstance.PositionInBoard)
	, BlockPositions(InInstance.BlockPositions)
{
}

Tetromino::Tetromino(const Tetromino& InInstance) noexcept
	: BlockColor(InInstance.BlockColor)
	, BoundSize(InInstance.BoundSize)
	, PositionInBoard(InInstance.PositionInBoard)
	, BlockPositions(InInstance.BlockPositions)
{
}

Tetromino& Tetromino::operator=(Tetromino&& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	BlockColor      = InInstance.BlockColor;
	BoundSize       = InInstance.BoundSize;
	PositionInBoard = InInstance.PositionInBoard;
	BlockPositions  = InInstance.BlockPositions;

	return *this;
}

Tetromino& Tetromino::operator=(const Tetromino& InInstance) noexcept
{	
	if (this == &InInstance) return *this;

	BlockColor      = InInstance.BlockColor;
	BoundSize       = InInstance.BoundSize;
	PositionInBoard = InInstance.PositionInBoard;
	BlockPositions  = InInstance.BlockPositions;

	return *this;
}

void Tetromino::Spin(ESpin InSpin)
{
	switch (InSpin)
	{
	case ESpin::CW:
		BlockPositions[0] = Vec2i(BoundSize - 1 - BlockPositions[0].y, BlockPositions[0].x);
		BlockPositions[1] = Vec2i(BoundSize - 1 - BlockPositions[1].y, BlockPositions[1].x);
		BlockPositions[2] = Vec2i(BoundSize - 1 - BlockPositions[2].y, BlockPositions[2].x);
		BlockPositions[3] = Vec2i(BoundSize - 1 - BlockPositions[3].y, BlockPositions[3].x);
		break;

	case ESpin::CCW:
		BlockPositions[0] = Vec2i(BlockPositions[0].y, BoundSize - 1 - BlockPositions[0].x);
		BlockPositions[1] = Vec2i(BlockPositions[1].y, BoundSize - 1 - BlockPositions[1].x);
		BlockPositions[2] = Vec2i(BlockPositions[2].y, BoundSize - 1 - BlockPositions[2].x);
		BlockPositions[3] = Vec2i(BlockPositions[3].y, BoundSize - 1 - BlockPositions[3].x);
		break;

	default:
		Game::Logger::Warning("undefined spin type");
	}
}

void Tetromino::Move(EMove InMove)
{
	switch (InMove)
	{
	case EMove::Left:
		PositionInBoard.x -= 1;
		break;

	case EMove::Right:
		PositionInBoard.x += 1;
		break;

	case EMove::Down:
		PositionInBoard.y += 1;
		break;

	case EMove::Up:
		PositionInBoard.y -= 1;
		break;

	default:
		Game::Logger::Warning("undefined move type");
	}
}

void Tetromino::Draw(SDL_Renderer* InRenderer, const Vec2i& InWindowPosition, int32_t InBlockSize, const LinearColor& InOutlineColor)
{
	for (const auto& BlockPosition : BlockPositions)
	{
		Vec2i LeftTopPosition(
			InWindowPosition.x + InBlockSize * BlockPosition.x, 
			InWindowPosition.y + InBlockSize * BlockPosition.y
		);

		Vec2i RightBottomPosition(
			InWindowPosition.x + InBlockSize * (BlockPosition.x + 1),
			InWindowPosition.y + InBlockSize * (BlockPosition.y + 1)
		);

		Game::Renderer::DrawRectangle2D(InRenderer, LeftTopPosition, RightBottomPosition, BlockColor);
		Game::Renderer::DrawWireframeRectangle2D(InRenderer, LeftTopPosition, RightBottomPosition, InOutlineColor);
	}
}

void Tetromino::GenerateBlockPositions(const EShape& InShape)
{
	BlockPositions.resize(4);

	switch (InShape)
	{
	case EShape::I:
		BoundSize = 4;
		BlockPositions[0] = Vec2i(0, 1);
		BlockPositions[1] = Vec2i(1, 1);
		BlockPositions[2] = Vec2i(2, 1);
		BlockPositions[3] = Vec2i(3, 1);
		break;

	case EShape::O:
		BoundSize = 4;
		BlockPositions[0] = Vec2i(1, 1);
		BlockPositions[1] = Vec2i(2, 1);
		BlockPositions[2] = Vec2i(1, 2);
		BlockPositions[3] = Vec2i(2, 2);
		break;

	case EShape::T:
		BoundSize = 3;
		BlockPositions[0] = Vec2i(0, 1);
		BlockPositions[1] = Vec2i(1, 1);
		BlockPositions[2] = Vec2i(2, 1);
		BlockPositions[3] = Vec2i(1, 2);
		break;

	case EShape::J:
		BoundSize = 3;
		BlockPositions[0] = Vec2i(0, 1);
		BlockPositions[1] = Vec2i(1, 1);
		BlockPositions[2] = Vec2i(2, 1);
		BlockPositions[3] = Vec2i(2, 2);
		break;

	case EShape::L:
		BoundSize = 3;
		BlockPositions[0] = Vec2i(0, 1);
		BlockPositions[1] = Vec2i(1, 1);
		BlockPositions[2] = Vec2i(2, 1);
		BlockPositions[3] = Vec2i(0, 2);
		break;

	case EShape::S:
		BoundSize = 3;
		BlockPositions[0] = Vec2i(1, 0);
		BlockPositions[1] = Vec2i(2, 0);
		BlockPositions[2] = Vec2i(0, 1);
		BlockPositions[3] = Vec2i(1, 1);
		break;

	case EShape::Z:
		BoundSize = 3;
		BlockPositions[0] = Vec2i(0, 0);
		BlockPositions[1] = Vec2i(0, 1);
		BlockPositions[2] = Vec2i(1, 1);
		BlockPositions[3] = Vec2i(2, 1);
		break;

	default:
		Game::Logger::Warning("undefined tetromino shape");
	}
}
