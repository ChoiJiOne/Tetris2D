#pragma once

#include "Vector.hpp"
#include "Matrix.hpp"
#include "Shader.h"

#include <unordered_map>
#include <vector>


/**
 * @brief 2D �⺻ ������ �������ϴ� ���̴��Դϴ�.
 */
class Primitive2DRenderShader : public Shader
{
public:
	/**
	 * @brief ���� ������ Ÿ���Դϴ�.
	 */
	enum class ERenderType
	{
		POINT    = 0,
		LINE     = 1,
		TRIANGLE = 2
	};


	/**
	 * @brief �⺻ ������ �����Դϴ�.
	 */
	struct PrimitiveVertex
	{
		Vec3f Position;
		Vec4f Color;
	};


	/**
	 * @brief �� ������ ����Ǵ� ���̴� ���� ��� �����Դϴ�.
	 */
	struct EveryFramConstantBuffer
	{
		Matrix4x4F World;
		Matrix4x4F View;
		Matrix4x4F Projection;
	};


public:
	/**
	 * @brief ���̴��� �������ϰ� ���� ���̴��� �ȼ� ���̴��� �����մϴ�.
	 *
	 * @param Device ���̴� ���ҽ��� ������ �� ����� ����̽��Դϴ�.
	 * @param VertexShaderSourcePath ���� ���̴� �ҽ� ������ ����Դϴ�.
	 * @param PixelShaderSourcePath �ȼ� ���̴� �ҽ� ������ ����Դϴ�.
	 *
	 * @throws
	 * ���̴� �����Ͽ� �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 * ���̴� ���ҽ� ������ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	Primitive2DRenderShader(ID3D11Device* Device, const std::wstring& VertexShaderSourcePath, const std::wstring& PixelShaderSourcePath);
	

	/**
	 * @brief �⺻ ������ �������ϴ� ���̴��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Primitive2DRenderShader();


	/**
	 * @brief ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Primitive2DRenderShader);


	/**
	 * @brief ���̴����� ����ϴ� ���� ����� �����մϴ�.
	 * 
	 * @param World ������ ���� ����Դϴ�.
	 */
	void SetWorldMatrix(const Matrix4x4F& World) { EveryFrameBufferResource_.World = World; }


	/**
	 * @brief ���̴����� ����ϴ� �þ� ����� �����մϴ�.
	 * 
	 * @param View ������ �þ� ����Դϴ�.
	 */
	void SetViewMatrix(const Matrix4x4F& View) { EveryFrameBufferResource_.View = View; }


	/**
	 * @brief ���̴����� ����ϴ� ���� ����� �����մϴ�.
	 * 
	 * @param Projection ������ ���� ����Դϴ�.
	 */
	void SetProjectionMatrix(const Matrix4x4F& Projection) { EveryFrameBufferResource_.Projection = Projection; }


	/**
	 * @brief �� ���ۿ� 2D ���� �׸��ϴ�.
	 * 
	 * @param Context �������� ������ ���ؽ�Ʈ�Դϴ�.
	 * @param Position ���� ��ġ�Դϴ�.
	 * @param Color ���� �����Դϴ�.
	 */
	void RenderPoint(
		ID3D11DeviceContext* Context,
		const Vec3f& Position, const Vec4f& Color
	);


	/**
	 * @brief �� ���ۿ� 2D ���� �׸��ϴ�.
	 * 
	 * @param Context �������� ������ ���ؽ�Ʈ�Դϴ�.
	 * @param PositionFrom ���� �������Դϴ�.
	 * @param ColorFrom ���� ������ �����Դϴ�.
	 * @param PositionTo ���� �����Դϴ�.
	 * @param ColorTo ���� ���� �����Դϴ�.
	 */
	void RenderLine(
		ID3D11DeviceContext* Context,
		const Vec3f& PositionFrom, const Vec4f& ColorFrom,
		const Vec3f& PositionTo, const Vec4f& ColorTo
	);


