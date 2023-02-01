#include "PlayScene.h"
#include "Background.h"
#include "Button.h"
#include "Board.h"
#include "Camera2D.h"
#include "GameText.h"
#include "InputManager.h"
#include "Tetromino.h"
#include "TileMap.h"
#include "WorldManager.h"

PlayScene::PlayScene()
{
	Buttons_ = {
		WorldManager::Get().CreateGameObject<Button>(
			"ESC_PlayScene", Vec2f(-410.0f, +250.0f), 60.0f, 60.0f, "Box", L"ESC", MAGENTA, "Font32", EKeyCode::CODE_ESCAPE,
			[&]() {
				// TODO
			},
			0.9f,
			false
		),

		WorldManager::Get().CreateGameObject<Button>(
			"LEFT_PlayScene", Vec2f(-410.0f, +180.0f), 60.0f, 60.0f, "Left", EKeyCode::CODE_LEFT,
			[&]() {
				// TODO
			},
			0.9f,
			false
		),

		WorldManager::Get().CreateGameObject<Button>(
			"DOWN_PlayScene", Vec2f(-340.0f, +180.0f), 60.0f, 60.0f, "Down", EKeyCode::CODE_DOWN,
			[&]() {
				// TODO
			},
			0.9f,
			false
		),
		
		WorldManager::Get().CreateGameObject<Button>(
			"UP_PlayScene", Vec2f(-340.0f, +250.0f), 60.0f, 60.0f, "Up", EKeyCode::CODE_UP,
			[&]() {
				// TODO
			},
			0.9f,
			false
		),

		WorldManager::Get().CreateGameObject<Button>(
			"Right_PlayScene", Vec2f(-270.0f, +180.0f), 60.0f, 60.0f, "Right", EKeyCode::CODE_RIGHT,
			[&]() {
				// TODO
			},
			0.9f,
			false
		),

		WorldManager::Get().CreateGameObject<Button>(
			"Space_PlayScene", Vec2f(-340.0f, +110.0f), 200.0f, 60.0f, "Button", L"SPACE", MAGENTA, "Font32", EKeyCode::CODE_SPACE,
			[&]() {
				// TODO
			},
			0.9f,
			false
		),

		WorldManager::Get().CreateGameObject<Button>(
			"Play_PlayScene", Vec2f(-410.0f, +40.0f), 60.0f, 60.0f, "Play", EKeyCode::CODE_LBUTTON,
			[&]() {
				// TODO
			},
			0.9f
		),

		WorldManager::Get().CreateGameObject<Button>(
			"Stop_PlayScene", Vec2f(-340.0f, +40.0f), 60.0f, 60.0f, "Stop", EKeyCode::CODE_LBUTTON,
			[&]() {
				// TODO
			},
			0.9f
		),

		WorldManager::Get().CreateGameObject<Button>(
			"Reset_PlayScene", Vec2f(-270.0f, +40.0f), 60.0f, 60.0f, "Reset", EKeyCode::CODE_LBUTTON,
			[&]() {
				// TODO
			},
			0.9f
		),

		WorldManager::Get().CreateGameObject<Button>(
			"Voluble_PlayScene", Vec2f(-340.0f, -30.0f), 60.0f, 60.0f, "Voluble", EKeyCode::CODE_LBUTTON,
			[&]() {
				// TODO
			},
			0.9f
		),

		WorldManager::Get().CreateGameObject<Button>(
			"Mute_PlayScene", Vec2f(-270.0f, -30.0f), 60.0f, 60.0f, "Mute", EKeyCode::CODE_LBUTTON,
			[&]() {
				// TODO
			},
			0.9f
		),
	};

	WorldManager::Get().CreateGameObject<GameText>("Next", L"NEXT", "Font32", Vec2f(250.0f, 330.0f), MAGENTA);
	WorldManager::Get().CreateGameObject<GameText>(
		"Time", 
		Format(L"TIME : %d", static_cast<int32_t>(PlayTime_)),
		"Font32",
		Vec2f(250.0f, 0.0f), 
		MAGENTA
	);
	WorldManager::Get().CreateGameObject<GameText>(
		"Line",
		Format(L"LINE : %d", 0),
		"Font32",
		Vec2f(250.0f, -60.0f),
		MAGENTA
	);
}

PlayScene::~PlayScene()
{
}

void PlayScene::Tick(float DeltaSeconds)
{
	PlayTime_ += DeltaSeconds;
	WorldManager::Get().GetGameObject<GameText>("Time")->SetText(
		Format(L"TIME : %d", static_cast<int32_t>(PlayTime_))
	);

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


		WorldManager::Get().GetGameObject<GameText>("Line")->SetText(
			Format(L"LINE : %d", BoardObject->GetRemoveLine())
		);
	}

	for (auto& SceneButton : Buttons_)
	{
		SceneButton->Tick(DeltaSeconds);
	}

	WorldManager::Get().GetGameObject<GameText>("Next")->Tick(DeltaSeconds);
	WorldManager::Get().GetGameObject<GameText>("Time")->Tick(DeltaSeconds);
	WorldManager::Get().GetGameObject<GameText>("Line")->Tick(DeltaSeconds);
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

	PlayTime_ = 0.0f;
	CurrentTetromino_ = 0;
	CountOfTetromino_ = 0;
	CameraPosition_ = Vec2f(0.0f, 0.0f);
	TileMapPosition_ = Vec2f(0.0f, 0.0f);
	StartPosition_ = Vec2i(10, 1);
	WaitPosition_ = Vec2i(20, 2);

	WorldManager::Get().CreateMainCamera(CameraPosition_, 1000.0f, 800.0f);

	WorldManager::Get().CreateGameObject<TileMap>("TileMap", TileMapPosition_, 22, 26, 30);

	WorldManager::Get().CreateGameObject<Board>("Board", Vec2i(6, 0), 12, 22);
	WorldManager::Get().CreateGameObject<Tetromino>(std::to_string(CountOfTetromino_++), StartPosition_);
	WorldManager::Get().CreateGameObject<Tetromino>(std::to_string(CountOfTetromino_++), WaitPosition_);

	WorldManager::Get().GetGameObject<Tetromino>(std::to_string(CurrentTetromino_))->SetState(Tetromino::EState::ACTIVE);

	CurrentState_ = EState::PLAY;
}
