#include "PlayScene.h"
#include "Background.h"
#include "Button.h"
#include "GameObject.h"
#include "Label.h"
#include "InputManager.h"
#include "WorldManager.h"

PlayScene::PlayScene()
{
	WorldManager& GWorld = WorldManager::Get();

	SceneObjects_ = {
		GWorld.CreateGameObject<Background>(
			"BACKGROUND::PlayScene",
			"Background",
			"Play"
		)
	};
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update(float DeltaSeconds)
{
	for (auto& SceneObject : SceneObjects_)
	{
		SceneObject->Tick(DeltaSeconds);
	}
}

void PlayScene::Reset()
{
	reinterpret_cast<Background*>(SceneObjects_[0])->ActiveAudio();
}
