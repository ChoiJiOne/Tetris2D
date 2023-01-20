#include "PrimitiveShader.h"

PrimitiveShader::PrimitiveShader(ID3D11Device* Device, const std::wstring& VertexShaderSourcePath, const std::wstring& PixelShaderSourcePath)
	: Shader(Device, VertexShaderSourcePath, PixelShaderSourcePath)
{
	std::vector<D3D11_INPUT_ELEMENT_DESC> InputLayout = {
		{ "POSITION", 0,    DXGI_FORMAT_R32G32B32_FLOAT, 0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{    "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	CHECK_HR(CreateInputLayout(Device, InputLayout), "failed to create input layout");
	CHECK_HR(CreateEveryFrameConstantBuffer(Device), "failed to every frame constant buffer");
}

PrimitiveShader::~PrimitiveShader()
{
	SAFE_RELEASE(EveryFramBuffer_);
	SAFE_RELEASE(InputLayout_);
}

HRESULT PrimitiveShader::CreateInputLayout(ID3D11Device* Device, const std::vector<D3D11_INPUT_ELEMENT_DESC>& InputLayout)
{
	return Device->CreateInputLayout(
		&InputLayout[0],
		static_cast<uint32_t>(InputLayout.size()),
		VertexShaderSource_->GetBufferPointer(),
		VertexShaderSource_->GetBufferSize(),
		&InputLayout_
	);
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
