#include "Primitive2DRenderShader.h"

Primitive2DRenderShader::Primitive2DRenderShader(ID3D11Device* Device, const std::wstring& VertexShaderSourcePath, const std::wstring& PixelShaderSourcePath)
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

	std::vector<PrimitiveVertex> Vertices;
	std::vector<uint32_t> Indices;

	Vertices.resize(1);
	Indices = { 0 };
	PrimitiveVertex_["Point"] = Vertices;
	PrimitiveIndex_["Point"] = Indices;
	CHECK_HR(CreateVertexBuffer(Device, PrimitiveVertex_["Point"], &PrimitiveVertexBuffer_["Point"]), "failed to create vertex buffer");
	CHECK_HR(CreateIndexBuffer(Device, PrimitiveIndex_["Point"], &PrimitiveIndexBuffer_["Point"]), "failed to create index buffer");

	Vertices.resize(2);
	Indices = { 0, 1 };
	PrimitiveVertex_["Line"] = Vertices;
	PrimitiveIndex_["Line"] = Indices;
	CHECK_HR(CreateVertexBuffer(Device, PrimitiveVertex_["Line"], &PrimitiveVertexBuffer_["Line"]), "failed to create vertex buffer");
	CHECK_HR(CreateIndexBuffer(Device, PrimitiveIndex_["Line"], &PrimitiveIndexBuffer_["Line"]), "failed to create index buffer");

	Vertices.resize(3);
	Indices = { 0, 1, 2 };
	PrimitiveVertex_["Triangle"] = Vertices;
	PrimitiveIndex_["Triangle"] = Indices;
	CHECK_HR(CreateVertexBuffer(Device, PrimitiveVertex_["Triangle"], &PrimitiveVertexBuffer_["Triangle"]), "failed to create vertex buffer");
	CHECK_HR(CreateIndexBuffer(Device, PrimitiveIndex_["Triangle"], &PrimitiveIndexBuffer_["Triangle"]), "failed to create index buffer");

	Vertices.resize(3);
	Indices = { 0, 1, 1, 2, 2, 0 };
	PrimitiveVertex_["WireframeTriangle"] = Vertices;
	PrimitiveIndex_["WireframeTriangle"] = Indices;
	CHECK_HR(CreateVertexBuffer(Device, PrimitiveVertex_["WireframeTriangle"], &PrimitiveVertexBuffer_["WireframeTriangle"]), "failed to create vertex buffer");
	CHECK_HR(CreateIndexBuffer(Device, PrimitiveIndex_["WireframeTriangle"], &PrimitiveIndexBuffer_["WireframeTriangle"]), "failed to create index buffer");

	Vertices.resize(4);
	Indices = { 0, 1, 2, 0, 2, 3};
	PrimitiveVertex_["Quad"] = Vertices;
	PrimitiveIndex_["Quad"] = Indices;
	CHECK_HR(CreateVertexBuffer(Device, PrimitiveVertex_["Quad"], &PrimitiveVertexBuffer_["Quad"]), "failed to create vertex buffer");
	CHECK_HR(CreateIndexBuffer(Device, PrimitiveIndex_["Quad"], &PrimitiveIndexBuffer_["Quad"]), "failed to create index buffer");

	Vertices.resize(4);
	Indices = {0, 1, 1, 2, 2, 3, 3, 0};
	PrimitiveVertex_["WireframeQuad"] = Vertices;
	PrimitiveIndex_["WireframeQuad"] = Indices;
	CHECK_HR(CreateVertexBuffer(Device, PrimitiveVertex_["WireframeQuad"], &PrimitiveVertexBuffer_["WireframeQuad"]), "failed to create vertex buffer");
	CHECK_HR(CreateIndexBuffer(Device, PrimitiveIndex_["WireframeQuad"], &PrimitiveIndexBuffer_["WireframeQuad"]), "failed to create index buffer");
}

Primitive2DRenderShader::~Primitive2DRenderShader()
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
}

void Primitive2DRenderShader::RenderPoint(ID3D11DeviceContext* Context, const Vec3f& Position, const Vec4f& Color)
{
	PrimitiveVertex_["Point"][0].Position = Position;
	PrimitiveVertex_["Point"][0].Color = Color;

	RenderPrimitive(Context, "Point", ERenderType::POINT);
}

void Primitive2DRenderShader::RenderLine(
	ID3D11DeviceContext* Context, 
	const Vec3f& PositionFrom, const Vec4f& ColorFrom, 
	const Vec3f& PositionTo, const Vec4f& ColorTo
)
{
	PrimitiveVertex_["Line"][0].Position = PositionFrom;
	PrimitiveVertex_["Line"][0].Color = ColorFrom;

	PrimitiveVertex_["Line"][1].Position = PositionTo;
	PrimitiveVertex_["Line"][1].Color = ColorTo;

	RenderPrimitive(Context, "Line", ERenderType::LINE);
}

void Primitive2DRenderShader::RenderFillTriangle(
	ID3D11DeviceContext* Context, 
	const Vec3f& PositionFrom, const Vec4f& ColorFrom, 
	const Vec3f& PositionBy, const Vec4f& ColorBy, 
	const Vec3f& PositionTo, const Vec4f& ColorTo
)
{
	PrimitiveVertex_["Triangle"][0].Position = PositionFrom;
	PrimitiveVertex_["Triangle"][0].Color = ColorFrom;

	PrimitiveVertex_["Triangle"][1].Position = PositionBy;
	PrimitiveVertex_["Triangle"][1].Color = ColorBy;

	PrimitiveVertex_["Triangle"][2].Position = PositionTo;
	PrimitiveVertex_["Triangle"][2].Color = ColorTo;

	RenderPrimitive(Context, "Triangle", ERenderType::TRIANGLE);
}

