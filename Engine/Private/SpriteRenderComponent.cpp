#include "SpriteRenderComponent.h"
#include "ContentManager.h"
#include "GraphicsManager.h"
#include "Shader.h"
#include "Texture2D.h"

void SpriteRenderComponent::Tick()
{
	Texture2D& SpriteTexture = ContentManager::Get().GetTexture2D(TextureSignature_);
	GraphicsManager::Get().DrawTexture2D(SpriteTexture, Position_, Width_, Height_);
}