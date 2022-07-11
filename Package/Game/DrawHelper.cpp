#include "Macro.h"
#include "ResourceHelper.h"
#include "Texture2D.h"
#include "Font.h"

#include "DrawHelper.h"


void Game::DrawHelper::BeginDraw(SDL_Renderer* InRenderer, const LinearColor& InColor)
{
	SetDrawColor(InRenderer, InColor);
	CHECK_SDL_FAILED((SDL_RenderClear(InRenderer) == 0));
}

void Game::DrawHelper::EndDraw(SDL_Renderer* InRenderer)
{
	SDL_RenderPresent(InRenderer);
}

void Game::DrawHelper::DrawPoint2D(SDL_Renderer* InRenderer, const Vec2i& InPosition, const LinearColor& InColor)
{
	SetDrawColor(InRenderer, InColor);
	CHECK_SDL_FAILED((SDL_RenderDrawPoint(InRenderer, InPosition.x, InPosition.y) == 0));
}

void Game::DrawHelper::DrawLine2D(SDL_Renderer* InRenderer, const Vec2i& InP0, const Vec2i& InP1, const LinearColor& InColor)
{
	SetDrawColor(InRenderer, InColor);
	CHECK_SDL_FAILED((SDL_RenderDrawLine(InRenderer, InP0.x, InP0.y, InP1.x, InP1.y) == 0));
}

void Game::DrawHelper::DrawWireframeRectangle2D(SDL_Renderer* InRenderer, const Vec2i& InP0, const Vec2i& InP1, const LinearColor& InColor)
{
	SetDrawColor(InRenderer, InColor);

	SDL_Rect Rect = {
		std::min(InP0.x, InP1.x),
		std::min(InP0.y, InP1.y),
		std::abs(InP1.x - InP0.x) + 1,
		std::abs(InP1.y - InP0.y) + 1
	};

	CHECK_SDL_FAILED((SDL_RenderDrawRect(InRenderer, &Rect) == 0));
}

void Game::DrawHelper::DrawWireframeRectangle2D(SDL_Renderer* InRenderer, const Vec2i& InCenterPosition, int32_t InWidth, int32_t InHeight, const LinearColor& InColor)
{
	Vec2i P0, P1;

	P0.x = static_cast<int32_t>(InCenterPosition.x - (InWidth  / 2));
	P0.y = static_cast<int32_t>(InCenterPosition.y - (InHeight / 2));

	P1.x = static_cast<int32_t>(InCenterPosition.x + (InWidth  / 2));
	P1.y = static_cast<int32_t>(InCenterPosition.y + (InHeight / 2));

	DrawWireframeRectangle2D(InRenderer, P0, P1, InColor);
}

void Game::DrawHelper::DrawRectangle2D(SDL_Renderer* InRenderer, const Vec2i& InP0, const Vec2i& InP1, const LinearColor& InColor)
{
	SetDrawColor(InRenderer, InColor);

	SDL_Rect Rect = {
		std::min(InP0.x, InP1.x),
		std::min(InP0.y, InP1.y),
		std::abs(InP1.x - InP0.x) + 1,
		std::abs(InP1.y - InP0.y) + 1
	};

	CHECK_SDL_FAILED((SDL_RenderFillRect(InRenderer, &Rect) == 0));
}

void Game::DrawHelper::DrawRectangle2D(SDL_Renderer* InRenderer, const Vec2i& InCenterPosition, int32_t InWidth, int32_t InHeight, const LinearColor& InColor)
{
	Vec2i P0, P1;

	P0.x = static_cast<int32_t>(InCenterPosition.x - (InWidth  / 2));
	P0.y = static_cast<int32_t>(InCenterPosition.y - (InHeight / 2));

	P1.x = static_cast<int32_t>(InCenterPosition.x + (InWidth  / 2));
	P1.y = static_cast<int32_t>(InCenterPosition.y + (InHeight / 2));

	DrawRectangle2D(InRenderer, P0, P1, InColor);
}

void Game::DrawHelper::DrawTexture2D(SDL_Renderer* InRenderer, const std::size_t& InHashKey, const Vec2i& InCenterPosition, float InWidthScaling, float InHeightScaling)
{
	const Texture2D& Texture = ResourceHelper::GetTexture2D(InHashKey);

	float ScaleWidth = static_cast<float>(Texture.GetWidth()) * InWidthScaling;
	float ScaleHeight = static_cast<float>(Texture.GetHeight()) * InHeightScaling;

	SDL_Rect Rect = {
		InCenterPosition.x - static_cast<int32_t>(ScaleWidth  / 2.0f),
		InCenterPosition.y - static_cast<int32_t>(ScaleHeight / 2.0f),
		static_cast<int32_t>(ScaleWidth),
		static_cast<int32_t>(ScaleHeight)
	};

	CHECK_SDL_FAILED((SDL_RenderCopy(InRenderer, Texture.GetTexture(), nullptr, &Rect) == 0));
}

void Game::DrawHelper::DrawText2D(SDL_Renderer* InRenderer, const std::size_t& InHashKey, const Vec2i& InPosition, const std::wstring& InText, const LinearColor& InColor)
{
	const Game::Font& Font = ResourceHelper::GetFont(InHashKey);

	int32_t x = InPosition.x;
	int32_t y = InPosition.y;

	uint8_t R = 0, G = 0, B = 0, A = 0;
	ColorHelper::ConvertLinearColorToR8G8B8A8(InColor, R, G, B, A);

	for (const auto& Unicode : InText)
	{
		SDL_Texture* Texture = Font.GetAtlas(Unicode);

		if (!Texture) continue;

		SDL_SetTextureColorMod(Texture, R, G, B);
		SDL_SetTextureAlphaMod(Texture, A);

		const stbtt_packedchar& Info = Font.GetPackedchar(Unicode);

		SDL_Rect Src =
		{
			Info.x0,
			Info.y0,
			Info.x1 - Info.x0,
			Info.y1 - Info.y0
		};

		SDL_Rect Dst =
		{
			x + static_cast<int32_t>(Info.xoff),
			y,
			(Info.x1 - Info.x0),
			(Info.y1 - Info.y0)
		};

		SDL_RenderCopy(InRenderer, Texture, &Src, &Dst);
		x += static_cast<int32_t>(Info.xadvance);
	}
}

void Game::DrawHelper::SetDrawColor(SDL_Renderer* InRenderer, const LinearColor& InColor)
{
	uint8_t R = 0, G = 0, B = 0, A = 0;
	ColorHelper::ConvertLinearColorToR8G8B8A8(InColor, R, G, B, A);
	SetDrawColor(InRenderer, R, G, B, A);
}

void Game::DrawHelper::SetDrawColor(SDL_Renderer* InRenderer, uint8_t InRed, uint8_t InGreen, uint8_t InBlue, uint8_t InAlpha)
{
	CHECK_SDL_FAILED((SDL_SetRenderDrawColor(InRenderer, InRed, InGreen, InBlue, InAlpha) == 0));
}