#pragma once

#include "Macro.h"

#include <d3d11.h>


/**
 * @brief �׷��� ���� ó���� �����մϴ�.
 * 
 * @note �� Ŭ������ �̱������� ����� �߰��ϸ� �ٷ� ����� �� �ֽ��ϴ�.
 */
class GraphicsManager
{
public:
	/**
	 * @brief ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(GraphicsManager);


	/**
	 * @brief GraphicsManager�� �ν��Ͻ��� ����ϴ�.
	 * 
	 * @return GraphicsManager�� �ν��Ͻ��� ��ȯ�մϴ�.
	 */
	static GraphicsManager& Get()
	{
		static GraphicsManager Instance;
		return Instance;
	}


	/**
	 * @brief GraphicsManager�� ���������� �ʱ�ȭ�մϴ�.
	 */
	void Init();


	/**
	 * @brief GraphicsManager�� ���� ��Ҹ� ���������� �����մϴ�.
	 */
	void Cleanup();


	/**
	 * @brief ������������ �� ��Ʈ�� �����մϴ�.
	 * 
	 * @param TopLeftX �� ��Ʈ ���� ����� X��ǥ�Դϴ�.
	 * @param TopLeftY �� ��Ʈ ���� ����� Y��ǥ�Դϴ�.
	 * @param Width �� ��Ʈ�� ���� ũ���Դϴ�.
	 * @param Height �� ��Ʈ�� ���� ũ���Դϴ�.
	 * @param MinDepth �� ��Ʈ�� �ּ� �����Դϴ�. �⺻ ���� 0.0 �Դϴ�.
	 * @param MaxDepth �� ��Ʈ�� �ִ� �����Դϴ�. �⺻ ���� 1.0 �Դϴ�.
	 */
	void SetViewport(float TopLeftX, float TopLeftY, float Width, float Height, float MinDepth = 0.0f, float MaxDepth = 1.0f);


	/**
	 * @brief �� ���۸� �ʱ�ȭ�մϴ�.
	 * 
	 * @param Red �� ������ �ʱ�ȭ�� ���� �����Դϴ�.
	 * @param Green �� ������ �ʱ�ȭ�� �ʷ� �����Դϴ�.
	 * @param Blue �� ������ �ʱ�ȭ�� �Ķ� �����Դϴ�.
	 * @param Alpha �� ������ �ʱ�ȭ�� ���� �����Դϴ�.
	 */
	void Clear(float Red, float Green, float Blue, float Alpha);


	/**
	 * @brief �� ���ۿ� ����Ʈ ���۸� ��ȯ�մϴ�.
	 * 
	 * @param bIsVSync ���� ����ȭ ���θ� Ȯ���մϴ�. �⺻������ ���� ����ȭ ó���մϴ�.
	 * 
	 * @see https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-idxgiswapchain-present
	 */
	void Present(bool bIsVSync = true);


private:
	/**
	 * @brief �׷��� ���� ó���� �����ϴ� Ŭ������ �������Դϴ�.
	 * 
	 * @note �����ڴ� �ƹ��� ���۵� �������� �ʽ��ϴ�.
	 */
	GraphicsManager() = default;


	/**
	 * @brief �׷��� ���� ���ҽ��� �����ϴ� ���� �Ҹ����Դϴ�.
	 */
	virtual ~GraphicsManager();


	/**
	 * @brief �׷��� ���� ���ҽ��� �ʱ�ȭ�մϴ�.
	 */
	void InitAllProperties();


	/**
	 * @brief �׷��� ���� ���ҽ��� �����մϴ�.
	 */
	void CleanupAllProperties();


	/**
	 * @brief ����̽� �� ���ؽ�Ʈ�� �����մϴ�.
	 * 
	 * @param WindowHandle ����� �Ǵ� ������ �ڵ��Դϴ�.
	 * 
	 * @return ����̽� �� ���ؽ�Ʈ�� ���� ����� ��ȯ�մϴ�. �����ߴٸ� S_OK, �׷��� �ʴٸ� �� �̿��� ���� ��ȯ�մϴ�.
	 */
	HRESULT CreateDeviceAndContext(HWND WindowHandle);


	/**
	 * @brief ���� ü���� �����մϴ�.
	 * 
	 * @param WindowHandle ����� �Ǵ� ������ �ڵ��Դϴ�.
	 * 
	 * @return ���� ü�� ���� ����� ��ȯ�մϴ�. �����ߴٸ� S_OK, �׷��� �ʴٸ� �� �̿��� ���� ��ȯ�մϴ�.
	 */
	HRESULT CreateSwapChain(HWND WindowHandle);


	/**
	 * @brief ���� Ÿ�� �並 �����մϴ�.
	 * 
	 * @return ���� Ÿ�� �� ���� ����� ��ȯ�մϴ�. �����ߴٸ� S_OK, �׷��� �ʴٸ� �� �̿��� ���� ��ȯ�մϴ�.
	 */
	HRESULT CreateRenderTargetView();


private:
	/**
	 * @brief ����̹� Ÿ���Դϴ�.
	 *
	 * @see https://learn.microsoft.com/en-us/windows/win32/api/d3dcommon/ne-d3dcommon-d3d_driver_type
	 */
	D3D_DRIVER_TYPE	DriverType_ = D3D_DRIVER_TYPE_NULL;


	/**
	 * @brief ����̽��� ������� �ϴ� ����Դϴ�.
	 *
	 * @see https://learn.microsoft.com/en-us/windows/win32/api/d3dcommon/ne-d3dcommon-d3d_feature_level
	 */
	D3D_FEATURE_LEVEL FeatureLevel_ = D3D_FEATURE_LEVEL_11_0;


	/**
	 * @brief ���ҽ��� ����� ���÷��� ������� ����� �����ϴ� �� ����մϴ�.
	 *
	 * @see https://learn.microsoft.com/ko-kr/windows/win32/direct3d11/overviews-direct3d-11-devices-intro
	 */
	ID3D11Device* Device_ = nullptr;


	/**
	 * @brief ����̽��� ������ ���ҽ��� ����Ͽ� ���������� ���¸� �����ϰ� ������ ������ �����ϴ� �� ����մϴ�.
	 *
	 * @see https://learn.microsoft.com/ko-kr/windows/win32/direct3d11/overviews-direct3d-11-devices-intro
	 */
	ID3D11DeviceContext* Context_ = nullptr;


	/**
	 * @brief �������� �����͸� ��¿� ǥ���ϱ� ���� �����մϴ�.
	 *
	 * @see https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgiswapchain
	 */
	IDXGISwapChain* SwapChain_ = nullptr;


	/**
	 * @brief ������ �� ������ �� �� �ִ� ���ҽ��Դϴ�.
	 *
	 * @see https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11rendertargetview
	 */
	ID3D11RenderTargetView* RenderTargetView_ = nullptr;
};