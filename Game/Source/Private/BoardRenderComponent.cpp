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
	const std::vector<BlockComponent*>& Blocks = reinterpret_cast<Board*>(GetGameObject())->GetBlocks();
	RenderBlocks(Blocks);
}

void BoardRenderComponent::RenderBlocks(const std::vector<BlockComponent*>& Blocks)
{
	Vec2f Position;
	float Width = 0.0f, Height = 0.0f;

	for (auto& Block : Blocks)
	{
		Position = Block->GetCenter();
		Width = Block->GetWidth();
		Height = Block->GetHeight();

		if (Block->GetState() == BlockComponent::EState::FILL && Block->GetColor() != BlockComponent::EColor::NONE)
		{
			GraphicsManager::Get().DrawTexture2D(
				ContentManager::Get().GetTexture2D(Block->GetColorTextureSignature()),
				Position,
				Width,
				Height
			);
		}
	}
}
