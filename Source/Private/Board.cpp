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