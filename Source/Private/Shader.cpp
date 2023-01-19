#include "Shader.h"

#include <d3dcompiler.h>

Shader::Shader(ID3D11Device* Device, const std::wstring& VertexShaderSourcePath, const std::wstring& PixelShaderSourcePath)
{
	CHECK_HR(CreateVertexShaderFromFile(Device, VertexShaderSourcePath), "failed to create vertex shader");
	CHECK_HR(CreatePixelShaderFromFile(Device, PixelShaderSourcePath), "failed to create pixel shader");
}

Shader::~Shader()
{
	SAFE_RELEASE(VertexShader_);
	SAFE_RELEASE(PixelShader_);
}

void Shader::Bind(ID3D11DeviceContext* Context)
{
	Context->VSSetShader(VertexShader_, nullptr, 0);
	Context->PSSetShader(PixelShader_, nullptr, 0);
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
	ID3DBlob* VSBlob = nullptr;

	HR = CompileShaderFromFile(SourcePath, "main", "vs_4_0_level_9_3", &VSBlob);

	if (SUCCEEDED(HR))
	{
		HR = Device->CreateVertexShader(VSBlob->GetBufferPointer(), VSBlob->GetBufferSize(), nullptr, &VertexShader_);
	}

	SAFE_RELEASE(VSBlob);
	
	return HR;
}

HRESULT Shader::CreatePixelShaderFromFile(ID3D11Device* Device, const std::wstring& SourcePath)
{
	HRESULT HR = S_OK;
	ID3DBlob* PSBlob = nullptr;

	HR = CompileShaderFromFile(SourcePath, "main", "ps_4_0_level_9_3", &PSBlob);

	if (SUCCEEDED(HR))
	{
		HR = Device->CreatePixelShader(PSBlob->GetBufferPointer(), PSBlob->GetBufferSize(), nullptr, &PixelShader_);
	}

	SAFE_RELEASE(PSBlob);

	return HR;
}
