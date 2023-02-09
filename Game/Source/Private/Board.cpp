#include "Board.h"
#include "BoardRenderComponent.h"
#include "ContentManager.h"
#include "GraphicsManager.h"
#include "Shader.h"
#include "Text.hpp"
#include "Utility.hpp"

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

	CreateBoardWall();
}

Board::~Board()
{
}

void Board::Tick(float DeltaSeconds)
{
	if (State_ == EState::ACTIVE)
	{
		AccrueFrameTime_ += DeltaSeconds;

		if (AccrueFrameTime_ >= ClearStep_)
		{
			AccrueFrameTime_ = 0.0f;

			//int32_t RemoveLine = HaveRemoveLine();

			//if (RemoveLine == -1)
			//{
			//	CleanupEmptyRowLine();
			//	State_ = EState::WAIT;
			//}
			//else
			//{
			//	RemoveRowLine(RemoveLine);
			//	RemoveLine_++;
			//}
		}
	}

	GetComponent<BoardRenderComponent>("Renderer")->Tick();
}

void Board::AddBlocks(const std::array<BlockComponent*, 4>& Blocks)
{
	for (const auto& Block : Blocks)
	{
		//CreateBlock(CalculateColRowFromBlock(LTPosition_, Block, Block->GetWidth()), Block->GetType());
	}
}

void Board::CreateBoardWall()
{
	int32_t CountOfWall = 0;
	Vec2f BlockPosition;

	for (int32_t Row = 0; Row < RowBlockCount_; ++Row)
	{
		for (int32_t Col = 0; Col < ColBlockCount_; ++Col)
		{
			if (Row == 0 || Row == RowBlockCount_ - 1 || Col == 0 || Col == ColBlockCount_ - 1)
			{
				BlockPosition = Vec2f(
					LTPosition_.x + static_cast<float>(Col) * BlockSide_,
					LTPosition_.y - static_cast<float>(Row) * BlockSide_
				);

				WallBlocks_.push_back(
					AddComponent<BlockComponent>(
						Format("WALL%d", CountOfWall++),
						BlockPosition, BlockSide_, BlockComponent::EType::GRAY)
				);
			}
		}
	}
}