#include "BackgroundRenderComponent.h"
#include "Camera2D.h"
#include "WorldManager.h"

BackgroundRenderComponent::BackgroundRenderComponent(GameObject* Object, const std::string& TextureSignature)
	: SpriteRenderComponent(Object, TextureSignature, Vec2f(0.0f, 0.0f), 0.0f, 0.0f)
{
	Camera2D& MainCamera = WorldManager::Get().GetMainCamera();
	SetPosition(MainCamera.GetPosition());
	SetWidth(MainCamera.GetWidth());
	SetHeight(MainCamera.GetHeight());
}

void BackgroundRenderComponent::Tick()
{
	Camera2D& MainCamera = WorldManager::Get().GetMainCamera();
	SetPosition(MainCamera.GetPosition());
	SetWidth(MainCamera.GetWidth());
	SetHeight(MainCamera.GetHeight());

	SpriteRenderComponent::Tick();
}
