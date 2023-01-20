#include "Shader.h"

#include <d3dcompiler.h>

Shader::~Shader()
{
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
	HRESULT HR = S_OK;

	HR = CompileShaderFromFile(SourcePath, "main", "ps_4_0_level_9_3", &PixelShaderSource_);

	if (SUCCEEDED(HR))
	{
		HR = Device->CreatePixelShader(PixelShaderSource_->GetBufferPointer(), PixelShaderSource_->GetBufferSize(), nullptr, &PixelShader_);
	}

	return HR;
}
