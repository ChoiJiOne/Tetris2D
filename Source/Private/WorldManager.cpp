#include "WorldManager.h"
#include "GameObject.h"
#include "Utility.hpp"

void WorldManager::RegisterOjbect(GameObject* Object, const std::string& Key)
{
	if (IsRegisterObject(Key)) return;

	GameObjects_.insert({ Key, Object });
}

bool WorldManager::IsRegisterObject(const std::string& Key)
{
	return IsExistKey<std::string, GameObject*>(Key, GameObjects_);
}

GameObject* WorldManager::GetGameObject(const std::string& Key)
{
	if (!IsRegisterObject(Key)) return nullptr;

	return GameObjects_.at(Key);
}

void WorldManager::UnregisterObject(const std::string& Key)
{
	RemoveValue<std::string, GameObject*>(Key, GameObjects_);
}
