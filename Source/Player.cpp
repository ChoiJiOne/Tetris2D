#include "Game/Renderer.h"
#include "Game/StringHelper.h"
#include "Player.h"

Player::~Player()
{
}

void Player::LevelUp()
{
	Lavel++;
}

void Player::AddRemoveLine(int32_t InRemoveLine)
{
	RemoveLine += InRemoveLine;
}

void Player::UpdateRemainTime(float InDeltaTime)
{
	RemainTime -= InDeltaTime;
}

bool Player::IsOverPlayTime()
{
	return RemainTime <= 0.0f;
}

void Player::ResetAllProperties()
{
	ResetLevel();
	ResetRemoveLine();
	ResetRemainTime();
}

void Player::ResetLevel()
{
	Lavel = 1;
}

void Player::ResetRemoveLine()
{
	RemoveLine = 0;
}

void Player::ResetRemainTime()
{
	RemainTime = static_cast<float>(PLAY_TIME);
}

void Player::Draw(SDL_Renderer* InRenderer, const Game::Font& InFont, const Vec2i& InWindowPosition)
{
	LinearColor RemainTimeColor = (RemainTime <= 10.0f) ? ColorHelper::Red : ColorHelper::White;

	Game::Renderer::DrawWireframeRectangle2D(InRenderer, Vec2i(370, 340), Vec2i(580, 410), ColorHelper::White);
	Game::Renderer::DrawText2D(InRenderer, InFont, Vec2i(380, 390), Game::StringHelper::Format(L"Time : %3d", static_cast<int32_t>(RemainTime)), RemainTimeColor);

	Game::Renderer::DrawWireframeRectangle2D(InRenderer, Vec2i(370, 490), Vec2i(580, 560), ColorHelper::White);
	Game::Renderer::DrawText2D(InRenderer, InFont, Vec2i(380, 540), Game::StringHelper::Format(L"Level: %3d", Lavel), ColorHelper::White);

	Game::Renderer::DrawWireframeRectangle2D(InRenderer, Vec2i(370, 640), Vec2i(580, 710), ColorHelper::White);
	Game::Renderer::DrawText2D(InRenderer, InFont, Vec2i(380, 690), Game::StringHelper::Format(L"Line : %3d", RemoveLine), ColorHelper::White);
}
