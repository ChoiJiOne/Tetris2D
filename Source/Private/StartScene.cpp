#include "StartScene.h"
#include "Background.h"
#include "Button.h"
#include "ContentManager.h"
#include "GraphicsManager.h"
#include "GameTitle.h"
#include "Shader.h"
#include "Texture2D.h"
#include "WorldManager.h"

StartScene::StartScene()
{
	Buttons_ = {
		WorldManager::Get().CreateGameObject<Button>(
			"Start_StartScene", Vec2f(0.0f, 100.0f), 300.0f, 50.0f, "Button", L"START", MAGENTA, "Font32", EKeyCode::CODE_LBUTTON,
			[&]() {
				CurrentSelectState_ = ESelectState::START;
				RunSwitchEvent();
			},
			0.9f
		),

		WorldManager::Get().CreateGameObject<Button>(
			"Setting_StartScene", Vec2f(0.0f, 0.0f), 300.0f, 50.0f, "Button", L"SETTING", MAGENTA, "Font32", EKeyCode::CODE_LBUTTON,
			[&]() {
				CurrentSelectState_ = ESelectState::SETTING;
				RunSwitchEvent();
			},
			0.9f
		),
				
		WorldManager::Get().CreateGameObject<Button>(
			"Quit_StartScene", Vec2f(0.0f, -100.0f), 300.0f, 50.0f, "Button", L"QUIT", MAGENTA, "Font32", EKeyCode::CODE_LBUTTON,
			[&]() {
				CurrentSelectState_ = ESelectState::QUIT;
				RunSwitchEvent();
			},
			0.9f
		)
	};
}

StartScene::~StartScene()
{
}

void StartScene::Tick(float DeltaSeconds)
{
	WorldManager::Get().GetGameObject<Background>("Background")->Tick(DeltaSeconds);
	WorldManager::Get().GetGameObject<GameTitle>("Title")->Tick(DeltaSeconds);

	for (auto& SceneButton : Buttons_)
	{
		SceneButton->Tick(DeltaSeconds);
	}
}