#include "Tetromino.h"
#include "ContentManager.h"
#include "GraphicsManager.h"
#include "Shader.h"
#include "TetrominoRenderComponent.h"
#include "TetrominoInputComponent.h"
#include "Utility.hpp"

static const std::array<Tetromino::EShape, 7> SHAPES = {
	Tetromino::EShape::I,
	Tetromino::EShape::O,
	Tetromino::EShape::T,
	Tetromino::EShape::J,
	Tetromino::EShape::L,
	Tetromino::EShape::S,
	Tetromino::EShape::Z
};

static const std::array<BlockComponent::EType, 8> BLOCKCOLORS = {
	BlockComponent::EType::BLUE,
	BlockComponent::EType::CYAN,
	BlockComponent::EType::GREEN,
	BlockComponent::EType::ORANGE,
	BlockComponent::EType::PINK,
	BlockComponent::EType::PURPLE,
	BlockComponent::EType::RED,
	BlockComponent::EType::YELLOW,
};

Tetromino::Tetromino(const std::string& Signature, const Vec2f& LTPosition, const float& Side, const float& MoveStep)
	: Tetromino(
		Signature,
		LTPosition, 
		Side, 
		GetRandomElement<BlockComponent::EType, 8>(BLOCKCOLORS),
		MoveStep, 
		GetRandomElement<EShape, 7>(SHAPES)
	) {}

Tetromino::Tetromino(
	const std::string& Signature,
	const Vec2f& LTPosition,
	const float& Side,
	const BlockComponent::EType& Type,
	const float& MoveStep,
	const EShape& Shape)
	: GameObject(Signature)
	, LTPosition_(LTPosition)
	, MoveLength_(Side)
	, MoveStep_(MoveStep)
	, Shape_(Shape)
{
	AddComponent<TetrominoRenderComponent>("Renderer");
	AddComponent<TetrominoInputComponent>("Input");
	CreateTetrominoBlocks(LTPosition_, Side, Type, Shape_);
}

Tetromino::~Tetromino()
{
}

void Tetromino::Tick(float DeltaSeconds)
{
	reinterpret_cast<TetrominoInputComponent*>(GetComponent<TetrominoInputComponent>("Input"))->Tick(DeltaSeconds);
	GetComponent<TetrominoRenderComponent>("Renderer")->Tick();
}

void Tetromino::Move(const EDirection& Direction)
{
	Vec2f Center;
	float Bias = (Direction == Tetromino::EDirection::LEFT || Direction == Tetromino::EDirection::DOWN) ? -1.0f : 1.0f;

	switch (Direction)
	{
	case Tetromino::EDirection::LEFT:
	case Tetromino::EDirection::RIGHT:
		LTPosition_.x += (Bias * MoveLength_);

		for (auto& Block : Blocks_)
		{
			Center = Block->GetCenter();
			Center.x += (Bias * MoveLength_);
			Block->SetCenter(Center);
		}
		break;

	case Tetromino::EDirection::UP:
	case Tetromino::EDirection::DOWN:
		LTPosition_.y += (Bias * MoveLength_);

		for (auto& Block : Blocks_)
		{
			Center = Block->GetCenter();
			Center.y += (Bias * MoveLength_);
			Block->SetCenter(Center);
		}
		break;
	}
}

