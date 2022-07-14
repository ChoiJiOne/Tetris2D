// @third party code - BEGIN SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
// @third party code - END

#include "Macro.h"
#include "TTFont.h"

Game::UnicodeTextureAtlas::~UnicodeTextureAtlas()
{
	if (TextureAtlas)
	{
		SDL_DestroyTexture(TextureAtlas);
		TextureAtlas = nullptr;
	}
}

void Game::UnicodeTextureAtlas::Initialize(SDL_Renderer* InRenderer, const std::vector<uint8_t>& InTTFBuffer, float InSize, int32_t InStartUnicode, int32_t InEndUnicode)
{
	if (TextureAtlas)
	{
		Packedchars.resize(0);

		SDL_DestroyTexture(TextureAtlas);
		TextureAtlas = nullptr;
	}

	StartUnicode = InStartUnicode;
	EndUnicode = InEndUnicode;
	FontSize = InSize;

	GenerateUnicodeTextureAtlas(InRenderer, InTTFBuffer, TextureAtlas, Packedchars, TextureAtlasSize);
}

bool Game::UnicodeTextureAtlas::IsUnicodeInRange(const wchar_t& InUnicode) const
{
	int32_t Code = static_cast<int32_t>(InUnicode);
	return (StartUnicode <= Code && Code <= EndUnicode);
}

void Game::UnicodeTextureAtlas::GenerateUnicodeTextureAtlas(
	SDL_Renderer*                  InRenderer,
	const std::vector<uint8_t>&    InTTFBuffer,
	SDL_Texture*&                  OutTextureAtlas,
	std::vector<stbtt_packedchar>& OutPackedchars,
	int32_t&                       OutTextureSize
)
{
	std::size_t UnicodeRange = EndUnicode - StartUnicode + 1;
	OutPackedchars.resize(UnicodeRange);

	int32_t Success = 0;
	stbtt_pack_context PackContext;
	std::unique_ptr<uint8_t[]> Bitmap = nullptr;

	for (int32_t TextureSize = 16; TextureSize < 8192; TextureSize *= 2)
	{
		Bitmap = std::make_unique<uint8_t[]>(TextureSize * TextureSize);

		Success = stbtt_PackBegin(&PackContext, Bitmap.get(), TextureSize, TextureSize, 0, 1, nullptr);
		CHECK((Success == 1), "failed to stbtt_PackBegin");

		Success = stbtt_PackFontRange(
			&PackContext,
			reinterpret_cast<const unsigned char*>(&InTTFBuffer[0]),
			0,
			FontSize,
			StartUnicode,
			static_cast<int>(OutPackedchars.size()),
			&OutPackedchars[0]
		);

		if (Success)
		{
			stbtt_PackEnd(&PackContext);
			OutTextureSize = TextureSize;
			break;
		}
		else
		{
			stbtt_PackEnd(&PackContext);
			Bitmap.reset();
		}
	}

	CHECK((Success == 1), "failed to create character texture atlas");


	auto pixels = std::make_unique<uint32_t[]>(OutTextureSize * OutTextureSize);
	OutTextureAtlas = SDL_CreateTexture(InRenderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, OutTextureSize, OutTextureSize);
	SDL_SetTextureBlendMode(OutTextureAtlas, SDL_BLENDMODE_BLEND);
	SDL_PixelFormat* format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);


	for (int32_t index = 0; index < OutTextureSize * OutTextureSize; ++index)
	{
		pixels[index] = SDL_MapRGBA(format, 0xFF, 0xFF, 0xFF, Bitmap[index]);
	}


	CHECK((SDL_UpdateTexture(OutTextureAtlas, nullptr, pixels.get(), OutTextureSize * sizeof(uint32_t)) == 0), SDL_GetError());
	SDL_FreeFormat(format);
}

Game::TTFont::~TTFont()
{
	AsciiTextureAtlas.reset();
	HangulTextureAtlas.reset();
}

void Game::TTFont::Initialize(SDL_Renderer* InRenderer, const std::string& InPath, float InFontSize)
{
	if (AsciiTextureAtlas && HangulTextureAtlas)
	{
		AsciiTextureAtlas.reset();
		HangulTextureAtlas.reset();
	}

	std::vector<uint8_t> Buffer;
	stbtt_fontinfo FontInfo;

	FontSize = InFontSize;
	LoadTrueTypeFontFromFile(InPath, Buffer, FontInfo);

	AsciiTextureAtlas = std::make_unique<UnicodeTextureAtlas>();
	AsciiTextureAtlas->Initialize(InRenderer, Buffer, FontSize, 0x20, 0x7E);

	HangulTextureAtlas = std::make_unique<UnicodeTextureAtlas>();
	HangulTextureAtlas->Initialize(InRenderer, Buffer, FontSize, 0xAC00, 0xD7AF);
}

SDL_Texture* Game::TTFont::GetTextureAtlas(const wchar_t& InUnicode) const
{
	int32_t Code = static_cast<int32_t>(InUnicode);

	if (AsciiTextureAtlas->IsUnicodeInRange(InUnicode))
	{
		return AsciiTextureAtlas->GetTextureAtlas();
	}
	else if (HangulTextureAtlas->IsUnicodeInRange(InUnicode))
	{
		return HangulTextureAtlas->GetTextureAtlas();
	}
	else
	{
		return nullptr;
	}
}

const stbtt_packedchar& Game::TTFont::GetPackedchar(const wchar_t& InUnicode) const
{
	int32_t Code = static_cast<int32_t>(InUnicode);

	if (AsciiTextureAtlas->IsUnicodeInRange(InUnicode))
	{
		return AsciiTextureAtlas->GetPackedchars()[Code - AsciiTextureAtlas->GetStartUnicode()];
	}
	else if (HangulTextureAtlas->IsUnicodeInRange(InUnicode))
	{
		return HangulTextureAtlas->GetPackedchars()[Code - HangulTextureAtlas->GetStartUnicode()];
	}
	else
	{
		return AsciiTextureAtlas->GetPackedchars()[0];
	}
}

void Game::TTFont::LoadTrueTypeFontFromFile(const std::string& InPath, std::vector<uint8_t>& OutBuffer, stbtt_fontinfo& OutFontInfo)
{
	OutBuffer.resize(1 << 25);

	FILE* File = nullptr;

	CHECK((fopen_s(&File, InPath.c_str(), "rb") == 0), "failed to call fopen_s");

	fread(&OutBuffer[0], 1, 1 << 25, File);
	fclose(File);

	bool bSuccess = stbtt_InitFont(
		&OutFontInfo,
		reinterpret_cast<const unsigned char*>(&OutBuffer[0]),
		stbtt_GetFontOffsetForIndex(reinterpret_cast<const unsigned char*>(&OutBuffer[0]), 0)
	) != 0 ? true : false;

	CHECK((bSuccess), "failed to call stbtt_InitFont");
}