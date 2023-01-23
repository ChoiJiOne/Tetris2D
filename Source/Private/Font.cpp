#include "Font.h"

// @third party code - BEGIN
#include <stb/stb_rect_pack.h>
#include <stb/stb_truetype.h>
// @third party code - END

Font::Font(ID3D11Device* Device, const std::string& ResourcePath, int32_t BeginCodePoint, int32_t EndCodePoint, float FontSize)
	: BeginCodePoint_(BeginCodePoint)
	, EndCodePoint_(EndCodePoint)
{
	std::vector<uint8_t> Buffer;
	CHECK((LoadTrueTypeFontFromFile(ResourcePath, Buffer)), "failed to load trye type font");

	stbtt_fontinfo Info;
	CHECK((stbtt_InitFont(
		&Info,
		reinterpret_cast<const unsigned char*>(&Buffer[0]),
		stbtt_GetFontOffsetForIndex(reinterpret_cast<const unsigned char*>(&Buffer[0]), 0)
	) != 0), "failed to initialize stb_truetype");

	std::shared_ptr<uint8_t[]> AtlasBitmap = GenerateTextureAtlasBitmap(Buffer, BeginCodePoint_, EndCodePoint_, FontSize, CharacterInfos_, AtlasSize_);

	CHECK_HR(CreateTextureAtlasFromBitmap(Device, AtlasBitmap, AtlasSize_), "failed to create texture atlas");
}

Font::~Font()
{
	SAFE_RELEASE(TextureAtlas_);
	SAFE_RELEASE(TextureAtlasView_);
}

const CharacterInfo& Font::GetCharacterInfo(int32_t CodePoint) const
{
	CHECK(HasCodePointInRange(CodePoint), "code point is out of range");
	int32_t Index = CodePoint - BeginCodePoint_;
	return CharacterInfos_[Index];
}

bool Font::HasCodePointInRange(int32_t CodePoint) const
{
	return (BeginCodePoint_ <= CodePoint) && (CodePoint <= EndCodePoint_);
}

bool Font::LoadTrueTypeFontFromFile(const std::string& ResourcePath, std::vector<uint8_t>& Buffer)
{
	HANDLE FontFileHandle = CreateFileA(ResourcePath.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
	DWORD FileSize = GetFileSize(FontFileHandle, nullptr);
	Buffer.resize(FileSize);
	DWORD BytesRead;

	CHECK(ReadFile(FontFileHandle, &Buffer[0], FileSize, &BytesRead, NULL), "failed to read font file");
	CHECK(CloseHandle(FontFileHandle), "failed to close font file");

	return true;
}

std::shared_ptr<uint8_t[]> Font::GenerateTextureAtlasBitmap(
	const std::vector<uint8_t>& Buffer, 
	int32_t BeginCodePoint, 
	int32_t EndCodePoint, 
	float FontSize, 
	std::vector<CharacterInfo>& CharacterInfos, 
	int32_t& AtlasSize
)
{
	std::vector<stbtt_packedchar> Packedchars(EndCodePoint - BeginCodePoint + 1);
	CharacterInfos.resize(EndCodePoint - BeginCodePoint + 1);

	int32_t Success = 0;
	stbtt_pack_context PackContext;
	std::shared_ptr<uint8_t[]> Bitmap = nullptr;

	for (int32_t Size = 16; Size < 8192; Size *= 2)
	{
		Bitmap = std::make_unique<uint8_t[]>(Size * Size);
		Success = stbtt_PackBegin(&PackContext, Bitmap.get(), Size, Size, 0, 1, nullptr);
		stbtt_PackSetOversampling(&PackContext, 1, 1);

		Success = stbtt_PackFontRange(
			&PackContext,
			reinterpret_cast<const unsigned char*>(&Buffer[0]),
			0,
			FontSize,
			BeginCodePoint,
			static_cast<int>(Packedchars.size()),
			&Packedchars[0]
		);

		if (Success)
		{
			stbtt_PackEnd(&PackContext);
			AtlasSize = Size;
			break;
		}
		else
		{
			stbtt_PackEnd(&PackContext);
			Bitmap.reset();
		}
	}

	for (std::size_t Index = 0; Index < Packedchars.size(); ++Index)
	{
		CharacterInfos[Index].CodePoint = static_cast<int32_t>(Index + BeginCodePoint);

		CharacterInfos[Index].Position0 = Vec2i(Packedchars[Index].x0, Packedchars[Index].y0);
		CharacterInfos[Index].Position1 = Vec2i(Packedchars[Index].x1, Packedchars[Index].y1);

		CharacterInfos[Index].XOffset = Packedchars[Index].xoff;
		CharacterInfos[Index].YOffset = Packedchars[Index].yoff;

		CharacterInfos[Index].XOffset2 = Packedchars[Index].xoff2;
		CharacterInfos[Index].YOffset2 = Packedchars[Index].yoff2;

		CharacterInfos[Index].XAdvance = Packedchars[Index].xadvance;
	}

	return Bitmap;
}

HRESULT Font::CreateTextureAtlasFromBitmap(ID3D11Device* Device, const std::shared_ptr<uint8_t[]>& Bitmap, const int32_t& AtlasSize)
{
	HRESULT HR = S_OK;

	D3D11_TEXTURE2D_DESC TextureDesc;
	TextureDesc.Height = static_cast<uint32_t>(AtlasSize);
	TextureDesc.Width = static_cast<uint32_t>(AtlasSize);
	TextureDesc.MipLevels = 1;
	TextureDesc.ArraySize = 1;
	TextureDesc.Format = DXGI_FORMAT_R8_UNORM;
	TextureDesc.SampleDesc.Count = 1;
	TextureDesc.SampleDesc.Quality = 0;
	TextureDesc.Usage = D3D11_USAGE_DEFAULT;
	TextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	TextureDesc.CPUAccessFlags = 0;
	TextureDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA TextueBufferData;
	TextueBufferData.pSysMem = reinterpret_cast<const void*>(&Bitmap[0]);
	TextueBufferData.SysMemPitch = AtlasSize;
	TextueBufferData.SysMemSlicePitch = 0;

	HR = Device->CreateTexture2D(&TextureDesc, &TextueBufferData, &TextureAtlas_);
	if (SUCCEEDED(HR))
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC ShaderResourceViewDesc;

		ShaderResourceViewDesc.Format = DXGI_FORMAT_R8_UNORM;
		ShaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		ShaderResourceViewDesc.Texture2D.MipLevels = TextureDesc.MipLevels;
		ShaderResourceViewDesc.Texture2D.MostDetailedMip = 0;

		HR = Device->CreateShaderResourceView(
			TextureAtlas_,
			&ShaderResourceViewDesc,
			&TextureAtlasView_
		);
	}

	return HR;
}
