#include "Board.h"
#include "ContentManager.h"
#include "Camera2D.h"
#include "GraphicsManager.h"
#include "Shader.h"
#include "Texture2D.h"
#include "TileMap.h"
#include "Utility.hpp"
#include "WorldManager.h"

float Board::MaxAccrueTickTime_ = 1.0f;

Board::Board(const std::string& Signature, const Vec2i& TilePosition, const int32_t& Width, const int32_t& Height)
	: GameObject(Signature)
	, TilePosition_(TilePosition)
	, Width_(Width)
	, Height_(Height)
{
	Tiles_ = CreateBoardTile(TilePosition_, Width_, Height_);
	DumpTileMapFromBoard();
}

void Board::Tick(float DeltaSeconds)
{
	if(State_ == EState::WAIT)
	{
		DumpBoardFromTileMap();
		AccrueTickTime_ += DeltaSeconds;

		if (AccrueTickTime_ > MaxAccrueTickTime_)
		{
			bool bHaveRemoveRowLine = false;
			int32_t RemoveYPosition = 0;

			for (int32_t BoardY = Height_ - 2; BoardY >= 1; --BoardY)
			{
				if (CanRemoveRowLine(BoardY))
				{
					bHaveRemoveRowLine = true;
					RemoveYPosition = BoardY;
					break;
				}
			}

			if (bHaveRemoveRowLine)
			{
				ClearRowLine(RemoveYPosition);
				RemoveLine_++;
			}
			else
			{
				ArrangeEmptyRowLine();
				State_ = EState::ACTIVE;
			}

			AccrueTickTime_ = 0.0f;
		}

		DumpTileMapFromBoard();
	}
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

void Board::DumpBoardFromTileMap()
{
	TileMap* Object = WorldManager::Get().GetGameObject<TileMap>("TileMap");

	Vec2i BoardPosition;
	for (int32_t BoardX = 0; BoardX < Width_; ++BoardX)
	{
		for (int32_t BoardY = 0; BoardY < Height_; ++BoardY)
		{
			BoardPosition = Vec2i(BoardX, BoardY);
			Vec2i Position = TilePosition_ + BoardPosition;

			Tiles_[GetOffset(BoardPosition.x, BoardPosition.y, Width_, Height_)] = Object->GetTileInMap(Position);
		}
	}
}

void Board::DumpTileMapFromBoard()
{
	WorldManager::Get().GetGameObject<TileMap>("TileMap")->AddTilesInMap(Tiles_);
}

bool Board::IsAllSameRowLine(const int32_t& BoardYPosition, const Tile::EState& TileState)
{
	Vec2i BoardPosition;

	for (int32_t BoardX = 1; BoardX < Width_ - 1; ++BoardX)
	{
		BoardPosition = Vec2i(BoardX, BoardYPosition);

		const Tile& BoardTile = Tiles_[GetOffset(BoardPosition.x, BoardPosition.y, Width_, Height_)];

		if (BoardTile.GetState() != TileState)
		{
			return false;
		}
	}

	return true;
}

bool Board::CanRemoveRowLine(const int32_t& BoardYPosition)
{
	return IsAllSameRowLine(BoardYPosition, Tile::EState::FILL);
}

bool Board::IsEmptyRowLine(const int32_t& BoardYPosition)
{
	return IsAllSameRowLine(BoardYPosition, Tile::EState::EMPTY);
}

void Board::ClearRowLine(const int32_t& BoardYPosition)
{
	Vec2i BoardPosition;

	for (int32_t BoardX = 1; BoardX < Width_ - 1; ++BoardX)
	{
		BoardPosition = Vec2i(BoardX, BoardYPosition);

		Tile& BoardTile = Tiles_[GetOffset(BoardPosition.x, BoardPosition.y, Width_, Height_)];
		BoardTile.SetState(Tile::EState::EMPTY);
		BoardTile.SetColor(Tile::EColor::NONE);
	}
}

void Board::ArrangeEmptyRowLine()
{
	std::vector<Tile> NewTiles = CreateBoardTile(TilePosition_, Width_, Height_);

	for (int32_t BoardY = Height_ - 2, CurrentRowLine = Height_ - 2; BoardY >= 1; --BoardY)
	{
		if (!IsEmptyRowLine(BoardY))
		{
			for (int32_t BoardX = 1; BoardX < Width_ - 1; ++BoardX)
			{
				Tile& OriginTile = Tiles_[GetOffset(BoardX, BoardY, Width_, Height_)];
				Tile& NewTile = NewTiles[GetOffset(BoardX, CurrentRowLine, Width_, Height_)];

				NewTile.SetState(OriginTile.GetState());
				NewTile.SetColor(OriginTile.GetColor());
			}

			CurrentRowLine--;
		}
	}

	Tiles_ = NewTiles;
}
