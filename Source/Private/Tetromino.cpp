#include "Tetromino.h"
#include "Board.h"
#include "ContentManager.h"
#include "Camera2D.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "Shader.h"
#include "Texture2D.h"
#include "TileMap.h"
#include "Utility.hpp"
#include "WorldManager.h"

float Tetromino::MaxAccrueTickTime_ = 1.0f;

static const std::array<Tetromino::EShape, 7> SHAPES = {
	Tetromino::EShape::I,
	Tetromino::EShape::O,
	Tetromino::EShape::T,
	Tetromino::EShape::J,
	Tetromino::EShape::L,
	Tetromino::EShape::S,
	Tetromino::EShape::Z
};

static const std::array<Tile::EColor, 8> COLORS = {
	Tile::EColor::BLUE,
	Tile::EColor::CYAN,
	Tile::EColor::GREEN,
	Tile::EColor::ORANGE,
	Tile::EColor::PINK,
	Tile::EColor::PURPLE,
	Tile::EColor::RED,
	Tile::EColor::YELLOW,
};

static const std::unordered_map<EKeyCode, Tetromino::EDirection> KEY_DIRECTIONS = {
	{ EKeyCode::CODE_LEFT,  Tetromino::EDirection::LEFT },
	{ EKeyCode::CODE_RIGHT, Tetromino::EDirection::RIGHT },
	{ EKeyCode::CODE_UP,    Tetromino::EDirection::CW },
	{ EKeyCode::CODE_DOWN,  Tetromino::EDirection::DOWN },
	{ EKeyCode::CODE_SPACE, Tetromino::EDirection::JUMP },
};

Tetromino::Tetromino(const std::string& Signature, const Vec2i& TilePosition)
	: Tetromino(Signature, TilePosition, GetRandomElement<EShape, 7>(SHAPES), GetRandomElement<Tile::EColor, 8>(COLORS)) {}

Tetromino::Tetromino(const std::string& Signature, const Vec2i& TilePosition, const EShape& Shape, const Tile::EColor& Color)
	: GameObject(Signature)
	, TilePosition_(TilePosition)
	, Shape_(Shape)
{
	Tiles_ = CreateTetrominoTile(TilePosition_, Shape_, Color);
}

void Tetromino::Tick(float DeltaSeconds)
{
	if (State_ == EState::ACTIVE)
	{
		AccrueTickTime_ += DeltaSeconds;
		EDirection Direction = EDirection::NONE;

		for (const auto& KeyDirection : KEY_DIRECTIONS)
		{
			if (InputManager::Get().GetKeyPressState(KeyDirection.first) == EPressState::PRESSED)
			{
				Direction = KeyDirection.second;
			}
		}

		if (AccrueTickTime_ >= MaxAccrueTickTime_)
		{
			Direction = EDirection::DOWN;
			AccrueTickTime_ = 0.0f;
		}

		if (CanMove(Direction))
		{
			State_ = (Direction == EDirection::JUMP) ? EState::DONE : EState::ACTIVE;
			Move(Direction);
		}
		else
		{
			State_ = (Direction == EDirection::DOWN) ? EState::DONE : EState::ACTIVE;
		}

	} 
	else if (State_ == EState::WAIT)
	{
		TileMap* Object = WorldManager::Get().GetGameObject<TileMap>("TileMap");

		if (!Object->IsCollisionTilesInMap(Tiles_))
		{
			Object->AddTilesInMap(Tiles_);
		}
	}
}

void Tetromino::Move(const EDirection& Direction)
{
	TileMap* Object = WorldManager::Get().GetGameObject<TileMap>("TileMap");

	Object->RemoveTilesInMap(Tiles_);

	if (CanMove(TilePosition_, Tiles_, Shape_, Direction))
	{
		Move(TilePosition_, Tiles_, Shape_, Direction);
	}

	Object->AddTilesInMap(Tiles_);
}

bool Tetromino::CanMove(const EDirection& Direction)
{
	bool bCanMove = true;
	TileMap* Object = WorldManager::Get().GetGameObject<TileMap>("TileMap");

	Object->RemoveTilesInMap(Tiles_);
	bCanMove = CanMove(TilePosition_, Tiles_, Shape_, Direction);
	Object->AddTilesInMap(Tiles_);

	return bCanMove;
}

void Tetromino::Teleport(const Vec2i& Position)
{
	TileMap* Object = WorldManager::Get().GetGameObject<TileMap>("TileMap");

	Object->RemoveTilesInMap(Tiles_);

	if (CanTeleport(TilePosition_, Tiles_, Position))
	{
		Teleport(TilePosition_, Tiles_, Position);
	}

	Object->AddTilesInMap(Tiles_);
}

