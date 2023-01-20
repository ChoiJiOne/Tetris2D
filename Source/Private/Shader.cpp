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

HRESULT Shader::CreateVertexShaderFromFile(ID3D11Device* Device, const std::wstring& SourcePath, ID3DBlob** VSBlob, ID3D11VertexShader** VertexShader)
{
	HRESULT HR = S_OK;

	HR = CompileShaderFromFile(SourcePath, "main", "vs_4_0_level_9_3", VSBlob);

	if (SUCCEEDED(HR))
	{
		HR = Device->CreateVertexShader((*VSBlob)->GetBufferPointer(), (*VSBlob)->GetBufferSize(), nullptr, VertexShader);
	}
	
	return HR;
}

HRESULT Shader::CreatePixelShaderFromFile(ID3D11Device* Device, const std::wstring& SourcePath, ID3DBlob** PSBlob, ID3D11PixelShader** PixelShader)
{
	HRESULT HR = S_OK;

	HR = CompileShaderFromFile(SourcePath, "main", "ps_4_0_level_9_3", PSBlob);

	if (SUCCEEDED(HR))
	{
		HR = Device->CreatePixelShader((*PSBlob)->GetBufferPointer(), (*PSBlob)->GetBufferSize(), nullptr, PixelShader);
	}

	return HR;
}

HRESULT Shader::CreateInputLayout(ID3D11Device* Device, const std::vector<D3D11_INPUT_ELEMENT_DESC>& InputLayoutElements, ID3D11InputLayout** InputLayout)
{
	return Device->CreateInputLayout(
		&InputLayoutElements[0],
		static_cast<uint32_t>(InputLayoutElements.size()),
		VertexShaderSource_->GetBufferPointer(),
		VertexShaderSource_->GetBufferSize(),
		InputLayout
	);
}
