#include "DoneScene.h"
#include "Background.h"
#include "Button.h"
#include "ContentManager.h"
#include "GraphicsManager.h"
#include "GameTitle.h"
#include "Shader.h"
#include "Texture2D.h"
#include "WorldManager.h"

DoneScene::DoneScene()
{
	Buttons_ = {
		WorldManager::Get().CreateGameObject<Button>(
			"Replay_DoneScene", Vec2f(0.0f, 100.0f), 300.0f, 50.0f, "Button", L"REPLAY", MAGENTA, "Font32", EKeyCode::CODE_LBUTTON,
			[&]() {
				CurrentSelectState_ = ESelectState::REPLAY;
				RunSwitchEvent();
			},
			0.9f
		),

		WorldManager::Get().CreateGameObject<Button>(
			"Reset_DoneScene", Vec2f(0.0f, 0.0f), 300.0f, 50.0f, "Button", L"RESET", MAGENTA, "Font32", EKeyCode::CODE_LBUTTON,
			[&]() {
				CurrentSelectState_ = ESelectState::RESET;
				RunSwitchEvent();
			},
			0.9f
		),

		WorldManager::Get().CreateGameObject<Button>(
			"Quit_DoneScene", Vec2f(0.0f, -100.0f), 300.0f, 50.0f, "Button", L"QUIT", MAGENTA, "Font32", EKeyCode::CODE_LBUTTON,
			[&]() {
				CurrentSelectState_ = ESelectState::QUIT;
				RunSwitchEvent();
			},
			0.9f
		)
	};
}

DoneScene::~DoneScene()
{
}

void DoneScene::Tick(float DeltaSeconds)
{
	WorldManager::Get().GetGameObject<Background>("Background")->Tick(DeltaSeconds);
	WorldManager::Get().GetGameObject<GameTitle>("Title")->Tick(DeltaSeconds);

	for (auto& SceneButton : Buttons_)
	{
		SceneButton->Tick(DeltaSeconds);
	}
}
