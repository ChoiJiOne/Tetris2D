#pragma once

#include "Macro.h"

#include <d3d11.h>


/**
 * @brief ���̴� ���� ����� �����մϴ�.
 */
class Shader
{
public:
	/**
	 * @brief ���̴� Ŭ������ ����Ʈ �������Դϴ�.
	 */
	Shader() = default;


	/**
	 * @brief ���̴� Ŭ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Shader();


	/**
	 * @brief ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Shader);


protected:
	/**
	 * @brief ���̴��� �������մϴ�.
	 * 
	 * @see https://learn.microsoft.com/en-us/windows/win32/api/d3dcompiler/nf-d3dcompiler-d3dcompilefromfile
	 * 
	 * @note https://github.com/walbourn/directx-sdk-samples/blob/main/Direct3D11Tutorials/Tutorial07/Tutorial07.cpp#L177
	 * 
	 * @param SourcePath ���̴� �ҽ� ������ ����Դϴ�.
	 * @param EntryPoint ���̴��� �������Դϴ�.
	 * @param ShaderModel ���̴��� ��� �����Դϴ�.
	 * @param Blob �����ϵ� ���̴� ���ҽ��Դϴ�.
	 * 
	 * @return ���̴� ������ ����� ��ȯ�մϴ�. �����Ͽ� �����ߴٸ� S_OK, �׷��� �ʴٸ� �� �̿��� ���� ��ȯ�մϴ�.
	 */
	HRESULT CompileShaderFromFile(const std::wstring& SourcePath, const std::string& EntryPoint, const std::string& ShaderModel, ID3DBlob** Blob);


	/**
	 * @brief ���� ���̴� �ҽ��κ��� ���� ���̴� ���ҽ��� �����մϴ�.
	 * 
	 * @param Device ���̴� ������ �ʿ��� ����̽��Դϴ�.
	 * @param SourcePath ���� ���̴� �ҽ��� ����Դϴ�.
	 * 
	 * @return ���̴� ���ҽ� ���� ����� ��ȯ�մϴ�. ������ �����ߴٸ� S_OK, �׷��� �ʴٸ� �� �̿��� ���� ��ȯ�մϴ�.
	 */
	HRESULT CreateVertexShaderFromFile(ID3D11Device* Device, const std::wstring& SourcePath);


	/**
	 * @brief �ȼ� ���̴� �ҽ��κ��� ���� ���̴� ���ҽ��� �����մϴ�.
	 *
	 * @param Device ���̴� ������ �ʿ��� ����̽��Դϴ�. 
	 * @param SourcePath �ȼ� ���̴� �ҽ��� ����Դϴ�.
	 *
	 * @return ���̴� ���ҽ� ���� ����� ��ȯ�մϴ�. ������ �����ߴٸ� S_OK, �׷��� �ʴٸ� �� �̿��� ���� ��ȯ�մϴ�.
	 */
	HRESULT CreatePixelShaderFromFile(ID3D11Device* Device, const std::wstring& SourcePath);


	/**
	 * @brief ���� ���̴��� ������ ���� �����͸� �����մϴ�.
	 *
	 * @note �� �޼��带 ȣ���ϱ� ���� ���� ���̴��� ������ �Ǿ�� �մϴ�.
	 *
	 * @param Device ���� �����͸� ������ �� ����� ����̽��Դϴ�.
	 * @param InputLayoutElements ���� ���̴��� ������ ���� ������ �����Դϴ�.
	 *
	 * @return ���� ������ ���� ����� ��ȯ�մϴ�. ������ �����ϸ� S_OK, �׷��� �ʴٸ� �� �̿��� ���� ��ȯ�մϴ�.
	 */
	HRESULT CreateInputLayout(ID3D11Device* Device, const std::vector<D3D11_INPUT_ELEMENT_DESC>& InputLayoutElements);


protected:
	/**
	 * @brief ���� ���̴� �ҽ� ���ҽ��Դϴ�.
	 */
	ID3DBlob* VertexShaderSource_ = nullptr;

	
	/**
	 * @brief ���� ���̴� ���ҽ��Դϴ�.
	 */
	ID3D11VertexShader* VertexShader_ = nullptr;


	/**
	 * @brief �ȼ� ���̴� �ҽ� ���ҽ��Դϴ�.
	 */
	ID3DBlob* PixelShaderSource_ = nullptr;


	/**
	 * @brief �ȼ� ���̴� ���ҽ��Դϴ�.
	 */
	ID3D11PixelShader* PixelShader_ = nullptr;


	/**
	 * @brief ������ ������������ ���� �����͸� �����մϴ�.
	 * 
	 * @note https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11inputlayout
	 */
	ID3D11InputLayout* InputLayout_ = nullptr;
};