void Primitive2DRenderShader::RenderWireframeTriangle(
	ID3D11DeviceContext* Context, 
	const Vec3f& PositionFrom, const Vec4f& ColorFrom, 
	const Vec3f& PositionBy, const Vec4f& ColorBy, 
	const Vec3f& PositionTo, const Vec4f& ColorTo
)
{
	PrimitiveVertex_["WireframeTriangle"][0].Position = PositionFrom;
	PrimitiveVertex_["WireframeTriangle"][0].Color = ColorFrom;

	PrimitiveVertex_["WireframeTriangle"][1].Position = PositionBy;
	PrimitiveVertex_["WireframeTriangle"][1].Color = ColorBy;

	PrimitiveVertex_["WireframeTriangle"][2].Position = PositionTo;
	PrimitiveVertex_["WireframeTriangle"][2].Color = ColorTo;

	RenderPrimitive(Context, "WireframeTriangle", ERenderType::LINE);
}

void Primitive2DRenderShader::RenderFillQuad(
	ID3D11DeviceContext* Context, 
	const Vec3f& PositionFrom, const Vec4f& ColorFrom, 
	const Vec3f& PositionBy0, const Vec4f& ColorBy0, 
	const Vec3f& PositionBy1, const Vec4f& ColorBy1, 
	const Vec3f& PositionTo, const Vec4f& ColorTo
)
{
	PrimitiveVertex_["Quad"][0].Position = PositionFrom;
	PrimitiveVertex_["Quad"][0].Color = ColorFrom;

	PrimitiveVertex_["Quad"][1].Position = PositionBy0;
	PrimitiveVertex_["Quad"][1].Color = ColorBy0;

	PrimitiveVertex_["Quad"][2].Position = PositionBy1;
	PrimitiveVertex_["Quad"][2].Color = ColorBy1;

	PrimitiveVertex_["Quad"][3].Position = PositionTo;
	PrimitiveVertex_["Quad"][3].Color = ColorTo;

	RenderPrimitive(Context, "Quad", ERenderType::TRIANGLE);
}

void Primitive2DRenderShader::RenderWireframeQuad(
	ID3D11DeviceContext* Context, 
	const Vec3f& PositionFrom, const Vec4f& ColorFrom, 
	const Vec3f& PositionBy0, const Vec4f& ColorBy0, 
	const Vec3f& PositionBy1, const Vec4f& ColorBy1, 
	const Vec3f& PositionTo, const Vec4f& ColorTo
)
{
	PrimitiveVertex_["WireframeQuad"][0].Position = PositionFrom;
	PrimitiveVertex_["WireframeQuad"][0].Color = ColorFrom;

	PrimitiveVertex_["WireframeQuad"][1].Position = PositionBy0;
	PrimitiveVertex_["WireframeQuad"][1].Color = ColorBy0;

	PrimitiveVertex_["WireframeQuad"][2].Position = PositionBy1;
	PrimitiveVertex_["WireframeQuad"][2].Color = ColorBy1;

	PrimitiveVertex_["WireframeQuad"][3].Position = PositionTo;
	PrimitiveVertex_["WireframeQuad"][3].Color = ColorTo;

	RenderPrimitive(Context, "WireframeQuad", ERenderType::LINE);
}

HRESULT Primitive2DRenderShader::CreateEveryFrameConstantBuffer(ID3D11Device* Device)
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

HRESULT Primitive2DRenderShader::CreateVertexBuffer(ID3D11Device* Device, const std::vector<PrimitiveVertex>& Vertices, ID3D11Buffer** VertexBuffer)
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

HRESULT Primitive2DRenderShader::CreateIndexBuffer(ID3D11Device* Device, const std::vector<uint32_t>& Indices, ID3D11Buffer** IndexBuffer)
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

void Primitive2DRenderShader::RenderPrimitive(ID3D11DeviceContext* Context, const std::string& PrimitiveSignature, const ERenderType& RenderType)
{
	D3D_PRIMITIVE_TOPOLOGY Topology;

	switch (RenderType)
	{
	case ERenderType::POINT:
		Topology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
		break;

	case ERenderType::LINE:
		Topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
		break;

	case ERenderType::TRIANGLE:
		Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		break;

	default:
		ENFORCE_THROW_EXCEPTION("undefined render type");
	}

	D3D11_MAPPED_SUBRESOURCE VertexBufferMappedResource;

	if (SUCCEEDED(Context->Map(PrimitiveVertexBuffer_[PrimitiveSignature], 0, D3D11_MAP_WRITE_DISCARD, 0, &VertexBufferMappedResource)))
	{
		PrimitiveVertex* Buffer = reinterpret_cast<PrimitiveVertex*>(VertexBufferMappedResource.pData);

		std::memcpy(
			Buffer,
			reinterpret_cast<const void*>(&PrimitiveVertex_[PrimitiveSignature][0]),
			PrimitiveVertex_[PrimitiveSignature].size() * sizeof(PrimitiveVertex)
		);

		Context->Unmap(PrimitiveVertexBuffer_[PrimitiveSignature], 0);
	}

	uint32_t Stride = sizeof(PrimitiveVertex);
	uint32_t Offset = 0;

	Context->IASetVertexBuffers(0, 1, &PrimitiveVertexBuffer_[PrimitiveSignature], &Stride, &Offset);
	Context->IASetIndexBuffer(PrimitiveIndexBuffer_[PrimitiveSignature], DXGI_FORMAT_R32_UINT, 0);
	Context->IASetPrimitiveTopology(Topology);

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

	Context->DrawIndexed(static_cast<uint32_t>(PrimitiveIndex_[PrimitiveSignature].size()), 0, 0);
}