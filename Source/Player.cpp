#include "Game/Renderer.h"
#include "Game/StringHelper.h"
#include "Player.h"

Player::~Player()
{
}

void Player::LevelUp()
{
	Level++;
}

void Player::AddRemoveLine(int32_t InRemoveLine)
{
	RemoveLine += InRemoveLine;
}

void Player::Update(float InDeltaTime)
{
	StateElapsedTime += InDeltaTime;
	StepTime += InDeltaTime;
	BeforeState = CurrentState;

	switch (CurrentState)
	{
	case EState::Play:
		if (StateElapsedTime >= static_cast<float>(PLAY_TIME_PER_LEVEL))
		{
			StateElapsedTime = 0.0f;
			CurrentState = EState::Wait;
		}
		break;

	case EState::Wait:
		if (StateElapsedTime >= static_cast<float>(WAIT_TIME_PER_LEVEL))
		{
			LevelUp();

			StateElapsedTime = 0.0f;
			CurrentState = EState::Play;
		}
		break;

	default:
		break;
	}
}

void Player::SetCurrentMaxStepTime(float InCurrentMaxStepTime)
{
	if (InCurrentMaxStepTime < MinStepTime)
	{
		CurrentMaxStepTime = MinStepTime;
	}
	else
	{
		CurrentMaxStepTime = InCurrentMaxStepTime;
	}
}

void Player::ResetAllProperties()
{
	ResetLevel();
	ResetRemoveLine();
	ResetStepTime();
}

void Player::ResetLevel()
{
	Level = 0;
}

void Player::ResetRemoveLine()
{
	RemoveLine = 0;
}

void Player::ResetStepTime()
{
	StepTime = 0.0f;
}

void Player::Draw(SDL_Renderer* InRenderer, const Game::Font& InFont, const Vec2i& InWindowPosition)
{
	DrawUILayout(InRenderer, InFont, InWindowPosition);

	float ShowTime = 0.0f;
	LinearColor ShowTimeColor;

	if (CurrentState == EState::Play)
	{
		ShowTime = static_cast<float>(PLAY_TIME_PER_LEVEL) - StateElapsedTime;
		ShowTimeColor = (ShowTime <= 10.0f) ? ColorHelper::Red : ColorHelper::White;
		Game::Renderer::DrawText2D(InRenderer, InFont, Vec2i(380, 390), Game::StringHelper::Format(L"Play : %3d", static_cast<int32_t>(ShowTime)), ShowTimeColor);

	}
	else if (CurrentState == EState::Wait)
	{
		ShowTime = static_cast<float>(WAIT_TIME_PER_LEVEL) - StateElapsedTime;
		ShowTimeColor = ColorHelper::White;
		Game::Renderer::DrawText2D(InRenderer, InFont, Vec2i(380, 390), Game::StringHelper::Format(L"Wait : %3d", static_cast<int32_t>(ShowTime)), ShowTimeColor);
	}
	else // CurrentState == EState::Done
	{
		ShowTime = 0.0f;
		ShowTimeColor = ColorHelper::White;
		Game::Renderer::DrawText2D(InRenderer, InFont, Vec2i(380, 390), Game::StringHelper::Format(L"Done : %3d", static_cast<int32_t>(ShowTime)), ShowTimeColor);
	}

	Game::Renderer::DrawText2D(InRenderer, InFont, Vec2i(380, 540), Game::StringHelper::Format(L"Level: %3d", Level), ColorHelper::White);
	Game::Renderer::DrawText2D(InRenderer, InFont, Vec2i(380, 690), Game::StringHelper::Format(L"Line : %3d", RemoveLine), ColorHelper::White);
}

void Player::DrawUILayout(SDL_Renderer* InRenderer, const Game::Font& InFont, const Vec2i& InWindowPosition)
{
	Game::Renderer::DrawWireframeRectangle2D(InRenderer, Vec2i(370, 340), Vec2i(580, 410), ColorHelper::White);
	Game::Renderer::DrawWireframeRectangle2D(InRenderer, Vec2i(370, 490), Vec2i(580, 560), ColorHelper::White);
	Game::Renderer::DrawWireframeRectangle2D(InRenderer, Vec2i(370, 640), Vec2i(580, 710), ColorHelper::White);
}
