#include "Texture2DRenderShader.h"
#include "Texture2D.h"

Texture2DRenderShader::Texture2DRenderShader(ID3D11Device* Device, const std::wstring& VertexShaderSourcePath, const std::wstring& PixelShaderSourcePath)
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

	QuadTextureVertex_ = std::vector<QuadTextureVertex>(4);
	QuadTextureIndex_ = std::vector<uint32_t>{ 0, 1, 2, 0, 2, 3 };

	CHECK_HR(CreateVertexBuffer(Device, QuadTextureVertex_, &QuadTextureVertexBuffer_), "failed to create vertex buffer");
	CHECK_HR(CreateIndexBuffer(Device, QuadTextureIndex_, &QuadTextureIndexBuffer_), "failed to create index buffer");
}

Texture2DRenderShader::~Texture2DRenderShader()
{
	SAFE_RELEASE(LinearSampler_);
	SAFE_RELEASE(QuadTextureIndexBuffer_);
	SAFE_RELEASE(QuadTextureVertexBuffer_);
	SAFE_RELEASE(EveryFramBuffer_);
}

void Texture2DRenderShader::RenderTexture2D(ID3D11DeviceContext* Context, Texture2D& Texture, const Vec3f& Center, float Width, float Height)
{
	QuadTextureVertex_[0].Position = Vec3f(Center.x - Width / 2.0f, Center.y - Height / 2.0f, Center.z);
	QuadTextureVertex_[0].UV = Vec2f(0.0f, 1.0f);

	QuadTextureVertex_[1].Position = Vec3f(Center.x - Width / 2.0f, Center.y + Height / 2.0f, Center.z);
	QuadTextureVertex_[1].UV = Vec2f(0.0f, 0.0f);

	QuadTextureVertex_[2].Position = Vec3f(Center.x + Width / 2.0f, Center.y + Height / 2.0f, Center.z);
	QuadTextureVertex_[2].UV = Vec2f(1.0f, 0.0f);
	
	QuadTextureVertex_[3].Position = Vec3f(Center.x + Width / 2.0f, Center.y - Height / 2.0f, Center.z);
	QuadTextureVertex_[3].UV = Vec2f(1.0f, 1.0f);

	D3D11_MAPPED_SUBRESOURCE VertexBufferMappedResource;

	if (SUCCEEDED(Context->Map(QuadTextureVertexBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &VertexBufferMappedResource)))
	{
		QuadTextureVertex* Buffer = reinterpret_cast<QuadTextureVertex*>(VertexBufferMappedResource.pData);

		std::memcpy(
			Buffer,
			reinterpret_cast<const void*>(&QuadTextureVertex_[0]),
			QuadTextureVertex_.size() * sizeof(QuadTextureVertex)
		);

		Context->Unmap(QuadTextureVertexBuffer_, 0);
	}

	uint32_t Stride = sizeof(QuadTextureVertex);
	uint32_t Offset = 0;

	Context->IASetVertexBuffers(0, 1, &QuadTextureVertexBuffer_, &Stride, &Offset);
	Context->IASetIndexBuffer(QuadTextureIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);
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
	ID3D11ShaderResourceView* TextureView = Texture.GetTextureView();
	Context->PSSetShaderResources(TextureBindSlot, 1, &TextureView);

	Context->DrawIndexed(static_cast<uint32_t>(QuadTextureIndex_.size()), 0, 0);
}

HRESULT Texture2DRenderShader::CreateEveryFrameConstantBuffer(ID3D11Device* Device)
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

HRESULT Texture2DRenderShader::CreateVertexBuffer(ID3D11Device* Device, const std::vector<QuadTextureVertex>& Vertices, ID3D11Buffer** VertexBuffer)
{
	D3D11_BUFFER_DESC VertexBufferDesc = {};

	VertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	VertexBufferDesc.ByteWidth = sizeof(QuadTextureVertex) * static_cast<uint32_t>(Vertices.size());
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

HRESULT Texture2DRenderShader::CreateIndexBuffer(ID3D11Device* Device, const std::vector<uint32_t>& Indices, ID3D11Buffer** IndexBuffer)
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

HRESULT Texture2DRenderShader::CreateTextureSampler(ID3D11Device* Device)
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
