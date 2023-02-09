#include "BoardRenderComponent.h"
#include "BlockComponent.h"
#include "ContentManager.h"
#include "GraphicsManager.h"
#include "Shader.h"
#include "Board.h"

BoardRenderComponent::BoardRenderComponent(GameObject* Object)
	: GraphicsComponent(Object)
{
}

BoardRenderComponent::~BoardRenderComponent()
{
}

void BoardRenderComponent::Tick()
{
	const std::list<BlockComponent*>& WallBlocks = reinterpret_cast<Board*>(GetGameObject())->GetWallBlocks();
	const std::list<BlockComponent*>& Blocks = reinterpret_cast<Board*>(GetGameObject())->GetBlocks();

	RenderBlocks(WallBlocks);
	RenderBlocks(Blocks);
}

void BoardRenderComponent::RenderBlocks(const std::list<BlockComponent*>& Blocks)
{
	Vec2f Position;
	float Width = 0.0f, Height = 0.0f;

	for (auto& Block : Blocks)
	{
		Position = Block->GetCenter();
		Width = Block->GetWidth();
		Height = Block->GetHeight();

		GraphicsManager::Get().DrawTexture2D(
			ContentManager::Get().GetTexture2D(Block->GetTypeTextureSignature()),
			Position,
			Width,
			Height
		);
	}
}
