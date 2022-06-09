#include <stb/stb_image.h>

#include "Macro.h"
#include "GameTexture2D.h"

GameTexture2D::~GameTexture2D()
{
	if (Texture)
	{
		SDL_DestroyTexture(Texture);
		Texture = nullptr;
	}
}

void GameTexture2D::CreateTextureFromFile(SDL_Renderer* InRenderer, const std::string& InPath)
{
	uint8_t* Buffer = nullptr;

	LoadTextureBufferFromFile(InPath, Buffer, Width, Height, PixelFormat);
	Texture = CreateTextureFromBuffer(InRenderer, Buffer, Width, Height, PixelFormat);

	SDL_SetTextureBlendMode(Texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(Texture, 0xFF);

	stbi_image_free(Buffer);
}

void GameTexture2D::LoadTextureBufferFromFile(const std::string& InPath, uint8_t*& OutBuffer, int32_t& OutWidth, int32_t& OutHeight, int32_t& OutFormat)
{
	OutBuffer = stbi_load(InPath.c_str(), &OutWidth, &OutHeight, &OutFormat, 0);
	CHECK_FAILED((OutBuffer != nullptr), StringUtil::StringFormat("failed to load texture : %s", stbi_failure_reason()).c_str());
}

SDL_Texture* GameTexture2D::CreateTextureFromBuffer(SDL_Renderer* InRenderer, uint8_t*& InBuffer, const int32_t& InWidth, const int32_t& InHeight, const int32_t& InFormat)
{
	uint32_t TextureFormat;

	switch (InFormat)
	{
	case PIXEL_FORMAT_RGBA32:
		TextureFormat = SDL_PIXELFORMAT_ABGR8888;
		break;

	case PIXEL_FORMAT_RGB24:
		TextureFormat = SDL_PIXELFORMAT_BGR888;
		break;

	default:
		ENFORCE_THROW_EXCEPTION("not support pixel format");
		break;
	}

	SDL_Texture* SDLTexture = SDL_CreateTexture(InRenderer, TextureFormat, SDL_TEXTUREACCESS_STATIC, InWidth, InHeight);

	CHECK_SDL_FAILED((SDLTexture != nullptr));

	if (SDL_UpdateTexture(SDLTexture, nullptr, InBuffer, InWidth * InFormat) != 0)
	{
		SDL_DestroyTexture(SDLTexture);
		SDLTexture = nullptr;

		ENFORCE_THROW_EXCEPTION("failed to update texture");
	}

	return SDLTexture;
}