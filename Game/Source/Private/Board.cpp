#include "Board.h"
#include "BoardRenderComponent.h"
#include "ContentManager.h"
#include "GraphicsManager.h"
#include "GameAudioComponent.h"
#include "Shader.h"
#include "Text.hpp"
#include "Utility.hpp"

Board::Board(
	const std::string& Signature, 
	const Vec2f& LTPosition, 
	const int32_t& RowBlockCount, 
	const int32_t& ColBlockCount, 
	const float& Side, 
	const float& UpdateStep
) : GameObject(Signature),
    LTPosition_(LTPosition),
    BlockSide_(Side),
    RowBlockCount_(RowBlockCount),
    ColBlockCount_(ColBlockCount),
    UpdateStep_(UpdateStep),
	Blocks_(RowBlockCount_ * ColBlockCount)
{
	AddComponent<BoardRenderComponent>("Renderer");
	AddComponent<GameAudioComponent>("LevelUp", "LevelUp", false);
	AddComponent<GameAudioComponent>("RemoveLine", "RemoveLine", false);

	CreateBoardBlocks();
}

Board::~Board()
{
}

void Board::Tick(float DeltaSeconds)
{
	if (State_ == EState::ACTIVE)
	{
		AccrueFrameTime_ += DeltaSeconds;

		if (AccrueFrameTime_ >= UpdateStep_)
		{
			AccrueFrameTime_ = 0.0f;

			int32_t RemoveLine = FindRemoveRowLine();

			if (RemoveLine == -1)
			{
				CleanupEmptyRowLine();
				State_ = EState::WAIT;
			}
			else
			{
				RemoveRowLine(RemoveLine);
				CountOfRemoveLine_++;
				LevelRemoveLine_++;

				GetComponent<GameAudioComponent>("RemoveLine")->Play();
			}
		}

		if (LevelRemoveLine_ >= 10)
		{
			LevelRemoveLine_ = 0;
			GetComponent<GameAudioComponent>("LevelUp")->Play();
		}
	}

	GetComponent<BoardRenderComponent>("Renderer")->Tick();
}

void Board::AddBlocks(const std::array<BlockComponent*, 4>& Blocks)
{
	for (const auto& Block : Blocks)
	{
		ColRow BoardColRow = CalculateColRowFromBlock(LTPosition_, Block, BlockSide_);

		int32_t Offset = GetOffset(BoardColRow.first, BoardColRow.second, ColBlockCount_, RowBlockCount_);

		Blocks_[Offset]->SetState(Block->GetState());
		Blocks_[Offset]->SetColor(Block->GetColor());
	}
}

void Board::CreateBoardBlocks()
{
	int32_t CountOfWall = 0;
	Vec2f BlockPosition;

	BlockComponent::EState State;
	BlockComponent::EColor Color;

	for (int32_t Row = 0; Row < RowBlockCount_; ++Row)
	{
		for (int32_t Col = 0; Col < ColBlockCount_; ++Col)
		{
			if (Row == 0 || Row == RowBlockCount_ - 1 || Col == 0 || Col == ColBlockCount_ - 1)
			{
				State = BlockComponent::EState::FILL;
				Color = BlockComponent::EColor::GRAY;
			}
			else
			{
				State = BlockComponent::EState::EMPTY;
				Color = BlockComponent::EColor::NONE;
			}

			int32_t Offset = GetOffset(Col, Row, ColBlockCount_, RowBlockCount_);

			Blocks_[Offset] = AddComponent<BlockComponent>(
				Format("BOARD:%d", CountOfWall++), 
				CalculateBlockPositionFromColRow(LTPosition_, ColRow(Col, Row), BlockSide_),
				BlockSide_,
				Color, 
				State
			);
		}
	}
}

bool Board::IsFullRowLine(const int32_t& RowLine)
{
	for (int32_t Col = 1; Col < ColBlockCount_ - 1; ++Col)
	{
		int32_t Offset = GetOffset(Col, RowLine, ColBlockCount_, RowBlockCount_);

		if (Blocks_[Offset]->GetState() != BlockComponent::EState::FILL)
		{
			return false;
		}
	}

	return true;
}

