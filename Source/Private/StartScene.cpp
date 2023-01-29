#include "StartScene.h"
#include "Background.h"
#include "InputManager.h"
#include "WorldManager.h"

StartScene::~StartScene()
{
}

void StartScene::Tick(float DeltaSeconds)
{
	if (InputManager::Get().GetKeyPressState(EKeyCode::CODE_RETURN) == EPressState::PRESSED)
	{
		RunSwitchEvent();
	}

	WorldManager::Get().GetGameObject<Background>("Background")->Tick(DeltaSeconds);
}