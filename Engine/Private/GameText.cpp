#include "GameText.h"
#include "ContentManager.h"
#include "Font.h"
#include "GraphicsManager.h"
#include "Shader.h"

GameText::GameText(
	const std::string& Signature, 
	const std::wstring& Text, 
	const std::string& FontSignature,
	const Vec2f& Position, 
	const LinearColor& Color
)
	: GameObject(Signature)
	, Text_(Text)
	, FontSignature_(FontSignature)
	, Position_(Position)
	, Color_(Color)
{
}

void GameText::Tick(float DeltaSeconds)
{
	Font& TitleFont = ContentManager::Get().GetFont(FontSignature_);
	GraphicsManager::Get().DrawText2D(TitleFont, Text_, Position_, Color_);
}