bool Board::IsEmptyRowLine(const int32_t& RowLine)
{
	for (int32_t Col = 1; Col < ColBlockCount_ - 1; ++Col)
	{
		int32_t Offset = GetOffset(Col, RowLine, ColBlockCount_, RowBlockCount_);

		if (Blocks_[Offset]->GetState() != BlockComponent::EState::EMPTY)
		{
			return false;
		}
	}

	return true;
}

void Board::RemoveRowLine(const int32_t& RowLine)
{
	for (int32_t Col = 1; Col < ColBlockCount_ - 1; ++Col)
	{
		int32_t Offset = GetOffset(Col, RowLine, ColBlockCount_, RowBlockCount_);

		Blocks_[Offset]->SetState(BlockComponent::EState::EMPTY);
		Blocks_[Offset]->SetColor(BlockComponent::EColor::NONE);
	}
}

int32_t Board::FindRemoveRowLine()
{
	for (int32_t Row = RowBlockCount_ - 2; Row >= 1; --Row)
	{
		if (IsFullRowLine(Row))
		{
			return Row;
		}
	}

	return -1;
}

void Board::CleanupEmptyRowLine()
{
	std::vector<int32_t> ExistRowLines;

	for (int32_t Row = RowBlockCount_ - 2; Row >= 1; --Row)
	{
		if (!IsEmptyRowLine(Row))
		{
			ExistRowLines.push_back(Row);
		}
	}

	if (ExistRowLines.empty()) return;
	
	std::vector<BlockState> BloardBlocks = GetCopyBoardBlocks();
	CleanupAllRowLine();

	int32_t CurrentRowLine = RowBlockCount_ - 2;
	for (auto ExistRowLine : ExistRowLines)
	{
		for (int32_t Col = 1; Col < ColBlockCount_ - 1; ++Col)
		{
			int32_t FromOffset = GetOffset(Col, ExistRowLine, ColBlockCount_, RowBlockCount_);
			int32_t ToOffset = GetOffset(Col, CurrentRowLine, ColBlockCount_, RowBlockCount_);

			Blocks_[ToOffset]->SetState(BloardBlocks[FromOffset].first);
			Blocks_[ToOffset]->SetColor(BloardBlocks[FromOffset].second);
		}

		CurrentRowLine--;
	}
}

void Board::CleanupAllRowLine()
{
	for (int32_t Row = 1; Row < RowBlockCount_ - 1; ++Row)
	{
		RemoveRowLine(Row);
	}
}

std::vector<Board::BlockState> Board::GetCopyBoardBlocks()
{
	std::vector<BlockState> BloardBlocks(RowBlockCount_ * ColBlockCount_);

	for (int32_t Row = 0; Row < RowBlockCount_; ++Row)
	{
		for (int32_t Col = 0; Col < ColBlockCount_; ++Col)
		{
			int32_t Offset = GetOffset(Col, Row, ColBlockCount_, RowBlockCount_);
			BloardBlocks[Offset] = BlockState(Blocks_[Offset]->GetState(), Blocks_[Offset]->GetColor());
		}
	}

	return BloardBlocks;
}

Vec2f Board::CalculateBlockPositionFromColRow(const Vec2f& LTPosition, const ColRow& BlockColRow, const float& Side) const
{
	return Vec2f(
		LTPosition.x + static_cast<float>(BlockColRow.first) * Side,
		LTPosition.y - static_cast<float>(BlockColRow.second) * Side
	);
}

Board::ColRow Board::CalculateColRowFromBlock(const Vec2f& LTPosition, const BlockComponent* Block, const float& Side) const
{
	Vec2f BlockPosition = Block->GetCenter();

	return ColRow(
		static_cast<int32_t>((BlockPosition.x - LTPosition.x) / Side),
		static_cast<int32_t>((LTPosition.y - BlockPosition.y) / Side)
	);
}