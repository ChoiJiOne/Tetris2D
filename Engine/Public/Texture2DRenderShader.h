#pragma once

#include "Vector.hpp"
#include "Matrix.hpp"
#include "Shader.h"

class Texture2D;


/**
 * @brief 2D 텍스처를 렌더링하는 셰이더입니다.
 */
class Texture2DRenderShader : public Shader
{
public:
	/**
	 * @brief 2D 텍스처의 정점입니다.
	 */
	struct QuadTextureVertex
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
	Texture2DRenderShader(ID3D11Device* Device, const std::wstring& VertexShaderSourcePath, const std::wstring& PixelShaderSourcePath);


	/**
	 * @brief 2D 텍스처를 렌더링하는 셰이더의 가상 소멸자입니다.
	 */
	virtual ~Texture2DRenderShader();


	/**
	 * @brief 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Texture2DRenderShader);


	/**
	 * @brief 셰이더에서 사용하는 월드 행렬을 설정합니다.
	 *
	 * @param World 설정할 월드 행렬입니다.
	 */
	void SetWorldMatrix(const Matrix4x4F& World) { EveryFrameBufferResource_.World = World; }


	/**
	 * @brief 셰이더에서 사용하는 투영 행렬을 설정합니다.
	 *
	 * @param Projection 설정할 투영 행렬입니다.
	 */
	void SetProjectionMatrix(const Matrix4x4F& Projection) { EveryFrameBufferResource_.Projection = Projection; }


	/**
	 * @brief 백 버퍼에 2D 텍스처를 그립니다.
	 * 
	 * @param Context 렌더링을 수행할 컨텍스트입니다.
	 * @param Texture 렌더링 대상이 되는 2D 텍스처입니다.
	 * @param Center 텍스처의 중심 좌표입니다.
	 * @param Width 텍스처의 가로 크기입니다.
	 * @param Height 텍스처의 세로 크기입니다.
	 */
	void RenderTexture2D(ID3D11DeviceContext* Context, Texture2D& Texture, const Vec3f& Center, float Width, float Height);
	

private:
	/**
	 * @brief 매 프레임 변경되는 셰이더 내의 리소스입니다.
	 */
	EveryFramConstantBuffer EveryFrameBufferResource_;


	/**
	 * @brief 매 프레임 변경되는 셰이더 내의 상수 버퍼입니다.
	 */
	ID3D11Buffer* EveryFrameBuffer_ = nullptr;


	/**
	 * @brief 텍스처의 정점 목록입니다.
	 */
	std::vector<QuadTextureVertex> QuadTextureVertex_;


	/**
	 * @brief 텍스처의 정점 버퍼입니다.
	 */
	ID3D11Buffer* QuadTextureVertexBuffer_ = nullptr;


	/**
	 * @brief 텍스처의 인덱스 목록입니다.
	 */
	std::vector<uint32_t> QuadTextureIndex_;


	/**
	 * @brief 텍스처의 인덱스 버퍼입니다.
	 */
	ID3D11Buffer* QuadTextureIndexBuffer_ = nullptr;


	/**
	 * @brief 선형 텍스처 샘플러입니다.
	 */
	ID3D11SamplerState* LinearSampler_ = nullptr;
};