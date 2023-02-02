#include "GameScene.h"
#include "Button.h"
#include "ContentManager.h"

void GameScene::Tick(float DeltaSeconds)
{
	for (auto& SceneButton : SceneButton_)
	{
		SceneButton->Tick(DeltaSeconds);
	}
}