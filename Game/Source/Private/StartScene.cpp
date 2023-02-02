#include "StartScene.h"
#include "Background.h"
#include "Button.h"
#include "ContentManager.h"
#include "GraphicsManager.h"
#include "GameText.h"
#include "Shader.h"
#include "Texture2D.h"
#include "WorldManager.h"

StartScene::StartScene()
{
	WorldManager& GWorld = WorldManager::Get();

	std::function<void()> StartSwitchEvent = [&]() {
		CurrentState_ = EState::START;
		RunSwitchEvent();
	};

	std::function<void()> SettingSwitchEvent = [&]() {
		CurrentState_ = EState::SETTING;
		RunSwitchEvent();
	};

	std::function<void()> QuitSwitchEvent = [&]() {
		CurrentState_ = EState::QUIT;
		RunSwitchEvent();
	};

	std::string TextureSignature = "Button";
	std::string FontSignature = "Font32";
	Vec2f Position = Vec2f(0.0f, 100.0f);
	float Width = 300.0f;
	float Height = 50.0f;
	float ReduceRate = 0.9f;
	LinearColor Color = MAGENTA;
	float Gap = 100.0f;

	SceneButton_ = {
		GWorld.CreateGameObject<Button>(
			"Start::StartScene", 
			Vec2f(Position.x, Position.y),
			Width,
			Height,
			TextureSignature, 
			L"START", 
			Color,
			FontSignature,
			EKeyCode::CODE_LBUTTON,
			StartSwitchEvent,
			ReduceRate
		),

		GWorld.CreateGameObject<Button>(
			"Setting::StartScene", 
			Vec2f(Position.x, Position.y - Gap),
			Width,
			Height,
			TextureSignature, 
			L"SETTING", 
			Color,
			FontSignature, 
			EKeyCode::CODE_LBUTTON,
			SettingSwitchEvent,
			ReduceRate
		),
				
		GWorld.CreateGameObject<Button>(
			"Quit::StartScene", 
			Vec2f(Position.x, Position.y - 2.0f * Gap),
			Width,
			Height,
			TextureSignature,
			L"QUIT", 
			Color,
			FontSignature, 
			EKeyCode::CODE_LBUTTON,
			QuitSwitchEvent,
			ReduceRate
		)
	};
}

StartScene::~StartScene()
{
}

void StartScene::Tick(float DeltaSeconds)
{
	WorldManager::Get().GetGameObject<Background>("Background")->Tick(DeltaSeconds);
	WorldManager::Get().GetGameObject<GameText>("Title")->Tick(DeltaSeconds);

	GameScene::Tick(DeltaSeconds);
}