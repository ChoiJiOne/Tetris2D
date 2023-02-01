#include "SettingScene.h"
#include "Board.h"
#include "Background.h"
#include "Button.h"
#include "ContentManager.h"
#include "Font.h"
#include "GraphicsManager.h"
#include "GameText.h"
#include "Shader.h"
#include "Texture2D.h"
#include "Tetromino.h"
#include "WorldManager.h"

SettingScene::SettingScene()
{
	Buttons_ = {
		WorldManager::Get().CreateGameObject<Button>(
			"TetrominoSpeed0.2_SettingScene", Vec2f(0.0f, 0.0f), 60.0f, 60.0f, "Box", L"0.2", MAGENTA, "Font32", EKeyCode::CODE_LBUTTON,
			[&]() {
				Tetromino::SetMaxAccrueTickTime(0.2f);
			},
			0.9f
		),

		WorldManager::Get().CreateGameObject<Button>(
			"TetrominoSpeed0.4_SettingScene", Vec2f(100.0f, 0.0f), 60.0f, 60.0f, "Box", L"0.4", MAGENTA, "Font32", EKeyCode::CODE_LBUTTON,
			[&]() {
				Tetromino::SetMaxAccrueTickTime(0.4f);
			},
			0.9f
		),

		WorldManager::Get().CreateGameObject<Button>(
			"TetrominoSpeed0.6_SettingScene", Vec2f(200.0f, 0.0f), 60.0f, 60.0f, "Box", L"0.6", MAGENTA, "Font32", EKeyCode::CODE_LBUTTON,
			[&]() {
				Tetromino::SetMaxAccrueTickTime(0.6f);
			},
			0.9f
		),

		WorldManager::Get().CreateGameObject<Button>(
			"TetrominoSpeed0.8_SettingScene", Vec2f(300.0f, 0.0f), 60.0f, 60.0f, "Box", L"0.8", MAGENTA, "Font32", EKeyCode::CODE_LBUTTON,
			[&]() {
				Tetromino::SetMaxAccrueTickTime(0.8f);
			},
			0.9f
		),


		WorldManager::Get().CreateGameObject<Button>(
			"TetrominoSpeed1.0_SettingScene", Vec2f(400.0f, 0.0f), 60.0f, 60.0f, "Box", L"1.0", MAGENTA, "Font32", EKeyCode::CODE_LBUTTON,
			[&]() {
				Tetromino::SetMaxAccrueTickTime(1.0f);
			},
			0.9f
		),

		WorldManager::Get().CreateGameObject<Button>(
			"BoardClear0.2_SettingScene", Vec2f(0.0f, -100.0f), 60.0f, 60.0f, "Box", L"0.2", MAGENTA, "Font32", EKeyCode::CODE_LBUTTON,
			[&]() {
				Board::SetMaxAccrueTickTime(0.2f);
			},
			0.9f
		),

		WorldManager::Get().CreateGameObject<Button>(
			"BoardClear0.4_SettingScene", Vec2f(100.0f, -100.0f), 60.0f, 60.0f, "Box", L"0.4", MAGENTA, "Font32", EKeyCode::CODE_LBUTTON,
			[&]() {
				Board::SetMaxAccrueTickTime(0.4f);
			},
			0.9f
		),

		WorldManager::Get().CreateGameObject<Button>(
			"BoardClear0.6_SettingScene", Vec2f(200.0f, -100.0f), 60.0f, 60.0f, "Box", L"0.6", MAGENTA, "Font32", EKeyCode::CODE_LBUTTON,
			[&]() {
				Board::SetMaxAccrueTickTime(0.6f);
			},
			0.9f
		),

		WorldManager::Get().CreateGameObject<Button>(
			"BoardClear0.8_SettingScene", Vec2f(300.0f, -100.0f), 60.0f, 60.0f, "Box", L"0.8", MAGENTA, "Font32", EKeyCode::CODE_LBUTTON,
			[&]() {
				Board::SetMaxAccrueTickTime(0.8f);
			},
			0.9f
		),


		WorldManager::Get().CreateGameObject<Button>(
			"BoardClear1.0_SettingScene", Vec2f(400.0f, -100.0f), 60.0f, 60.0f, "Box", L"1.0", MAGENTA, "Font32", EKeyCode::CODE_LBUTTON,
			[&]() {
				Board::SetMaxAccrueTickTime(1.0f);
			},
			0.9f
		),

		WorldManager::Get().CreateGameObject<Button>(
			"Ok_SettingScene", Vec2f(0.0f, -200.0f), 300.0f, 50.0f, "Button", L"OK", MAGENTA, "Font32", EKeyCode::CODE_LBUTTON,
			[&]() {
				CurrentSelectState_ = ESelectState::BACK;
				RunSwitchEvent();
			},
			0.9f
		),
	};
}

SettingScene::~SettingScene()
{
}

void SettingScene::Tick(float DeltaSeconds)
{
	WorldManager::Get().GetGameObject<Background>("Background")->Tick(DeltaSeconds);
	WorldManager::Get().GetGameObject<GameText>("Title")->Tick(DeltaSeconds);

	Font& Font32 = ContentManager::Get().GetFont("Font32");
	GraphicsManager::Get().DrawText2D(Font32, Format(L"테트로미노 속도 : %.1f", Tetromino::GetMaxAccrueTickTime()), Vec2f(-250.0f,    0.0f), MAGENTA);
	GraphicsManager::Get().DrawText2D(Font32, Format(L"보드 정리 속도 : %.1f", Board::GetMaxAccrueTickTime()), Vec2f(-250.0f, -100.0f), MAGENTA);

	for (auto& SceneButton : Buttons_)
	{
		SceneButton->Tick(DeltaSeconds);
	}
}