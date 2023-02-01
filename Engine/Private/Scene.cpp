#include "Scene.h"
#include "Button.h"
#include "ContentManager.h"

void Scene::Tick(float DeltaSeconds)
{
	for (auto& SceneButton : SceneButton_)
	{
		SceneButton->Tick(DeltaSeconds);
	}
}