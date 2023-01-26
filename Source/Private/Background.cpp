#include "Background.h"
#include "ContentManager.h"
#include "Camera2D.h"
#include "GraphicsManager.h"
#include "Shader.h"
#include "Texture2D.h"
#include "Utility.hpp"
#include "Window.h"

Background::Background(const std::string& Signature)
	: GameObject(Signature)
{
}

void Background::Tick(float DeltaSeconds)
{
	float Width = 0.0f, Height = 0.0f;

	GraphicsManager::Get().GetBackBufferSize(Width, Height);
	GraphicsManager::Get().DrawTexture2D(ContentManager::Get().GetTexture2D("Background"), Vec2f(0.0f, 0.0f), Width, Height);
}
