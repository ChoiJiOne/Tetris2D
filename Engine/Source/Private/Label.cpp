#include "Label.h"
#include "ContentManager.h"
#include "Font.h"
#include "GraphicsManager.h"
#include "Shader.h"

Label::Label(
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

void Label::Tick(float DeltaSeconds)
{
	Font& TitleFont = ContentManager::Get().GetFont(FontSignature_);
	GraphicsManager::Get().DrawText2D(TitleFont, Text_, Position_, Color_);
}
