#include "Text2DRenderShader.h"
#include "Font.h"

Text2DRenderShader::Text2DRenderShader(ID3D11Device* Device, const std::wstring& VertexShaderSourcePath, const std::wstring& PixelShaderSourcePath)
{
	std::vector<D3D11_INPUT_ELEMENT_DESC> InputLayoutElements = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0,    DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	CHECK_HR(CreateVertexShaderFromFile(Device, VertexShaderSourcePath), "failed to create vertex shader");
	CHECK_HR(CreatePixelShaderFromFile(Device, PixelShaderSourcePath), "failed to create pixel shader");
	CHECK_HR(CreateInputLayout(Device, InputLayoutElements), "failed to create input layout");
	CHECK_HR(CreateEveryFrameConstantBuffer(Device), "failed to every frame constant buffer");
	CHECK_HR(CreateTextureSampler(Device), "failed to create texture sampler");

	EveryFrameBufferResource_.World.Identify();
	EveryFrameBufferResource_.View.Identify();
	EveryFrameBufferResource_.Projection.Identify();

	CharacterVertex_ = std::vector<CharacterVertex>(4);
	CharacterIndex_ = std::vector<uint32_t>{ 0, 1, 2, 0, 2, 3 };

	CHECK_HR(CreateVertexBuffer(Device, CharacterVertex_, &CharacterVertexBuffer_), "failed to create vertex buffer");
	CHECK_HR(CreateIndexBuffer(Device, CharacterIndex_, &CharacterIndexBuffer_), "failed to create index buffer");
}

Text2DRenderShader::~Text2DRenderShader()
{
	SAFE_RELEASE(LinearSampler_);
	SAFE_RELEASE(CharacterIndexBuffer_);
	SAFE_RELEASE(CharacterVertexBuffer_);
	SAFE_RELEASE(EveryFramBuffer_);
}

void Text2DRenderShader::RenderText2D(ID3D11DeviceContext* Context, Font& FontResource, const std::wstring& Text, const Vec3f& Center)
{
	float TextWidth = 0.0f, TextHeight = 0.0f;
	FontResource.MeasureText<float>(Text, TextWidth, TextHeight);

	float AtlasSize = static_cast<float>(FontResource.GetAtlasSize());

	Vec3f Position(Center.x - TextWidth / 2.0f, Center.y + TextHeight / 2.0f, Center.z);

	for (auto& Unicode : Text)
	{
		const CharacterInfo& UnicodeInfo = FontResource.GetCharacterInfo(static_cast<int32_t>(Unicode));

		float UniucodeWidth = static_cast<float>(UnicodeInfo.Position1.x - UnicodeInfo.Position0.x);
		float UniucodeHeight = static_cast<float>(UnicodeInfo.Position1.y - UnicodeInfo.Position0.y);

		CharacterVertex_[0].Position = Vec3f(Position.x, Position.y + UniucodeHeight, Position.z);
		CharacterVertex_[0].UV = Vec2f(static_cast<float>(UnicodeInfo.Position0.x) / AtlasSize, static_cast<float>(UnicodeInfo.Position1.y) / AtlasSize);

		CharacterVertex_[1].Position = Vec3f(Position.x, Position.y, Position.z);
		CharacterVertex_[1].UV = Vec2f(static_cast<float>(UnicodeInfo.Position0.x) / AtlasSize, static_cast<float>(UnicodeInfo.Position0.y) / AtlasSize);

		CharacterVertex_[2].Position = Vec3f(Position.x + UniucodeWidth, Position.y, Position.z);
		CharacterVertex_[2].UV = Vec2f(static_cast<float>(UnicodeInfo.Position1.x) / AtlasSize, static_cast<float>(UnicodeInfo.Position0.y) / AtlasSize);

		CharacterVertex_[3].Position = Vec3f(Position.x + UniucodeWidth, Position.y + UniucodeHeight, Position.z);
		CharacterVertex_[3].UV = Vec2f(static_cast<float>(UnicodeInfo.Position1.x) / AtlasSize, static_cast<float>(UnicodeInfo.Position1.y) / AtlasSize);

		D3D11_MAPPED_SUBRESOURCE VertexBufferMappedResource;

		if (SUCCEEDED(Context->Map(CharacterVertexBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &VertexBufferMappedResource)))
		{
			CharacterVertex* Buffer = reinterpret_cast<CharacterVertex*>(VertexBufferMappedResource.pData);

			std::memcpy(
				Buffer,
				reinterpret_cast<const void*>(&CharacterVertex_[0]),
				CharacterVertex_.size() * sizeof(CharacterVertex)
			);

			Context->Unmap(CharacterVertexBuffer_, 0);
		}

		uint32_t Stride = sizeof(CharacterVertex);
		uint32_t Offset = 0;

		Context->IASetVertexBuffers(0, 1, &CharacterVertexBuffer_, &Stride, &Offset);
		Context->IASetIndexBuffer(CharacterIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);
		Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		Context->IASetInputLayout(InputLayout_);

		Context->VSSetShader(VertexShader_, nullptr, 0);
		Context->PSSetShader(PixelShader_, nullptr, 0);

		D3D11_MAPPED_SUBRESOURCE ConstantBufferMappedResource;

		if (SUCCEEDED(Context->Map(EveryFramBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &ConstantBufferMappedResource)))
		{
			EveryFramConstantBuffer* Buffer = reinterpret_cast<EveryFramConstantBuffer*>(ConstantBufferMappedResource.pData);

			Buffer->World = EveryFrameBufferResource_.World;
			Buffer->View = EveryFrameBufferResource_.View;
			Buffer->Projection = EveryFrameBufferResource_.Projection;

			Context->Unmap(EveryFramBuffer_, 0);
		}

		uint32_t BindSlot = 0;
		Context->VSSetConstantBuffers(BindSlot, 1, &EveryFramBuffer_);

		uint32_t SamplerBindSlot = 0;
		Context->PSSetSamplers(SamplerBindSlot, 1, &LinearSampler_);

		uint32_t TextureBindSlot = 0;
		ID3D11ShaderResourceView* TextureAtlasView = FontResource.GetTextureAtlasView();
		Context->PSSetShaderResources(TextureBindSlot, 1, &TextureAtlasView);

		Context->DrawIndexed(static_cast<uint32_t>(CharacterIndex_.size()), 0, 0);

		Position.x += UnicodeInfo.XAdvance;
	}
}