void Tetromino::CreateTetrominoBlocks(const Vec2f& LTPosition, const float& Side, const BlockComponent::EType& Type, const EShape& Shape)
{
	switch (Shape)
	{
	case EShape::I:
		Blocks_ = {
			AddComponent<BlockComponent>("0", Vec2f(LTPosition.x + 0.0f * Side, LTPosition.y - 1.0f * Side), Side, Type),
			AddComponent<BlockComponent>("1", Vec2f(LTPosition.x + 1.0f * Side, LTPosition.y - 1.0f * Side), Side, Type),
			AddComponent<BlockComponent>("2", Vec2f(LTPosition.x + 2.0f * Side, LTPosition.y - 1.0f * Side), Side, Type),
			AddComponent<BlockComponent>("3", Vec2f(LTPosition.x + 3.0f * Side, LTPosition.y - 1.0f * Side), Side, Type),
		};
		break;

	case EShape::O:
		Blocks_ = {
			AddComponent<BlockComponent>("0", Vec2f(LTPosition.x + 1.0f * Side, LTPosition.y - 1.0f * Side), Side, Type),
			AddComponent<BlockComponent>("1", Vec2f(LTPosition.x + 2.0f * Side, LTPosition.y - 1.0f * Side), Side, Type),
			AddComponent<BlockComponent>("2", Vec2f(LTPosition.x + 1.0f * Side, LTPosition.y - 2.0f * Side), Side, Type),
			AddComponent<BlockComponent>("3", Vec2f(LTPosition.x + 2.0f * Side, LTPosition.y - 2.0f * Side), Side, Type),
		};
		break;

	case EShape::T:
		Blocks_ = {
			AddComponent<BlockComponent>("0", Vec2f(LTPosition.x + 0.0f * Side, LTPosition.y - 1.0f * Side), Side, Type),
			AddComponent<BlockComponent>("1", Vec2f(LTPosition.x + 1.0f * Side, LTPosition.y - 1.0f * Side), Side, Type),
			AddComponent<BlockComponent>("2", Vec2f(LTPosition.x + 2.0f * Side, LTPosition.y - 1.0f * Side), Side, Type),
			AddComponent<BlockComponent>("3", Vec2f(LTPosition.x + 1.0f * Side, LTPosition.y - 2.0f * Side), Side, Type),
		};
		break;

	case EShape::J:
		Blocks_ = {
			AddComponent<BlockComponent>("0", Vec2f(LTPosition.x + 0.0f * Side, LTPosition.y - 1.0f * Side), Side, Type),
			AddComponent<BlockComponent>("1", Vec2f(LTPosition.x + 1.0f * Side, LTPosition.y - 1.0f * Side), Side, Type),
			AddComponent<BlockComponent>("2", Vec2f(LTPosition.x + 2.0f * Side, LTPosition.y - 1.0f * Side), Side, Type),
			AddComponent<BlockComponent>("3", Vec2f(LTPosition.x + 2.0f * Side, LTPosition.y - 2.0f * Side), Side, Type),
		};
		break;

	case EShape::L:
		Blocks_ = {
			AddComponent<BlockComponent>("0", Vec2f(LTPosition.x + 0.0f * Side, LTPosition.y - 1.0f * Side), Side, Type),
			AddComponent<BlockComponent>("1", Vec2f(LTPosition.x + 1.0f * Side, LTPosition.y - 1.0f * Side), Side, Type),
			AddComponent<BlockComponent>("2", Vec2f(LTPosition.x + 2.0f * Side, LTPosition.y - 1.0f * Side), Side, Type),
			AddComponent<BlockComponent>("3", Vec2f(LTPosition.x + 0.0f * Side, LTPosition.y - 2.0f * Side), Side, Type),
		};
		break;

	case EShape::S:
		Blocks_ = {
			AddComponent<BlockComponent>("0", Vec2f(LTPosition.x + 1.0f * Side, LTPosition.y - 0.0f * Side), Side, Type),
			AddComponent<BlockComponent>("1", Vec2f(LTPosition.x + 2.0f * Side, LTPosition.y - 0.0f * Side), Side, Type),
			AddComponent<BlockComponent>("2", Vec2f(LTPosition.x + 0.0f * Side, LTPosition.y - 1.0f * Side), Side, Type),
			AddComponent<BlockComponent>("3", Vec2f(LTPosition.x + 1.0f * Side, LTPosition.y - 1.0f * Side), Side, Type),
		};
		break;

	case EShape::Z:
		Blocks_ = {
			AddComponent<BlockComponent>("0", Vec2f(LTPosition.x + 0.0f * Side, LTPosition.y - 0.0f * Side), Side, Type),
			AddComponent<BlockComponent>("1", Vec2f(LTPosition.x + 1.0f * Side, LTPosition.y - 0.0f * Side), Side, Type),
			AddComponent<BlockComponent>("2", Vec2f(LTPosition.x + 1.0f * Side, LTPosition.y - 1.0f * Side), Side, Type),
			AddComponent<BlockComponent>("3", Vec2f(LTPosition.x + 2.0f * Side, LTPosition.y - 1.0f * Side), Side, Type),
		};
		break;

	default:
		ENFORCE_THROW_EXCEPTION("undefined tetromino type...");
	}
}
