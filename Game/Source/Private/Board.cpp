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
    ClearStep_(ClearStep),
	Blocks_(RowBlockCount_ * ColBlockCount_, nullptr)
{
	AddComponent<BoardRenderComponent>("Renderer");

	CreateBoardWall();
}

Board::~Board()
{
}

void Board::Tick(float DeltaSeconds)
{
	GetComponent<BoardRenderComponent>("Renderer")->Tick();
}

void Board::CreateBoardWall()
{
	for (int32_t Row = 0; Row < RowBlockCount_; ++Row)
	{
		for (int32_t Col = 0; Col < ColBlockCount_; ++Col)
		{
			if (Row == 0 || Row == RowBlockCount_ - 1 || Col == 0 || Col == ColBlockCount_ - 1)
			{
				CreateBlock(ColRow(Col, Row), BlockComponent::EType::GRAY);
			}
		}
	}
}

void Board::CreateBlock(const ColRow& BlockColRow, const BlockComponent::EType& Type)
{
	if (!IsExistBlock(BlockColRow))
	{
		int32_t Offset = GetOffset(BlockColRow.first, BlockColRow.second, ColBlockCount_, RowBlockCount_);
		Vec2f BlockPosition = CalculateBlockPositionFromColRow(LTPosition_, BlockColRow, BlockSide_);

		Blocks_[Offset] = AddComponent<BlockComponent>(
			Format("%d,%d", BlockColRow.first, BlockColRow.second),
			BlockPosition, BlockSide_, Type
		);
	}
}

void Board::DestroyBlock(const ColRow& BlockColRow)
{
	if (IsExistBlock(BlockColRow))
	{
		int32_t Offset = GetOffset(BlockColRow.first, BlockColRow.second, ColBlockCount_, RowBlockCount_);
		Blocks_[Offset] = nullptr;

		RemoveComponent<BlockComponent>(Format("%d,%d", BlockColRow.first, BlockColRow.second));
	}
}

bool Board::IsExistBlock(const ColRow& BlockColRow)
{
	int32_t Offset = GetOffset(BlockColRow.first, BlockColRow.second, ColBlockCount_, RowBlockCount_);
	return (Blocks_[Offset] != nullptr);
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
