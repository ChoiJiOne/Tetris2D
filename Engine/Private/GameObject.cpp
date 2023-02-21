#include "GameObject.h"
#include "Component.h"
#include "Camera2D.h"
#include "WorldManager.h"

GameObject::GameObject(const std::string& Signature)
	: Signature_(Signature)
{
}

GameObject::~GameObject()
{
	for (auto& ObjectComponent : Components_)
	{
		ObjectComponent.second.reset();
	}
}