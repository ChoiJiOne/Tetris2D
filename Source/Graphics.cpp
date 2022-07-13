// @third party code - BEGIN SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
// @third party code - END

#include "Macro.h"
#include "ResourceHelper.h"
#include "Texture2D.h"
#include "Font.h"
#include "Graphics.h"


Graphics::~Graphics()
{
	if (Renderer)
	{
		SDL_DestroyRenderer(Renderer);
		Renderer = nullptr;
	}
}

void Graphics::Initialize(SDL_Window* InWindow)
{
	CHECK((InWindow != nullptr), "invalid function parameter");
	Renderer = SDL_CreateRenderer(InWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	CHECK((Renderer != nullptr), SDL_GetError());
}

void Graphics::BeginFrame(const LinearColor& InColor)
{
	SetDrawColor(InColor);
	CHECK((SDL_RenderClear(Renderer) == 0), SDL_GetError());
}

void Graphics::EndFrame()
{
	SDL_RenderPresent(Renderer);
}

void Graphics::DrawPoint2D(const Vec2i& InPosition, const LinearColor& InColor)
{
	SetDrawColor(InColor);
	CHECK((SDL_RenderDrawPoint(Renderer, InPosition.x, InPosition.y) == 0), SDL_GetError());
}

void Graphics::DrawLine2D(const Vec2i& InP0, const Vec2i& InP1, const LinearColor& InColor)
{
	SetDrawColor(InColor);
	CHECK((SDL_RenderDrawLine(Renderer, InP0.x, InP0.y, InP1.x, InP1.y) == 0), SDL_GetError());
}

void Graphics::DrawRect2D(const Vec2i& InP0, const Vec2i& InP1, const LinearColor& InColor)
{
	SetDrawColor(InColor);

	SDL_Rect Rect = {
		std::min(InP0.x, InP1.x),
		std::min(InP0.y, InP1.y),
		std::abs(InP1.x - InP0.x) + 1,
		std::abs(InP1.y - InP0.y) + 1
	};

	CHECK((SDL_RenderDrawRect(Renderer, &Rect) == 0), SDL_GetError());
}

void Graphics::DrawRect2D(const Vec2i& InCenterPosition, int32_t InWidth, int32_t InHeight, const LinearColor& InColor)
{
	Vec2i P0, P1;

	P0.x = static_cast<int32_t>(InCenterPosition.x - (InWidth  / 2));
	P0.y = static_cast<int32_t>(InCenterPosition.y - (InHeight / 2));

	P1.x = static_cast<int32_t>(InCenterPosition.x + (InWidth  / 2));
	P1.y = static_cast<int32_t>(InCenterPosition.y + (InHeight / 2));

	DrawRect2D(P0, P1, InColor);
}

void Graphics::DrawFillRect2D(const Vec2i& InP0, const Vec2i& InP1, const LinearColor& InColor)
{
	SetDrawColor(InColor);

	SDL_Rect Rect = {
		std::min(InP0.x, InP1.x),
		std::min(InP0.y, InP1.y),
		std::abs(InP1.x - InP0.x) + 1,
		std::abs(InP1.y - InP0.y) + 1
	};

	CHECK((SDL_RenderFillRect(Renderer, &Rect) == 0), SDL_GetError());
}

void Graphics::DrawFillRect2D(const Vec2i& InCenterPosition, int32_t InWidth, int32_t InHeight, const LinearColor& InColor)
{
	Vec2i P0, P1;

	P0.x = static_cast<int32_t>(InCenterPosition.x - (InWidth  / 2));
	P0.y = static_cast<int32_t>(InCenterPosition.y - (InHeight / 2));

	P1.x = static_cast<int32_t>(InCenterPosition.x + (InWidth  / 2));
	P1.y = static_cast<int32_t>(InCenterPosition.y + (InHeight / 2));

	DrawFillRect2D(P0, P1, InColor);
}

void Graphics::DrawTexture2D(const std::size_t& InHashKey, const Vec2i& InCenterPosition, float InWidthScaling, float InHeightScaling)
{
	const Game::Texture2D& Texture = Game::ResourceHelper::GetTexture2D(InHashKey);

	float ScaleWidth = static_cast<float>(Texture.GetWidth()) * InWidthScaling;
	float ScaleHeight = static_cast<float>(Texture.GetHeight()) * InHeightScaling;

	SDL_Rect Rect = {
		InCenterPosition.x - static_cast<int32_t>(ScaleWidth  / 2.0f),
		InCenterPosition.y - static_cast<int32_t>(ScaleHeight / 2.0f),
		static_cast<int32_t>(ScaleWidth),
		static_cast<int32_t>(ScaleHeight)
	};

	CHECK((SDL_RenderCopy(Renderer, Texture.GetTexture(), nullptr, &Rect) == 0), SDL_GetError());
}

void Graphics::DrawText2D(const std::size_t& InHashKey, const Vec2i& InPosition, const std::wstring& InText, const LinearColor& InColor)
{
	const Game::Font& Font = Game::ResourceHelper::GetFont(InHashKey);

	int32_t x = InPosition.x;
	int32_t y = InPosition.y;

	uint8_t R = 0, G = 0, B = 0, A = 0;
	ColorHelper::ConvertLinearColorToR8G8B8A8(InColor, R, G, B, A);

	for (const auto& Unicode : InText)
	{
		SDL_Texture* Texture = Font.GetAtlas(Unicode);

		if (!Texture) continue;

		CHECK((SDL_SetTextureColorMod(Texture, R, G, B) == 0), SDL_GetError());
		CHECK((SDL_SetTextureAlphaMod(Texture, A) == 0), SDL_GetError());

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

		CHECK((SDL_RenderCopy(Renderer, Texture, &Src, &Dst) == 0), SDL_GetError());
		x += static_cast<int32_t>(Info.xadvance);
	}
}

void Graphics::SetDrawColor(const LinearColor& InColor)
{
	uint8_t R = 0, G = 0, B = 0, A = 0;
	ColorHelper::ConvertLinearColorToR8G8B8A8(InColor, R, G, B, A);
	SetDrawColor(R, G, B, A);
}

void Graphics::SetDrawColor(uint8_t InRed, uint8_t InGreen, uint8_t InBlue, uint8_t InAlpha)
{
	CHECK((SDL_SetRenderDrawColor(Renderer, InRed, InGreen, InBlue, InAlpha) == 0), SDL_GetError());
}