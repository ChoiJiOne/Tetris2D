#include "GameTitle.h"
#include "ContentManager.h"
#include "Font.h"
#include "GraphicsManager.h"
#include "Shader.h"

GameTitle::GameTitle(
	const std::string& Signature, 
	const std::wstring& Title, 
	const std::string& FontSignature,
	const Vec2f& Position, 
	const LinearColor& Color
)
	: GameObject(Signature)
	, Title_(Title)
	, FontSignature_(FontSignature)
	, Position_(Position)
	, Color_(Color)
{
}

void GameTitle::Tick(float DeltaSeconds)
{
	Font& TitleFont = ContentManager::Get().GetFont(FontSignature_);
	GraphicsManager::Get().DrawText2D(TitleFont, Title_, Position_, Color_);
}
