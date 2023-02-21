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
	CHECK_HR(CreateDynamicConstantBuffer<EveryFramConstantBuffer>(Device, &EveryFrameBuffer_), "failed to every frame constant buffer");
	CHECK_HR(CreateDynamicConstantBuffer<TextColorConstantBuffer>(Device, &TextColorBuffer_), "failed to text color constant buffer");
	CHECK_HR(CreateLinearTextureSampler(Device, &LinearSampler_), "failed to create texture sampler");

	EveryFrameBufferResource_.Projection.Identify();

	CharacterVertex_ = std::vector<CharacterVertex>(4);
	CharacterIndex_ = std::vector<uint32_t>{ 0, 1, 2, 0, 2, 3 };

	CHECK_HR(CreateDynamicVertexBuffer<CharacterVertex>(Device, CharacterVertex_, &CharacterVertexBuffer_), "failed to create vertex buffer");
	CHECK_HR(CreateIndexBuffer(Device, CharacterIndex_, &CharacterIndexBuffer_), "failed to create index buffer");
}

Text2DRenderShader::~Text2DRenderShader()
{
	SAFE_RELEASE(LinearSampler_);
	SAFE_RELEASE(CharacterIndexBuffer_);
	SAFE_RELEASE(CharacterVertexBuffer_);
	SAFE_RELEASE(TextColorBuffer_);
	SAFE_RELEASE(EveryFrameBuffer_);
}

void Text2DRenderShader::RenderText2D(ID3D11DeviceContext* Context, Font& FontResource, const std::wstring& Text, const Vec3f& Center, const Vec4f& Color)
{
	float TextWidth = 0.0f, TextHeight = 0.0f;
	FontResource.MeasureText<float>(Text, TextWidth, TextHeight);

	float AtlasSize = static_cast<float>(FontResource.GetAtlasSize());

	Vec3f Position(Center.x - TextWidth / 2.0f, Center.y - TextHeight / 2.0f, Center.z);

	for (auto& Unicode : Text)
	{
		const Glyph& UnicodeInfo = FontResource.GetGlyph(static_cast<int32_t>(Unicode));

		float UniucodeWidth = static_cast<float>(UnicodeInfo.Position1.x - UnicodeInfo.Position0.x);
		float UniucodeHeight = static_cast<float>(UnicodeInfo.Position1.y - UnicodeInfo.Position0.y);

		CharacterVertex_[0].Position = Vec3f(Position.x, Position.y - UniucodeHeight - UnicodeInfo.YOffset, Position.z);
		CharacterVertex_[0].UV = Vec2f(static_cast<float>(UnicodeInfo.Position0.x) / AtlasSize, static_cast<float>(UnicodeInfo.Position1.y) / AtlasSize);

		CharacterVertex_[1].Position = Vec3f(Position.x, Position.y - UnicodeInfo.YOffset, Position.z);
		CharacterVertex_[1].UV = Vec2f(static_cast<float>(UnicodeInfo.Position0.x) / AtlasSize, static_cast<float>(UnicodeInfo.Position0.y) / AtlasSize);

		CharacterVertex_[2].Position = Vec3f(Position.x + UniucodeWidth, Position.y - UnicodeInfo.YOffset, Position.z);
		CharacterVertex_[2].UV = Vec2f(static_cast<float>(UnicodeInfo.Position1.x) / AtlasSize, static_cast<float>(UnicodeInfo.Position0.y) / AtlasSize);

		CharacterVertex_[3].Position = Vec3f(Position.x + UniucodeWidth, Position.y - UniucodeHeight - UnicodeInfo.YOffset, Position.z);
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

		if (SUCCEEDED(Context->Map(EveryFrameBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &ConstantBufferMappedResource)))
		{
			EveryFramConstantBuffer* Buffer = reinterpret_cast<EveryFramConstantBuffer*>(ConstantBufferMappedResource.pData);

			Buffer->Projection = EveryFrameBufferResource_.Projection;

			Context->Unmap(EveryFrameBuffer_, 0);
		}

		if (SUCCEEDED(Context->Map(TextColorBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &ConstantBufferMappedResource)))
		{
			TextColorConstantBuffer* Buffer = reinterpret_cast<TextColorConstantBuffer*>(ConstantBufferMappedResource.pData);

			Buffer->TextColor = Color;

			Context->Unmap(TextColorBuffer_, 0);
		}

		uint32_t BindSlot = 0;
		Context->VSSetConstantBuffers(BindSlot, 1, &EveryFrameBuffer_);

		uint32_t SamplerBindSlot = 0;
		Context->PSSetSamplers(SamplerBindSlot, 1, &LinearSampler_);

		uint32_t TextureBindSlot = 0;
		ID3D11ShaderResourceView* TextureAtlasView = FontResource.GetTextureAtlasView();
		Context->PSSetShaderResources(TextureBindSlot, 1, &TextureAtlasView);

		Context->PSSetConstantBuffers(BindSlot, 1, &TextColorBuffer_);

		Context->DrawIndexed(static_cast<uint32_t>(CharacterIndex_.size()), 0, 0);

		Position.x += UnicodeInfo.XAdvance;
	}
}