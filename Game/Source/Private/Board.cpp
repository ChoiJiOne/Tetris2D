#include "Board.h"
#include "BoardRenderComponent.h"
#include "BoardPhysicComponent.h"
#include "ContentManager.h"
#include "GraphicsManager.h"
#include "AudioPlayComponent.h"
#include "Shader.h"
#include "Text.hpp"
#include "Utils.hpp"

Board::Board(
	const std::string& Signature, 
	const Vec2f& LTPosition, 
	const int32_t& RowBlockCount, 
	const int32_t& ColBlockCount, 
	const float& Side, 
	const float& UpdateStep,
	const int32_t& LevelUpCondition
) : GameObject(Signature),
	Blocks_(RowBlockCount * ColBlockCount)
{
	AddComponent<BoardRenderComponent>("Renderer");
	AddComponent<BoardPhysicComponent>("Physic", LTPosition, RowBlockCount, ColBlockCount, Side, UpdateStep, LevelUpCondition);
	AddComponent<AudioPlayComponent>("LevelUp", "LevelUp");
	AddComponent<AudioPlayComponent>("RemoveLine", "RemoveLine");

	GetComponent<AudioPlayComponent>("LevelUp")->SetLooping(false);
	GetComponent<AudioPlayComponent>("RemoveLine")->SetLooping(false);
}

Board::~Board()
{
}

void Board::Tick(float DeltaSeconds)
{
	if (State_ == EState::ACTIVE)
	{
		GetComponent<BoardPhysicComponent>("Physic")->Tick(DeltaSeconds);
	}

	GetComponent<BoardRenderComponent>("Renderer")->Tick();
}

void Board::AddBlocks(const std::array<BlockComponent*, 4>& NewBlocks)
{
	GetComponent<BoardPhysicComponent>("Physic")->AddBlocksInBoard(Blocks_, NewBlocks);
}

int32_t Board::GetRemoveLine()
{
	return GetComponent<BoardPhysicComponent>("Physic")->GetRemoveLine();
}

int32_t Board::GetLevelRemoveLine()
{
	return GetComponent<BoardPhysicComponent>("Physic")->GetLevelRemoveLine();
}

void Board::ResetLevelRemoveLine()
{
	GetComponent<BoardPhysicComponent>("Physic")->ResetLevelRemoveLine();
}

void Board::SetUpdateStep(const float& UpdateStep)
{
	GetComponent<BoardPhysicComponent>("Physic")->SetUpdateStep(UpdateStep);
}
