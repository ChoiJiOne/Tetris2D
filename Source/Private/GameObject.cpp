#include "GameObject.h"
#include "Component.h"
#include "Camera2D.h"
#include "WorldManager.h"

GameObject::GameObject(const std::string& Signature)
	: Signature_(Signature)
{
	WorldManager::Get().RegisterOjbect(this, Signature_);
}

GameObject::~GameObject()
{
	WorldManager::Get().UnregisterObject(Signature_);
}
