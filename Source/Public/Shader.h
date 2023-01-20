#pragma once

#include "Macro.h"

#include <d3d11.h>


/**
 * @brief 셰이더 관련 기능을 제공합니다.
 */
class Shader
{
public:
	/**
	 * @brief 셰이더 클래스의 디폴트 생성자입니다.
	 */
	Shader() = default;


	/**
	 * @brief 셰이더 클래스의 가상 소멸자입니다.
	 */
	virtual ~Shader();


	/**
	 * @brief 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Shader);


protected:
	/**
	 * @brief 셰이더를 컴파일합니다.
	 * 
	 * @see https://learn.microsoft.com/en-us/windows/win32/api/d3dcompiler/nf-d3dcompiler-d3dcompilefromfile
	 * 
	 * @note https://github.com/walbourn/directx-sdk-samples/blob/main/Direct3D11Tutorials/Tutorial07/Tutorial07.cpp#L177
	 * 
	 * @param SourcePath 셰이더 소스 파일의 경로입니다.
	 * @param EntryPoint 셰이더의 진입점입니다.
	 * @param ShaderModel 셰이더의 기능 집합입니다.
	 * @param Blob 컴파일된 셰이더 리소스입니다.
	 * 
	 * @return 셰이더 컴파일 결과를 반환합니다. 컴파일에 성공했다면 S_OK, 그렇지 않다면 그 이외의 값을 반환합니다.
	 */
	HRESULT CompileShaderFromFile(const std::wstring& SourcePath, const std::string& EntryPoint, const std::string& ShaderModel, ID3DBlob** Blob);


	/**
	 * @brief 정점 셰이더 소스로부터 정점 셰이더 리소스를 생성합니다.
	 * 
	 * @param Device 셰이더 생성에 필요한 디바이스입니다.
	 * @param SourcePath 정점 셰이더 소스의 경로입니다.
	 * 
	 * @return 셰이더 리소스 생성 결과를 반환합니다. 생성에 성공했다면 S_OK, 그렇지 않다면 그 이외의 값을 반환합니다.
	 */
	HRESULT CreateVertexShaderFromFile(ID3D11Device* Device, const std::wstring& SourcePath);


	/**
	 * @brief 픽셀 셰이더 소스로부터 정점 셰이더 리소스를 생성합니다.
	 *
	 * @param Device 셰이더 생성에 필요한 디바이스입니다. 
	 * @param SourcePath 픽셀 셰이더 소스의 경로입니다.
	 *
	 * @return 셰이더 리소스 생성 결과를 반환합니다. 생성에 성공했다면 S_OK, 그렇지 않다면 그 이외의 값을 반환합니다.
	 */
	HRESULT CreatePixelShaderFromFile(ID3D11Device* Device, const std::wstring& SourcePath);


protected:
	/**
	 * @brief 정점 셰이더 소스 리소스입니다.
	 */
	ID3DBlob* VertexShaderSource_ = nullptr;

	
	/**
	 * @brief 정점 셰이더 리소스입니다.
	 */
	ID3D11VertexShader* VertexShader_ = nullptr;


	/**
	 * @brief 픽셀 셰이더 소스 리소스입니다.
	 */
	ID3DBlob* PixelShaderSource_ = nullptr;


	/**
	 * @brief 픽셀 셰이더 리소스입니다.
	 */
	ID3D11PixelShader* PixelShader_ = nullptr;
};