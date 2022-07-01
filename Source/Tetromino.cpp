#include "Logger.h"
#include "GameRenderer.h"
#include "GameEngine.h"
#include "Tetromino.h"

Tetromino::Tetromino(const Vec2i& InAbsolutePosition, const EShape& InShape, const LinearColor& InColor)
	: AbsolutePosition(InAbsolutePosition)
	, BlockColor(InColor)
{
	GenerateRelativePositions(InShape);
}

Tetromino::~Tetromino()
{
}

Tetromino::Tetromino(const Tetromino& InInstance) noexcept
	: BlockColor(InInstance.BlockColor)
	, BoundSize(InInstance.BoundSize)
	, AbsolutePosition(InInstance.AbsolutePosition)
	, RelativePositions(InInstance.RelativePositions)
{
}

Tetromino& Tetromino::operator=(const Tetromino& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	BlockColor = InInstance.BlockColor;
	BoundSize = InInstance.BoundSize;
	AbsolutePosition = InInstance.AbsolutePosition;
	RelativePositions = InInstance.RelativePositions;

	return *this;
}

Tetromino::Tetromino(Tetromino&& InInstance) noexcept
	: BlockColor(InInstance.BlockColor)
	, BoundSize(InInstance.BoundSize)
	, AbsolutePosition(InInstance.AbsolutePosition)
	, RelativePositions(InInstance.RelativePositions)
{
}

Tetromino& Tetromino::operator=(Tetromino&& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	BlockColor = InInstance.BlockColor;
	BoundSize = InInstance.BoundSize;
	AbsolutePosition = InInstance.AbsolutePosition;
	RelativePositions = InInstance.RelativePositions;

	return *this;
}

void Tetromino::Spin(ESpin spin)
{
	switch (spin)
	{
	case ESpin::CW:
		RelativePositions[0] = Vec2i(BoundSize - 1 - RelativePositions[0].y, RelativePositions[0].x);
		RelativePositions[1] = Vec2i(BoundSize - 1 - RelativePositions[1].y, RelativePositions[1].x);
		RelativePositions[2] = Vec2i(BoundSize - 1 - RelativePositions[2].y, RelativePositions[2].x);
		RelativePositions[3] = Vec2i(BoundSize - 1 - RelativePositions[3].y, RelativePositions[3].x);
		break;

	case ESpin::CCW:
		RelativePositions[0] = Vec2i(RelativePositions[0].y, BoundSize - 1 - RelativePositions[0].x);
		RelativePositions[1] = Vec2i(RelativePositions[1].y, BoundSize - 1 - RelativePositions[1].x);
		RelativePositions[2] = Vec2i(RelativePositions[2].y, BoundSize - 1 - RelativePositions[2].x);
		RelativePositions[3] = Vec2i(RelativePositions[3].y, BoundSize - 1 - RelativePositions[3].x);
		break;

	default:
		Logger::Warning("not support spin type");
	}
}

void Tetromino::Move(EMove move)
{
	switch (move)
	{
	case EMove::Left:
		AbsolutePosition.x -= 1;
		break;

	case EMove::Right:
		AbsolutePosition.x += 1;
		break;

	case EMove::Down:
		AbsolutePosition.y += 1;
		break;

	case EMove::Up:
		AbsolutePosition.y -= 1;
		break;

	default:
		Logger::Warning("not support move type");
	}
}

void Tetromino::Draw(const Vec2i& InWindowPosition, int32_t InBlockSize, const LinearColor& InOutlineColor)
{
	for (const auto& Position : RelativePositions)
	{
		GameEngine::GetGameRenderer().DrawRectangle2D(
			Vec2i(      InWindowPosition.x + InBlockSize * Position.x,       InWindowPosition.y + InBlockSize * Position.y),
			Vec2i(InWindowPosition.x + InBlockSize * (Position.x + 1), InWindowPosition.y + InBlockSize * (Position.y + 1)),
			BlockColor
		);

		GameEngine::GetGameRenderer().DrawWireframeRectangle2D(
			Vec2i(      InWindowPosition.x + InBlockSize * Position.x,       InWindowPosition.y + InBlockSize * Position.y),
			Vec2i(InWindowPosition.x + InBlockSize * (Position.x + 1), InWindowPosition.y + InBlockSize * (Position.y + 1)),
			InOutlineColor
		);
	}
}

void Tetromino::GenerateRelativePositions(const EShape& InShape)
{
	RelativePositions.resize(4);

	switch (InShape)
	{
	case EShape::I:
		BoundSize = 4;
		RelativePositions[0] = Vec2i(0, 1);
		RelativePositions[1] = Vec2i(1, 1);
		RelativePositions[2] = Vec2i(2, 1);
		RelativePositions[3] = Vec2i(3, 1);
		break;

	case EShape::O:
		BoundSize = 4;
		RelativePositions[0] = Vec2i(1, 1);
		RelativePositions[1] = Vec2i(2, 1);
		RelativePositions[2] = Vec2i(1, 2);
		RelativePositions[3] = Vec2i(2, 2);
		break;

	case EShape::T:
		BoundSize = 3;
		RelativePositions[0] = Vec2i(0, 1);
		RelativePositions[1] = Vec2i(1, 1);
		RelativePositions[2] = Vec2i(2, 1);
		RelativePositions[3] = Vec2i(1, 2);
		break;

	case EShape::J:
		BoundSize = 3;
		RelativePositions[0] = Vec2i(0, 1);
		RelativePositions[1] = Vec2i(1, 1);
		RelativePositions[2] = Vec2i(2, 1);
		RelativePositions[3] = Vec2i(2, 2);
		break;

	case EShape::L:
		BoundSize = 3;
		RelativePositions[0] = Vec2i(0, 1);
		RelativePositions[1] = Vec2i(1, 1);
		RelativePositions[2] = Vec2i(2, 1);
		RelativePositions[3] = Vec2i(0, 2);
		break;

	case EShape::S:
		BoundSize = 3;
		RelativePositions[0] = Vec2i(1, 0);
		RelativePositions[1] = Vec2i(2, 0);
		RelativePositions[2] = Vec2i(0, 1);
		RelativePositions[3] = Vec2i(1, 1);
		break;

	case EShape::Z:
		BoundSize = 3;
		RelativePositions[0] = Vec2i(0, 0);
		RelativePositions[1] = Vec2i(0, 1);
		RelativePositions[2] = Vec2i(1, 1);
		RelativePositions[3] = Vec2i(2, 1);
		break;

	default:
		Logger::Warning("not support tetromino shape");
	}
}