#include "Macro.h"
#include "GameRenderer.h"

GameRenderer::GameRenderer(SDL_Window* InWindow)
{
	Renderer = SDL_CreateRenderer(InWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	CHECK_SDL_FAILED((Renderer != nullptr));
}

GameRenderer::~GameRenderer()
{
	if (Renderer)
	{
		SDL_DestroyRenderer(Renderer);
		Renderer = nullptr;
	}
}

void GameRenderer::BeginFrame(uint8_t InRed, uint8_t InGreen, uint8_t InBlue, uint8_t InAlpha)
{
	SetDrawColor(InRed, InGreen, InBlue, InAlpha);
	CHECK_SDL_FAILED((SDL_RenderClear(Renderer) == 0));
}

void GameRenderer::EndFrame()
{
	SDL_RenderPresent(Renderer);
}

void GameRenderer::SetDrawColor(uint8_t InRed, uint8_t InGreen, uint8_t InBlue, uint8_t InAlpha)
{
	CHECK_SDL_FAILED((SDL_SetRenderDrawColor(Renderer, InRed, InGreen, InBlue, InAlpha) == 0));
}
