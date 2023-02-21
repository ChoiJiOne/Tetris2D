#include "Button.h"
#include "ButtonInputComponent.h"
#include "ContentManager.h"
#include "Font.h"
#include "Texture2D.h"
#include "GraphicsManager.h"
#include "Shader.h"
#include "SpriteRenderComponent.h"
#include "WorldManager.h"

Button::Button(const std::string& Signature, const ButtonParamWithText& ConstructorParam)
	: Button(
		Signature,
		ConstructorParam.Position,
		ConstructorParam.Width,
		ConstructorParam.Height,
		ConstructorParam.TextureSignature,
		ConstructorParam.Text,
		ConstructorParam.Color,
		ConstructorParam.FontSignature,
		ConstructorParam.KeyCode,
		ConstructorParam.ClickEvent,
		ConstructorParam.ReduceRate,
		ConstructorParam.bIsMouseMode
	) {}

Button::Button(
	const std::string& Signature, 
	const Vec2f& Position, 
	const float& Width, 
	const float& Height,
	const std::string& TextureSignature,
	const std::wstring& Text,
	const LinearColor& Color,
	const std::string& FontSignature, 
	const EKeyCode& KeyCode, 
	const std::function<void()>& ClickEvent, 
	const float ReduceRate,
	bool bIsMouseMode
) : GameObject(Signature),
	bIsTextMode_(true),
	Position_(Position),
	Text_(Text),
	Color_(Color),
	FontSignature_(FontSignature)
{
	AddComponent<SpriteRenderComponent>("ButtonRenderer", TextureSignature, Position, Width, Height);
	AddComponent<ButtonInputComponent>("ButtonInput", Position, Width, Height, KeyCode, ClickEvent, ReduceRate, bIsMouseMode);
}

Button::Button(const std::string& Signature, const ButtonParamWithoutText& ConstructorParam)
	: Button(
		Signature,
		ConstructorParam.Position,
		ConstructorParam.Width,
		ConstructorParam.Height,
		ConstructorParam.TextureSignature,
		ConstructorParam.KeyCode,
		ConstructorParam.ClickEvent,
		ConstructorParam.ReduceRate,
		ConstructorParam.bIsMouseMode
	) {}

Button::Button(
	const std::string& Signature, 
	const Vec2f& Position, 
	const float& Width, 
	const float& Height,
	const std::string& TextureSignature,
	const EKeyCode& KeyCode, 
	const std::function<void()>& ClickEvent,
	const float ReduceRate,
	bool bIsMouseMode
) : GameObject(Signature),
	bIsTextMode_(false),
	Position_(Position)
{
	AddComponent<SpriteRenderComponent>("ButtonRenderer", TextureSignature, Position, Width, Height);
	AddComponent<ButtonInputComponent>("ButtonInput", Position, Width, Height, KeyCode, ClickEvent, ReduceRate, bIsMouseMode);
}

Button::~Button()
{
}

void Button::Tick(float DeltaSeconds)
{
	GetComponent<ButtonInputComponent>("ButtonInput")->Tick();
	GetComponent<SpriteRenderComponent>("ButtonRenderer")->Tick();

	if (bIsTextMode_)
	{
		Font& ButtonFont = ContentManager::Get().GetFont(FontSignature_);
		GraphicsManager::Get().DrawText2D(ButtonFont, Text_, Position_, Color_);
	}
}