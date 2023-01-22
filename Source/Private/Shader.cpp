#include "Shader.h"

#include <d3dcompiler.h>

Shader::~Shader()
{
	SAFE_RELEASE(InputLayout_);
	SAFE_RELEASE(VertexShaderSource_);
	SAFE_RELEASE(VertexShader_);
	SAFE_RELEASE(PixelShaderSource_);
	SAFE_RELEASE(PixelShader_);
}

HRESULT Shader::CompileShaderFromFile(const std::wstring& SourcePath, const std::string& EntryPoint, const std::string& ShaderModel, ID3DBlob** Blob)
{
	HRESULT HR = S_OK;

	DWORD ShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined(DEBUG) || defined(_DEBUG)
	ShaderFlags |= D3DCOMPILE_DEBUG;
	ShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	HR = D3DCompileFromFile(
		SourcePath.c_str(),
		nullptr, 
		nullptr, 
		EntryPoint.c_str(),
		ShaderModel.c_str(),
		ShaderFlags,
		0, 
		Blob, 
		nullptr
	);

	return HR;
}

HRESULT Shader::CreateVertexShaderFromFile(ID3D11Device* Device, const std::wstring& SourcePath)
{
	SAFE_RELEASE(VertexShaderSource_);
	SAFE_RELEASE(VertexShader_);

	HRESULT HR = S_OK;

	HR = CompileShaderFromFile(SourcePath, "main", "vs_4_0_level_9_3", &VertexShaderSource_);

	if (SUCCEEDED(HR))
	{
		HR = Device->CreateVertexShader(VertexShaderSource_->GetBufferPointer(), VertexShaderSource_->GetBufferSize(), nullptr, &VertexShader_);
	}
	
	return HR;
}

HRESULT Shader::CreatePixelShaderFromFile(ID3D11Device* Device, const std::wstring& SourcePath)
{
	SAFE_RELEASE(PixelShaderSource_);
	SAFE_RELEASE(PixelShader_);

	HRESULT HR = S_OK;

	HR = CompileShaderFromFile(SourcePath, "main", "ps_4_0_level_9_3", &PixelShaderSource_);

	if (SUCCEEDED(HR))
	{
		HR = Device->CreatePixelShader(PixelShaderSource_->GetBufferPointer(), PixelShaderSource_->GetBufferSize(), nullptr, &PixelShader_);
	}

	return HR;
}

HRESULT Shader::CreateInputLayout(ID3D11Device* Device, const std::vector<D3D11_INPUT_ELEMENT_DESC>& InputLayoutElements)
{
	SAFE_RELEASE(InputLayout_);

	return Device->CreateInputLayout(
		&InputLayoutElements[0],
		static_cast<uint32_t>(InputLayoutElements.size()),
		VertexShaderSource_->GetBufferPointer(),
		VertexShaderSource_->GetBufferSize(),
		&InputLayout_
	);
}

HRESULT Shader::CreateIndexBuffer(ID3D11Device* Device, const std::vector<uint32_t>& Indices, ID3D11Buffer** IndexBuffer)
{
	D3D11_BUFFER_DESC IndexBufferDesc;

	IndexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
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

HRESULT Shader::CreateLinearTextureSampler(ID3D11Device* Device, ID3D11SamplerState** LinearTextureSampler)
{
	D3D11_SAMPLER_DESC TextureSamplerDesc = { };

	TextureSamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	TextureSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	TextureSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	TextureSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	TextureSamplerDesc.MipLODBias = 0.0f;
	TextureSamplerDesc.MaxAnisotropy = 1;
	TextureSamplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	TextureSamplerDesc.BorderColor[0] = 0;
	TextureSamplerDesc.BorderColor[1] = 0;
	TextureSamplerDesc.BorderColor[2] = 0;
	TextureSamplerDesc.BorderColor[3] = 0;
	TextureSamplerDesc.MinLOD = 0;
	TextureSamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	return Device->CreateSamplerState(&TextureSamplerDesc, LinearTextureSampler);
}
