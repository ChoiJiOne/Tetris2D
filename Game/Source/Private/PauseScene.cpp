#include "PauseScene.h"
#include "Background.h"
#include "Button.h"
#include "ContentManager.h"
#include "GraphicsManager.h"
#include "GameText.h"
#include "Shader.h"
#include "Texture2D.h"
#include "WorldManager.h"

PauseScene::PauseScene()
{
	Buttons_ = {
		WorldManager::Get().CreateGameObject<Button>(
			"Start_PauseScene", Vec2f(0.0f, 100.0f), 300.0f, 50.0f, "Button", L"CONTINUE", MAGENTA, "Font32", EKeyCode::CODE_LBUTTON,
			[&]() {
				CurrentSelectState_ = ESelectState::CONTINUE;
				RunSwitchEvent();
			},
			0.9f
		),

		WorldManager::Get().CreateGameObject<Button>(
			"Setting_PaseScene", Vec2f(0.0f, 0.0f), 300.0f, 50.0f, "Button", L"RESET", MAGENTA, "Font32", EKeyCode::CODE_LBUTTON,
			[&]() {
				CurrentSelectState_ = ESelectState::RESET;
				RunSwitchEvent();
			},
			0.9f
		),

		WorldManager::Get().CreateGameObject<Button>(
			"Quit_PauseScene", Vec2f(0.0f, -100.0f), 300.0f, 50.0f, "Button", L"QUIT", MAGENTA, "Font32", EKeyCode::CODE_LBUTTON,
			[&]() {
				CurrentSelectState_ = ESelectState::QUIT;
				RunSwitchEvent();
			},
			0.9f
		)
	};
}

PauseScene::~PauseScene()
{
}

void PauseScene::Tick(float DeltaSeconds)
{
	WorldManager::Get().GetGameObject<Background>("Background")->Tick(DeltaSeconds);
	WorldManager::Get().GetGameObject<GameText>("Title")->Tick(DeltaSeconds);

	for (auto& SceneButton : Buttons_)
	{
		SceneButton->Tick(DeltaSeconds);
	}
}
