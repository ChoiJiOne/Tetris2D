#include "ButtonInputComponent.h"
#include "Camera2D.h"
#include "GameObject.h"
#include "InputManager.h"
#include "SpriteRenderComponent.h"
#include "WorldManager.h"

ButtonInputComponent::ButtonInputComponent(
	GameObject* Object, 
	const Vec2f& Position, 
	const float& Width, 
	const float& Height, 
	const EKeyCode& KeyCode, 
	const std::function<void()>& ClickEvent, 
	const float& ReduceRate, 
	bool bIsMouseMode
) : InputComponent(Object),
	Position_(Position),
	Width_(Width),
	Height_(Height),
	KeyCode_(KeyCode),
	ClickEvent_(ClickEvent),
	ReduceRate_(ReduceRate),
	bIsMouseMode_(bIsMouseMode)
{
}

ButtonInputComponent::~ButtonInputComponent()
{
}

void ButtonInputComponent::Tick()
{
	float ButtonWidth = Width_;
	float ButtonHeight = Height_;

	if (bIsMouseMode_)
	{
		if (IsDetectMouse())
		{
			ProcessButtonInput(ButtonWidth, ButtonHeight);
		}
	}
	else
	{
		ProcessButtonInput(ButtonWidth, ButtonHeight);
	}

	SpriteRenderComponent* SpriteRenderer = GetGameObject()->GetComponent<SpriteRenderComponent>("ButtonRenderer");
	SpriteRenderer->SetWidth(ButtonWidth);
	SpriteRenderer->SetHeight(ButtonHeight);
}

bool ButtonInputComponent::IsDetectMouse() const
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

void ButtonInputComponent::ProcessButtonInput(float& ButtonWidth, float& ButtonHeight)
{
	const EPressState& PressState = InputManager::Get().GetKeyPressState(KeyCode_);

	if (PressState == EPressState::HELD || PressState == EPressState::PRESSED)
	{
		ButtonWidth *= ReduceRate_;
		ButtonHeight *= ReduceRate_;
	}

	if (PressState == EPressState::RELEASED && ClickEvent_)
	{
		ClickEvent_();
	}
}
