#include "TetrominoPhysicComponent.h"
#include "Board.h"
#include "BlockComponent.h"
#include "GameAudioComponent.h"
#include "TetrominoInputComponent.h"
#include "WorldManager.h"

void TetrominoPhysicComponent::Tick()
{
	Tetromino* Object = reinterpret_cast<Tetromino*>(GetGameObject());
	Board* BoardObject = WorldManager::Get().GetGameObject<Board>("BOARD::PlayScene");
	std::array<BlockComponent*, 4>& Blocks = Object->GetBlocks();
	
	TetrominoInputComponent* Input = Object->GetComponent<TetrominoInputComponent>("Input");
	Tetromino::EDirection Direction = Input->GetDirection();

	if (Direction == Tetromino::EDirection::JUMP)
	{
		while (!IsCollision())
		{
			Move(Tetromino::EDirection::DOWN, Object->GetShape(), Blocks);
		}

		Move(GetCountDirection(Direction), Object->GetShape(), Blocks);
		Object->SetState(Tetromino::EState::DONE);
		BoardObject->AddBlocks(Blocks);
		BoardObject->SetState(Board::EState::ACTIVE);
		Input->ResetAccrueFrameTime();

		Object->GetComponent<GameAudioComponent>("Jump")->Play();
	}
	else
	{
		Move(Direction, Object->GetShape(), Blocks);

		if (IsCollision())
		{
			Move(GetCountDirection(Direction), Object->GetShape(), Blocks);
		}

		float AccrueFrameTime = Input->GetAccrueFrameTime();
		if (AccrueFrameTime >= Object->GetUpdateStep())
		{
			Move(Tetromino::EDirection::DOWN, Object->GetShape(), Blocks);

			if (IsCollision())
			{
				Move(GetCountDirection(Tetromino::EDirection::DOWN), Object->GetShape(), Blocks);
				Object->SetState(Tetromino::EState::DONE);
				BoardObject->AddBlocks(Blocks);
				BoardObject->SetState(Board::EState::ACTIVE);
			}

			Input->ResetAccrueFrameTime();
		}
	}
}

bool TetrominoPhysicComponent::IsCollision()
{
	Board* BoardObject = WorldManager::Get().GetGameObject<Board>("BOARD::PlayScene");
	Tetromino* TetrominoObject = reinterpret_cast<Tetromino*>(GetGameObject());

	return IsCollisionBlocks(BoardObject->GetBlocks(), TetrominoObject->GetBlocks());
}

void TetrominoPhysicComponent::Move(
	const Tetromino::EDirection& Direction, 
	const Tetromino::EShape& Shape, 
	std::array<BlockComponent*, 4>& Blocks
)
{
	Vec2f BlocksCenter;
	Vec2f Center;
	float MoveBias = (Direction == Tetromino::EDirection::LEFT || Direction == Tetromino::EDirection::DOWN) ? -1.0f : 1.0f;
	float SpinBias = (Direction == Tetromino::EDirection::CCW) ? -1.0f : 1.0f;

	switch (Direction)
	{
	case Tetromino::EDirection::LEFT:
	case Tetromino::EDirection::RIGHT:
		LTPosition_.x += (MoveBias * MoveLength_);

		for (auto& Block : Blocks)
		{
			Center = Block->GetCenter();
			Center.x += (MoveBias * MoveLength_);
			Block->SetCenter(Center);
		}
		break;

	case Tetromino::EDirection::UP:
	case Tetromino::EDirection::DOWN:
		LTPosition_.y += (MoveBias * MoveLength_);

		for (auto& Block : Blocks)
		{
			Center = Block->GetCenter();
			Center.y += (MoveBias * MoveLength_);
			Block->SetCenter(Center);
		}
		break;

	case Tetromino::EDirection::CW:
	case Tetromino::EDirection::CCW:
		BlocksCenter = CalculateBlocksCenter(Shape, LTPosition_, BlockSide_);

		for (auto& Block : Blocks)
		{
			Center = Block->GetCenter();
			Center -= BlocksCenter;

			Center = Vec2f(
				+SpinBias * Center.y,
				-SpinBias * Center.x
			);

			Center += BlocksCenter;
			Block->SetCenter(Center);
		}
		break;
	}
}

bool TetrominoPhysicComponent::CanTeleport(const Vec2f& LTPosition)
{
	Vec2f OriginLTPosition = LTPosition_;
	Vec2f TeleportPosition = LTPosition;

	Teleport(TeleportPosition);
	bool bCanTeleport = !IsCollision();
	Teleport(OriginLTPosition);

	return bCanTeleport;
}

void TetrominoPhysicComponent::Teleport(const Vec2f& TeleportPosition)
{
	std::array<BlockComponent*, 4>& Blocks = reinterpret_cast<Tetromino*>(GetGameObject())->GetBlocks();
	Vec2f Center;

	for (auto& Block : Blocks)
	{
		Center = Block->GetCenter();
		Center -= LTPosition_;

		Center += TeleportPosition;
		Block->SetCenter(Center);
	}

	LTPosition_ = TeleportPosition;
}

bool TetrominoPhysicComponent::IsCollisionBlocks(const std::vector<BlockComponent*>& LhsBlocks, const std::array<BlockComponent*, 4>& RhsBlocks)
{
	for (const auto& LhsBlock : LhsBlocks)
	{
		for (const auto& RhsBlock : RhsBlocks)
		{
			if (LhsBlock->IsCollision(RhsBlock))
			{
				return true;
			}
		}
	}

	return false;
}

Vec2f TetrominoPhysicComponent::CalculateBlocksCenter(const Tetromino::EShape& Shape, const Vec2f& LTPosition, const float& BlockSide)
{
	Vec2f BlocksCenter = LTPosition;
	float Bias = 0.0f;

	if (Shape == Tetromino::EShape::I || Shape == Tetromino::EShape::O)
	{
		Bias = (BlockSide * 3.0f) / 2.0f;
	}
	else
	{
		Bias = BlockSide;
	}

	BlocksCenter.x += Bias;
	BlocksCenter.y -= Bias;

	return BlocksCenter;
}

Tetromino::EDirection TetrominoPhysicComponent::GetCountDirection(const Tetromino::EDirection& Direction)
{
	Tetromino::EDirection CountDirection;

	switch (Direction)
	{
	case Tetromino::EDirection::NONE:
		CountDirection = Tetromino::EDirection::NONE;
		break;

	case Tetromino::EDirection::CW:
		CountDirection = Tetromino::EDirection::CCW;
		break;

	case Tetromino::EDirection::CCW:
		CountDirection = Tetromino::EDirection::CW;
		break;

	case Tetromino::EDirection::DOWN:
		CountDirection = Tetromino::EDirection::UP;
		break;

	case Tetromino::EDirection::UP:
		CountDirection = Tetromino::EDirection::DOWN;
		break;

	case Tetromino::EDirection::LEFT:
		CountDirection = Tetromino::EDirection::RIGHT;
		break;

	case Tetromino::EDirection::RIGHT:
		CountDirection = Tetromino::EDirection::LEFT;
		break;

	case Tetromino::EDirection::JUMP:
		CountDirection = Tetromino::EDirection::UP;
		break;

	default:
		ENFORCE_THROW_EXCEPTION("undefined movement type...");
	}

	return CountDirection;
}