	/**
	 * @brief �� ���ۿ� 2D ä�� �ﰢ���� �׸��ϴ�.
	 * 
	 * @param Context �������� ������ ���ؽ�Ʈ�Դϴ�.
	 * @param PositionFrom �ﰢ�� ������ �������Դϴ�.
	 * @param ColorFrom �ﰢ�� ������ ������ �����Դϴ�.
	 * @param PositionBy �ﰢ�� ������ �߰����Դϴ�.
	 * @param ColorBy �ﰢ�� ������ �߰��� �����Դϴ�.
	 * @param PositionTo �ﰢ�� ������ �����Դϴ�.
	 * @param ColorTo �ﰢ�� ������ ���� �����Դϴ�.
	 */
	void RenderFillTriangle (
		ID3D11DeviceContext* Context,
		const Vec3f& PositionFrom, const Vec4f& ColorFrom,
		const Vec3f& PositionBy, const Vec4f& ColorBy,
		const Vec3f& PositionTo, const Vec4f& ColorTo
	);


	/**
	 * @brief �� ���ۿ� 2D ���̾� ������ �ﰢ���� �׸��ϴ�.
	 * 
	 * @param Context �������� ������ ���ؽ�Ʈ�Դϴ�.
	 * @param PositionFrom �ﰢ�� ������ �������Դϴ�.
	 * @param ColorFrom �ﰢ�� ������ ������ �����Դϴ�.
	 * @param PositionBy �ﰢ�� ������ �߰����Դϴ�.
	 * @param ColorBy �ﰢ�� ������ �߰��� �����Դϴ�.
	 * @param PositionTo �ﰢ�� ������ �����Դϴ�.
	 * @param ColorTo �ﰢ�� ������ ���� �����Դϴ�.
	 */
	void RenderWireframeTriangle(
		ID3D11DeviceContext* Context,
		const Vec3f& PositionFrom, const Vec4f& ColorFrom,
		const Vec3f& PositionBy, const Vec4f& ColorBy,
		const Vec3f& PositionTo, const Vec4f& ColorTo
	);


	/**
	 * @brief �� ���ۿ� 2D ä�� �簢���� �׸��ϴ�.
	 * 
	 * @param Context �������� ������ ���ؽ�Ʈ�Դϴ�.
	 * @param PositionFrom �ﰢ�� ������ �������Դϴ�.
	 * @param ColorFrom �ﰢ�� ������ ������ �����Դϴ�.
	 * @param PositionBy0 �ﰢ�� ������ �߰����Դϴ�.
	 * @param ColorBy0 �ﰢ�� ������ �߰��� �����Դϴ�.	 
	 * @param PositionBy1 �ﰢ�� ������ �߰����Դϴ�.
	 * @param ColorBy1 �ﰢ�� ������ �߰��� �����Դϴ�.
	 * @param PositionTo �ﰢ�� ������ �����Դϴ�.
	 * @param ColorTo �ﰢ�� ������ ���� �����Դϴ�.
	 */
	void RenderFillQuad(
		ID3D11DeviceContext* Context,
		const Vec3f& PositionFrom, const Vec4f& ColorFrom,
		const Vec3f& PositionBy0, const Vec4f& ColorBy0,
		const Vec3f& PositionBy1, const Vec4f& ColorBy1,
		const Vec3f& PositionTo, const Vec4f& ColorTo
	);


