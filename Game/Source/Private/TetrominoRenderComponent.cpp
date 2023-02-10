#include "TetrominoRenderComponent.h"
#include "BlockComponent.h"
#include "ContentManager.h"
#include "GraphicsManager.h"
#include "Shader.h"
#include "Tetromino.h"

TetrominoRenderComponent::TetrominoRenderComponent(GameObject* Object)
	: GraphicsComponent(Object)
{
}

TetrominoRenderComponent::~TetrominoRenderComponent()
{
}

void TetrominoRenderComponent::Tick()
{
	const std::array<BlockComponent*, 4>& Blocks = reinterpret_cast<Tetromino*>(GetGameObject())->GetBlocks();

	Vec2f BlockPosition;
	float BlockWidth = 0.0f, BlockHeight = 0.0f;

	for (const auto& Block : Blocks)
	{
		BlockPosition = Block->GetCenter();
		BlockWidth    = Block->GetWidth();
		BlockHeight   = Block->GetHeight();

		if (Block->GetState() == BlockComponent::EState::FILL)
		{
			GraphicsManager::Get().DrawTexture2D(
				ContentManager::Get().GetTexture2D(Block->GetColorTextureSignature()),
				BlockPosition,
				BlockWidth,
				BlockHeight
			);
		}
	}
}
