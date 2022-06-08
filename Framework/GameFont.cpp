#include "Macro.h"
#include "GameFont.h"

GameFont::~GameFont()
{
}

void GameFont::CreateGameFont(SDL_Renderer* InRenderer, const std::string& InPath, float InSize)
{
	if (!bIsInitialize)
	{
		std::vector<uint8_t> Buffer;
		stbtt_fontinfo FontInfo;

		LoadTrueTypeFont(InPath, Buffer, FontInfo);

		AsciiTextureAtlas.CreateCharacterTextureAtlas(InRenderer, Buffer, InSize, 0x20, 0x7E);
		HangulTextureAtlas.CreateCharacterTextureAtlas(InRenderer, Buffer, InSize, 0xAC00, 0xD7AF);

		bIsInitialize = true;
	}
}

SDL_Texture* GameFont::GetAtlas(const wchar_t& InUnicode) const
{
	int32_t Code = static_cast<int32_t>(InUnicode);

	if (Code >= 0x20 && Code <= 0x7E)
	{
		return AsciiTextureAtlas.GetTextureAtlas();
	}
	else if (Code >= 0xAC00 && Code <= 0xD7AF)
	{
		return HangulTextureAtlas.GetTextureAtlas();
	}
	else
	{
		return nullptr;
	}
}

const stbtt_packedchar& GameFont::GetPackedchar(const wchar_t& InUnicode) const
{
	int32_t Code = static_cast<int32_t>(InUnicode);

	if (Code >= 0x20 && Code <= 0x7E)
	{
		return AsciiTextureAtlas.GetPackedchars()[Code - 0x20];
	}
	else if (Code >= 0xAC00 && Code <= 0xD7AF)
	{
		return HangulTextureAtlas.GetPackedchars()[Code - 0xAC00];
	}
	else
	{
		return AsciiTextureAtlas.GetPackedchars()[0];
	}
}

void GameFont::LoadTrueTypeFont(const std::string& InPath, std::vector<uint8_t>& OutBuffer, stbtt_fontinfo& OutFontInfo)
{
	OutBuffer.resize(1 << 25);

	FILE* File = nullptr;

	CHECK_FAILED((fopen_s(&File, InPath.c_str(), "rb") == 0), "failed to call fopen_s");

	fread(&OutBuffer[0], 1, 1 << 25, File);
	fclose(File);

	bool bSuccess = stbtt_InitFont(
		&OutFontInfo,
		reinterpret_cast<const unsigned char*>(&OutBuffer[0]),
		stbtt_GetFontOffsetForIndex(reinterpret_cast<const unsigned char*>(&OutBuffer[0]), 0)
	) != 0 ? true : false;

	CHECK_FAILED((bSuccess), "failed to call stbtt_InitFont");
}

CharacterTextureAtlas::~CharacterTextureAtlas()
{
	if (TextureAtlas)
	{
		SDL_DestroyTexture(TextureAtlas);
		TextureAtlas = nullptr;
	}
}

void CharacterTextureAtlas::CreateCharacterTextureAtlas(SDL_Renderer* InRenderer, const std::vector<uint8_t>& InBuffer, float InSize, int32_t InStartUnicode, int32_t InEndUnicode)
{
	if (TextureAtlas)
	{
		SDL_DestroyTexture(TextureAtlas);
		TextureAtlas = nullptr;
	}

	StartUnicode = InStartUnicode;
	EndUnicode = InEndUnicode;

	Packedchars.resize(InEndUnicode - InStartUnicode + 1);

	CreateCharacterTextureAtlas(InRenderer, InBuffer, InSize);
}

void CharacterTextureAtlas::CreateCharacterTextureAtlas(SDL_Renderer* InRenderer, const std::vector<uint8_t>& InBuffer, float InSize)
{
	int32_t Success = 0;
	stbtt_pack_context PackContext;
	std::unique_ptr<uint8_t[]> Bitmap = nullptr;

	
	for (int32_t TextureSize = 16; TextureSize < 8192; TextureSize *= 2)
	{
		Bitmap = std::make_unique<uint8_t[]>(TextureSize * TextureSize);

		Success = stbtt_PackBegin(&PackContext, Bitmap.get(), TextureSize, TextureSize, 0, 1, nullptr);
		CHECK_FAILED((Success == 1), "failed to stbtt_PackBegin");

		Success = stbtt_PackFontRange(
			&PackContext, 
			reinterpret_cast<const unsigned char*>(&InBuffer[0]), 
			0, 
			InSize, 
			StartUnicode, 
			static_cast<int>(Packedchars.size()), 
			&Packedchars[0]
		);

		if (Success)
		{
			stbtt_PackEnd(&PackContext);
			TextureAtlasSize = TextureSize;
			break;
		}
		else
		{
			stbtt_PackEnd(&PackContext);
			Bitmap.reset();
		}
	}

	CHECK_FAILED((Success == 1), "failed to create character texture atlas");


	auto pixels = std::make_unique<uint32_t[]>(TextureAtlasSize * TextureAtlasSize);
	TextureAtlas = SDL_CreateTexture(InRenderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, TextureAtlasSize, TextureAtlasSize);
	SDL_SetTextureBlendMode(TextureAtlas, SDL_BLENDMODE_BLEND);
	SDL_PixelFormat* format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);


	for (int32_t index = 0; index < TextureAtlasSize * TextureAtlasSize; ++index)
	{
		pixels[index] = SDL_MapRGBA(format, 0xFF, 0xFF, 0xFF, Bitmap[index]);
	}


	CHECK_SDL_FAILED((SDL_UpdateTexture(TextureAtlas, nullptr, pixels.get(), TextureAtlasSize * sizeof(uint32_t)) == 0));
	SDL_FreeFormat(format);
}
