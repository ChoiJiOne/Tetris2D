#include "Texture2D.h"

#include <array>

// @third party code - BEGIN
#include <stb/stb_image.h>
#include <stb/stb_image_resize.h>
// @third party code - END

std::array<int32_t, 10> Texture2D::Resolutions_ = {
	16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192 
};

Texture2D::Texture2D(ID3D11Device* Device, const std::string& ResourcePath)
{
	std::vector<uint8_t> Buffer;
	int32_t TextureFormat = 0, TextureWidth = 0, TextureHeight = 0;

	CHECK(LoadTextureFromFile(ResourcePath, Buffer, TextureFormat, TextureWidth, TextureHeight), "failed to load texture file");
	CHECK_HR(CreateTextureResource(Device, Buffer, TextureFormat, TextureWidth, TextureHeight), "failed to create texture resource");
}

Texture2D::~Texture2D()
{
	SAFE_RELEASE(Texture_);
	SAFE_RELEASE(TextureView_);
}

bool Texture2D::LoadTextureFromFile(const std::string& ResourcePath, std::vector<uint8_t>& Buffer, int32_t& Format, int32_t& Width, int32_t& Height)
{
	uint8_t* ResourceBuffer = stbi_load(ResourcePath.c_str(), &Width, &Height, &Format, STBI_rgb_alpha);

	if (!ResourceBuffer) return false;

	std::size_t BufferSize = Width * Height * Format;
	Buffer.resize(BufferSize);
	std::copy(ResourceBuffer, ResourceBuffer + BufferSize, &Buffer[0]);

	stbi_image_free(ResourceBuffer);
	ResourceBuffer = nullptr;

	bool bIsResizeBuffer = true;
	if (Width == Height)
	{
		for (std::size_t Index = 0; Index < Resolutions_.size(); ++Index)
		{
			if (Resolutions_[Index] == Width)
			{
				bIsResizeBuffer = false;
			}
		}
	}

	bool bIsSuccessed = true;
	if (bIsResizeBuffer)
	{
		std::vector<uint8_t> NewResizeBuffer;
		int32_t NewWidth = 0, NewHeight = 0;

		bIsSuccessed = ResizeTextureBuffer(Buffer, Width, Height, NewResizeBuffer, NewWidth, NewHeight);

		Buffer = NewResizeBuffer;
		Width = NewWidth;
		Height = NewHeight;
	}

	return bIsSuccessed;
}

HRESULT Texture2D::CreateTextureResource(ID3D11Device* Device, std::vector<uint8_t>& Buffer, int32_t Format, int32_t Width, int32_t Height)
{
	HRESULT HR = S_OK;

	D3D11_TEXTURE2D_DESC TextureDesc;
	TextureDesc.Height = static_cast<uint32_t>(Width);
	TextureDesc.Width = static_cast<uint32_t>(Height);
	TextureDesc.MipLevels = 1;
	TextureDesc.ArraySize = 1;
	TextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	TextureDesc.SampleDesc.Count = 1;
	TextureDesc.SampleDesc.Quality = 0;
	TextureDesc.Usage = D3D11_USAGE_DEFAULT;
	TextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	TextureDesc.CPUAccessFlags = 0;
	TextureDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA TextueBufferData;
	TextueBufferData.pSysMem = reinterpret_cast<const void*>(&Buffer[0]);
	TextueBufferData.SysMemPitch = Width * Format;
	TextueBufferData.SysMemSlicePitch = 0;

	HR = Device->CreateTexture2D(&TextureDesc, &TextueBufferData, &Texture_);
	if (SUCCEEDED(HR))
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC ShaderResourceViewDesc;

		ShaderResourceViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		ShaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		ShaderResourceViewDesc.Texture2D.MipLevels = TextureDesc.MipLevels;
		ShaderResourceViewDesc.Texture2D.MostDetailedMip = 0;

		HR = Device->CreateShaderResourceView(
			Texture_,
			&ShaderResourceViewDesc,
			&TextureView_
		);
	}

	return HR;
}

Texture2D::EResolution Texture2D::GetResolutionFromSize(int32_t Width, int32_t Height)
{
	int32_t TextureSize = (Width > Height) ? Width : Height;
	EResolution TextureResolution = EResolution::SIZE_8192X8192;

	for (std::size_t Index = 0; Index < Resolutions_.size() - 1; ++Index)
	{
		if (Resolutions_[Index] <= TextureSize && TextureSize <= Resolutions_[Index + 1])
		{
			int32_t Diff0 = TextureSize - Resolutions_[Index];
			int32_t Diff1 = Resolutions_[Index + 1] - TextureSize;

			TextureResolution = (Diff0 < Diff1) ? static_cast<EResolution>(Resolutions_[Index]) : static_cast<EResolution>(Resolutions_[Index + 1]);
			break;
		}
	}
	
	return TextureResolution;
}

bool Texture2D::ResizeTextureBuffer(std::vector<uint8_t>& OldBuffer, int32_t OldWidth, int32_t OldHeight, std::vector<uint8_t>& NewBuffer, int32_t& NewWidth, int32_t& NewHeight)
{
	EResolution TextureResolution = GetResolutionFromSize(OldWidth, OldHeight);

	NewWidth = static_cast<int32_t>(TextureResolution);
	NewHeight = static_cast<int32_t>(TextureResolution);

	NewBuffer.resize(NewWidth * NewHeight * STBI_rgb_alpha);

	int32_t Success = stbir_resize_uint8(
		&OldBuffer[0], OldWidth, OldHeight, 0,
		&NewBuffer[0], NewWidth, NewHeight, 0,
		STBI_rgb_alpha
	);

	return (Success != 0);
}
