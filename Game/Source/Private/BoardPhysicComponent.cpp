#include "BoardPhysicComponent.h"
#include "Board.h"
#include "GameAudioComponent.h"
#include "Tetromino.h"

BoardPhysicComponent::BoardPhysicComponent(
	GameObject* Object,
	const Vec2f& LTPosition,
	const int32_t& RowBlockCount,
	const int32_t& ColBlockCount,
	const float& Side,
	const float& UpdateStep,
	const int32_t& LevelUpCondition
) : PhysicComponent(Object),
    LTPosition_(LTPosition),
    BlockSide_(Side),
    RowBlockCount_(RowBlockCount),
    ColBlockCount_(ColBlockCount),
	UpdateStep_(UpdateStep),
	LevelUpCondition_(LevelUpCondition)
{
	Board* BoardObject = reinterpret_cast<Board*>(GetGameObject());
	CreateBoardBlocks(BoardObject->GetBlocks());
}

BoardPhysicComponent::~BoardPhysicComponent()
{
}

void BoardPhysicComponent::Tick(float DeltaSeconds)
{
	Board* BoardObject = reinterpret_cast<Board*>(GetGameObject());
	std::vector<BlockComponent*>& BoardBlocks = BoardObject->GetBlocks();

	AccrueFrameTime_ += DeltaSeconds;

	if (AccrueFrameTime_ >= UpdateStep_)
	{
		AccrueFrameTime_ = 0.0f;

		int32_t RemoveLine = FindRemoveRowLine(BoardBlocks);

		if (RemoveLine == -1)
		{
			CleanupEmptyRowLine(BoardBlocks);
			BoardObject->SetState(Board::EState::WAIT);
		}
		else
		{
			RemoveRowLine(BoardBlocks, RemoveLine);
			CountOfRemoveLine_++;
			LevelRemoveLine_++;

			GetGameObject()->GetComponent<GameAudioComponent>("RemoveLine")->Play();
		}
	}

	if (LevelRemoveLine_ >= LevelUpCondition_)
	{
		LevelRemoveLine_ = 0;
		GetGameObject()->GetComponent<GameAudioComponent>("LevelUp")->Play();
	}
}

void BoardPhysicComponent::AddBlocksInBoard(std::vector<BlockComponent*>& BoardBlocks, const std::array<BlockComponent*, 4>& AddBlocks)
{
	for (const auto& AddBlock : AddBlocks)
	{
		ColRow BoardColRow = CalculateColRowFromBlock(LTPosition_, AddBlock, BlockSide_);

		int32_t Offset = GetOffset(BoardColRow.first, BoardColRow.second, ColBlockCount_, RowBlockCount_);

		BoardBlocks[Offset]->SetState(AddBlock->GetState());
		BoardBlocks[Offset]->SetColor(AddBlock->GetColor());
	}
}

void BoardPhysicComponent::CreateBoardBlocks(std::vector<BlockComponent*>& Blocks)
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

			Blocks[Offset] = GetGameObject()->AddComponent<BlockComponent>(
				Format("BOARD:%d", CountOfWall++),
				CalculateBlockPositionFromColRow(LTPosition_, ColRow(Col, Row), BlockSide_),
				BlockSide_,
				Color,
				State
			);
		}
	}
}

bool BoardPhysicComponent::IsFullRowLine(const std::vector<BlockComponent*>& Blocks, const int32_t& RowLine)
{
	for (int32_t Col = 1; Col < ColBlockCount_ - 1; ++Col)
	{
		int32_t Offset = GetOffset(Col, RowLine, ColBlockCount_, RowBlockCount_);

		if (Blocks[Offset]->GetState() != BlockComponent::EState::FILL)
		{
			return false;
		}
	}

	return true;
}

bool BoardPhysicComponent::IsEmptyRowLine(const std::vector<BlockComponent*>& Blocks, const int32_t& RowLine)
{
	for (int32_t Col = 1; Col < ColBlockCount_ - 1; ++Col)
	{
		int32_t Offset = GetOffset(Col, RowLine, ColBlockCount_, RowBlockCount_);

		if (Blocks[Offset]->GetState() != BlockComponent::EState::EMPTY)
		{
			return false;
		}
	}

	return true;
}

