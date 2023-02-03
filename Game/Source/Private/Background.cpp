#include "Background.h"
#include "BackgroundRenderComponent.h"

Background::Background(const std::string& Signature)
	: GameObject(Signature)
{
	AddComponent<BackgroundRenderComponent>("Render", "Background");
}

void Background::Tick(float DeltaSeconds)
{
	GetComponent<BackgroundRenderComponent>("Render")->Tick();
}