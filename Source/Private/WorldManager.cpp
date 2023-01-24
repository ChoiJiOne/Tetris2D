#include "WorldManager.h"
#include "GameObject.h"

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
	Remove<std::string, GameObject*>(Key, GameObjects_);
}
