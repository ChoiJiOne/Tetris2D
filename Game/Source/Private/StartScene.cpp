#include "StartScene.h"
#include "Background.h"
#include "Button.h"
#include "GameObject.h"
#include "Label.h"
#include "InputManager.h"
#include "WorldManager.h"

StartScene::StartScene()
{
	WorldManager& GWorld = WorldManager::Get();

	SceneObjects_ = {		
		GWorld.CreateGameObject<Background>(
			"BACKGROUND::StartScene", 
			"Background", 
			"Title"
		),

		GWorld.CreateGameObject<Label>(
			"TITLE::StartScene",
			L"TETRIS 2D",
			"Font128",
			Vec2f(0.0f, 200.f),
			MAGENTA
		),

		GWorld.CreateGameObject<Button>(
			"START::StartScene",
			Vec2f(0.0f, 0.0f),
			400.0f,
			100.0f,
			"Button",
			L"START",
			MAGENTA,
			"Font64",
			EKeyCode::CODE_LBUTTON,
			[&]() {
				reinterpret_cast<Background*>(SceneObjects_[0])->InactiveAudio();
				RunSwitchEvent("START");
			},
			0.9f,
			true
		),
			
		GWorld.CreateGameObject<Button>(
			"QUIT::StartScene",
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

	reinterpret_cast<Background*>(SceneObjects_[0])->ActiveAudio();
}

StartScene::~StartScene()
{
}

void StartScene::Update(float DeltaSeconds)
{
	for (auto& SceneObject : SceneObjects_)
	{
		SceneObject->Tick(DeltaSeconds);
	}
}
