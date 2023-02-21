#pragma once

#include "Vector.hpp"
#include "Matrix.hpp"
#include "Shader.h"

#include <unordered_map>
#include <vector>


/**
 * @brief 2D 기본 도형을 렌더링하는 셰이더입니다.
 */
class Primitive2DRenderShader : public Shader
{
public:
	/**
	 * @brief 내부 렌더링 타입입니다.
	 */
	enum class ERenderType
	{
		POINT    = 0,
		LINE     = 1,
		TRIANGLE = 2
	};


	/**
	 * @brief 기본 도형의 정점입니다.
	 */
	struct PrimitiveVertex
	{
		Vec3f Position;
		Vec4f Color;
	};


	/**
	 * @brief 매 프레임 변경되는 셰이더 내의 상수 버퍼입니다.
	 */
	struct EveryFramConstantBuffer
	{
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
	Primitive2DRenderShader(ID3D11Device* Device, const std::wstring& VertexShaderSourcePath, const std::wstring& PixelShaderSourcePath);
	

	/**
	 * @brief 기본 도형을 렌더링하는 셰이더의 가상 소멸자입니다.
	 */
	virtual ~Primitive2DRenderShader();


	/**
	 * @brief 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Primitive2DRenderShader);


	/**
	 * @brief 셰이더에서 사용하는 투영 행렬을 설정합니다.
	 * 
	 * @param Projection 설정할 투영 행렬입니다.
	 */
	void SetProjectionMatrix(const Matrix4x4F& Projection) { EveryFrameBufferResource_.Projection = Projection; }


	/**
	 * @brief 백 버퍼에 2D 점을 그립니다.
	 * 
	 * @param Context 렌더링을 수행할 컨텍스트입니다.
	 * @param Position 점의 위치입니다.
	 * @param Color 점의 색상입니다.
	 */
	void RenderPoint(
		ID3D11DeviceContext* Context,
		const Vec3f& Position, const Vec4f& Color
	);


	/**
	 * @brief 백 버퍼에 2D 선을 그립니다.
	 * 
	 * @param Context 렌더링을 수행할 컨텍스트입니다.
	 * @param PositionFrom 선의 시작점입니다.
	 * @param ColorFrom 선의 시작점 색상입니다.
	 * @param PositionTo 선의 끝점입니다.
	 * @param ColorTo 선의 끝점 색상입니다.
	 */
	void RenderLine(
		ID3D11DeviceContext* Context,
		const Vec3f& PositionFrom, const Vec4f& ColorFrom,
		const Vec3f& PositionTo, const Vec4f& ColorTo
	);


	/**
	 * @brief 백 버퍼에 2D 채움 삼각형을 그립니다.
	 * 
	 * @param Context 렌더링을 수행할 컨텍스트입니다.
	 * @param PositionFrom 삼각형 정점의 시작점입니다.
	 * @param ColorFrom 삼각형 정점의 시작점 색상입니다.
	 * @param PositionBy 삼각형 정점의 중간점입니다.
	 * @param ColorBy 삼각형 정점의 중간점 색상입니다.
	 * @param PositionTo 삼각형 정점의 끝점입니다.
	 * @param ColorTo 삼각형 정점의 끝점 색상입니다.
	 */
	void RenderFillTriangle(
		ID3D11DeviceContext* Context,
		const Vec3f& PositionFrom, const Vec4f& ColorFrom,
		const Vec3f& PositionBy, const Vec4f& ColorBy,
		const Vec3f& PositionTo, const Vec4f& ColorTo
	);


	/**
	 * @brief 백 버퍼에 2D 와이어 프레임 삼각형을 그립니다.
	 * 
	 * @param Context 렌더링을 수행할 컨텍스트입니다.
	 * @param PositionFrom 삼각형 정점의 시작점입니다.
	 * @param ColorFrom 삼각형 정점의 시작점 색상입니다.
	 * @param PositionBy 삼각형 정점의 중간점입니다.
	 * @param ColorBy 삼각형 정점의 중간점 색상입니다.
	 * @param PositionTo 삼각형 정점의 끝점입니다.
	 * @param ColorTo 삼각형 정점의 끝점 색상입니다.
	 */
	void RenderWireframeTriangle(
		ID3D11DeviceContext* Context,
		const Vec3f& PositionFrom, const Vec4f& ColorFrom,
		const Vec3f& PositionBy, const Vec4f& ColorBy,
		const Vec3f& PositionTo, const Vec4f& ColorTo
	);


