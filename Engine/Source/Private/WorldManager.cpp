#include "WorldManager.h"
#include "Utils.hpp"

bool WorldManager::IsRegisterObject(const std::string& Key)
{
	return IsExistGameObject(Key);
}

void WorldManager::UnregisterObject(const std::string& Key)
{
	RemoveGameObject(Key);
}

Camera2D& WorldManager::CreateMainCamera(const Vec2f& Position, const float& Width, const float& Height, const float& Rotate, const float& Velocity)
{
	DestroyMainCamera();

	MainCamera_ = std::make_unique<Camera2D>(Position, Width, Height, Rotate, Velocity);

	return *MainCamera_.get();
}

Camera2D& WorldManager::GetMainCamera()
{
	return *MainCamera_.get();
}

void WorldManager::DestroyMainCamera()
{
	if (MainCamera_) MainCamera_.reset();
}

WorldManager::~WorldManager()
{
	MainCamera_.reset();

	for (auto& RemoveObject : GameObjects_)
	{
		RemoveObject.second.reset();
	}
}
