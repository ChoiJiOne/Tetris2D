#include "Tetromino.h"
#include "AudioPlayComponent.h"
#include "TetrominoRenderComponent.h"
#include "TetrominoInputComponent.h"
#include "TetrominoPhysicComponent.h"
#include "Utils.hpp"

static const std::array<Tetromino::EShape, 7> SHAPES = {
	Tetromino::EShape::I,
	Tetromino::EShape::O,
	Tetromino::EShape::T,
	Tetromino::EShape::J,
	Tetromino::EShape::L,
	Tetromino::EShape::S,
	Tetromino::EShape::Z
};

static const std::array<BlockComponent::EColor, 8> BLOCKCOLORS = {
	BlockComponent::EColor::BLUE,
	BlockComponent::EColor::CYAN,
	BlockComponent::EColor::GREEN,
	BlockComponent::EColor::ORANGE,
	BlockComponent::EColor::PINK,
	BlockComponent::EColor::PURPLE,
	BlockComponent::EColor::RED,
	BlockComponent::EColor::YELLOW,
};

Tetromino::Tetromino(const std::string& Signature, const Vec2f& LTPosition, const float& Side, const float& UpdateStep)
	: Tetromino(
		Signature,
		LTPosition, 
		Side, 
		GetRandomElement<BlockComponent::EColor, 8>(BLOCKCOLORS),
		UpdateStep, 
		GetRandomElement<EShape, 7>(SHAPES)
	) {}

Tetromino::Tetromino(
	const std::string& Signature,
	const Vec2f& LTPosition,
	const float& Side,
	const BlockComponent::EColor& Color,
	const float& UpdateStep,
	const EShape& Shape)
	: GameObject(Signature)
	, UpdateStep_(UpdateStep)
	, Shape_(Shape)
{
	AddComponent<TetrominoRenderComponent>("Renderer");
	AddComponent<TetrominoInputComponent>("Input");
	AddComponent<TetrominoPhysicComponent>("Physic", LTPosition, Side, Side);
	AddComponent<AudioPlayComponent>("Jump", "Jump");
	
	GetComponent<AudioPlayComponent>("Jump")->SetLooping(false);

	CreateTetrominoBlocks(LTPosition, Side, Color, Shape_);
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

	if (State_ != EState::DONE)
	{
		GetComponent<TetrominoRenderComponent>("Renderer")->Tick();
	}
}

bool Tetromino::CanTeleport(const Vec2f& LTPosition)
{
	return GetComponent<TetrominoPhysicComponent>("Physic")->CanTeleport(LTPosition);
}

void Tetromino::Teleport(const Vec2f& LTPosition)
{
	GetComponent<TetrominoPhysicComponent>("Physic")->Teleport(LTPosition);
}

