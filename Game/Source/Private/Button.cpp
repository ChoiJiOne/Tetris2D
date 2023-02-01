#include "Button.h"
#include "ContentManager.h"
#include "Font.h"
#include "Texture2D.h"
#include "GraphicsManager.h"
#include "Shader.h"
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
	Width_(Width),
	Height_(Height),
	TextureSignature_(TextureSignature),
	Text_(Text),
	Color_(Color),
	FontSignature_(FontSignature),
	KeyCode_(KeyCode),
	ClickEvent_(ClickEvent),
	ReduceRate_(ReduceRate),
	bIsMouseMode_(bIsMouseMode)
{
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
	Position_(Position),
	Width_(Width),
	Height_(Height),
	TextureSignature_(TextureSignature),
	KeyCode_(KeyCode),
	ClickEvent_(ClickEvent),
	ReduceRate_(ReduceRate),
	bIsMouseMode_(bIsMouseMode)
{
}

Button::~Button()
{
}

void Button::Tick(float DeltaSeconds)
{
	bIsDetectMouse_ = IsDetectMouse();

	float ButtonTextureWidth = Width_;
	float ButtonTextureHeight = Height_;

	if (bIsMouseMode_)
	{
		if (bIsDetectMouse_)
		{
			const EPressState& PressState = InputManager::Get().GetKeyPressState(KeyCode_);

			if (PressState == EPressState::HELD || PressState == EPressState::PRESSED)
			{
				ButtonTextureWidth *= ReduceRate_;
				ButtonTextureHeight *= ReduceRate_;
			}

			if (PressState == EPressState::RELEASED && ClickEvent_)
			{
				ClickEvent_();
			}
		}
	}
	else
	{
		const EPressState& PressState = InputManager::Get().GetKeyPressState(KeyCode_);

		if (PressState == EPressState::HELD || PressState == EPressState::PRESSED)
		{
			ButtonTextureWidth *= ReduceRate_;
			ButtonTextureHeight *= ReduceRate_;
		}

		if (PressState == EPressState::RELEASED && ClickEvent_)
		{
			ClickEvent_();
		}
	}

	Texture2D& ButtonTexture = ContentManager::Get().GetTexture2D(TextureSignature_);
	GraphicsManager::Get().DrawTexture2D(ButtonTexture, Position_, ButtonTextureWidth, ButtonTextureHeight);

	if (bIsTextMode_)
	{
		Font& ButtonFont = ContentManager::Get().GetFont(FontSignature_);
		GraphicsManager::Get().DrawText2D(ButtonFont, Text_, Position_, Color_);
	}
}

bool Button::IsDetectMouse() const
{
	Vec2i MousePosition = InputManager::Get().GetCurrMousePositionFromWindow();

	Vec2f WindowMousePosition = Vec2f(static_cast<float>(MousePosition.x), static_cast<float>(MousePosition.y));
	Vec2f CameraPositon = WorldManager::Get().GetMainCamera().GetPosition();
	float CameraWidth = WorldManager::Get().GetMainCamera().GetWidth();
	float CameraHeight = WorldManager::Get().GetMainCamera().GetHeight();
	
	Vec2f MousePositionFromWorld = Vec2f(
		+WindowMousePosition.x + CameraPositon.x - CameraWidth / 2.0f,
		-WindowMousePosition.y + CameraPositon.y + CameraHeight / 2.0f
	);

	float DiffX = std::abs(Position_.x - MousePositionFromWorld.x);
	float DiffY = std::abs(Position_.y - MousePositionFromWorld.y);

	return (0.0f <= DiffX && DiffX <= Width_ / 2.0f)
		&& (0.0f <= DiffY && DiffY <= Height_ / 2.0f);
}
