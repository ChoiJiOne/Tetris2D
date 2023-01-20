#pragma once

#include "Vector.hpp"
#include "Matrix.hpp"
#include "Shader.h"

#include <vector>


/**
 * @brief 기본 도형을 렌더링하는 셰이더입니다.
 */
class PrimitiveShader : public Shader
{
public:
	/**
	 * @brief 기본 도형 타입입니다.
	 */
	enum class PrimitiveType
	{
		NONE     = 0,
		POINT    = 1,
		LINE     = 2,
		TRIANGLE = 3,
		QUAD     = 4
	};


	/**
	 * @brief 매 프레임 변경되는 셰이더 내의 상수 버퍼입니다.
	 */
	struct EveryFramConstantBuffer
	{
		Matrix4x4F World;
		Matrix4x4F View;
		Matrix4x4F Projection;
	};


public:
	/**
	 * @brief 셰이더를 컴파일하고 정점 셰이더와 픽셀 셰이더를 생성합니다.
	 *
	 * @param Device 셰이더 리소스를 생성할 때 사용할 디바이스입니다.
	 * @param VertexShaderSourcePath 정점 셰이더 소스 파일의 경로입니다.
	 * @param PixelShaderSourcePath 픽셀 셰이더 소스 파일의 경로입니다.
	 *
	 * @throws
	 * 셰이더 컴파일에 실패하면 C++ 표준 예외를 던집니다.
	 * 셰이더 리소스 생성에 실패하면 C++ 표준 예외를 던집니다.
	 */
	PrimitiveShader(ID3D11Device* Device, const std::wstring& VertexShaderSourcePath, const std::wstring& PixelShaderSourcePath);
	

	/**
	 * @brief 기본 도형을 렌더링하는 셰이더의 가상 소멸자입니다.
	 */
	virtual ~PrimitiveShader();


	/**
	 * @brief 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(PrimitiveShader);


	/**
	 * @brief 셰이더 및 렌더링에 필요한 요소를 파이프라인에 바인딩합니다.
	 */


private:
	/**
	 * @brief 정점 셰이더에 전달할 정점 데이터를 생성합니다.
	 * 
	 * @param Device 정점 데이터를 생성할 때 사용할 디바이스입니다.
	 * @param InputLayout 정점 셰이더에 전달할 정점 데이터 정보입니다.
	 * 
	 * @return 정점 데이터 생성 결과를 반환합니다. 생성에 성공하면 S_OK, 그렇지 않다면 그 이외의 값을 반환합니다.
	 */
	HRESULT CreateInputLayout(ID3D11Device* Device, const std::vector<D3D11_INPUT_ELEMENT_DESC>& InputLayout);


	/**
	 * @brief 매 프레임 사용할 상수 버퍼를 생성합니다.
	 * 
	 * @param Device 버퍼를 생성할 때 사용할 디바이스입니다.
	 * 
	 * @return 버퍼 생성 결과를 반환합니다. 생성에 성공하면 S_OK, 그렇지 않으면 그 이외의 값을 반환합니다.
	 */
	HRESULT CreateEveryFrameConstantBuffer(ID3D11Device* Device);


private:
	/**
	 * @brief 렌더링 파이프라인의 정점 데이터를 정의합니다.
	 * 
	 * @note https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11inputlayout
	 */
	ID3D11InputLayout* InputLayout_ = nullptr;


	/**
	 * @brief 셰이더 내의 상수 버퍼입니다.
	 */
	ID3D11Buffer* EveryFramBuffer_ = nullptr;
};