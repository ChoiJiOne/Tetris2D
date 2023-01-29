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

	Texture2D& ButtonPush = ContentManager::Get().GetTexture2D("ButtonPush");
	Texture2D& ButtonRelease = ContentManager::Get().GetTexture2D("ButtonRelease");

	if (InputManager::Get().GetKeyPressState(EKeyCode::CODE_SPACE) == EPressState::HELD ||
	    InputManager::Get().GetKeyPressState(EKeyCode::CODE_SPACE) == EPressState::PRESSED)
	{
		GraphicsManager::Get().DrawTexture2D(ButtonPush, Vec2f(0.0f, 0.0f), 100.0f, 20.0f);
	}
	
	if (InputManager::Get().GetKeyPressState(EKeyCode::CODE_SPACE) == EPressState::RELEASED ||
	    InputManager::Get().GetKeyPressState(EKeyCode::CODE_SPACE) == EPressState::NONE)
	{
		GraphicsManager::Get().DrawTexture2D(ButtonRelease, Vec2f(0.0f, 0.0f), 100.0f, 20.0f);
	}
}