HRESULT Text2DRenderShader::CreateEveryFrameConstantBuffer(ID3D11Device* Device)
{
	D3D11_BUFFER_DESC EveryFrameBufferDesc = {};

	EveryFrameBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	EveryFrameBufferDesc.ByteWidth = sizeof(EveryFramConstantBuffer);
	EveryFrameBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	EveryFrameBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	EveryFrameBufferDesc.MiscFlags = 0;
	EveryFrameBufferDesc.StructureByteStride = 0;

	return Device->CreateBuffer(&EveryFrameBufferDesc, nullptr, &EveryFramBuffer_);
}

HRESULT Text2DRenderShader::CreateVertexBuffer(ID3D11Device* Device, const std::vector<CharacterVertex>& Vertices, ID3D11Buffer** VertexBuffer)
{
	D3D11_BUFFER_DESC VertexBufferDesc = {};

	VertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	VertexBufferDesc.ByteWidth = sizeof(CharacterVertex) * static_cast<uint32_t>(Vertices.size());
	VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	VertexBufferDesc.MiscFlags = 0;
	VertexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA VertexData;
	VertexData.pSysMem = reinterpret_cast<const void*>(&Vertices[0]);
	VertexData.SysMemPitch = 0;
	VertexData.SysMemSlicePitch = 0;

	return Device->CreateBuffer(&VertexBufferDesc, &VertexData, VertexBuffer);
}

HRESULT Text2DRenderShader::CreateIndexBuffer(ID3D11Device* Device, const std::vector<uint32_t>& Indices, ID3D11Buffer** IndexBuffer)
{
	D3D11_BUFFER_DESC IndexBufferDesc;

	IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	IndexBufferDesc.ByteWidth = sizeof(uint32_t) * static_cast<uint32_t>(Indices.size());
	IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IndexBufferDesc.CPUAccessFlags = 0;
	IndexBufferDesc.MiscFlags = 0;
	IndexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA IndexData;
	IndexData.pSysMem = reinterpret_cast<const void*>(&Indices[0]);
	IndexData.SysMemPitch = 0;
	IndexData.SysMemSlicePitch = 0;

	return Device->CreateBuffer(&IndexBufferDesc, &IndexData, IndexBuffer);
}

HRESULT Text2DRenderShader::CreateTextureSampler(ID3D11Device* Device)
{
	D3D11_SAMPLER_DESC SamplerDesc = { };

	SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.MipLODBias = 0.0f;
	SamplerDesc.MaxAnisotropy = 1;
	SamplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	SamplerDesc.BorderColor[0] = 0;
	SamplerDesc.BorderColor[1] = 0;
	SamplerDesc.BorderColor[2] = 0;
	SamplerDesc.BorderColor[3] = 0;
	SamplerDesc.MinLOD = 0;
	SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	return Device->CreateSamplerState(&SamplerDesc, &LinearSampler_);
}
