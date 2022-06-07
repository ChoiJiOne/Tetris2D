#include "Macro.h"
#include "GameTexture2D.h"

GameTexture2D::GameTexture2D(SDL_Renderer* InRenderer, const std::string& InPath)
{
	SDL_Surface* TextureSurface = IMG_Load(InPath.c_str());
	CHECK_SDL_FAILED((TextureSurface != nullptr));

	Texture = SDL_CreateTextureFromSurface(InRenderer, TextureSurface);

	Width = TextureSurface->w;
	Height = TextureSurface->h;

	SDL_FreeSurface(TextureSurface);
	TextureSurface = nullptr;

	CHECK_SDL_FAILED((Texture != nullptr));

	SDL_SetTextureBlendMode(Texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(Texture, 0xFF);
}

GameTexture2D::~GameTexture2D()
{
	if (Texture)
	{
		SDL_DestroyTexture(Texture);
		Texture = nullptr;
	}
}