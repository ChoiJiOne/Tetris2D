#include "Tetromino.h"
#include "BlockComponent.h"
#include "ContentManager.h"
#include "GraphicsManager.h"
#include "Shader.h"

Tetromino::Tetromino(const std::string& Signature)
	: GameObject(Signature)
{
	Blocks_ = {
		AddComponent<BlockComponent>("0", Vec2f(  0.0f, 0.0f), 100.0f, BlockComponent::EType::BLUE),
		AddComponent<BlockComponent>("1", Vec2f(100.0f, 0.0f), 100.0f, BlockComponent::EType::GREEN),
		AddComponent<BlockComponent>("2", Vec2f(200.0f, 0.0f), 100.0f, BlockComponent::EType::PINK),
		AddComponent<BlockComponent>("3", Vec2f(300.0f, 0.0f), 100.0f, BlockComponent::EType::RED),
	};
}

Tetromino::~Tetromino()
{
}

void Tetromino::Tick(float DeltaSeconds)
{
	Vec2f Position;
	float Width = 0.0f, Height = 0.0f;

	for (auto& Block : Blocks_)
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
