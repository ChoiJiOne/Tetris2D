#include "Tetromino.h"
#include "TetrominoRenderComponent.h"
#include "TetrominoInputComponent.h"
#include "TetrominoPhysicComponent.h"
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
	, MoveStep_(MoveStep)
	, Shape_(Shape)
{
	AddComponent<TetrominoRenderComponent>("Renderer");
	AddComponent<TetrominoInputComponent>("Input");
	AddComponent<TetrominoPhysicComponent>("Physic", LTPosition, Side, Side);

	CreateTetrominoBlocks(LTPosition, Side, Type, Shape_);
}

Tetromino::~Tetromino()
{
}

void Tetromino::Tick(float DeltaSeconds)
{
	if (State_ == EState::ACTIVE)
	{
		GetComponent<TetrominoInputComponent>("Input")->Tick(DeltaSeconds);
		GetComponent<TetrominoPhysicComponent>("Physic")->Tick();
	}

	GetComponent<TetrominoRenderComponent>("Renderer")->Tick();
}

bool Tetromino::Teleport(const Vec2f& LTPosition)
{
	return GetComponent<TetrominoPhysicComponent>("Physic")->Teleport(LTPosition);
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