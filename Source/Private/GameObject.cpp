#include "GameObject.h"
#include "Component.h"
#include "Camera2D.h"

GameObject::GameObject(const std::string& Signature)
	: Signature_(Signature)
{
}

GameObject::~GameObject()
{
}
