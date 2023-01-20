#include "PrimitiveShader.h"

PrimitiveShader::PrimitiveShader(ID3D11Device* Device, const std::wstring& VertexShaderSourcePath, const std::wstring& PixelShaderSourcePath)
{
	std::vector<D3D11_INPUT_ELEMENT_DESC> InputLayoutElements = {
		{ "POSITION", 0,    DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{    "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	CHECK_HR(CreateVertexShaderFromFile(Device, VertexShaderSourcePath), "failed to create vertex shader");
	CHECK_HR(CreatePixelShaderFromFile(Device, PixelShaderSourcePath), "failed to create pixel shader");
	CHECK_HR(CreateInputLayout(Device, InputLayoutElements), "failed to create input layout");
	CHECK_HR(CreateEveryFrameConstantBuffer(Device), "failed to every frame constant buffer");

	EveryFrameBufferResource_.World.Identify();
	EveryFrameBufferResource_.View.Identify();
	EveryFrameBufferResource_.Projection.Identify();

	std::vector<PrimitiveVertex> Vertices = {
		{ Vec3f(-0.5f, -0.5f, 0.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f) },
		{ Vec3f(+0.0f, +0.5f, 0.0f), Vec4f(0.0f, 1.0f, 0.0f, 1.0f) },
		{ Vec3f(+0.5f, -0.5f, 0.0f), Vec4f(0.0f, 0.0f, 1.0f, 1.0f) }
	};

	std::vector<uint32_t> Indices = {
		0, 1, 2
	};

	PrimitiveVertex_["Triangle"] = Vertices;
	PrimitiveIndex_["Triangle"] = Indices;

	CHECK_HR(CreateVertexBuffer(Device, PrimitiveVertex_["Triangle"], &PrimitiveVertexBuffer_["Triangle"]), "failed to create vertex buffer");
	CHECK_HR(CreateIndexBuffer(Device, PrimitiveIndex_["Triangle"], &PrimitiveIndexBuffer_["Triangle"]), "failed to create index buffer");
}

PrimitiveShader::~PrimitiveShader()
{
	for (auto& VertexBuffer : PrimitiveVertexBuffer_)
	{
		SAFE_RELEASE(VertexBuffer.second);
	}

	for (auto& IndexBuffer : PrimitiveIndexBuffer_)
	{
		SAFE_RELEASE(IndexBuffer.second);
	}

	SAFE_RELEASE(EveryFramBuffer_);
	SAFE_RELEASE(InputLayout_);
}

void PrimitiveShader::Draw(ID3D11DeviceContext* Context)
{
	uint32_t Stride = sizeof(PrimitiveVertex);
	uint32_t Offset = 0;

	Context->IASetVertexBuffers(0, 1, &PrimitiveVertexBuffer_["Triangle"], &Stride, &Offset);
	Context->IASetIndexBuffer(PrimitiveIndexBuffer_["Triangle"], DXGI_FORMAT_R32_UINT, 0);
	Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Context->IASetInputLayout(InputLayout_);

	Context->VSSetShader(VertexShader_, nullptr, 0);
	Context->PSSetShader(PixelShader_, nullptr, 0);

	D3D11_MAPPED_SUBRESOURCE MappedResource;

	if (SUCCEEDED(Context->Map(EveryFramBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource)))
	{
		EveryFramConstantBuffer* Buffer = reinterpret_cast<EveryFramConstantBuffer*>(MappedResource.pData);

		Buffer->World = EveryFrameBufferResource_.World;
		Buffer->View = EveryFrameBufferResource_.View;
		Buffer->Projection = EveryFrameBufferResource_.Projection;

		Context->Unmap(EveryFramBuffer_, 0);
	}

	uint32_t BindSlot = 0;
	Context->VSSetConstantBuffers(BindSlot, 1, &EveryFramBuffer_);

	Context->DrawIndexed(static_cast<uint32_t>(PrimitiveIndex_["Triangle"].size()), 0, 0);
}

HRESULT PrimitiveShader::CreateEveryFrameConstantBuffer(ID3D11Device* Device)
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

HRESULT PrimitiveShader::CreateVertexBuffer(ID3D11Device* Device, const std::vector<PrimitiveVertex>& Vertices, ID3D11Buffer** VertexBuffer)
{
	D3D11_BUFFER_DESC VertexBufferDesc = {};

	VertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	VertexBufferDesc.ByteWidth = sizeof(PrimitiveVertex) * static_cast<uint32_t>(Vertices.size());
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

HRESULT PrimitiveShader::CreateIndexBuffer(ID3D11Device* Device, const std::vector<uint32_t>& Indices, ID3D11Buffer** IndexBuffer)
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