void BoardPhysicComponent::RemoveRowLine(std::vector<BlockComponent*>& Blocks, const int32_t& RowLine)
{
	for (int32_t Col = 1; Col < ColBlockCount_ - 1; ++Col)
	{
		int32_t Offset = GetOffset(Col, RowLine, ColBlockCount_, RowBlockCount_);

		Blocks[Offset]->SetState(BlockComponent::EState::EMPTY);
		Blocks[Offset]->SetColor(BlockComponent::EColor::NONE);
	}
}

int32_t BoardPhysicComponent::FindRemoveRowLine(const std::vector<BlockComponent*>& Blocks)
{
	for (int32_t Row = RowBlockCount_ - 2; Row >= 1; --Row)
	{
		if (IsFullRowLine(Blocks, Row))
		{
			return Row;
		}
	}

	return -1;
}

void BoardPhysicComponent::CleanupEmptyRowLine(std::vector<BlockComponent*>& Blocks)
{	
	std::vector<int32_t> ExistRowLines;

	for (int32_t Row = RowBlockCount_ - 2; Row >= 1; --Row)
	{
		if (!IsEmptyRowLine(Blocks, Row))
		{
			ExistRowLines.push_back(Row);
		}
	}

	if (ExistRowLines.empty()) return;
	
	std::vector<BlockState> BloardBlocks = GetCopyBoardBlocks(Blocks);
	CleanupAllRowLine(Blocks);

	int32_t CurrentRowLine = RowBlockCount_ - 2;
	for (auto ExistRowLine : ExistRowLines)
	{
		for (int32_t Col = 1; Col < ColBlockCount_ - 1; ++Col)
		{
			int32_t FromOffset = GetOffset(Col, ExistRowLine, ColBlockCount_, RowBlockCount_);
			int32_t ToOffset = GetOffset(Col, CurrentRowLine, ColBlockCount_, RowBlockCount_);

			Blocks[ToOffset]->SetState(BloardBlocks[FromOffset].first);
			Blocks[ToOffset]->SetColor(BloardBlocks[FromOffset].second);
		}

		CurrentRowLine--;
	}
}

void BoardPhysicComponent::CleanupAllRowLine(std::vector<BlockComponent*>& Blocks)
{
	for (int32_t Row = 1; Row < RowBlockCount_ - 1; ++Row)
	{
		RemoveRowLine(Blocks, Row);
	}
}

std::vector<BoardPhysicComponent::BlockState> BoardPhysicComponent::GetCopyBoardBlocks(const std::vector<BlockComponent*>& Blocks)
{
	std::vector<BlockState> BloardBlocks(RowBlockCount_ * ColBlockCount_);

	for (int32_t Row = 0; Row < RowBlockCount_; ++Row)
	{
		for (int32_t Col = 0; Col < ColBlockCount_; ++Col)
		{
			int32_t Offset = GetOffset(Col, Row, ColBlockCount_, RowBlockCount_);
			BloardBlocks[Offset] = BlockState(Blocks[Offset]->GetState(), Blocks[Offset]->GetColor());
		}
	}

	return BloardBlocks;
}

Vec2f BoardPhysicComponent::CalculateBlockPositionFromColRow(const Vec2f& LTPosition, const ColRow& BlockColRow, const float& Side) const
{
	return Vec2f(
		LTPosition.x + static_cast<float>(BlockColRow.first) * Side,
		LTPosition.y - static_cast<float>(BlockColRow.second) * Side
	);
}

BoardPhysicComponent::ColRow BoardPhysicComponent::CalculateColRowFromBlock(const Vec2f& LTPosition, const BlockComponent* Block, const float& Side) const
{
	Vec2f BlockPosition = Block->GetCenter();

	return ColRow(
		static_cast<int32_t>((BlockPosition.x - LTPosition.x) / Side),
		static_cast<int32_t>((LTPosition.y - BlockPosition.y) / Side)
	);
}
