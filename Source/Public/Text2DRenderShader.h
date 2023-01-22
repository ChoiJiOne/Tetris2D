#pragma once

#include "Vector.hpp"
#include "Matrix.hpp"
#include "Shader.h"

class Font;


/**
 * @brief 2D 텍스트를 렌더링하는 셰이더입니다.
 */
class Text2DRenderShader : public Shader
{
public:
	/**
	 * @brief 2D 문자의 정점입니다.
	 */
	struct CharacterVertex
	{
		Vec3f Position;
		Vec2f UV;
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


	/**
	 * @brief 텍스트의 색상을 나타내는 상수 버퍼입니다.
	 */
	struct TextColorConstantBuffer
	{
		Vec4f TextColor;
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
	Text2DRenderShader(ID3D11Device* Device, const std::wstring& VertexShaderSourcePath, const std::wstring& PixelShaderSourcePath);


	/**
	 * @brief 2D 텍스트를 렌더링하는 셰이더의 가상 소멸자입니다.
	 */
	virtual ~Text2DRenderShader();


	/**
	 * @brief 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Text2DRenderShader);


	/**
	 * @brief 셰이더에서 사용하는 월드 행렬을 설정합니다.
	 *
	 * @param World 설정할 월드 행렬입니다.
	 */
	void SetWorldMatrix(const Matrix4x4F& World) { EveryFrameBufferResource_.World = World; }


	/**
	 * @brief 셰이더에서 사용하는 시야 행렬을 설정합니다.
	 *
	 * @param View 설정할 시야 행렬입니다.
	 */
	void SetViewMatrix(const Matrix4x4F& View) { EveryFrameBufferResource_.View = View; }


	/**
	 * @brief 셰이더에서 사용하는 투영 행렬을 설정합니다.
	 *
	 * @param Projection 설정할 투영 행렬입니다.
	 */
	void SetProjectionMatrix(const Matrix4x4F& Projection) { EveryFrameBufferResource_.Projection = Projection; }


	/**
	 * @brief 백 버퍼에 2D 텍스트를 그립니다.
	 *
	 * @param Context 렌더링을 수행할 컨텍스트입니다.
	 * @param FontResource 텍스트를 렌더링할 때 참조할 폰트 리소스입니다.
	 * @param Text 렌더링할 텍스트입니다.
	 * @param Center 텍스처의 중심 좌표입니다.
	 * @param Color 텍스트의 색상입니다.
	 */
	void RenderText2D(ID3D11DeviceContext* Context, Font& FontResource, const std::wstring& Text, const Vec3f& Center, const Vec4f& Color);


private:
	/**
	 * @brief 매 프레임 사용할 상수 버퍼를 생성합니다.
	 *
	 * @param Device 버퍼를 생성할 때 사용할 디바이스입니다.
	 *
	 * @return 버퍼 생성 결과를 반환합니다. 생성에 성공하면 S_OK, 그렇지 않으면 그 이외의 값을 반환합니다.
	 */
	HRESULT CreateEveryFrameConstantBuffer(ID3D11Device* Device);


	/**
	 * @brief 텍스트 색상을 나타내는 상수 버퍼를 생성합니다.
	 * 
	 * @param Device 버퍼를 생성할 때 사용할 디바이스입니다.
	 * 
	 * @return 버퍼 생성 결과를 반환합니다. 생성에 성공하면 S_OK, 그렇지 않으면 그 이외의 값을 반환합니다.
	 */
	HRESULT CreateTextColorConstantBuffer(ID3D11Device* Device);


	/**
	 * @brief 파이프라인에서 사용할 정점 버퍼를 생성합니다.
	 *
	 * @param Device 버퍼를 생성할 때 사용할 디바이스입니다.
	 * @param Vertices 정점 버퍼를 생성할 때 참조할 정점 목록입니다.
	 * @param VertexBuffer 생성된 정점 버퍼입니다.
	 *
	 * @return 버퍼 생성 결과를 반환합니다. 생성에 성공하면 S_OK, 그렇지 않으면 그 이외의 값을 반환합니다.
	 */
	HRESULT CreateVertexBuffer(ID3D11Device* Device, const std::vector<CharacterVertex>& Vertices, ID3D11Buffer** VertexBuffer);


	/**
	 * @brief 파이프라인에서 사용할 인덱스 버퍼를 생성합니다.
	 *
	 * @param Device 버퍼를 생성할 때 사용할 디바이스입니다.
	 * @param Indices 인덱스 버퍼를 생성할 때 참조할 인덱스 목록입니다.
	 * @param IndexBuffer 생성된 인덱스 버퍼입니다.
	 *
	 * @return 버퍼 생성 결과를 반환합니다. 생성에 성공하면 S_OK, 그렇지 않으면 그 이외의 값을 반환합니다.
	 */
	HRESULT CreateIndexBuffer(ID3D11Device* Device, const std::vector<uint32_t>& Indices, ID3D11Buffer** IndexBuffer);


	/**
	 * @brief 텍스처를 샘플링할 텍스처 샘플러를 생성합니다.
	 *
	 * @param Device 샘플러를 생성할 때 사용할 디바이스입니다.
	 *
	 * @return 샘플러 생성 결과를 반환합니다. 생성에 성공하면 S_OK, 그렇지 않으면 그 이외의 값을 반환합니다.
	 */
	HRESULT CreateTextureSampler(ID3D11Device* Device);


private:
	/**
	 * @brief 매 프레임 변경되는 셰이더 내의 리소스입니다.
	 */
	EveryFramConstantBuffer EveryFrameBufferResource_;


	/**
	 * @brief 매 프레임 변경되는 셰이더 내의 상수 버퍼입니다.
	 */
	ID3D11Buffer* EveryFramBuffer_ = nullptr;


	/**
	 * @brief 텍스트 색상입니다.
	 */
	TextColorConstantBuffer TextColorBufferResource_;


	/**
	 * @brief 텍스트 색상을 나타내는 상수 버퍼입니다.
	 */
	ID3D11Buffer* TextColorBuffer_ = nullptr;


	/**
	 * @brief 텍스처의 정점 목록입니다.
	 */
	std::vector<CharacterVertex> CharacterVertex_;


	/**
	 * @brief 텍스처의 정점 버퍼입니다.
	 */
	ID3D11Buffer* CharacterVertexBuffer_ = nullptr;


	/**
	 * @brief 텍스처의 인덱스 목록입니다.
	 */
	std::vector<uint32_t> CharacterIndex_;


	/**
	 * @brief 텍스처의 인덱스 버퍼입니다.
	 */
	ID3D11Buffer* CharacterIndexBuffer_ = nullptr;


	/**
	 * @brief 선형 텍스처 샘플러입니다.
	 */
	ID3D11SamplerState* LinearSampler_ = nullptr;
};