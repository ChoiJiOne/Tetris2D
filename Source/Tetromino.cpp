#include "Public/GameEngine.h"
#include "Public/GameRenderer.h"
#include "Public/Macro.h"
#include "Tetromino.h"

Tetromino::Tetromino(const EShape& InShape, const EBlockColor& InBlockColor, const Vec2i& InPositionInBoard)
	: PositionInBoard(InPositionInBoard)
	, BlockColor(InBlockColor)
{
	GenerateBlockPositions(InShape);
	TetrominoTexture.CreateTextureFromFile(GameEngine::GetResourceDirectory() + "texture/GrayBlock.png");
}

Tetromino::~Tetromino()
{
}

Tetromino::Tetromino(const Tetromino& InInstance) noexcept
	: BoundSize(InInstance.BoundSize)
	, PositionInBoard(InInstance.PositionInBoard)
	, BlockPositions(InInstance.BlockPositions)
	, BlockColor(InInstance.BlockColor)
{
}

Tetromino& Tetromino::operator=(const Tetromino& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	BoundSize = InInstance.BoundSize;
	PositionInBoard = InInstance.PositionInBoard;
	BlockPositions = InInstance.BlockPositions;
	BlockColor = InInstance.BlockColor;

	return *this;
}

Tetromino::Tetromino(Tetromino&& InInstance) noexcept
	: BoundSize(InInstance.BoundSize)
	, PositionInBoard(InInstance.PositionInBoard)
	, BlockPositions(InInstance.BlockPositions)
	, BlockColor(InInstance.BlockColor)
{
}

Tetromino& Tetromino::operator=(Tetromino&& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	BoundSize = InInstance.BoundSize;
	PositionInBoard = InInstance.PositionInBoard;
	BlockPositions = InInstance.BlockPositions;
	BlockColor = InInstance.BlockColor;

	return *this;
}

std::shared_ptr<Tetromino> Tetromino::GenerateRandomTetromino(const Vec2i& InPositionInBoard)
{
	static EShape TetrominoShapes[] = {
		EShape::I,
		EShape::O,
		EShape::T,
		EShape::J,
		EShape::L,
		EShape::S,
		EShape::Z
	};

	static EBlockColor TetrominoColors[] = {
		EBlockColor::BLUE,
		EBlockColor::CYAN,
		EBlockColor::GRAY,
		EBlockColor::GREEN,
		EBlockColor::ORANGE,
		EBlockColor::PINK,
		EBlockColor::PURPLE,
		EBlockColor::RED,
		EBlockColor::YELLOW
	};

	int32_t TetrominoShape = MathUtil::GenerateRandomInt<int32_t>(0, std::size(TetrominoShapes) - 1);
	int32_t TetrominoColor = MathUtil::GenerateRandomInt<int32_t>(0, std::size(TetrominoColors) - 1);

	return std::make_shared<Tetromino>(
		TetrominoShapes[TetrominoShape],
		TetrominoColors[TetrominoColor],
		InPositionInBoard
	);
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
		Logger::Warning("not support spin type");
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
		Logger::Warning("not support move type");
	}
}

void Tetromino::DrawTetromino(const Vec2i& InPosition, float InScale)
{
	int32_t TextureWidth = 0, TextureHeight = 0;

	TextureWidth  = static_cast<int32_t>(static_cast<float>(TetrominoTexture.GetWidth()) * InScale);
	TextureHeight = static_cast<int32_t>(static_cast<float>(TetrominoTexture.GetHeight()) * InScale);

	for (const auto& BlockPosition : BlockPositions)
	{
		Vec2i MovePosition(BlockPosition.x * TextureWidth, BlockPosition.y * TextureHeight);

		GameEngine::GetGameRenderer().DrawTexture2D(
			TetrominoTexture,
			InPosition + MovePosition,
			InScale,
			InScale
		);
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
		Logger::Warning("not support tetromino shape");
	}
}
