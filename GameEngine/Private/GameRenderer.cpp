#include "../Public/Macro.h"
#include "../Public/GameFont.h"
#include "../Public/GameTexture2D.h"
#include "../Public/GameRenderer.h"

GameRenderer::~GameRenderer()
{
	if (Renderer)
	{
		SDL_DestroyRenderer(Renderer);
		Renderer = nullptr;
	}
}

void GameRenderer::Init(SDL_Window* InWindow)
{
	if (!bIsInitialize)
	{
		Renderer = SDL_CreateRenderer(InWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		CHECK_SDL_FAILED((Renderer != nullptr));

		bIsInitialize = true;
	}
}

void GameRenderer::BeginFrame(const LinearColor& InColor)
{
	SetDrawColor(InColor);
	CHECK_SDL_FAILED((SDL_RenderClear(Renderer) == 0));
}

void GameRenderer::EndFrame()
{
	SDL_RenderPresent(Renderer);
}

void GameRenderer::DrawPoint2D(const Vec2i& InPosition, const LinearColor& InColor)
{
	SetDrawColor(InColor);
	CHECK_SDL_FAILED((SDL_RenderDrawPoint(Renderer, InPosition.x, InPosition.y) == 0));
}

void GameRenderer::DrawLine2D(const Vec2i& InP0, const Vec2i& InP1, const LinearColor& InColor)
{
	SetDrawColor(InColor);
	CHECK_SDL_FAILED((SDL_RenderDrawLine(Renderer, InP0.x, InP0.y, InP1.x, InP1.y) == 0));
}

void GameRenderer::DrawWireframeRectangle2D(const Vec2i& InP0, const Vec2i& InP1, const LinearColor& InColor)
{
	SetDrawColor(InColor);

	SDL_Rect Rect = {
		std::min(InP0.x, InP1.x),
		std::min(InP0.y, InP1.y),
		std::abs(InP1.x - InP0.x),
		std::abs(InP1.y - InP0.y)
	};

	CHECK_SDL_FAILED((SDL_RenderDrawRect(Renderer, &Rect) == 0));
}

void GameRenderer::DrawWireframeRectangle2D(const Vec2i& InCenterPosition, int32_t InWidth, int32_t InHeight, const LinearColor& InColor)
{
	Vec2i P0, P1;

	P0.x = static_cast<int32_t>(InCenterPosition.x - (InWidth / 2));
	P0.y = static_cast<int32_t>(InCenterPosition.y - (InHeight / 2));

	P1.x = static_cast<int32_t>(InCenterPosition.x + (InWidth / 2));
	P1.y = static_cast<int32_t>(InCenterPosition.y + (InHeight / 2));

	DrawWireframeRectangle2D(P0, P1, InColor);
}

void GameRenderer::DrawRectangle2D(const Vec2i& InP0, const Vec2i& InP1, const LinearColor& InColor)
{
	SetDrawColor(InColor);

	SDL_Rect Rect = {
		std::min(InP0.x, InP1.x),
		std::min(InP0.y, InP1.y),
		std::abs(InP1.x - InP0.x),
		std::abs(InP1.y - InP0.y)
	};

	CHECK_SDL_FAILED((SDL_RenderFillRect(Renderer, &Rect) == 0));
}

void GameRenderer::DrawRectangle2D(const Vec2i& InCenterPosition, int32_t InWidth, int32_t InHeight, const LinearColor& InColor)
{
	Vec2i P0, P1;

	P0.x = static_cast<int32_t>(InCenterPosition.x - (InWidth / 2));
	P0.y = static_cast<int32_t>(InCenterPosition.y - (InHeight / 2));

	P1.x = static_cast<int32_t>(InCenterPosition.x + (InWidth / 2));
	P1.y = static_cast<int32_t>(InCenterPosition.y + (InHeight / 2));

	DrawRectangle2D(P0, P1, InColor);
}

void GameRenderer::DrawTexture2D(const GameTexture2D& InTexture, const Vec2i& InCenterPosition, float InWidthScaling, float InHeightScaling)
{
	float Width = static_cast<float>(InTexture.GetWidth()) * InWidthScaling;
	float Height = static_cast<float>(InTexture.GetHeight()) * InHeightScaling;

	SDL_Rect Rect = {
		InCenterPosition.x - InTexture.GetWidth() / 2,
		InCenterPosition.y - InTexture.GetHeight() / 2,
		static_cast<int32_t>(Width),
		static_cast<int32_t>(Height)
	};

	CHECK_SDL_FAILED((SDL_RenderCopy(Renderer, InTexture.GetTexture(), nullptr, &Rect) == 0));
}

void GameRenderer::DrawText2D(const GameFont& InFont, const Vec2i& InPosition, const std::wstring& InText, const LinearColor& InColor)
{
	int32_t x = InPosition.x;
	int32_t y = InPosition.y;

	uint8_t R = static_cast<uint8_t>(MathUtil::Clamp<float>(InColor.x, 0.0f, 1.0f) * 255.0f);
	uint8_t G = static_cast<uint8_t>(MathUtil::Clamp<float>(InColor.y, 0.0f, 1.0f) * 255.0f);
	uint8_t B = static_cast<uint8_t>(MathUtil::Clamp<float>(InColor.z, 0.0f, 1.0f) * 255.0f);
	uint8_t A = static_cast<uint8_t>(MathUtil::Clamp<float>(InColor.w, 0.0f, 1.0f) * 255.0f);

	for (const auto& Unicode : InText)
	{
		SDL_Texture* Texture = InFont.GetAtlas(Unicode);

		if (!Texture) continue;

		SDL_SetTextureColorMod(Texture, R, G, B);
		SDL_SetTextureAlphaMod(Texture, A);

		const stbtt_packedchar& Info = InFont.GetPackedchar(Unicode);

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
			y + static_cast<int32_t>(Info.yoff),
			(Info.x1 - Info.x0),
			(Info.y1 - Info.y0)
		};

		SDL_RenderCopy(Renderer, Texture, &Src, &Dst);
		x += static_cast<int32_t>(Info.xadvance);
	}
}

void GameRenderer::SetDrawColor(const LinearColor& InColor)
{
	uint8_t R = 0, G = 0, B = 0, A = 0;
	ColorUtil::ConvertLinearColorToR8G8B8A8(InColor, R, G, B, A);
	SetDrawColor(R, G, B, A);
}

void GameRenderer::SetDrawColor(uint8_t InRed, uint8_t InGreen, uint8_t InBlue, uint8_t InAlpha)
{
	CHECK_SDL_FAILED((SDL_SetRenderDrawColor(Renderer, InRed, InGreen, InBlue, InAlpha) == 0));
}
