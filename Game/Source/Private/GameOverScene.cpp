#include "GameOverScene.h"
#include "Background.h"
#include "Button.h"
#include "GameObject.h"
#include "Label.h"
#include "InputManager.h"
#include "WorldManager.h"

GameOverScene::GameOverScene()
{
	WorldManager& GWorld = WorldManager::Get();

	SceneObjects_ = {
		GWorld.CreateGameObject<Background>(
			"BACKGROUND::GameOverScene",
			"Background",
			"GameOver",
			false
		),

		GWorld.CreateGameObject<Label>(
			"TITLE::GameOverScene",
			L"TETRIS 2D",
			"Font128",
			Vec2f(0.0f, 200.f),
			MAGENTA
		),

		GWorld.CreateGameObject<Button>(
			"REPLAY::GameOverScene",
			Vec2f(0.0f, 0.0f),
			400.0f,
			100.0f,
			"Button",
			L"REPLAY",
			MAGENTA,
			"Font64",
			EKeyCode::CODE_LBUTTON,
			[&]() {
				reinterpret_cast<Background*>(SceneObjects_[0])->InactiveAudio();
				RunSwitchEvent("REPLAY");
			},
			0.9f,
			true
		),

		GWorld.CreateGameObject<Button>(
			"QUIT::GameOverScene",
			Vec2f(0.0f, -200.0f),
			400.0f,
			100.0f,
			"Button",
			L"QUIT",
			MAGENTA,
			"Font64",
			EKeyCode::CODE_LBUTTON,
			[&]() {
				reinterpret_cast<Background*>(SceneObjects_[0])->InactiveAudio();
				RunSwitchEvent("QUIT");
			},
			0.9f,
			true
		)
	};
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Update(float DeltaSeconds)
{
	for (auto& SceneObject : SceneObjects_)
	{
		SceneObject->Tick(DeltaSeconds);
	}
}

void GameOverScene::Reset()
{
	reinterpret_cast<Background*>(SceneObjects_[0])->ResetAudio();
	reinterpret_cast<Background*>(SceneObjects_[0])->ActiveAudio();
}
