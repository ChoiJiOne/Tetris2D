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
			SortBlocks();

			State_ = EState::WAIT;

			
			
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
		Blocks_.push_back(
			AddComponent<BlockComponent>(
				GetBlockKey(Block), 
				Block->GetCenter(), Block->GetWidth(), Block->GetType()
			)
		);
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
						BlockPosition, BlockSide_, BlockComponent::EType::GRAY
					)
				);
			}
		}
	}
}

std::string Board::GetBlockKey(const BlockComponent* Block)
{
	Vec2f BlockPosition = Block->GetCenter();

	int32_t Col = static_cast<int32_t>((BlockPosition.x - LTPosition_.x) / BlockSide_);
	int32_t Row = static_cast<int32_t>((LTPosition_.y - BlockPosition.y) / BlockSide_);

	return Format("%d:%d", Row, Col);
}

void Board::SortBlocks()
{
	auto BlockCompareFunc = [](BlockComponent* LhsBlock, BlockComponent* RhsBlock) {
		Vec2f LhsBlockPosition = LhsBlock->GetCenter();
		Vec2f RhsBlockPosition = RhsBlock->GetCenter();

		if (LhsBlockPosition.y > RhsBlockPosition.y)
		{
			return true;
		}
		else if (LhsBlockPosition.y == RhsBlockPosition.y)
		{
			if (LhsBlockPosition.x < RhsBlockPosition.x)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	};

	Blocks_.sort(BlockCompareFunc);
}

std::vector<Vec2f> Board::GetRemoveLinePositions()
{
	std::vector<Vec2f> RemoveLinePositions;
	//Vec2f StartPosition = LTPosition_ + Vec2f(BlockSide_, BlockSide_);

	//auto Iter = Blocks_.begin();

	//while (StartPosition.y <= LTPosition_.y + (static_cast<float>(RowBlockCount_ - 2) * BlockSide_))
	//{
	//	StartPosition.y += BlockSide_;
	//}

	//IsExistComponent()



	//return RemoveLinePositions;
}
