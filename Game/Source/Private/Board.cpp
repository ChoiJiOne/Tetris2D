#include "Board.h"
#include "BlockComponent.h"
#include "BoardRenderComponent.h"
#include "ContentManager.h"
#include "GraphicsManager.h"
#include "Shader.h"
#include "Text.hpp"

Board::Board(
	const std::string& Signature, 
	const Vec2f& LTPosition, 
	const int32_t& RowBlockCount, 
	const int32_t& ColBlockCount, 
	const float& Side, 
	const float& ClearStep
) : GameObject(Signature),
    LTPosition_(LTPosition),
    BlockSide_(Side),
    RowBlockCount_(RowBlockCount),
    ColBlockCount_(ColBlockCount),
    ClearStep_(ClearStep)
{
	AddComponent<BoardRenderComponent>("Renderer");
	CreateBoardBlocks(LTPosition_, BlockSide_, RowBlockCount_, ColBlockCount_);
}

Board::~Board()
{
}

void Board::Tick(float DeltaSeconds)
{
	GetComponent<BoardRenderComponent>("Renderer")->Tick();
}

void Board::CreateBoardBlocks(const Vec2f& LTPosition, const float& Side, const int32_t& RowBlockCount, const int32_t& ColBlockCount)
{
	for (int32_t Row = 0; Row < RowBlockCount; ++Row)
	{
		if (Row == 0 || Row == RowBlockCount - 1)
		{
			for (int32_t Col = 0; Col < ColBlockCount; ++Col)
			{
				Blocks_.push_back(
					AddComponent<BlockComponent>(
						std::to_string(Blocks_.size()),
						Vec2f(LTPosition.x + static_cast<float>(Col) * Side, LTPosition.y - static_cast<float>(Row) * Side),
						Side,
						BlockComponent::EType::GRAY
					)
				);
			}
		}
		else
		{
			Blocks_.push_back(
				AddComponent<BlockComponent>(
					std::to_string(Blocks_.size()),
					Vec2f(LTPosition.x, LTPosition.y - static_cast<float>(Row) * Side),
					Side,
					BlockComponent::EType::GRAY
					)
			);

			Blocks_.push_back(
				AddComponent<BlockComponent>(
					std::to_string(Blocks_.size()),
					Vec2f(LTPosition.x + static_cast<float>(ColBlockCount - 1) * Side, LTPosition.y - static_cast<float>(Row) * Side),
					Side,
					BlockComponent::EType::GRAY
					)
			);
		}
	}
}
