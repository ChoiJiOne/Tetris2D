#include "PlayScene.h"
#include "Background.h"
#include "Board.h"
#include "Camera2D.h"
#include "InputManager.h"
#include "Tetromino.h"
#include "TileMap.h"
#include "WorldManager.h"

PlayScene::~PlayScene()
{
}

void PlayScene::Tick(float DeltaSeconds)
{
	Background* BackgroundObject = WorldManager::Get().GetGameObject<Background>("Background");
	Tetromino* CurrTetrominoObject = WorldManager::Get().GetGameObject<Tetromino>(std::to_string(CurrentTetromino_));
	Tetromino* NextTetrominoObject = WorldManager::Get().GetGameObject<Tetromino>(std::to_string(CurrentTetromino_ + 1));

	if (InputManager::Get().GetKeyPressState(EKeyCode::CODE_ESCAPE) == EPressState::PRESSED)
	{
		CurrentState_ = EState::PAUSE;
		RunSwitchEvent();
	}

	BackgroundObject->Tick(DeltaSeconds);
	CurrTetrominoObject->Tick(DeltaSeconds);
	NextTetrominoObject->Tick(DeltaSeconds);

	Board* BoardObject = WorldManager::Get().GetGameObject<Board>("Board");
	BoardObject->Tick(DeltaSeconds);

	WorldManager::Get().GetGameObject<TileMap>("TileMap")->Tick(DeltaSeconds);

	if ((CurrTetrominoObject->GetState() == Tetromino::EState::DONE) && (BoardObject->GetState() == Board::EState::ACTIVE))
	{
		WorldManager::Get().UnregisterObject(std::to_string(CurrentTetromino_++));

		WorldManager::Get().GetGameObject<Tetromino>(std::to_string(CurrentTetromino_))->SetState(Tetromino::EState::ACTIVE);
		if (!WorldManager::Get().GetGameObject<Tetromino>(std::to_string(CurrentTetromino_))->CanTeleport(StartPosition_))
		{
			CurrentState_ = EState::DONE;
			RunSwitchEvent();
		}

		WorldManager::Get().GetGameObject<Tetromino>(std::to_string(CurrentTetromino_))->Teleport(StartPosition_);
		WorldManager::Get().CreateGameObject<Tetromino>(std::to_string(CountOfTetromino_++), WaitPosition_);
	}
}

void PlayScene::Reset()
{
	if (CountOfTetromino_ != 0) // 적어도 한번 초기화된 적 있을 때 ...
	{
		WorldManager::Get().DestroyMainCamera();

		WorldManager::Get().UnregisterObject("TileMap");
		WorldManager::Get().UnregisterObject("Board");
		WorldManager::Get().UnregisterObject(std::to_string(CurrentTetromino_));
		WorldManager::Get().UnregisterObject(std::to_string(CurrentTetromino_ + 1));
	}

	CurrentTetromino_ = 0;
	CountOfTetromino_ = 0;
	CameraPosition_ = Vec2f(0.0f, 0.0f);
	TileMapPosition_ = Vec2f(0.0f, 0.0f);
	StartPosition_ = Vec2i(10, 1);
	WaitPosition_ = Vec2i(19, 2);

	WorldManager::Get().CreateMainCamera(CameraPosition_, 1000.0f, 800.0f);

	WorldManager::Get().CreateGameObject<TileMap>("TileMap", TileMapPosition_, 22, 24, 30);

	WorldManager::Get().CreateGameObject<Board>("Board", Vec2i(6, 0), 12, 22);
	WorldManager::Get().CreateGameObject<Tetromino>(std::to_string(CountOfTetromino_++), StartPosition_);
	WorldManager::Get().CreateGameObject<Tetromino>(std::to_string(CountOfTetromino_++), WaitPosition_);

	WorldManager::Get().GetGameObject<Tetromino>(std::to_string(CurrentTetromino_))->SetState(Tetromino::EState::ACTIVE);

	CurrentState_ = EState::PLAY;
}
