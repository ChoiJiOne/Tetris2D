#include "Texture2D.h"

// @third party code - BEGIN
#include <stb/stb_image.h>
// @third party code - END

Texture2D::Texture2D(ID3D11Device* Device, const std::string& ResourcePath)
{
	std::vector<uint8_t> Buffer;
	int32_t Format = 0, Width = 0, Height = 0;

	CHECK(LoadTextureFromFile(ResourcePath, Buffer, Format, Width, Height), "failed to load texture file");
	CHECK_HR(CreateTextureResource(Device, Buffer, Format, Width, Height), "failed to create texture resource");
}

Texture2D::~Texture2D()
{
	SAFE_RELEASE(Texture_);
	SAFE_RELEASE(TextureView_);
}

bool Texture2D::LoadTextureFromFile(const std::string& ResourcePath, std::vector<uint8_t>& Buffer, int32_t& Format, int32_t& Width, int32_t& Height)
{
	uint8_t* ResourceBuffer = stbi_load(ResourcePath.c_str(), &Width, &Height, &Format, 0);

	if (!ResourceBuffer) return false;

	std::size_t BufferSize = Width * Height * Format;
	Buffer.resize(BufferSize);
	std::copy(ResourceBuffer, ResourceBuffer + BufferSize, &Buffer[0]);

	stbi_image_free(ResourceBuffer);
	ResourceBuffer = nullptr;

	return true;
}

HRESULT Texture2D::CreateTextureResource(ID3D11Device* Device, std::vector<uint8_t>& Buffer, int32_t Format, int32_t Width, int32_t Height)
{
	HRESULT HR = S_OK;

	D3D11_TEXTURE2D_DESC TextureDesc;
	TextureDesc.Height = static_cast<uint32_t>(Width);
	TextureDesc.Width = static_cast<uint32_t>(Height);
	TextureDesc.MipLevels = 0;
	TextureDesc.ArraySize = 1;
	TextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	TextureDesc.SampleDesc.Count = 1;
	TextureDesc.SampleDesc.Quality = 0;
	TextureDesc.Usage = D3D11_USAGE_DEFAULT;
	TextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	TextureDesc.CPUAccessFlags = 0;
	TextureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

	D3D11_SUBRESOURCE_DATA TextueBufferData;
	TextueBufferData.pSysMem = reinterpret_cast<const void*>(&Buffer[0]);
	TextueBufferData.SysMemPitch = Width * Format;

	HR = Device->CreateTexture2D(&TextureDesc, &TextueBufferData, &Texture_);
	if (SUCCEEDED(HR))
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC ShaderResourceViewDesc = {};

		ShaderResourceViewDesc.Format = TextureDesc.Format;
		ShaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		ShaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
		ShaderResourceViewDesc.Texture2D.MipLevels = -1;

		HR = Device->CreateShaderResourceView(
			Texture_,
			&ShaderResourceViewDesc,
			&TextureView_
		);
	}

	return HR;
}
