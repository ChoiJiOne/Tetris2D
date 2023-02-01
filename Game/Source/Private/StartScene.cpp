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
	WorldManager& GlobalWorldManager = WorldManager::Get();

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
	Vec2f ButtonPositon = Vec2f(0.0f, 100.0f);
	float ButtonWidth = 300.0f;
	float ButtonHeight = 50.0f;
	float ButtonReduceRate = 0.9f;
	LinearColor ButtonTextColor = MAGENTA;
	float ButtonGap = 100.0f;

	SceneButton_ = {
		GlobalWorldManager.CreateGameObject<Button>(
			"Start::StartScene", 
			Vec2f(ButtonPositon.x, ButtonPositon.y),
			ButtonWidth,
			ButtonHeight,
			TextureSignature, 
			L"START", 
			ButtonTextColor,
			FontSignature,
			EKeyCode::CODE_LBUTTON,
			StartSwitchEvent,
			ButtonReduceRate
		),

		GlobalWorldManager.CreateGameObject<Button>(
			"Setting::StartScene", 
			Vec2f(ButtonPositon.x, ButtonPositon.y - ButtonGap),
			ButtonWidth,
			ButtonHeight,
			TextureSignature, 
			L"SETTING", 
			ButtonTextColor,
			FontSignature, 
			EKeyCode::CODE_LBUTTON,
			SettingSwitchEvent,
			ButtonReduceRate
		),
				
		GlobalWorldManager.CreateGameObject<Button>(
			"Quit::StartScene", 
			Vec2f(ButtonPositon.x, ButtonPositon.y - 2.0f * ButtonGap),
			ButtonWidth,
			ButtonHeight,
			TextureSignature,
			L"QUIT", 
			ButtonTextColor,
			FontSignature, 
			EKeyCode::CODE_LBUTTON,
			QuitSwitchEvent,
			ButtonReduceRate
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

	Scene::Tick(DeltaSeconds);
}