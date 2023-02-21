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

		GWorld.CreateGameObject<Label>("TIME::GameOverScene",  L"", "Font32", Vec2f(0.0f, 100.0f), YELLOW),
		GWorld.CreateGameObject<Label>("LINE::GameOverScene",  L"", "Font32", Vec2f(0.0f,  60.0f), YELLOW),
		GWorld.CreateGameObject<Label>("LEVEL::GameOverScene", L"", "Font32", Vec2f(0.0f,  20.0f), YELLOW),

		GWorld.CreateGameObject<Button>(
			"REPLAY::GameOverScene",
			Vec2f(0.0f, -70.0f),
			400.0f,
			100.0f,
			"Button",
			L"REPLAY",
			MAGENTA,
			"Font64",
			EKeyCode::CODE_LBUTTON,
			[&]() {
				reinterpret_cast<Background*>(SceneObjects_[0])->StopAudio();
				RunSwitchEvent("REPLAY");
			},
			0.9f,
			true
		),

		GWorld.CreateGameObject<Button>(
			"QUIT::GameOverScene",
			Vec2f(0.0f, -220.0f),
			400.0f,
			100.0f,
			"Button",
			L"QUIT",
			MAGENTA,
			"Font64",
			EKeyCode::CODE_LBUTTON,
			[&]() {
				reinterpret_cast<Background*>(SceneObjects_[0])->StopAudio();
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
	reinterpret_cast<Background*>(SceneObjects_[0])->PlayAudio();

	reinterpret_cast<Label*>(SceneObjects_[2])->SetText(Format(L"%s%d", L"TIME : ", static_cast<int32_t>(PlayTime_)));
	reinterpret_cast<Label*>(SceneObjects_[3])->SetText(Format(L"%s%d", L"LINE : ", RemoveLine_));
	reinterpret_cast<Label*>(SceneObjects_[4])->SetText(Format(L"%s%d", L"LEVEL : ", Level_));
}