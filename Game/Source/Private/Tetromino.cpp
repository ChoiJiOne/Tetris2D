#include "Tetromino.h"
#include "BlockComponent.h"
#include "ContentManager.h"
#include "GraphicsManager.h"
#include "Shader.h"
#include "TetrominoRenderComponent.h"

Tetromino::Tetromino(const std::string& Signature)
	: GameObject(Signature)
{
	AddComponent<TetrominoRenderComponent>("Renderer");

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
	GetComponent<TetrominoRenderComponent>("Renderer")->Tick();
}
