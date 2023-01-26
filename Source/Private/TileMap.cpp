#include "TileMap.h"
#include "ContentManager.h"
#include "Camera2D.h"
#include "GraphicsManager.h"
#include "Shader.h"
#include "Texture2D.h"
#include "Utility.hpp"

std::unordered_map<Tile::EColor, std::string> TileMap::TileColorSignature_ = {
	{ Tile::EColor::BLUE,   "Blue"   },
	{ Tile::EColor::CYAN,   "Cyan"   },
	{ Tile::EColor::GRAY,   "Gray"   },
	{ Tile::EColor::GREEN,  "Green"  },
	{ Tile::EColor::ORANGE, "Orange" },
	{ Tile::EColor::PINK,   "Pink"   },
	{ Tile::EColor::PURPLE, "Purple" },
	{ Tile::EColor::RED,    "Red"    },
	{ Tile::EColor::YELLOW, "Yellow" },
};

TileMap::TileMap(
	const std::string& Signature,
	const Vec2f& CenterPosition,
	const int32_t& RowSize,
	const int32_t& ColSize,
	const int32_t& TileSize
) : GameObject(Signature)
, CenterPosition_(CenterPosition)
, RowSize_(RowSize)
, ColSize_(ColSize)
, TileSize_(TileSize)
, Tiles_(RowSize_* ColSize_, Tile())
{
	for (int32_t Row = 0; Row < RowSize_; ++Row)
	{
		for (int32_t Col = 0; Col < ColSize_; ++Col)
		{
			int32_t Offset = GetOffset(Col, Row, ColSize_, RowSize_);

			Tiles_[Offset].SetPositionInMap(Vec2i(Col, Row));
			Tiles_[Offset].SetState(Tile::EState::EMPTY);
			Tiles_[Offset].SetColor(Tile::EColor::NONE);
		}
	}
}

void TileMap::Tick(float DeltaSeconds)
{
	int32_t TileMapWidth = ColSize_ * TileSize_;
	int32_t TileMapHeight = RowSize_ * TileSize_;
	
	Vec2f TileLTPosition(
		CenterPosition_.x - static_cast<float>(TileMapWidth) / 2.0f + static_cast<float>(TileSize_) / 2.0f,
		CenterPosition_.y - static_cast<float>(TileMapHeight) / 2.0f + static_cast<float>(TileSize_) / 2.0f
	);

	for (int32_t Row = 0; Row < RowSize_; ++Row)
	{
		for (int32_t Col = 0; Col < ColSize_; ++Col)
		{
			int32_t Offset = GetOffset(Col, Row, ColSize_, RowSize_);
			Tile& CurrentTile = Tiles_[Offset];

			if (CurrentTile.GetState() == Tile::EState::FILL || CurrentTile.GetState() == Tile::EState::WALL)
			{
				Vec2f Position = TileLTPosition + Vec2f(
					static_cast<float>(Col * TileSize_),
					static_cast<float>(Row * TileSize_)
				);

				Texture2D& Texture = ContentManager::Get().GetTexture2D(TileColorSignature_[CurrentTile.GetColor()]);
				GraphicsManager::Get().DrawTexture2D(Texture, Position, static_cast<float>(TileSize_), static_cast<float>(TileSize_));
			}
		}
	}
}

void TileMap::WriteTileInMap(const Tile& WriteTile)
{
	const Vec2i& Position = WriteTile.GetPositionInMap();
	CHECK((0 <= Position.x && Position.x < ColSize_ && 0 <= Position.y && Position.y < RowSize_), "out of range in tile map");

	Tiles_[GetOffset(Position.x, Position.y, ColSize_, RowSize_)] = WriteTile;
}

Tile& TileMap::ReadTileInMap(const Vec2i& Position)
{
	CHECK((0 <= Position.x && Position.x < ColSize_ && 0 <= Position.y && Position.y < RowSize_), "out of range in tile map");
	return Tiles_[GetOffset(Position.x, Position.y, ColSize_, RowSize_)];
}

void TileMap::ClearMap()
{
	for (int32_t Row = 0; Row < RowSize_; ++Row)
	{
		for (int32_t Col = 0; Col < ColSize_; ++Col)
		{
			int32_t Offset = GetOffset(Col, Row, ColSize_, RowSize_);

			Tiles_[Offset].SetState(Tile::EState::EMPTY);
			Tiles_[Offset].SetColor(Tile::EColor::NONE);
		}
	}
}