void Tetromino::CreateTetrominoBlocks(const Vec2f& LTPosition, const float& Side, const BlockComponent::EColor& Color, const EShape& Shape)
{
	switch (Shape)
	{
	case EShape::I:
		Blocks_ = {
			AddComponent<BlockComponent>("0", Vec2f(LTPosition.x + 0.0f * Side, LTPosition.y - 1.0f * Side), Side, Color, BlockComponent::EState::FILL),
			AddComponent<BlockComponent>("1", Vec2f(LTPosition.x + 1.0f * Side, LTPosition.y - 1.0f * Side), Side, Color, BlockComponent::EState::FILL),
			AddComponent<BlockComponent>("2", Vec2f(LTPosition.x + 2.0f * Side, LTPosition.y - 1.0f * Side), Side, Color, BlockComponent::EState::FILL),
			AddComponent<BlockComponent>("3", Vec2f(LTPosition.x + 3.0f * Side, LTPosition.y - 1.0f * Side), Side, Color, BlockComponent::EState::FILL),
		};
		break;

	case EShape::O:
		Blocks_ = {
			AddComponent<BlockComponent>("0", Vec2f(LTPosition.x + 1.0f * Side, LTPosition.y - 1.0f * Side), Side, Color, BlockComponent::EState::FILL),
			AddComponent<BlockComponent>("1", Vec2f(LTPosition.x + 2.0f * Side, LTPosition.y - 1.0f * Side), Side, Color, BlockComponent::EState::FILL),
			AddComponent<BlockComponent>("2", Vec2f(LTPosition.x + 1.0f * Side, LTPosition.y - 2.0f * Side), Side, Color, BlockComponent::EState::FILL),
			AddComponent<BlockComponent>("3", Vec2f(LTPosition.x + 2.0f * Side, LTPosition.y - 2.0f * Side), Side, Color, BlockComponent::EState::FILL),
		};
		break;

	case EShape::T:
		Blocks_ = {
			AddComponent<BlockComponent>("0", Vec2f(LTPosition.x + 1.0f * Side, LTPosition.y - 0.0f * Side), Side, Color, BlockComponent::EState::FILL),
			AddComponent<BlockComponent>("1", Vec2f(LTPosition.x + 0.0f * Side, LTPosition.y - 1.0f * Side), Side, Color, BlockComponent::EState::FILL),
			AddComponent<BlockComponent>("2", Vec2f(LTPosition.x + 1.0f * Side, LTPosition.y - 1.0f * Side), Side, Color, BlockComponent::EState::FILL),
			AddComponent<BlockComponent>("3", Vec2f(LTPosition.x + 2.0f * Side, LTPosition.y - 1.0f * Side), Side, Color, BlockComponent::EState::FILL),
		};
		break;

	case EShape::J:
		Blocks_ = {
			AddComponent<BlockComponent>("0", Vec2f(LTPosition.x + 0.0f * Side, LTPosition.y - 1.0f * Side), Side, Color, BlockComponent::EState::FILL),
			AddComponent<BlockComponent>("1", Vec2f(LTPosition.x + 1.0f * Side, LTPosition.y - 1.0f * Side), Side, Color, BlockComponent::EState::FILL),
			AddComponent<BlockComponent>("2", Vec2f(LTPosition.x + 2.0f * Side, LTPosition.y - 1.0f * Side), Side, Color, BlockComponent::EState::FILL),
			AddComponent<BlockComponent>("3", Vec2f(LTPosition.x + 2.0f * Side, LTPosition.y - 2.0f * Side), Side, Color, BlockComponent::EState::FILL),
		};
		break;

	case EShape::L:
		Blocks_ = {
			AddComponent<BlockComponent>("0", Vec2f(LTPosition.x + 0.0f * Side, LTPosition.y - 1.0f * Side), Side, Color, BlockComponent::EState::FILL),
			AddComponent<BlockComponent>("1", Vec2f(LTPosition.x + 1.0f * Side, LTPosition.y - 1.0f * Side), Side, Color, BlockComponent::EState::FILL),
			AddComponent<BlockComponent>("2", Vec2f(LTPosition.x + 2.0f * Side, LTPosition.y - 1.0f * Side), Side, Color, BlockComponent::EState::FILL),
			AddComponent<BlockComponent>("3", Vec2f(LTPosition.x + 0.0f * Side, LTPosition.y - 2.0f * Side), Side, Color, BlockComponent::EState::FILL),
		};
		break;

	case EShape::S:
		Blocks_ = {
			AddComponent<BlockComponent>("0", Vec2f(LTPosition.x + 1.0f * Side, LTPosition.y - 0.0f * Side), Side, Color, BlockComponent::EState::FILL),
			AddComponent<BlockComponent>("1", Vec2f(LTPosition.x + 2.0f * Side, LTPosition.y - 0.0f * Side), Side, Color, BlockComponent::EState::FILL),
			AddComponent<BlockComponent>("2", Vec2f(LTPosition.x + 0.0f * Side, LTPosition.y - 1.0f * Side), Side, Color, BlockComponent::EState::FILL),
			AddComponent<BlockComponent>("3", Vec2f(LTPosition.x + 1.0f * Side, LTPosition.y - 1.0f * Side), Side, Color, BlockComponent::EState::FILL),
		};
		break;

	case EShape::Z:
		Blocks_ = {
			AddComponent<BlockComponent>("0", Vec2f(LTPosition.x + 0.0f * Side, LTPosition.y - 0.0f * Side), Side, Color, BlockComponent::EState::FILL),
			AddComponent<BlockComponent>("1", Vec2f(LTPosition.x + 1.0f * Side, LTPosition.y - 0.0f * Side), Side, Color, BlockComponent::EState::FILL),
			AddComponent<BlockComponent>("2", Vec2f(LTPosition.x + 1.0f * Side, LTPosition.y - 1.0f * Side), Side, Color, BlockComponent::EState::FILL),
			AddComponent<BlockComponent>("3", Vec2f(LTPosition.x + 2.0f * Side, LTPosition.y - 1.0f * Side), Side, Color, BlockComponent::EState::FILL),
		};
		break;

	default:
		ENFORCE_THROW_EXCEPTION("undefined tetromino type...");
	}
}