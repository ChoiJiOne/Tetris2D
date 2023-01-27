#include "Board.h"
#include "ContentManager.h"
#include "Camera2D.h"
#include "GraphicsManager.h"
#include "Shader.h"
#include "Texture2D.h"
#include "TileMap.h"
#include "Utility.hpp"
#include "WorldManager.h"

Board::Board(const std::string& Signature, const Vec2i& TilePosition, const int32_t& Width, const int32_t& Height)
	: GameObject(Signature)
	, TilePosition_(TilePosition)
	, Width_(Width)
	, Height_(Height)
{
	Tiles_ = CreateBoardTile(TilePosition_, Width_, Height_);

	TileMap* Object = WorldManager::Get().GetGameObject<TileMap>("TileMap");
	Object->AddTilesInMap(Tiles_);
}

void Board::Tick(float DeltaSeconds)
{
	if (bIsNeedUpdate_)
	{
		TileMap* Object = WorldManager::Get().GetGameObject<TileMap>("TileMap");
		Object->AddTilesInMap(Tiles_);
		bIsNeedUpdate_ = false;
	}
}

bool Board::IsOutOfRangeTiles(const std::vector<Tile>& Tiles)
{
	for (const auto& TargetTile : Tiles)
	{
		if (IsOutOfRangePosition(TargetTile.GetPositionInMap()))
		{
			return true;
		}
	}

	return false;
}

void Board::AddTiles(const std::vector<Tile>& Tiles)
{
	if (IsCollisionTiles(Tiles)) return;

	bIsNeedUpdate_ = true;
	Vec2i BoardPosition;

	for (const auto& AddTile : Tiles)
	{
		BoardPosition = AddTile.GetPositionInMap() - TilePosition_;
		Tile& BoardTile = Tiles_[GetOffset(BoardPosition.x, BoardPosition.y, Width_, Height_)];

		BoardTile = AddTile;
	}
}

void Board::RemoveTiles(const std::vector<Tile>& Tiles)
{
	if (IsCollisionTiles(Tiles)) return;

	bIsNeedUpdate_ = true;
	Vec2i BoardPosition;

	for (const auto& RemoveTile : Tiles)
	{
		BoardPosition = RemoveTile.GetPositionInMap() - TilePosition_;
		Tile& BoardTile = Tiles_[GetOffset(BoardPosition.x, BoardPosition.y, Width_, Height_)];

		BoardTile.SetColor(Tile::EColor::NONE);
		BoardTile.SetState(Tile::EState::EMPTY);
	}
}

bool Board::IsCollisionTiles(const std::vector<Tile>& Tiles)
{
	if (IsOutOfRangeTiles(Tiles)) return true;

	Vec2i BoardPosition;

	for (const auto& TargetTile : Tiles)
	{
		BoardPosition = TargetTile.GetPositionInMap() - TilePosition_;
		Tile& BoardTile = Tiles_[GetOffset(BoardPosition.x, BoardPosition.y, Width_, Height_)];

		if ((BoardTile.GetState() == Tile::EState::WALL || BoardTile.GetState() == Tile::EState::FILL) &&
			(TargetTile.GetState() == Tile::EState::WALL || TargetTile.GetState() == Tile::EState::FILL))
		{
			return true;
		}
	}

	return false;
}

std::vector<Tile> Board::CreateBoardTile(const Vec2i& TilePosition, const int32_t& Width, const int32_t& Height)
{
	std::vector<Tile> Tiles(Width * Height);

	Vec2i BoardPosition;

	for (int32_t BoardY = 0; BoardY < Height; ++BoardY)
	{
		for (int32_t BoardX = 0; BoardX < Width; ++BoardX)
		{
			BoardPosition = Vec2i(BoardX, BoardY);
			Vec2i Position = TilePosition + BoardPosition;
			Tile::EState State = Tile::EState::NONE;
			Tile::EColor Color = Tile::EColor::NONE;

			if (BoardX == 0 || BoardX == Width_ - 1 || BoardY == 0 || BoardY == Height_ - 1)
			{
				State = Tile::EState::WALL;
				Color = Tile::EColor::GRAY;

			}
			else
			{
				State = Tile::EState::EMPTY;
				Color = Tile::EColor::NONE;
			}

			Tiles[GetOffset(BoardPosition.x, BoardPosition.y, Width, Height)].SetPositionInMap(Position);
			Tiles[GetOffset(BoardPosition.x, BoardPosition.y, Width, Height)].SetState(State);
			Tiles[GetOffset(BoardPosition.x, BoardPosition.y, Width, Height)].SetColor(Color);
		}
	}

	return Tiles;
}

bool Board::IsOutOfRangePosition(const Vec2i& Position)
{
	Vec2i RelativePosition = Position - TilePosition_;
	return !(0 <= RelativePosition.x && RelativePosition.x < Width_ && 0 <= RelativePosition.y && RelativePosition.y < Height_);
}
