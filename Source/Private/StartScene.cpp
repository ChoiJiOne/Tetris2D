#include "StartScene.h"
#include "Background.h"
#include "ContentManager.h"
#include "InputManager.h"
#include "GraphicsManager.h"
#include "GameTitle.h"
#include "Shader.h"
#include "Texture2D.h"
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
	WorldManager::Get().GetGameObject<GameTitle>("Title")->Tick(DeltaSeconds);
}