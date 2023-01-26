#include "Tetromino.h"
#include "ContentManager.h"
#include "Camera2D.h"
#include "GraphicsManager.h"
#include "Shader.h"
#include "Texture2D.h"
#include "TileMap.h"
#include "Utility.hpp"

Tetromino::Tetromino(const std::string& Signature, const Vec2i& TilePosition)
	: GameObject(Signature)
{
}

Tetromino::Tetromino(const std::string& Signature, const Vec2i& TilePosition, const EShape& Shape, const Tile::EColor& Color)
	: GameObject(Signature)
{
}

void Tetromino::Tick(float DeltaSeconds)
{
}

std::vector<Tile> Tetromino::CreateTetrominoTile(const Vec2i& TilePosition, const EShape& Shape, const Tile::EColor& Color)
{
	std::vector<Tile> Tiles(4);

	switch (Shape)
	{
	case EShape::I:
		Tiles[0] = Tile(TilePosition + Vec2i(0, 1), Tile::EState::FILL, Color);
		Tiles[1] = Tile(TilePosition + Vec2i(1, 1), Tile::EState::FILL, Color);
		Tiles[2] = Tile(TilePosition + Vec2i(2, 1), Tile::EState::FILL, Color);
		Tiles[3] = Tile(TilePosition + Vec2i(3, 1), Tile::EState::FILL, Color);
		break;

	case EShape::O:
		Tiles[0] = Tile(TilePosition + Vec2i(1, 1), Tile::EState::FILL, Color);
		Tiles[1] = Tile(TilePosition + Vec2i(2, 1), Tile::EState::FILL, Color);
		Tiles[2] = Tile(TilePosition + Vec2i(1, 2), Tile::EState::FILL, Color);
		Tiles[3] = Tile(TilePosition + Vec2i(2, 2), Tile::EState::FILL, Color);
		break;

	case EShape::T:
		Tiles[0] = Tile(TilePosition + Vec2i(0, 1), Tile::EState::FILL, Color);
		Tiles[1] = Tile(TilePosition + Vec2i(1, 1), Tile::EState::FILL, Color);
		Tiles[2] = Tile(TilePosition + Vec2i(2, 1), Tile::EState::FILL, Color);
		Tiles[3] = Tile(TilePosition + Vec2i(1, 2), Tile::EState::FILL, Color);
		break;

	case EShape::J:
		Tiles[0] = Tile(TilePosition + Vec2i(0, 1), Tile::EState::FILL, Color);
		Tiles[1] = Tile(TilePosition + Vec2i(1, 1), Tile::EState::FILL, Color);
		Tiles[2] = Tile(TilePosition + Vec2i(2, 1), Tile::EState::FILL, Color);
		Tiles[3] = Tile(TilePosition + Vec2i(2, 2), Tile::EState::FILL, Color);
		break;

	case EShape::L:
		Tiles[0] = Tile(TilePosition + Vec2i(0, 1), Tile::EState::FILL, Color);
		Tiles[1] = Tile(TilePosition + Vec2i(1, 1), Tile::EState::FILL, Color);
		Tiles[2] = Tile(TilePosition + Vec2i(2, 1), Tile::EState::FILL, Color);
		Tiles[3] = Tile(TilePosition + Vec2i(0, 2), Tile::EState::FILL, Color);
		break;

	case EShape::S:
		Tiles[0] = Tile(TilePosition + Vec2i(1, 0), Tile::EState::FILL, Color);
		Tiles[1] = Tile(TilePosition + Vec2i(2, 0), Tile::EState::FILL, Color);
		Tiles[2] = Tile(TilePosition + Vec2i(0, 1), Tile::EState::FILL, Color);
		Tiles[3] = Tile(TilePosition + Vec2i(1, 1), Tile::EState::FILL, Color);
		break;

	case EShape::Z:
		Tiles[0] = Tile(TilePosition + Vec2i(0, 0), Tile::EState::FILL, Color);
		Tiles[1] = Tile(TilePosition + Vec2i(1, 0), Tile::EState::FILL, Color);
		Tiles[2] = Tile(TilePosition + Vec2i(1, 1), Tile::EState::FILL, Color);
		Tiles[3] = Tile(TilePosition + Vec2i(2, 1), Tile::EState::FILL, Color);
		break;

	default:
		ENFORCE_THROW_EXCEPTION("undefined tetromino type...");
	}

	return Tiles;
}
