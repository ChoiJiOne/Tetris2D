#include "TitleScene.h"
#include "Background.h"
#include "Button.h"
#include "GameObject.h"
#include "Label.h"
#include "InputManager.h"
#include "WorldManager.h"

TitleScene::TitleScene()
{
	WorldManager& GWorld = WorldManager::Get();

	SceneObjects_ = {		
		GWorld.CreateGameObject<Background>(
			"BACKGROUND::TitleScene", 
			"Background", 
			"Title",
			false
		),

		GWorld.CreateGameObject<Label>(
			"TITLE::TitleScene",
			L"TETRIS 2D",
			"Font128",
			Vec2f(0.0f, 200.f),
			MAGENTA
		),

		GWorld.CreateGameObject<Button>(
			"START::TitleScene",
			Vec2f(0.0f, 0.0f),
			400.0f,
			100.0f,
			"Button",
			L"START",
			MAGENTA,
			"Font64",
			EKeyCode::CODE_LBUTTON,
			[&]() {
				reinterpret_cast<Background*>(SceneObjects_[0])->StopAudio();
				RunSwitchEvent("START");
			},
			0.9f,
			true
		),
			
		GWorld.CreateGameObject<Button>(
			"QUIT::TitleScene",
			Vec2f(0.0f, -200.0f),
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

TitleScene::~TitleScene()
{
}

void TitleScene::Update(float DeltaSeconds)
{
	for (auto& SceneObject : SceneObjects_)
	{
		SceneObject->Tick(DeltaSeconds);
	}
}

void TitleScene::Reset()
{
	reinterpret_cast<Background*>(SceneObjects_[0])->ResetAudio();
	reinterpret_cast<Background*>(SceneObjects_[0])->PlayAudio();
}