	/**
	 * @brief 백 버퍼에 2D 채움 사각형을 그립니다.
	 * 
	 * @param Context 렌더링을 수행할 컨텍스트입니다.
	 * @param PositionFrom 삼각형 정점의 시작점입니다.
	 * @param ColorFrom 삼각형 정점의 시작점 색상입니다.
	 * @param PositionBy0 삼각형 정점의 중간점입니다.
	 * @param ColorBy0 삼각형 정점의 중간점 색상입니다.	 
	 * @param PositionBy1 삼각형 정점의 중간점입니다.
	 * @param ColorBy1 삼각형 정점의 중간점 색상입니다.
	 * @param PositionTo 삼각형 정점의 끝점입니다.
	 * @param ColorTo 삼각형 정점의 끝점 색상입니다.
	 */
	void RenderFillQuad(
		ID3D11DeviceContext* Context,
		const Vec3f& PositionFrom, const Vec4f& ColorFrom,
		const Vec3f& PositionBy0, const Vec4f& ColorBy0,
		const Vec3f& PositionBy1, const Vec4f& ColorBy1,
		const Vec3f& PositionTo, const Vec4f& ColorTo
	);


	/**
	 * @brief 백 버퍼에 2D 와이어 프레임 사각형을 그립니다.
	 * 
	 * @param Context 렌더링을 수행할 컨텍스트입니다.
	 * @param PositionFrom 삼각형 정점의 시작점입니다.
	 * @param ColorFrom 삼각형 정점의 시작점 색상입니다.
	 * @param PositionBy0 삼각형 정점의 중간점입니다.
	 * @param ColorBy0 삼각형 정점의 중간점 색상입니다.
	 * @param PositionBy1 삼각형 정점의 중간점입니다.
	 * @param ColorBy1 삼각형 정점의 중간점 색상입니다.
	 * @param PositionTo 삼각형 정점의 끝점입니다.
	 * @param ColorTo 삼각형 정점의 끝점 색상입니다.
	 */
	void RenderWireframeQuad(
		ID3D11DeviceContext* Context,
		const Vec3f& PositionFrom, const Vec4f& ColorFrom,
		const Vec3f& PositionBy0, const Vec4f& ColorBy0,
		const Vec3f& PositionBy1, const Vec4f& ColorBy1,
		const Vec3f& PositionTo, const Vec4f& ColorTo
	);


private:
	/**
	 * @brief 기본 도형을 화면에 그립니다.
	 * 
	 * @param Context 렌더링을 수행할 컨텍스트입니다.
	 * @param PrimitiveSignature 기본 도형의 정점 시그니처입니다.
	 * @param RenderType 렌더링 타입입니다.
	 */
	void RenderPrimitive(ID3D11DeviceContext* Context, const std::string& PrimitiveSignature, const ERenderType& RenderType);


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
	 * @brief 기본 도형의 정점 목록입니다.
	 */
	std::unordered_map<std::string, std::vector<PrimitiveVertex>> PrimitiveVertex_;


	/**
	 * @brief 기본 도형의 정점 버퍼입니다.
	 */
	std::unordered_map<std::string, ID3D11Buffer*> PrimitiveVertexBuffer_;


	/**
	 * @brief 기본 도형의 인덱스 목록입니다.
	 */
	std::unordered_map<std::string, std::vector<uint32_t>> PrimitiveIndex_;


	/**
	 * @brief 기본 도형의 인덱스 버퍼입니다.
	 */
	std::unordered_map<std::string, ID3D11Buffer*> PrimitiveIndexBuffer_;
};