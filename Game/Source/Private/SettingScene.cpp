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
	WorldManager& GWorld = WorldManager::Get();

	std::function<void()> TetrominoSpeed2Event = [&]() {
		Tetromino::SetMaxAccrueTickTime(0.2f);
	};

	std::function<void()> TetrominoSpeed4Event = [&]() {
		Tetromino::SetMaxAccrueTickTime(0.4f);
	};

	std::function<void()> TetrominoSpeed6Event = [&]() {
		Tetromino::SetMaxAccrueTickTime(0.6f);
	};

	std::function<void()> TetrominoSpeed8Event = [&]() {
		Tetromino::SetMaxAccrueTickTime(0.8f);
	};

	std::function<void()> TetrominoSpeed10Event = [&]() {
		Tetromino::SetMaxAccrueTickTime(1.0f);
	};

	std::function<void()> BoardClear2Event = [&]() {
		Board::SetMaxAccrueTickTime(0.2f);
	};

	std::function<void()> BoardClear4Event = [&]() {
		Board::SetMaxAccrueTickTime(0.4f);
	};

	std::function<void()> BoardClear6Event = [&]() {
		Board::SetMaxAccrueTickTime(0.6f);
	};

	std::function<void()> BoardClear8Event = [&]() {
		Board::SetMaxAccrueTickTime(0.8f);
	};

	std::function<void()> BoardClear10Event = [&]() {
		Board::SetMaxAccrueTickTime(1.0f);
	};

	std::function<void()> OkEvent = [&]() {
		CurrentState_ = EState::BACK;
		RunSwitchEvent();
	};

	std::string TextureSignature = "Box";
	std::string FontSignature = "Font32";
	Vec2f Position = Vec2f(0.0f, 0.0f);
	float Width = 60.0f;
	float Height = 60.0f;
	float ReduceRate = 0.9f;
	LinearColor Color = MAGENTA;
	float Gap = 100.0f;

	SceneButton_ = {
		GWorld.CreateGameObject<Button>(
			"Speed2::SettingScene", 
			Vec2f(Position.x, Position.y),
			Width,
			Height,
			TextureSignature,
			L"0.2", 
			Color,
			FontSignature,
			EKeyCode::CODE_LBUTTON,
			TetrominoSpeed2Event,
			ReduceRate
		),

		GWorld.CreateGameObject<Button>(
			"Speed4::SettingScene",
			Vec2f(Position.x + Gap, Position.y),
			Width,
			Height,
			TextureSignature,
			L"0.4", 
			Color,
			FontSignature,
			EKeyCode::CODE_LBUTTON,
			TetrominoSpeed4Event,
			ReduceRate
		),

		GWorld.CreateGameObject<Button>(
			"Speed6::SettingScene",
			Vec2f(Position.x + 2.0f * Gap, Position.y),
			Width,
			Height,
			TextureSignature,
			L"0.6", 
			Color,
			FontSignature,
			EKeyCode::CODE_LBUTTON,
			TetrominoSpeed6Event,
			ReduceRate
		),

		GWorld.CreateGameObject<Button>(
			"Speed8::SettingScene", 
			Vec2f(Position.x + 3.0f * Gap, Position.y),
			Width,
			Height,
			TextureSignature,
			L"0.8", 
			Color,
			FontSignature,
			EKeyCode::CODE_LBUTTON,
			TetrominoSpeed8Event,
			ReduceRate
		),


		GWorld.CreateGameObject<Button>(
			"Speed10::SettingScene", 
			Vec2f(Position.x + 4.0f * Gap, Position.y),
			Width,
			Height,
			TextureSignature,
			L"1.0", 
			Color,
			FontSignature,
			EKeyCode::CODE_LBUTTON,
			TetrominoSpeed10Event,
			ReduceRate
		),

		GWorld.CreateGameObject<Button>(
			"Clear2::SettingScene", 
			Vec2f(Position.x, Position.y - Gap),
			Width,
			Height,
			TextureSignature,
			L"0.2", 
			Color,
			FontSignature,
			EKeyCode::CODE_LBUTTON,
			BoardClear2Event,
			ReduceRate
		),

		GWorld.CreateGameObject<Button>(
			"Clear4::SettingScene", 
			Vec2f(Position.x + Gap, Position.y - Gap),
			Width,
			Height,
			TextureSignature,
			L"0.4", 
			Color,
			FontSignature,
			EKeyCode::CODE_LBUTTON,
			BoardClear4Event,
			ReduceRate
		),

		GWorld.CreateGameObject<Button>(
			"Clear6::SettingScene", 
			Vec2f(Position.x + 2.0f * Gap, Position.y - Gap),
			Width,
			Height,
			TextureSignature,
			L"0.6", 
			Color,
			FontSignature,
			EKeyCode::CODE_LBUTTON,
			BoardClear6Event,
			ReduceRate
		),

		GWorld.CreateGameObject<Button>(
			"Clear8::SettingScene", 
			Vec2f(Position.x + 3.0f * Gap, Position.y - Gap),
			Width,
			Height,
			TextureSignature,
			L"0.8", 
			Color,
			FontSignature,
			EKeyCode::CODE_LBUTTON,
			BoardClear8Event,
			ReduceRate
		),

		GWorld.CreateGameObject<Button>(
			"Clear10::SettingScene", 
			Vec2f(Position.x + 4.0f * Gap, Position.y - Gap),
			Width,
			Height,
			TextureSignature,
			L"1.0", 
			Color,
			FontSignature,
			EKeyCode::CODE_LBUTTON,
			BoardClear10Event,
			ReduceRate
		),

		GWorld.CreateGameObject<Button>(
			"Ok::SettingScene", 
			Vec2f(Position.x, Position.y - 2.0f * Gap),
			300.0f, 
			50.0f, 
			"Button", 
			L"OK", 
			Color,
			FontSignature,
			EKeyCode::CODE_LBUTTON,
			OkEvent,
			ReduceRate
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

	GameScene::Tick(DeltaSeconds);
}