bool Tetromino::CanTeleport(const Vec2i& Position)
{
	bool bCanTeleport = true;
	TileMap* Object = WorldManager::Get().GetGameObject<TileMap>("TileMap");

	Object->RemoveTilesInMap(Tiles_);
	bCanTeleport = CanTeleport(TilePosition_, Tiles_, Position);
	Object->AddTilesInMap(Tiles_);

	return bCanTeleport;
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

void Tetromino::Move(Vec2i& TilePosition, std::vector<Tile>& Tiles, const EShape& Shape, const EDirection& Direction)
{
	switch (Direction)
	{
	case EDirection::NONE:
		break;

	case EDirection::UP:
	case EDirection::DOWN:
		TilePosition.y += (Direction == EDirection::UP) ? -1 : 1;

		for (auto& TetrominoTile : Tiles)
		{
			Vec2i TilePositionInMap = TetrominoTile.GetPositionInMap();
			TilePositionInMap.y += (Direction == EDirection::UP) ? -1 : 1;
			TetrominoTile.SetPositionInMap(TilePositionInMap);
		}
		break;

	case EDirection::LEFT:
	case EDirection::RIGHT:
		TilePosition.x += (Direction == EDirection::LEFT) ? -1 : 1;

		for (auto& TetrominoTile : Tiles)
		{
			Vec2i TilePositionInMap = TetrominoTile.GetPositionInMap();
			TilePositionInMap.x += (Direction == EDirection::LEFT) ? -1 : 1;
			TetrominoTile.SetPositionInMap(TilePositionInMap);
		}
		break;

	case EDirection::CCW:
	case EDirection::CW:
		for (auto& TetrominoTile : Tiles)
		{
			Vec2i TilePositionInMap = TetrominoTile.GetPositionInMap();
			TilePositionInMap -= TilePosition;

			TilePositionInMap = (Direction == EDirection::CCW) 
				? Vec2i(TilePositionInMap.y, GetBoundSize(Shape) - 1 - TilePositionInMap.x)
				: Vec2i(GetBoundSize(Shape) - 1 - TilePositionInMap.y, TilePositionInMap.x);

			TilePositionInMap += TilePosition;
			TetrominoTile.SetPositionInMap(TilePositionInMap);
		}
		break;

	case EDirection::JUMP:
		while (CanMove(TilePosition, Tiles, Shape, EDirection::DOWN))
		{
			Move(TilePosition, Tiles, Shape, EDirection::DOWN);
		}
		break;

	default:
		ENFORCE_THROW_EXCEPTION("undefined tetromino type...");
	}
}

bool Tetromino::CanMove(Vec2i& TilePosition, std::vector<Tile>& Tiles, const EShape& Shape, const EDirection& Direction)
{
	bool bCanMove = true;
	TileMap* Object = WorldManager::Get().GetGameObject<TileMap>("TileMap");

	Move(TilePosition, Tiles, Shape, Direction);
	bCanMove = !Object->IsCollisionTilesInMap(Tiles);
	Move(TilePosition, Tiles, Shape, GetCountDirection(Direction));

	return bCanMove;
}

void Tetromino::Teleport(Vec2i& TilePosition, std::vector<Tile>& Tiles, const Vec2i& Position)
{
	for (auto& TeleportTile : Tiles)
	{
		Vec2i OriginTilePosition = TeleportTile.GetPositionInMap();
		OriginTilePosition -= TilePosition;
		OriginTilePosition += Position;

		TeleportTile.SetPositionInMap(OriginTilePosition);
	}

	TilePosition = Position;
}

bool Tetromino::CanTeleport(Vec2i& TilePosition, std::vector<Tile>& Tiles, const Vec2i& Position)
{
	bool bCanTeleport = true;
	TileMap* Object = WorldManager::Get().GetGameObject<TileMap>("TileMap");

	Teleport(TilePosition, Tiles,  Position);
	bCanTeleport = !Object->IsCollisionTilesInMap(Tiles);
	Teleport(TilePosition, Tiles, -Position);

	return bCanTeleport;
}

int32_t Tetromino::GetBoundSize(const EShape& Shape)
{
	int32_t BoundSize = 0;

	switch (Shape)
	{
	case EShape::I:
		BoundSize = 4;
		break;

	case EShape::O:
		BoundSize = 4;
		break;

	case EShape::T:
		BoundSize = 3;
		break;

	case EShape::J:
		BoundSize = 3;
		break;

	case EShape::L:
		BoundSize = 3;
		break;

	case EShape::S:
		BoundSize = 3;
		break;

	case EShape::Z:
		BoundSize = 3;
		break;

	default:
		ENFORCE_THROW_EXCEPTION("undefined tetromino type...");
	}

	return BoundSize;
}

Tetromino::EDirection Tetromino::GetCountDirection(const EDirection& Direction)
{
	EDirection CountDirection;

	switch (Direction)
	{
	case EDirection::NONE:
		CountDirection = EDirection::NONE;
		break;

	case EDirection::CW:
		CountDirection = EDirection::CCW;
		break;

	case EDirection::CCW:
		CountDirection = EDirection::CW;
		break;

	case EDirection::DOWN:
		CountDirection = EDirection::UP;
		break;

	case EDirection::UP:
		CountDirection = EDirection::DOWN;
		break;

	case EDirection::LEFT:
		CountDirection = EDirection::RIGHT;
		break;

	case EDirection::RIGHT:
		CountDirection = EDirection::LEFT;
		break;

	case EDirection::JUMP:
		CountDirection = EDirection::UP;
		break;

	default:
		ENFORCE_THROW_EXCEPTION("undefined movement type...");
	}

	return CountDirection;
}