	/**
	 * @brief �� ���ۿ� 2D ���̾� ������ �簢���� �׸��ϴ�.
	 * 
	 * @param Context �������� ������ ���ؽ�Ʈ�Դϴ�.
	 * @param PositionFrom �ﰢ�� ������ �������Դϴ�.
	 * @param ColorFrom �ﰢ�� ������ ������ �����Դϴ�.
	 * @param PositionBy0 �ﰢ�� ������ �߰����Դϴ�.
	 * @param ColorBy0 �ﰢ�� ������ �߰��� �����Դϴ�.
	 * @param PositionBy1 �ﰢ�� ������ �߰����Դϴ�.
	 * @param ColorBy1 �ﰢ�� ������ �߰��� �����Դϴ�.
	 * @param PositionTo �ﰢ�� ������ �����Դϴ�.
	 * @param ColorTo �ﰢ�� ������ ���� �����Դϴ�.
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
	 * @brief �� ������ ����� ��� ���۸� �����մϴ�.
	 * 
	 * @param Device ���۸� ������ �� ����� ����̽��Դϴ�.
	 * 
	 * @return ���� ���� ����� ��ȯ�մϴ�. ������ �����ϸ� S_OK, �׷��� ������ �� �̿��� ���� ��ȯ�մϴ�.
	 */
	HRESULT CreateEveryFrameConstantBuffer(ID3D11Device* Device);


	/**
	 * @brief ���������ο��� ����� ���� ���۸� �����մϴ�.
	 * 
	 * @param Device ���۸� ������ �� ����� ����̽��Դϴ�.
	 * @param Vertices ���� ���۸� ������ �� ������ ���� ����Դϴ�.
	 * @param VertexBuffer ������ ���� �����Դϴ�.
	 * 
	 * @return ���� ���� ����� ��ȯ�մϴ�. ������ �����ϸ� S_OK, �׷��� ������ �� �̿��� ���� ��ȯ�մϴ�.
	 */
	HRESULT CreateVertexBuffer(ID3D11Device* Device, const std::vector<PrimitiveVertex>& Vertices, ID3D11Buffer** VertexBuffer);


	/**
	 * @brief ���������ο��� ����� �ε��� ���۸� �����մϴ�.
	 * 
	 * @param Device ���۸� ������ �� ����� ����̽��Դϴ�.
	 * @param Indices �ε��� ���۸� ������ �� ������ �ε��� ����Դϴ�.
	 * @param IndexBuffer ������ �ε��� �����Դϴ�.
	 * 
	 * @return ���� ���� ����� ��ȯ�մϴ�. ������ �����ϸ� S_OK, �׷��� ������ �� �̿��� ���� ��ȯ�մϴ�.
	 */
	HRESULT CreateIndexBuffer(ID3D11Device* Device, const std::vector<uint32_t>& Indices, ID3D11Buffer** IndexBuffer);


	/**
	 * @brief �⺻ ������ ȭ�鿡 �׸��ϴ�.
	 * 
	 * @param Context �������� ������ ���ؽ�Ʈ�Դϴ�.
	 * @param PrimitiveSignature �⺻ ������ ���� �ñ״�ó�Դϴ�.
	 * @param RenderType ������ Ÿ���Դϴ�.
	 */
	void RenderPrimitive(ID3D11DeviceContext* Context, const std::string& PrimitiveSignature, const ERenderType& RenderType);


private:
	/**
	 * @brief �� ������ ����Ǵ� ���̴� ���� ���ҽ��Դϴ�.
	 */
	EveryFramConstantBuffer EveryFrameBufferResource_;


	/**
	 * @brief �� ������ ����Ǵ� ���̴� ���� ��� �����Դϴ�.
	 */
	ID3D11Buffer* EveryFramBuffer_ = nullptr;


	/**
	 * @brief �⺻ ������ ���� ����Դϴ�.
	 */
	std::unordered_map<std::string, std::vector<PrimitiveVertex>> PrimitiveVertex_;


	/**
	 * @brief �⺻ ������ ���� �����Դϴ�.
	 */
	std::unordered_map<std::string, ID3D11Buffer*> PrimitiveVertexBuffer_;


	/**
	 * @brief �⺻ ������ �ε��� ����Դϴ�.
	 */
	std::unordered_map<std::string, std::vector<uint32_t>> PrimitiveIndex_;


	/**
	 * @brief �⺻ ������ �ε��� �����Դϴ�.
	 */
	std::unordered_map<std::string, ID3D11Buffer*> PrimitiveIndexBuffer_;
};