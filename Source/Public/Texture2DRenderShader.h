#pragma once

#include "Vector.hpp"
#include "Matrix.hpp"
#include "Shader.h"

class Texture2D;


/**
 * @brief 2D �ؽ�ó�� �������ϴ� ���̴��Դϴ�.
 */
class Texture2DRenderShader : public Shader
{
public:
	/**
	 * @brief 2D �ؽ�ó�� �����Դϴ�.
	 */
	struct QuadTextureVertex
	{
		Vec3f Position;
		Vec2f UV;
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
	Texture2DRenderShader(ID3D11Device* Device, const std::wstring& VertexShaderSourcePath, const std::wstring& PixelShaderSourcePath);


	/**
	 * @brief 2D �ؽ�ó�� �������ϴ� ���̴��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Texture2DRenderShader();


	/**
	 * @brief ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Texture2DRenderShader);


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
	 * @brief �� ���ۿ� 2D �ؽ�ó�� �׸��ϴ�.
	 * 
	 * @param Context �������� ������ ���ؽ�Ʈ�Դϴ�.
	 * @param Texture ������ ����� �Ǵ� 2D �ؽ�ó�Դϴ�.
	 * @param Center �ؽ�ó�� �߽� ��ǥ�Դϴ�.
	 * @param Width �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param Height �ؽ�ó�� ���� ũ���Դϴ�.
	 */
	void RenderTexture2D(ID3D11DeviceContext* Context, Texture2D& Texture, const Vec3f& Center, float Width, float Height);


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
	HRESULT CreateVertexBuffer(ID3D11Device* Device, const std::vector<QuadTextureVertex>& Vertices, ID3D11Buffer** VertexBuffer);


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
	 * @brief �ؽ�ó�� ���ø��� �ؽ�ó ���÷��� �����մϴ�.
	 * 
	 * @param Device ���÷��� ������ �� ����� ����̽��Դϴ�.
	 * 
	 * @return ���÷� ���� ����� ��ȯ�մϴ�. ������ �����ϸ� S_OK, �׷��� ������ �� �̿��� ���� ��ȯ�մϴ�.
	 */
	HRESULT CreateTextureSampler(ID3D11Device* Device);


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
	 * @brief �ؽ�ó�� ���� ����Դϴ�.
	 */
	std::vector<QuadTextureVertex> QuadTextureVertex_;


	/**
	 * @brief �ؽ�ó�� ���� �����Դϴ�.
	 */
	ID3D11Buffer* QuadTextureVertexBuffer_ = nullptr;


	/**
	 * @brief �ؽ�ó�� �ε��� ����Դϴ�.
	 */
	std::vector<uint32_t> QuadTextureIndex_;


	/**
	 * @brief �ؽ�ó�� �ε��� �����Դϴ�.
	 */
	ID3D11Buffer* QuadTextureIndexBuffer_ = nullptr;


	/**
	 * @brief ���� �ؽ�ó ���÷��Դϴ�.
	 */
	ID3D11SamplerState* LinearSampler_ = nullptr;
};