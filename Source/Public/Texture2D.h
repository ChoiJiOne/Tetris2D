#pragma once

#include "Macro.h"

#include <vector>

#include <d3d11.h>


/**
 * @brief 2D �ؽ�ó ���ҽ��Դϴ�.
 */
class Texture2D
{
public:
	/**
	 * @brief 2D �ؽ�ó ���ҽ� �������Դϴ�.
	 * 
	 * @param Device �ؽ�ó ���ҽ��� ������ �� ����� ����̽��Դϴ�.
	 * @param ResourcePath �ؽ�ó ���� ����Դϴ�.
	 * 
	 * @throws 
	 * �ؽ�ó ���� �ε��� �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 * �ؽ�ó ���ҽ� ������ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	Texture2D(ID3D11Device* Device, const std::string& ResourcePath);


	/**
	 * @brief 2D �ؽ�ó ���ҽ��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Texture2D();


	/**
	 * @brief ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Texture2D);


	/**
	 * @brief 2D �ؽ�ó �����͸� ����ϴ�.
	 * 
	 * @return 2D �ؽ�ó �����͸� ��ȯ�մϴ�.
	 */
	ID3D11Texture2D* GetTexture() { return Texture_; }


	/**
	 * @brief ���̴��� ���ε��� 2D �ؽ�ó ���ҽ� �並 ����ϴ�.
	 * 
	 * @return ���̴��� ���ε��� 2D �ؽ�ó ���ҽ� �並 ��ȯ�մϴ�.
	 */
	ID3D11ShaderResourceView* GetTextureView() { return TextureView_; }


private:
	/**
	 * @brief �ؽ�ó ������ �ε��մϴ�.
	 * 
	 * @param ResourcePath �ؽ�ó ������ ����Դϴ�.
	 * @param Buffer[out] �ؽ�ó �����Դϴ�.
	 * @param Format[out] �ؽ�ó �ȼ� �����Դϴ�.
	 * @param Width[out] �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param Height[out] �ؽ�ó�� ���� ũ���Դϴ�.
	 * 
	 * @return �ؽ�ó ���� �ε��� �����ϸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool LoadTextureFromFile(
		const std::string& ResourcePath, 
		std::vector<uint8_t>& Buffer, 
		int32_t& Format,
		int32_t& Width,
		int32_t& Height
	);


	/**
	 * @brief �ؽ�ó ���ҽ��� �����մϴ�.
	 * 
	 * @param Device �ؽ�ó ���ҽ��� ������ �� ����� ����̽��Դϴ�.
	 * @param Buffer �ؽ�ó �����Դϴ�.
	 * @param Format �ؽ�ó �ȼ� �����Դϴ�.
	 * @param Width �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param Height �ؽ�ó�� ���� ũ���Դϴ�.
	 * 
	 * @return �ؽ�ó ���ҽ� ���� ����� ��ȯ�մϴ�. ������ �����ϸ� S_OK, �׷��� ������ �� �̿��� ���� ��ȯ�մϴ�.
	 */
	HRESULT CreateTextureResource(ID3D11Device* Device, std::vector<uint8_t>& Buffer, int32_t Format, int32_t Width, int32_t Height);


private:
	/**
	 * @brief 2D �ؽ�ó �������Դϴ�.
	 * 
	 * @see https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11texture2d
	 */
	ID3D11Texture2D* Texture_ = nullptr;


	/**
	 * @brief ���̴��� ���ε��� 2D �ؽ�ó ���ҽ� ���Դϴ�.
	 */
	ID3D11ShaderResourceView* TextureView_ = nullptr;
};