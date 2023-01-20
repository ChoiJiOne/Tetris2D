#pragma once

#include "Vector.hpp"
#include "Matrix.hpp"
#include "Shader.h"

#include <unordered_map>
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
	 * @brief 백 버퍼에 2D 삼각형을 그립니다.
	 * 
	 * @param Context 렌더링을 수행할 컨텍스트입니다.
	 * @param PositionFrom 삼각형 정점의 시작점입니다.
	 * @param ColorFrom 삼각형 정점의 시작점 색상입니다.
	 * @param PositionBy 삼각형 정점의 중간점입니다.
	 * @param ColorBy 삼각형 정점의 중간점 색상입니다.
	 * @param PositionTo 삼각형 정점의 끝점입니다.
	 * @param ColorTo 삼각형 정점의 끝점 색상입니다.
	 */
	void RenderTriangle (
		ID3D11DeviceContext* Context,
		const Vec3f& PositionFrom, const Vec4f& ColorFrom,
		const Vec3f& PositionBy, const Vec4f& ColorBy,
		const Vec3f& PositionTo, const Vec4f& ColorTo
	);


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
	 * @brief 파이프라인에서 사용할 정점 버퍼를 생성합니다.
	 * 
	 * @param Device 버퍼를 생성할 때 사용할 디바이스입니다.
	 * @param Vertices 정점 버퍼를 생성할 때 참조할 정점 목록입니다.
	 * @param VertexBuffer 생성된 정점 버퍼입니다.
	 * 
	 * @return 버퍼 생성 결과를 반환합니다. 생성에 성공하면 S_OK, 그렇지 않으면 그 이외의 값을 반환합니다.
	 */
	HRESULT CreateVertexBuffer(ID3D11Device* Device, const std::vector<PrimitiveVertex>& Vertices, ID3D11Buffer** VertexBuffer);


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